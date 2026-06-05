// Decompiled methods for class: CGoblin
// Source: gameserver.cc
// Total methods: 43

#####################################
void __cdecl CGoblin::~CGoblin(CGoblin *const this)
{
  CGoblin::~CGoblin(this);
  operator delete(this);
}


#####################################
void __cdecl CGoblin::OnLoadFromDB(CGoblin *const this, const PlayerDBData *const dbData)
{
  CfgData *v2; // rax
  int32_t TalentLevel; // r12d
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int SuitId; // [rsp+14h] [rbp-1Ch]
  const VipEQuipPosSuit *pCfg; // [rsp+18h] [rbp-18h]

  std::map<int,GoblinInfo>::operator=(&this->m_GoblinInfoMap, &dbData->m_CGoblinData.m_GoblinInfoMap);
  std::map<int,int>::operator=(&this->m_ShouHuRefiningLeveMap, &dbData->m_CGoblinData.m_ShouHuRefiningLeveMap);
  std::map<int,int>::operator=(&this->m_WingEquipPolishMap, &dbData->m_CGoblinData.m_WingEquipPolishMap);
  std::map<int,int>::operator=(&this->m_MoFuZhuNengMap, &dbData->m_CGoblinData.m_MoFuZhuNengMap);
  std::map<int,int>::operator=(&this->m_WingEquipRefiningMap, &dbData->m_CGoblinData.m_WingEquipRefiningMap);
  std::map<int,int>::operator=(&this->m_VipEquipPosLevelMap, &dbData->m_CGoblinData.m_VipEquipPosLevelMap);
  SuitId = CGoblin::GetVipEquipPosLevelSuitId(this);
  if ( SuitId > 0 )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetVipEQuipPosSuit(v2, SuitId);
    if ( pCfg )
    {
      if ( pCfg->nTalentId > 0 && pCfg->TalentLevel > 0 )
      {
        TalentLevel = pCfg->TalentLevel;
        nTalentId = pCfg->nTalentId;
        CharSkill = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(CharSkill, nTalentId, TalentLevel);
      }
    }
  }
}


#####################################
void __cdecl CGoblin::OnSaveToDB(CGoblin *const this, PlayerDBData *const dbData)
{
  std::map<int,GoblinInfo>::operator=(&dbData->m_CGoblinData.m_GoblinInfoMap, &this->m_GoblinInfoMap);
  std::map<int,int>::operator=(&dbData->m_CGoblinData.m_ShouHuRefiningLeveMap, &this->m_ShouHuRefiningLeveMap);
  std::map<int,int>::operator=(&dbData->m_CGoblinData.m_WingEquipPolishMap, &this->m_WingEquipPolishMap);
  std::map<int,int>::operator=(&dbData->m_CGoblinData.m_MoFuZhuNengMap, &this->m_MoFuZhuNengMap);
  std::map<int,int>::operator=(&dbData->m_CGoblinData.m_WingEquipRefiningMap, &this->m_WingEquipRefiningMap);
  std::map<int,int>::operator=(&dbData->m_CGoblinData.m_VipEquipPosLevelMap, &this->m_VipEquipPosLevelMap);
}


#####################################
void __cdecl CGoblin::OnCleanUp(CGoblin *const this)
{
  std::map<int,GoblinInfo>::clear(&this->m_GoblinInfoMap);
  std::map<int,int>::clear(&this->m_ShouHuRefiningLeveMap);
  std::map<int,int>::clear(&this->m_WingEquipPolishMap);
  std::map<int,int>::clear(&this->m_MoFuZhuNengMap);
  std::map<int,int>::clear(&this->m_WingEquipRefiningMap);
  std::map<int,int>::clear(&this->m_VipEquipPosLevelMap);
}


#####################################
void __cdecl CGoblin::GetInterestsProtocol(CGoblin *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v3; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v4; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v5; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v6; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v7; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 550;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 546;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 547;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 548;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 549;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 542;
  std::list<unsigned short>::push_back(procList, &v7);
}


#####################################
int32_t __cdecl CGoblin::DispatchNetDatas(CGoblin *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x21Eu:
      result = CGoblin::OnVipEquipPosLevellUp(this, inPacket);
      break;
    case 0x222u:
      result = CGoblin::OnShouHuRefiningLevelUp(this, inPacket);
      break;
    case 0x223u:
      result = CGoblin::OnWingEquipPolishLevelUp(this, inPacket);
      break;
    case 0x224u:
      result = CGoblin::OnMoFuZhuNeng(this, inPacket);
      break;
    case 0x225u:
      result = CGoblin::OnWingEquipRefiningLevelUp(this, inPacket);
      break;
    case 0x226u:
      result = CGoblin::OnGoblinLevelUp(this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CGoblin::GetAddAttrRate(CGoblin *const this, int32_t nType)
{
  int32_t GoblinLevel; // r12d
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t nTypea; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+20h] [rbp-20h] BYREF
  GoblinCfg *pCfg; // [rsp+28h] [rbp-18h]

  thisa = this;
  nTypea = nType;
  if ( !IsGoblinType(nType) )
    return 0;
  it._M_node = std::map<int,GoblinInfo>::find(&thisa->m_GoblinInfoMap, &nTypea)._M_node;
  __x._M_node = std::map<int,GoblinInfo>::end(&thisa->m_GoblinInfoMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&it, &__x)
    && (GoblinLevel = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it)->second.GoblinLevel,
        v4 = nTypea,
        v5 = Answer::Singleton<CfgData>::instance(),
        (pCfg = CfgData::GetGoblinCfg(v5, v4, GoblinLevel)) != 0) )
  {
    return pCfg->UpAttr;
  }
  else
  {
    return 0;
  }
}


#####################################
bool __cdecl CGoblin::AddGoblinRes(CGoblin *const this, int8_t nType, int32_t Values)
{
  GoblinInfo *v4; // rax
  int __k; // [rsp+1Ch] [rbp-4h] BYREF

  if ( !this->m_pPlayer )
    return 0;
  if ( !IsGoblinType(nType) )
    return 0;
  if ( Values <= 0 )
    return 0;
  __k = nType;
  v4 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &__k);
  v4->GoblinRes += Values;
  CGoblin::SendGoblinInfo(this, nType);
  return 1;
}


#####################################
void __cdecl CGoblin::SendAllGoblinInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,GoblinInfo> *v3; // rax
  std::pair<const int,GoblinInfo> *v4; // rax
  std::pair<const int,GoblinInfo> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D1Fu);
    if ( packet )
    {
      nSize = std::map<int,GoblinInfo>::size(&this->m_GoblinInfoMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,GoblinInfo>::begin(&this->m_GoblinInfoMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,GoblinInfo>::end(&this->m_GoblinInfoMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second.GoblinLevel);
        v5 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->second.GoblinRes);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CGoblin::OnGoblinLevelUp(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t IsLeftType; // edx
  int32_t v4; // r12d
  int32_t v5; // ebx
  CfgData *v6; // rax
  GoblinInfo *v7; // rax
  GoblinInfo *v8; // rax
  GoblinInfo *v9; // rax
  int32_t v10; // edx
  int64_t v11; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v15; // rax
  int8_t v16; // bl
  GameService *v17; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v20; // rax
  int32_t nType; // [rsp+1Ch] [rbp-54h] BYREF
  std::string val; // [rsp+20h] [rbp-50h] BYREF
  int32_t OldSuitId; // [rsp+34h] [rbp-3Ch]
  GoblinCfg *pCfg; // [rsp+38h] [rbp-38h]
  int32_t NewSuitId; // [rsp+40h] [rbp-30h]
  int32_t GongGaoId; // [rsp+44h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( !IsGoblinType(nType) )
    return 2;
  IsLeftType = CGoblin::IsLeftType(this, nType);
  OldSuitId = CGoblin::GetSuitId(this, IsLeftType);
  v4 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType)->GoblinLevel + 1;
  v5 = nType;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetGoblinCfg(v6, v5, v4);
  if ( !pCfg )
    return 2;
  if ( pCfg->ConstCurr < 0 )
    return 2;
  v7 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType);
  if ( v7->GoblinRes < pCfg->ConstCurr )
    return 2;
  v8 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType);
  v8->GoblinRes -= pCfg->ConstCurr;
  v9 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType);
  ++v9->GoblinLevel;
  CGoblin::SendGoblinInfo(this, nType);
  Player::RecalcAttr(this->m_pPlayer);
  v10 = CGoblin::IsLeftType(this, nType);
  NewSuitId = CGoblin::GetSuitId(this, v10);
  v11 = nType;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v15 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v15, ConnId, GateIndex, Proc, v11);
  if ( NewSuitId != OldSuitId )
  {
    GongGaoId = 0;
    if ( CGoblin::IsLeftType(this, nType) )
      GongGaoId = 477;
    else
      GongGaoId = 478;
    v16 = Player::getConnId(this->m_pPlayer);
    v17 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v17, v16, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 2;
    Answer::NetPacket::writeInt32(packet, GongGaoId);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, NewSuitId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v20 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v20, 0, packet);
  }
  return 0;
}


#####################################
void __cdecl CGoblin::SendGoblinInfo(CGoblin *const this, int32_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,GoblinInfo> *v4; // rax
  std::pair<const int,GoblinInfo> *v5; // rax
  std::pair<const int,GoblinInfo> *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int32_t nTypea; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nTypea = nType;
  if ( this->m_pPlayer )
  {
    if ( IsGoblinType(nTypea) )
    {
      it._M_node = std::map<int,GoblinInfo>::find(&thisa->m_GoblinInfoMap, &nTypea)._M_node;
      __x._M_node = std::map<int,GoblinInfo>::end(&thisa->m_GoblinInfoMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D20u);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second.GoblinLevel);
          v6 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v6->second.GoblinRes);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v9 = Player::getConnId(thisa->m_pPlayer);
          v10 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v10, v9, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
bool __cdecl CGoblin::IsLeftType(CGoblin *const this, int32_t nType)
{
  return nType > 28 && nType <= 31;
}


#####################################
int32_t __cdecl CGoblin::GetSuitId(CGoblin *const this, int32_t IsLeft)
{
  int32_t GoblinLevel; // r12d
  int32_t v3; // ebx
  CfgData *v4; // rax
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Start; // [rsp+2Ch] [rbp-24h]
  int32_t End; // [rsp+30h] [rbp-20h]
  int32_t SuitId; // [rsp+34h] [rbp-1Ch]
  GoblinCfg *pCfg; // [rsp+38h] [rbp-18h]

  Start = 0;
  End = 0;
  if ( IsLeft )
  {
    Start = 29;
    End = 31;
  }
  else
  {
    Start = 32;
    End = 34;
  }
  SuitId = 0;
  for ( i = Start; i <= End; ++i )
  {
    it._M_node = std::map<int,GoblinInfo>::find(&this->m_GoblinInfoMap, &i)._M_node;
    __x._M_node = std::map<int,GoblinInfo>::end(&this->m_GoblinInfoMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&it, &__x) )
      return 0;
    GoblinLevel = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it)->second.GoblinLevel;
    v3 = i;
    v4 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetGoblinCfg(v4, v3, GoblinLevel);
    if ( !pCfg )
      return 0;
    if ( pCfg->SuitId <= 0 )
      return 0;
    if ( SuitId )
    {
      if ( pCfg->SuitId < SuitId )
        SuitId = pCfg->SuitId;
    }
    else
    {
      SuitId = pCfg->SuitId;
    }
  }
  return SuitId;
}


#####################################
void __cdecl CGoblin::AddChrAttr(CGoblin *const this)
{
  int32_t v1; // eax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  int32_t v4; // eax
  int32_t v5; // ebx
  AddAttribute *v6; // rax
  std::_List_iterator<AddAttribute> it_0; // [rsp+10h] [rbp-70h] BYREF
  AddAttrList AddAttrs_0; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<AddAttribute> it; // [rsp+30h] [rbp-50h] BYREF
  AddAttrList AddAttrs; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+50h] [rbp-30h] BYREF
  std::_List_iterator<AddAttribute> v12; // [rsp+60h] [rbp-20h] BYREF
  int32_t LeftSuitId; // [rsp+68h] [rbp-18h]
  int32_t RightSuitId; // [rsp+6Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    LeftSuitId = CGoblin::GetSuitId(this, 1);
    v1 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetGoblinSuitAttr((CfgData *const)&AddAttrs, v1);
    for ( it._M_node = std::list<AddAttribute>::begin(&AddAttrs)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&AddAttrs)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v3 = std::_List_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
    }
    std::list<AddAttribute>::~list(&AddAttrs);
    RightSuitId = CGoblin::GetSuitId(this, 0);
    v4 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetGoblinSuitAttr((CfgData *const)&AddAttrs_0, v4);
    for ( it_0._M_node = std::list<AddAttribute>::begin(&AddAttrs_0)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it_0, 0) )
    {
      v12._M_node = std::list<AddAttribute>::end(&AddAttrs_0)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &v12) )
        break;
      v5 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
      v6 = std::_List_iterator<AddAttribute>::operator->(&it_0);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v6->m_nAddAttrType, v5);
    }
    std::list<AddAttribute>::~list(&AddAttrs_0);
  }
}


#####################################
void __cdecl CGoblin::AppendInfo(CGoblin *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t GoblinLevel; // edx
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    nSize = std::map<int,GoblinInfo>::size(&this->m_GoblinInfoMap);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,GoblinInfo>::begin(&this->m_GoblinInfoMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,GoblinInfo>::end(&this->m_GoblinInfoMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      GoblinLevel = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it)->second.GoblinLevel;
      Answer::NetPacket::writeInt32(packet, GoblinLevel);
    }
  }
}


#####################################
void __cdecl CGoblin::SendAllShouHuRefiningInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D21u);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_ShouHuRefiningLeveMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_ShouHuRefiningLeveMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_ShouHuRefiningLeveMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
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
void __cdecl CGoblin::AddShouHuChrAttr(CGoblin *const this)
{
  int32_t v1; // eax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  int32_t second; // r12d
  int first; // ebx
  CfgData *v6; // rax
  int v8; // ebx
  CExtEquip *v9; // rax
  CExtEquip *v10; // rax
  int32_t v11; // ebx
  AddAttribute *v12; // rax
  __int64 Equip; // [rsp+10h] [rbp-C0h]
  std::_List_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-A0h] BYREF
  AddAttrList AddAttrs_0; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+50h] [rbp-80h] BYREF
  std::_List_iterator<AddAttribute> it; // [rsp+60h] [rbp-70h] BYREF
  AddAttrList AddAttrs; // [rsp+70h] [rbp-60h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+80h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v20; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> v21; // [rsp+A0h] [rbp-30h] BYREF
  int32_t SuitId; // [rsp+B4h] [rbp-1Ch]
  ShouHuRefinishingCfg *pCfg; // [rsp+B8h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    SuitId = CGoblin::GetShouHuSuitId(this);
    v1 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetShouHuRefinishingSuitAttr((CfgData *const)&AddAttrs, v1);
    for ( it._M_node = std::list<AddAttribute>::begin(&AddAttrs)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&AddAttrs)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v3 = std::_List_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
    }
    std::list<AddAttribute>::~list(&AddAttrs);
    for ( iter._M_node = std::map<int,int>::begin(&this->m_ShouHuRefiningLeveMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter, 0) )
    {
      v20._M_node = std::map<int,int>::end(&this->m_ShouHuRefiningLeveMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v20) )
        break;
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
      v6 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetShouHuRefinishingCfg(v6, first, second);
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first >= 0
        && std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first <= 92 )
      {
        v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
        v9 = Player::GetEquip(this->m_pPlayer);
        LOBYTE(v8) = CExtEquip::GetEquipSlotPlace(v9, v8);
        v10 = Player::GetEquip(this->m_pPlayer);
        Equip = *(_QWORD *)&CExtEquip::GetEquipSlot(v10, v8)->itemId;
        if ( pCfg )
        {
          if ( (int)Equip > 0 )
          {
            std::list<AddAttribute>::list(&AddAttrs_0, &pCfg->lAttrList);
            for ( it_0._M_node = std::list<AddAttribute>::begin(&AddAttrs_0)._M_node;
                  ;
                  std::_List_iterator<AddAttribute>::operator++(&it_0, 0) )
            {
              v21._M_node = std::list<AddAttribute>::end(&AddAttrs_0)._M_node;
              if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &v21) )
                break;
              v11 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
              v12 = std::_List_iterator<AddAttribute>::operator->(&it_0);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v12->m_nAddAttrType, v11);
            }
            std::list<AddAttribute>::~list(&AddAttrs_0);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::AppendShouHuInfo(CGoblin *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    nSize = std::map<int,int>::size(&this->m_ShouHuRefiningLeveMap);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,int>::begin(&this->m_ShouHuRefiningLeveMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_ShouHuRefiningLeveMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
  }
}


#####################################
int32_t __cdecl CGoblin::GetShouHuSuitId(CGoblin *const this)
{
  int32_t second; // r12d
  int32_t v2; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Start; // [rsp+2Ch] [rbp-24h]
  int32_t End; // [rsp+30h] [rbp-20h]
  int32_t SuitId; // [rsp+34h] [rbp-1Ch]
  ShouHuRefinishingCfg *pCfg; // [rsp+38h] [rbp-18h]

  Start = 17;
  End = 28;
  SuitId = 0;
  for ( i = 17; i <= End; ++i )
  {
    it._M_node = std::map<int,int>::find(&this->m_ShouHuRefiningLeveMap, &i)._M_node;
    __x._M_node = std::map<int,int>::end(&this->m_ShouHuRefiningLeveMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      return 0;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v2 = i;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetShouHuRefinishingCfg(v3, v2, second);
    if ( !pCfg )
      return 0;
    if ( pCfg->SuitId <= 0 )
      return 0;
    if ( SuitId )
    {
      if ( pCfg->SuitId < SuitId )
        SuitId = pCfg->SuitId;
    }
    else
    {
      SuitId = pCfg->SuitId;
    }
  }
  return SuitId;
}


#####################################
int32_t __cdecl CGoblin::OnShouHuRefiningLevelUp(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // r13d
  int32_t v4; // r12d
  CfgData *v5; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *Bag; // rax
  ItemData *v9; // rax
  ItemData *v10; // rax
  ItemData *v11; // rax
  int32_t v12; // r13d
  int8_t v13; // r12
  CfgData *v14; // rax
  int v15; // r12d
  std::_List_iterator<ItemData> v16; // rax
  int64_t Currency; // rax
  CExtCharBag *v19; // rax
  CExtCharBag *v21; // rax
  ShouHuRefinishingCfg *v23; // r12
  CExtCharBag *v24; // rax
  CExtCharBag *v26; // rax
  int *v27; // rax
  GameService *v28; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v31; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-B0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-A0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-90h] BYREF
  int __k; // [rsp+4Ch] [rbp-74h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-70h] BYREF
  int v38; // [rsp+5Ch] [rbp-64h] BYREF
  std::string val; // [rsp+60h] [rbp-60h] BYREF
  int8_t nType; // [rsp+72h] [rbp-4Eh]
  int8_t AutoBuy; // [rsp+73h] [rbp-4Dh]
  int32_t OldSuitId; // [rsp+74h] [rbp-4Ch]
  ShouHuRefinishingCfg *pCfg; // [rsp+78h] [rbp-48h]
  int32_t NewSuitId; // [rsp+80h] [rbp-40h]
  int32_t nCostGold; // [rsp+84h] [rbp-3Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-38h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-34h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( inPacket && this->m_pPlayer )
  {
    nType = Answer::NetPacket::readInt8(inPacket);
    AutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( !IsShouHunType(nType) )
    {
      v2 = 2;
    }
    else
    {
      OldSuitId = CGoblin::GetShouHuSuitId(this);
      __k = nType;
      v3 = *std::map<int,int>::operator[](&this->m_ShouHuRefiningLeveMap, &__k) + 1;
      v4 = nType;
      v5 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetShouHuRefinishingCfg(v5, v4, v3);
      if ( pCfg )
      {
        if ( AutoBuy )
        {
          nCostGold = 0;
          std::list<ItemData>::list(&costItemList, &pCfg->lCostList);
          iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
          while ( 1 )
          {
            __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
            if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
              break;
            nBuyCount = 0;
            m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
            m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
            Bag = Player::GetBag(this->m_pPlayer);
            nItemCount = CExtCharBag::GetItemCount(Bag, &vSlot, m_nClass, m_nId);
            v9 = std::_List_iterator<ItemData>::operator->(&iter);
            if ( v9->m_nCount > nItemCount )
            {
              v10 = std::_List_iterator<ItemData>::operator->(&iter);
              nBuyCount = v10->m_nCount - nItemCount;
              v11 = std::_List_iterator<ItemData>::operator->(&iter);
              v11->m_nCount = nItemCount;
            }
            if ( nBuyCount > 0 )
            {
              v12 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
              v13 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
              v14 = Answer::Singleton<CfgData>::instance();
              pCfgGameShop = CfgData::GetGameShopItem(v14, v13, v12);
              if ( !pCfgGameShop )
              {
                v2 = 2;
                v15 = 0;
                goto LABEL_39;
              }
              nCostGold += nBuyCount * pCfgGameShop->Price;
            }
            if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
            {
              std::_List_iterator<ItemData>::operator++(&iter);
            }
            else
            {
              v16._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
              std::list<ItemData>::erase(&costItemList, v16);
            }
          }
          if ( nCostGold > 0
            && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
          {
            v2 = 10002;
            v15 = 0;
          }
          else if ( !std::list<ItemData>::empty(&costItemList)
                 && (v19 = Player::GetBag(this->m_pPlayer),
                     !CExtCharBag::RemoveItem(v19, &vSlot, &costItemList, ITEM_CHANGE_REASON::IDCR_SHOU_HU_REFINING)) )
          {
            v2 = 10002;
            v15 = 0;
          }
          else
          {
            v21 = Player::GetBag(this->m_pPlayer);
            CExtCharBag::ForceSendDirty(v21);
            if ( nCostGold > 0
              && !Player::DecCurrency(
                    this->m_pPlayer,
                    CURRENCY_TYPE::CURRENCY_GOLD,
                    nCostGold,
                    CURRENCY_CHANGE_REASON::GCR_SHOU_HU_REFINING,
                    0) )
            {
              v2 = 10002;
              v15 = 0;
            }
            else
            {
              v15 = 1;
            }
          }
LABEL_39:
          std::list<ItemData>::~list(&costItemList);
          if ( !v15 )
            goto LABEL_53;
        }
        else
        {
          if ( !std::list<ItemData>::empty(&pCfg->lCostList) )
          {
            v23 = pCfg;
            v24 = Player::GetBag(this->m_pPlayer);
            if ( !CExtCharBag::RemoveItem(v24, &vSlot, &v23->lCostList, ITEM_CHANGE_REASON::IDCR_SHOU_HU_REFINING) )
            {
              v2 = 10002;
              goto LABEL_53;
            }
          }
          v26 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::ForceSendDirty(v26);
        }
        v38 = nType;
        v27 = std::map<int,int>::operator[](&this->m_ShouHuRefiningLeveMap, &v38);
        ++*v27;
        CGoblin::SendShouHuRefiningInfo(this, nType);
        Player::RecalcAttr(this->m_pPlayer);
        NewSuitId = CGoblin::GetShouHuSuitId(this);
        if ( OldSuitId != NewSuitId )
        {
          v28 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v28, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
          {
            v2 = 10002;
            goto LABEL_53;
          }
          Answer::NetPacket::writeInt32(packet, 497);
          Cid = Player::getCid(this->m_pPlayer);
          Answer::NetPacket::writeInt64(packet, Cid);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          Answer::NetPacket::writeInt32(packet, NewSuitId);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v31 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v31, 0, packet);
        }
        v2 = 0;
        goto LABEL_53;
      }
      v2 = 2;
    }
LABEL_53:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


#####################################
void __cdecl CGoblin::SendShouHuRefiningInfo(CGoblin *const this, int32_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nTypea; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nTypea = nType;
  if ( this->m_pPlayer )
  {
    if ( IsShouHunType(nTypea) )
    {
      it._M_node = std::map<int,int>::find(&thisa->m_ShouHuRefiningLeveMap, &nTypea)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_ShouHuRefiningLeveMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D22u);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v8 = Player::getConnId(thisa->m_pPlayer);
          v9 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v9, v8, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::SendAllWingEquipPolishInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D23u);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_WingEquipPolishMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_WingEquipPolishMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_WingEquipPolishMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
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
void __cdecl CGoblin::AddWingEquipPolishChrAttr(CGoblin *const this)
{
  int32_t v1; // eax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  int32_t second; // r12d
  int first; // ebx
  CfgData *v6; // rax
  int8_t v8; // bl
  CExtEquip *v9; // rax
  int32_t v10; // ebx
  AddAttribute *v11; // rax
  __int64 Equip; // [rsp+10h] [rbp-C0h]
  std::_List_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-A0h] BYREF
  AddAttrList AddAttrs_0; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+50h] [rbp-80h] BYREF
  std::_List_iterator<AddAttribute> it; // [rsp+60h] [rbp-70h] BYREF
  AddAttrList AddAttrs; // [rsp+70h] [rbp-60h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+80h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v19; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> v20; // [rsp+A0h] [rbp-30h] BYREF
  int32_t SuitId; // [rsp+B4h] [rbp-1Ch]
  WingEquipPolish *pCfg; // [rsp+B8h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    SuitId = CGoblin::GetWingEquipPolishSuitId(this);
    v1 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetWingEquipPolishSuitAttr((CfgData *const)&AddAttrs, v1);
    for ( it._M_node = std::list<AddAttribute>::begin(&AddAttrs)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&AddAttrs)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v3 = std::_List_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
    }
    std::list<AddAttribute>::~list(&AddAttrs);
    for ( iter._M_node = std::map<int,int>::begin(&this->m_WingEquipPolishMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter, 0) )
    {
      v19._M_node = std::map<int,int>::end(&this->m_WingEquipPolishMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v19) )
        break;
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
      v6 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetWingEquipPolishCfg(v6, first, second);
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first >= 0
        && std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first <= 92 )
      {
        v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
        v9 = Player::GetEquip(this->m_pPlayer);
        Equip = *(_QWORD *)&CExtEquip::GetEquipSlot(v9, v8)->itemId;
        if ( pCfg )
        {
          if ( (int)Equip > 0 )
          {
            std::list<AddAttribute>::list(&AddAttrs_0, &pCfg->lAttrList);
            for ( it_0._M_node = std::list<AddAttribute>::begin(&AddAttrs_0)._M_node;
                  ;
                  std::_List_iterator<AddAttribute>::operator++(&it_0, 0) )
            {
              v20._M_node = std::list<AddAttribute>::end(&AddAttrs_0)._M_node;
              if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &v20) )
                break;
              v10 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
              v11 = std::_List_iterator<AddAttribute>::operator->(&it_0);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v11->m_nAddAttrType, v10);
            }
            std::list<AddAttribute>::~list(&AddAttrs_0);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::AppendWingEquipPolishInfo(CGoblin *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    nSize = std::map<int,int>::size(&this->m_WingEquipPolishMap);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,int>::begin(&this->m_WingEquipPolishMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_WingEquipPolishMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
  }
}


#####################################
int32_t __cdecl CGoblin::GetWingEquipPolishSuitId(CGoblin *const this)
{
  int32_t second; // r12d
  int32_t v2; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Start; // [rsp+2Ch] [rbp-24h]
  int32_t End; // [rsp+30h] [rbp-20h]
  int32_t SuitId; // [rsp+34h] [rbp-1Ch]
  WingEquipPolish *pCfg; // [rsp+38h] [rbp-18h]

  Start = 44;
  End = 49;
  SuitId = 0;
  for ( i = 44; i <= End; ++i )
  {
    it._M_node = std::map<int,int>::find(&this->m_WingEquipPolishMap, &i)._M_node;
    __x._M_node = std::map<int,int>::end(&this->m_WingEquipPolishMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      return 0;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v2 = i;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetWingEquipPolishCfg(v3, v2, second);
    if ( !pCfg )
      return 0;
    if ( pCfg->SuitId <= 0 )
      return 0;
    if ( SuitId )
    {
      if ( pCfg->SuitId < SuitId )
        SuitId = pCfg->SuitId;
    }
    else
    {
      SuitId = pCfg->SuitId;
    }
  }
  return SuitId;
}


#####################################
int32_t __cdecl CGoblin::OnWingEquipPolishLevelUp(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // r12d
  CExtEquip *Equip; // rax
  int32_t MaxPolishLevel; // r12d
  int32_t v6; // r13d
  int32_t v7; // r12d
  CfgData *v8; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *v11; // rax
  ItemData *v12; // rax
  ItemData *v13; // rax
  ItemData *v14; // rax
  int32_t v15; // r13d
  int8_t v16; // r12
  CfgData *v17; // rax
  int v18; // r12d
  std::_List_iterator<ItemData> v19; // rax
  int64_t v20; // rax
  CExtCurrency *v22; // rax
  int64_t v23; // rax
  CExtCharBag *v25; // rax
  int64_t v28; // r12
  CExtCurrency *v29; // rax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  ItemDataList *p_lCostList; // rbx
  CExtCharBag *Bag; // rax
  int64_t nConstMoney; // rbx
  CExtCurrency *v38; // rax
  CExtCharBag *v40; // rax
  int *v41; // rax
  GameService *v42; // rax
  CharId_t Cid; // rax
  int *v44; // rax
  uint32_t WOffset; // eax
  GameService *v46; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-B0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-A0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-90h] BYREF
  int __k; // [rsp+48h] [rbp-78h] BYREF
  int v52; // [rsp+4Ch] [rbp-74h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-70h] BYREF
  int v54; // [rsp+5Ch] [rbp-64h] BYREF
  std::string val; // [rsp+60h] [rbp-60h] BYREF
  int v56; // [rsp+70h] [rbp-50h] BYREF
  int8_t nSlot; // [rsp+76h] [rbp-4Ah]
  int8_t AutoBuy; // [rsp+77h] [rbp-49h]
  WingEquipPolish *pCfg; // [rsp+78h] [rbp-48h]
  int32_t nCostGold; // [rsp+84h] [rbp-3Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-38h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-34h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( inPacket && this->m_pPlayer )
  {
    nSlot = Answer::NetPacket::readInt8(inPacket);
    AutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( !IsWingEquipSlot(nSlot) )
    {
      v2 = 2;
    }
    else
    {
      v3 = nSlot;
      Equip = Player::GetEquip(this->m_pPlayer);
      MaxPolishLevel = CExtEquip::GetMaxPolishLevel(Equip, v3);
      __k = nSlot;
      if ( MaxPolishLevel > *std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &__k) )
      {
        v52 = nSlot;
        v6 = *std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &v52) + 1;
        v7 = nSlot;
        v8 = Answer::Singleton<CfgData>::instance();
        pCfg = CfgData::GetWingEquipPolishCfg(v8, v7, v6);
        if ( pCfg )
        {
          if ( AutoBuy <= 0 )
          {
            if ( pCfg->nConstMoney > 0 )
            {
              Currency = Player::GetCurrency(this->m_pPlayer);
              MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
              if ( MoneyBindAndNoBind < pCfg->nConstMoney )
              {
                v2 = 10002;
                goto LABEL_78;
              }
            }
            if ( !std::list<ItemData>::empty(&pCfg->lCostList) )
            {
              p_lCostList = &pCfg->lCostList;
              Bag = Player::GetBag(this->m_pPlayer);
              if ( !CExtCharBag::RemoveItem(Bag, p_lCostList, ITEM_CHANGE_REASON::ICR_WING_EQUIP_POLISH_LEVEL_UP) )
              {
                v2 = 10002;
                goto LABEL_78;
              }
            }
            if ( pCfg->nConstMoney > 0 )
            {
              nConstMoney = pCfg->nConstMoney;
              v38 = Player::GetCurrency(this->m_pPlayer);
              if ( !CExtCurrency::DecMoneyAndNoBind(
                      v38,
                      nConstMoney,
                      CURRENCY_CHANGE_REASON::GCR_WING_EQUIP_POLISH_LEVEL_UP,
                      0) )
              {
                v2 = 10002;
                goto LABEL_78;
              }
            }
          }
          else
          {
            nCostGold = 0;
            std::list<ItemData>::list(&costItemList, &pCfg->lCostList);
            iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
            while ( 1 )
            {
              __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
              if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
                break;
              nBuyCount = 0;
              m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
              m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
              v11 = Player::GetBag(this->m_pPlayer);
              nItemCount = CExtCharBag::GetItemCount(v11, &vSlot, m_nClass, m_nId);
              v12 = std::_List_iterator<ItemData>::operator->(&iter);
              if ( v12->m_nCount > nItemCount )
              {
                v13 = std::_List_iterator<ItemData>::operator->(&iter);
                nBuyCount = v13->m_nCount - nItemCount;
                v14 = std::_List_iterator<ItemData>::operator->(&iter);
                v14->m_nCount = nItemCount;
              }
              if ( nBuyCount > 0 )
              {
                v15 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
                v16 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
                v17 = Answer::Singleton<CfgData>::instance();
                pCfgGameShop = CfgData::GetGameShopItem(v17, v16, v15);
                if ( !pCfgGameShop )
                {
                  v2 = 2;
                  v18 = 0;
                  goto LABEL_53;
                }
                nCostGold += nBuyCount * pCfgGameShop->Price;
              }
              if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
              {
                std::_List_iterator<ItemData>::operator++(&iter);
              }
              else
              {
                v19._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
                std::list<ItemData>::erase(&costItemList, v19);
              }
            }
            if ( nCostGold > 0
              && (v20 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), v20 < nCostGold) )
            {
              v2 = 10002;
              v18 = 0;
            }
            else if ( pCfg->nConstMoney > 0
                   && (v22 = Player::GetCurrency(this->m_pPlayer),
                       v23 = CExtCurrency::GetMoneyBindAndNoBind(v22),
                       v23 < pCfg->nConstMoney) )
            {
              v2 = 10002;
              v18 = 0;
            }
            else if ( !std::list<ItemData>::empty(&costItemList)
                   && (v25 = Player::GetBag(this->m_pPlayer),
                       !CExtCharBag::RemoveItem(
                          v25,
                          &vSlot,
                          &costItemList,
                          ITEM_CHANGE_REASON::ICR_WING_EQUIP_POLISH_LEVEL_UP)) )
            {
              v2 = 10002;
              v18 = 0;
            }
            else if ( nCostGold > 0
                   && !Player::DecCurrency(
                         this->m_pPlayer,
                         CURRENCY_TYPE::CURRENCY_GOLD,
                         nCostGold,
                         CURRENCY_CHANGE_REASON::GCR_WING_EQUIP_POLISH_LEVEL_UP,
                         0) )
            {
              v2 = 10002;
              v18 = 0;
            }
            else if ( pCfg->nConstMoney > 0
                   && (v28 = pCfg->nConstMoney,
                       v29 = Player::GetCurrency(this->m_pPlayer),
                       !CExtCurrency::DecMoneyAndNoBind(
                          v29,
                          v28,
                          CURRENCY_CHANGE_REASON::GCR_WING_EQUIP_POLISH_LEVEL_UP,
                          0)) )
            {
              v2 = 10002;
              v18 = 0;
            }
            else
            {
              v18 = 1;
            }
LABEL_53:
            std::list<ItemData>::~list(&costItemList);
            if ( !v18 )
              goto LABEL_78;
          }
          v40 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::ForceSendDirty(v40);
          v54 = nSlot;
          v41 = std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &v54);
          ++*v41;
          CGoblin::SendWingEquipPolishInfo(this, nSlot);
          Player::RecalcAttr(this->m_pPlayer);
          if ( pCfg->GongGaoId > 0 )
          {
            v42 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v42, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v2 = 10002;
              goto LABEL_78;
            }
            Answer::NetPacket::writeInt32(packet, pCfg->GongGaoId);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Answer::NetPacket::writeInt8(packet, nSlot);
            v56 = nSlot;
            v44 = std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &v56);
            Answer::NetPacket::writeInt32(packet, *v44);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v46 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v46, 0, packet);
          }
          v2 = 0;
          goto LABEL_78;
        }
        v2 = 2;
      }
      else
      {
        v2 = 2;
      }
    }
LABEL_78:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


#####################################
void __cdecl CGoblin::SendWingEquipPolishInfo(CGoblin *const this, int32_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nSlota = nSlot;
  if ( this->m_pPlayer )
  {
    if ( IsWingEquipSlot(nSlota) )
    {
      it._M_node = std::map<int,int>::find(&thisa->m_WingEquipPolishMap, &nSlota)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_WingEquipPolishMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D24u);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v8 = Player::getConnId(thisa->m_pPlayer);
          v9 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v9, v8, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::SendAllMoFuZhuNengInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D25u);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_MoFuZhuNengMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_MoFuZhuNengMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_MoFuZhuNengMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
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
int32_t __cdecl CGoblin::GetMoFuChrAttr(CGoblin *const this, int32_t Slot)
{
  int32_t second; // r12d
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t Slota; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  ZhuNengCfg *pZhuNengCfg; // [rsp+28h] [rbp-18h]

  thisa = this;
  Slota = Slot;
  it._M_node = std::map<int,int>::find(&this->m_MoFuZhuNengMap, &Slota)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_MoFuZhuNengMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
    return 0;
  second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  v4 = Slota;
  v5 = Answer::Singleton<CfgData>::instance();
  pZhuNengCfg = CfgData::GetZhuNengCfg(v5, v4, second);
  if ( pZhuNengCfg )
    return pZhuNengCfg->BasicAttr;
  else
    return 0;
}


#####################################
int32_t __cdecl CGoblin::OnMoFuZhuNeng(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t second; // r12d
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t v6; // r12d
  int32_t v7; // ebx
  CfgData *v8; // rax
  int32_t v9; // ebx
  CfgData *v10; // rax
  int32_t v11; // ebx
  CfgData *v12; // rax
  ItemData *p_Item; // rbx
  CExtCharBag *Bag; // rax
  std::pair<const int,int> *v15; // rax
  int64_t v16; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v20; // rax
  int8_t v21; // bl
  GameService *v22; // rax
  CharId_t Cid; // rax
  int *v24; // rax
  uint32_t WOffset; // eax
  GameService *v26; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+20h] [rbp-A0h] BYREF
  int32_t nSlot; // [rsp+2Ch] [rbp-94h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v30; // [rsp+40h] [rbp-80h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,int> >,bool> v31; // [rsp+50h] [rbp-70h]
  std::pair<const int,int> v32; // [rsp+60h] [rbp-60h] BYREF
  std::pair<int,int> __p; // [rsp+70h] [rbp-50h] BYREF
  std::string val; // [rsp+80h] [rbp-40h] BYREF
  ZhuNengCfg *pCfg; // [rsp+88h] [rbp-38h]
  ZhuNengCfg *pNext; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nSlot = Answer::NetPacket::readInt8(inPacket);
  if ( !IsMoFuSlot(nSlot) )
    return 2;
  pCfg = 0;
  pNext = 0;
  it._M_node = std::map<int,int>::find(&this->m_MoFuZhuNengMap, &nSlot)._M_node;
  __x._M_node = std::map<int,int>::end(&this->m_MoFuZhuNengMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
  {
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v4 = nSlot;
    v5 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetZhuNengCfg(v5, v4, second);
    v6 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second + 1;
    v7 = nSlot;
    v8 = Answer::Singleton<CfgData>::instance();
    pNext = CfgData::GetZhuNengCfg(v8, v7, v6);
  }
  else
  {
    v9 = nSlot;
    v10 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetZhuNengCfg(v10, v9, 0);
    v11 = nSlot;
    v12 = Answer::Singleton<CfgData>::instance();
    pNext = CfgData::GetZhuNengCfg(v12, v11, 1);
  }
  if ( !pCfg || !pNext )
    return 2;
  p_Item = &pCfg->Item;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::RemoveItem(Bag, p_Item, ITEM_CHANGE_REASON::IDCR_ZHU_NENG) )
    return 2;
  v30._M_node = std::map<int,int>::end(&this->m_MoFuZhuNengMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &v30) )
  {
    __p = std::make_pair<int,int>(nSlot, 1);
    std::pair<int const,int>::pair<int,int>(&v32, &__p);
    v31 = std::map<int,int>::insert(&this->m_MoFuZhuNengMap, &v32);
  }
  else
  {
    v15 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    ++v15->second;
  }
  CGoblin::SendMoFuZhuNengInfo(this, nSlot);
  Player::RecalcAttr(this->m_pPlayer);
  v16 = nSlot;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v20 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v20, ConnId, GateIndex, Proc, v16);
  if ( pNext->GongGaoId > 0 )
  {
    v21 = Player::getConnId(this->m_pPlayer);
    v22 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v22, v21, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 2;
    Answer::NetPacket::writeInt32(packet, pNext->GongGaoId);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, nSlot);
    v24 = std::map<int,int>::operator[](&this->m_MoFuZhuNengMap, &nSlot);
    Answer::NetPacket::writeInt32(packet, *v24);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v26 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v26, 0, packet);
  }
  return 0;
}


#####################################
void __cdecl CGoblin::SendMoFuZhuNengInfo(CGoblin *const this, int32_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nSlota = nSlot;
  if ( this->m_pPlayer )
  {
    if ( IsMoFuSlot(nSlota) )
    {
      it._M_node = std::map<int,int>::find(&thisa->m_MoFuZhuNengMap, &nSlota)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_MoFuZhuNengMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D26u);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v8 = Player::getConnId(thisa->m_pPlayer);
          v9 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v9, v8, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::SendAllWingEquipRefiningInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D27u);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_WingEquipRefiningMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_WingEquipRefiningMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_WingEquipRefiningMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
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
void __cdecl CGoblin::AddWingEquipRefiningChrAttr(CGoblin *const this)
{
  int32_t v1; // eax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  AddAttrList AddAttrs; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t SuitId; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    SuitId = CGoblin::GetWingEquipRefiningSuitId(this);
    v1 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetWingEquipRefiningSuitAttr((CfgData *const)&AddAttrs, v1);
    for ( it._M_node = std::list<AddAttribute>::begin(&AddAttrs)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&AddAttrs)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v3 = std::_List_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
    }
    std::list<AddAttribute>::~list(&AddAttrs);
  }
}


#####################################
void __cdecl CGoblin::AppendWingEquipRefiningInfo(CGoblin *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    nSize = std::map<int,int>::size(&this->m_WingEquipRefiningMap);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,int>::begin(&this->m_WingEquipRefiningMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_WingEquipRefiningMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
  }
}


#####################################
int32_t __cdecl CGoblin::GetWingEquipRefiningSuitId(CGoblin *const this)
{
  int32_t second; // r12d
  int32_t v2; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Start; // [rsp+2Ch] [rbp-24h]
  int32_t End; // [rsp+30h] [rbp-20h]
  int32_t SuitId; // [rsp+34h] [rbp-1Ch]
  WinRefiningCfg *pCfg; // [rsp+38h] [rbp-18h]

  Start = 44;
  End = 49;
  SuitId = 0;
  for ( i = 44; i <= End; ++i )
  {
    it._M_node = std::map<int,int>::find(&this->m_WingEquipRefiningMap, &i)._M_node;
    __x._M_node = std::map<int,int>::end(&this->m_WingEquipRefiningMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      return 0;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v2 = i;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetWingEquipRefiningCfg(v3, v2, second);
    if ( !pCfg )
      return 0;
    if ( pCfg->SuitId <= 0 )
      return 0;
    if ( SuitId )
    {
      if ( pCfg->SuitId < SuitId )
        SuitId = pCfg->SuitId;
    }
    else
    {
      SuitId = pCfg->SuitId;
    }
  }
  return SuitId;
}


#####################################
int32_t __cdecl CGoblin::OnWingEquipRefiningLevelUp(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t v4; // r12d
  CExtEquip *Equip; // rax
  int32_t MaxRefiningLevel; // r12d
  int32_t v7; // r13d
  int32_t v8; // r12d
  CfgData *v9; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *v12; // rax
  ItemData *v13; // rax
  ItemData *v14; // rax
  ItemData *v15; // rax
  int32_t v16; // r13d
  int8_t v17; // r12
  CfgData *v18; // rax
  int v19; // r12d
  std::_List_iterator<ItemData> v20; // rax
  int64_t Currency; // rax
  CExtCharBag *v23; // rax
  ItemDataList *p_lCostList; // rbx
  CExtCharBag *Bag; // rax
  CExtCharBag *v29; // rax
  int *v30; // rax
  GameService *v31; // rax
  CharId_t Cid; // rax
  int *v33; // rax
  uint32_t WOffset; // eax
  GameService *v35; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-B0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-A0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-90h] BYREF
  int __k; // [rsp+48h] [rbp-78h] BYREF
  int v41; // [rsp+4Ch] [rbp-74h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-70h] BYREF
  int v43; // [rsp+5Ch] [rbp-64h] BYREF
  std::string val; // [rsp+60h] [rbp-60h] BYREF
  int v45; // [rsp+70h] [rbp-50h] BYREF
  int8_t nSlot; // [rsp+76h] [rbp-4Ah]
  int8_t AutoBuy; // [rsp+77h] [rbp-49h]
  WinRefiningCfg *pCfg; // [rsp+78h] [rbp-48h]
  int32_t nCostGold; // [rsp+84h] [rbp-3Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-38h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-34h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( inPacket && this->m_pPlayer )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1 <= 39 )
      return 10002;
    nSlot = Answer::NetPacket::readInt8(inPacket);
    AutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( !IsWingEquipSlot(nSlot) )
    {
      v2 = 2;
    }
    else
    {
      v4 = nSlot;
      Equip = Player::GetEquip(this->m_pPlayer);
      MaxRefiningLevel = CExtEquip::GetMaxRefiningLevel(Equip, v4);
      __k = nSlot;
      if ( MaxRefiningLevel > *std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &__k) )
      {
        v41 = nSlot;
        v7 = *std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &v41) + 1;
        v8 = nSlot;
        v9 = Answer::Singleton<CfgData>::instance();
        pCfg = CfgData::GetWingEquipRefiningCfg(v9, v8, v7);
        if ( pCfg )
        {
          if ( AutoBuy <= 0 )
          {
            if ( !std::list<ItemData>::empty(&pCfg->lCostList) )
            {
              p_lCostList = &pCfg->lCostList;
              Bag = Player::GetBag(this->m_pPlayer);
              if ( !CExtCharBag::RemoveItem(Bag, p_lCostList, ITEM_CHANGE_REASON::ICR_WING_EQUIP_POLISH_LEVEL_UP) )
              {
                v2 = 10002;
                goto LABEL_56;
              }
            }
          }
          else
          {
            nCostGold = 0;
            std::list<ItemData>::list(&costItemList, &pCfg->lCostList);
            iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
            while ( 1 )
            {
              __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
              if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
                break;
              nBuyCount = 0;
              m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
              m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
              v12 = Player::GetBag(this->m_pPlayer);
              nItemCount = CExtCharBag::GetItemCount(v12, &vSlot, m_nClass, m_nId);
              v13 = std::_List_iterator<ItemData>::operator->(&iter);
              if ( v13->m_nCount > nItemCount )
              {
                v14 = std::_List_iterator<ItemData>::operator->(&iter);
                nBuyCount = v14->m_nCount - nItemCount;
                v15 = std::_List_iterator<ItemData>::operator->(&iter);
                v15->m_nCount = nItemCount;
              }
              if ( nBuyCount > 0 )
              {
                v16 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
                v17 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
                v18 = Answer::Singleton<CfgData>::instance();
                pCfgGameShop = CfgData::GetGameShopItem(v18, v17, v16);
                if ( !pCfgGameShop )
                {
                  v2 = 2;
                  v19 = 0;
                  goto LABEL_43;
                }
                nCostGold += nBuyCount * pCfgGameShop->Price;
              }
              if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
              {
                std::_List_iterator<ItemData>::operator++(&iter);
              }
              else
              {
                v20._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
                std::list<ItemData>::erase(&costItemList, v20);
              }
            }
            if ( nCostGold > 0
              && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
            {
              v2 = 10002;
              v19 = 0;
            }
            else if ( !std::list<ItemData>::empty(&costItemList)
                   && (v23 = Player::GetBag(this->m_pPlayer),
                       !CExtCharBag::RemoveItem(
                          v23,
                          &vSlot,
                          &costItemList,
                          ITEM_CHANGE_REASON::ICR_WING_EQUIP_POLISH_LEVEL_UP)) )
            {
              v2 = 10002;
              v19 = 0;
            }
            else if ( nCostGold > 0
                   && !Player::DecCurrency(
                         this->m_pPlayer,
                         CURRENCY_TYPE::CURRENCY_GOLD,
                         nCostGold,
                         CURRENCY_CHANGE_REASON::GCR_WING_EQUIP_POLISH_LEVEL_UP,
                         0) )
            {
              v2 = 10002;
              v19 = 0;
            }
            else
            {
              v19 = 1;
            }
LABEL_43:
            std::list<ItemData>::~list(&costItemList);
            if ( !v19 )
              goto LABEL_56;
          }
          v29 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::ForceSendDirty(v29);
          v43 = nSlot;
          v30 = std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &v43);
          ++*v30;
          CGoblin::SendWingEquipRefiningInfo(this, nSlot);
          Player::RecalcAttr(this->m_pPlayer);
          if ( pCfg->GongGaoId > 0 )
          {
            v31 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v31, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v2 = 10002;
              goto LABEL_56;
            }
            Answer::NetPacket::writeInt32(packet, pCfg->GongGaoId);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Answer::NetPacket::writeInt8(packet, nSlot);
            v45 = nSlot;
            v33 = std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &v45);
            Answer::NetPacket::writeInt32(packet, *v33);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v35 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v35, 0, packet);
          }
          v2 = 0;
          goto LABEL_56;
        }
        v2 = 2;
      }
      else
      {
        v2 = 2;
      }
    }
LABEL_56:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


#####################################
void __cdecl CGoblin::SendWingEquipRefiningInfo(CGoblin *const this, int32_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nSlota = nSlot;
  if ( this->m_pPlayer )
  {
    if ( IsWingEquipSlot(nSlota) )
    {
      it._M_node = std::map<int,int>::find(&thisa->m_WingEquipRefiningMap, &nSlota)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_WingEquipRefiningMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D28u);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v8 = Player::getConnId(thisa->m_pPlayer);
          v9 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v9, v8, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CGoblin::GetWingEquipRefiningAttr(CGoblin *const this, int32_t nSlot)
{
  int32_t v3; // r12d
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t nSlota; // [rsp+4h] [rbp-2Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-28h]
  WinRefiningCfg *pCfg; // [rsp+18h] [rbp-18h]

  thisa = this;
  nSlota = nSlot;
  if ( !IsWingEquipSlot(nSlot) )
    return 0;
  v3 = *std::map<int,int>::operator[](&thisa->m_WingEquipRefiningMap, &nSlota);
  v4 = nSlota;
  v5 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetWingEquipRefiningCfg(v5, v4, v3);
  if ( pCfg )
    return pCfg->Attr;
  else
    return 0;
}


#####################################
void __cdecl CGoblin::SendAllVipEquipPosLevelInfo(CGoblin *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D29u);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_VipEquipPosLevelMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_VipEquipPosLevelMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_VipEquipPosLevelMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
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
void __cdecl CGoblin::AddVipEquipPosLevelCharAttr(CGoblin *const this)
{
  CfgData *v1; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v3; // rax
  int32_t second; // r12d
  int first; // ebx
  CfgData *v6; // rax
  int8_t v8; // bl
  CExtEquip *v9; // rax
  int32_t v10; // ebx
  AddAttribute *v11; // rax
  __int64 Equip; // [rsp+10h] [rbp-B0h]
  std::_List_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-90h] BYREF
  AddAttrList AddAttrs; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+50h] [rbp-70h] BYREF
  std::_List_const_iterator<AddAttribute> it; // [rsp+60h] [rbp-60h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+70h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v18; // [rsp+80h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> v19; // [rsp+90h] [rbp-30h] BYREF
  int32_t SuitId; // [rsp+9Ch] [rbp-24h]
  const VipEQuipPosSuit *pCfg; // [rsp+A0h] [rbp-20h]
  const VipEquipPosLevelUp *pCfg_0; // [rsp+A8h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    SuitId = CGoblin::GetVipEquipPosLevelSuitId(this);
    if ( SuitId > 0 )
    {
      v1 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetVipEQuipPosSuit(v1, SuitId);
      if ( pCfg )
      {
        for ( it._M_node = std::list<AddAttribute>::begin(&pCfg->lAddAttrs)._M_node;
              ;
              std::_List_const_iterator<AddAttribute>::operator++(&it, 0) )
        {
          __x._M_node = std::list<AddAttribute>::end(&pCfg->lAddAttrs)._M_node;
          if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it, &__x) )
            break;
          m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
          v3 = std::_List_const_iterator<AddAttribute>::operator->(&it);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
        }
      }
    }
    for ( iter._M_node = std::map<int,int>::begin(&this->m_VipEquipPosLevelMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter, 0) )
    {
      v18._M_node = std::map<int,int>::end(&this->m_VipEquipPosLevelMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v18) )
        break;
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
      v6 = Answer::Singleton<CfgData>::instance();
      pCfg_0 = CfgData::GetVipEquipPosLevelUp(v6, first, second);
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first >= 0
        && std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first <= 92 )
      {
        v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
        v9 = Player::GetEquip(this->m_pPlayer);
        Equip = *(_QWORD *)&CExtEquip::GetEquipSlot(v9, v8)->itemId;
        if ( pCfg_0 )
        {
          if ( (int)Equip > 0 )
          {
            std::list<AddAttribute>::list(&AddAttrs, &pCfg_0->lAddAttrs);
            for ( it_0._M_node = std::list<AddAttribute>::begin(&AddAttrs)._M_node;
                  ;
                  std::_List_iterator<AddAttribute>::operator++(&it_0, 0) )
            {
              v19._M_node = std::list<AddAttribute>::end(&AddAttrs)._M_node;
              if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &v19) )
                break;
              v10 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
              v11 = std::_List_iterator<AddAttribute>::operator->(&it_0);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v11->m_nAddAttrType, v10);
            }
            std::list<AddAttribute>::~list(&AddAttrs);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CGoblin::SendVipEquipPosLevelInfo(CGoblin *const this, int32_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CGoblin *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  nSlota = nSlot;
  if ( this->m_pPlayer )
  {
    if ( IsVipEquipSlot(nSlota) )
    {
      it._M_node = std::map<int,int>::find(&thisa->m_VipEquipPosLevelMap, &nSlota)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_VipEquipPosLevelMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v3 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D2Au);
        if ( packet )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->first);
          v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(thisa->m_pPlayer);
          v8 = Player::getConnId(thisa->m_pPlayer);
          v9 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v9, v8, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CGoblin::GetVipEquipPosLevelSuitId(CGoblin *const this)
{
  int32_t second; // r12d
  int32_t v2; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Start; // [rsp+2Ch] [rbp-24h]
  int32_t End; // [rsp+30h] [rbp-20h]
  int32_t SuitId; // [rsp+34h] [rbp-1Ch]
  const VipEquipPosLevelUp *pCfg; // [rsp+38h] [rbp-18h]

  Start = 81;
  End = 86;
  SuitId = 0;
  for ( i = 81; i <= End; ++i )
  {
    it._M_node = std::map<int,int>::find(&this->m_VipEquipPosLevelMap, &i)._M_node;
    __x._M_node = std::map<int,int>::end(&this->m_VipEquipPosLevelMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      return 0;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v2 = i;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetVipEquipPosLevelUp(v3, v2, second);
    if ( !pCfg )
      return 0;
    if ( pCfg->nLevel <= 0 )
      return 0;
    if ( SuitId )
    {
      if ( pCfg->nLevel < SuitId )
        SuitId = pCfg->nLevel;
    }
    else
    {
      SuitId = pCfg->nLevel;
    }
  }
  return SuitId;
}


#####################################
int32_t __cdecl CGoblin::OnVipEquipPosLevellUp(CGoblin *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // r13d
  int32_t v4; // r12d
  CfgData *v5; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *v8; // rax
  ItemData *v9; // rax
  ItemData *v10; // rax
  ItemData *v11; // rax
  int32_t v12; // r13d
  int8_t v13; // r12
  CfgData *v14; // rax
  int v15; // r12d
  std::_List_iterator<ItemData> v16; // rax
  int64_t Currency; // rax
  CExtCharBag *v19; // rax
  ItemDataList *p_lCostItems; // rbx
  CExtCharBag *Bag; // rax
  CExtCharBag *v25; // rax
  Answer::Random *v26; // rax
  uint16_t v27; // r13
  int16_t v28; // r12
  int8_t v29; // bl
  GameService *v30; // rax
  int *v31; // rax
  CfgData *v32; // rax
  CfgData *v33; // rax
  int32_t TalentLevel; // r12d
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t v37; // r12d
  int32_t v38; // ebx
  CExtCharSkill *v39; // rax
  GameService *v40; // rax
  CharId_t Cid; // rax
  int *v42; // rax
  uint32_t WOffset; // eax
  GameService *v44; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v48; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-C0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-B0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-A0h] BYREF
  int __k; // [rsp+4Ch] [rbp-84h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-80h] BYREF
  int v55; // [rsp+5Ch] [rbp-74h] BYREF
  std::string val; // [rsp+60h] [rbp-70h] BYREF
  int v57; // [rsp+68h] [rbp-68h] BYREF
  int8_t nSlot; // [rsp+6Eh] [rbp-62h]
  int8_t AutoBuy; // [rsp+6Fh] [rbp-61h]
  const VipEquipPosLevelUp *pCfg; // [rsp+70h] [rbp-60h]
  int32_t OldSuitId; // [rsp+78h] [rbp-58h]
  int32_t nRand; // [rsp+7Ch] [rbp-54h]
  int32_t SuitId; // [rsp+80h] [rbp-50h]
  int32_t nCostGold; // [rsp+84h] [rbp-4Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-48h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-44h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-40h]
  const VipEQuipPosSuit *pCfg_0; // [rsp+98h] [rbp-38h]
  const VipEQuipPosSuit *OldCfg; // [rsp+A0h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+A8h] [rbp-28h]

  if ( inPacket && this->m_pPlayer )
  {
    nSlot = Answer::NetPacket::readInt8(inPacket);
    AutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( !IsVipEquipSlot(nSlot) )
    {
      v2 = 2;
    }
    else
    {
      __k = nSlot;
      v3 = *std::map<int,int>::operator[](&this->m_VipEquipPosLevelMap, &__k) + 1;
      v4 = nSlot;
      v5 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetVipEquipPosLevelUp(v5, v4, v3);
      if ( pCfg )
      {
        if ( AutoBuy <= 0 )
        {
          if ( !std::list<ItemData>::empty(&pCfg->lCostItems) )
          {
            p_lCostItems = &pCfg->lCostItems;
            Bag = Player::GetBag(this->m_pPlayer);
            if ( !CExtCharBag::RemoveItem(Bag, p_lCostItems, ITEM_CHANGE_REASON::IDCR_VIP_EQUIP_LEVEL_UP) )
            {
              v2 = 10002;
              goto LABEL_63;
            }
          }
        }
        else
        {
          nCostGold = 0;
          std::list<ItemData>::list(&costItemList, &pCfg->lCostItems);
          iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
          while ( 1 )
          {
            __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
            if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
              break;
            nBuyCount = 0;
            m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
            m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
            v8 = Player::GetBag(this->m_pPlayer);
            nItemCount = CExtCharBag::GetItemCount(v8, &vSlot, m_nClass, m_nId);
            v9 = std::_List_iterator<ItemData>::operator->(&iter);
            if ( v9->m_nCount > nItemCount )
            {
              v10 = std::_List_iterator<ItemData>::operator->(&iter);
              nBuyCount = v10->m_nCount - nItemCount;
              v11 = std::_List_iterator<ItemData>::operator->(&iter);
              v11->m_nCount = nItemCount;
            }
            if ( nBuyCount > 0 )
            {
              v12 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
              v13 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
              v14 = Answer::Singleton<CfgData>::instance();
              pCfgGameShop = CfgData::GetGameShopItem(v14, v13, v12);
              if ( !pCfgGameShop )
              {
                v2 = 2;
                v15 = 0;
                goto LABEL_39;
              }
              nCostGold += nBuyCount * pCfgGameShop->Price;
            }
            if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
            {
              std::_List_iterator<ItemData>::operator++(&iter);
            }
            else
            {
              v16._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
              std::list<ItemData>::erase(&costItemList, v16);
            }
          }
          if ( nCostGold > 0
            && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
          {
            v2 = 10002;
            v15 = 0;
          }
          else if ( !std::list<ItemData>::empty(&costItemList)
                 && (v19 = Player::GetBag(this->m_pPlayer),
                     !CExtCharBag::RemoveItem(v19, &vSlot, &costItemList, ITEM_CHANGE_REASON::IDCR_VIP_EQUIP_LEVEL_UP)) )
          {
            v2 = 10002;
            v15 = 0;
          }
          else if ( nCostGold > 0
                 && !Player::DecCurrency(
                       this->m_pPlayer,
                       CURRENCY_TYPE::CURRENCY_GOLD,
                       nCostGold,
                       CURRENCY_CHANGE_REASON::GCR_VIP_EQUIP_LEVEL_UP,
                       0) )
          {
            v2 = 10002;
            v15 = 0;
          }
          else
          {
            v15 = 1;
          }
LABEL_39:
          std::list<ItemData>::~list(&costItemList);
          if ( !v15 )
            goto LABEL_63;
        }
        OldSuitId = CGoblin::GetVipEquipPosLevelSuitId(this);
        v25 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::ForceSendDirty(v25);
        v26 = Answer::Singleton<Answer::Random>::instance();
        nRand = Answer::Random::generate(v26, 1, 10000);
        if ( pCfg->nRate >= nRand )
        {
          v55 = nSlot;
          v31 = std::map<int,int>::operator[](&this->m_VipEquipPosLevelMap, &v55);
          ++*v31;
          CGoblin::SendVipEquipPosLevelInfo(this, nSlot);
          SuitId = CGoblin::GetVipEquipPosLevelSuitId(this);
          if ( SuitId != OldSuitId )
          {
            v32 = Answer::Singleton<CfgData>::instance();
            pCfg_0 = CfgData::GetVipEQuipPosSuit(v32, SuitId);
            v33 = Answer::Singleton<CfgData>::instance();
            OldCfg = CfgData::GetVipEQuipPosSuit(v33, OldSuitId);
            if ( OldCfg && OldCfg->nTalentId > 0 && OldCfg->TalentLevel > 0 )
            {
              TalentLevel = OldCfg->TalentLevel;
              nTalentId = OldCfg->nTalentId;
              CharSkill = Player::GetCharSkill(this->m_pPlayer);
              CExtCharSkill::removeSkillByTalent(CharSkill, nTalentId, TalentLevel);
            }
            if ( pCfg_0 && pCfg_0->nTalentId > 0 && pCfg_0->TalentLevel > 0 )
            {
              v37 = pCfg_0->TalentLevel;
              v38 = pCfg_0->nTalentId;
              v39 = Player::GetCharSkill(this->m_pPlayer);
              CExtCharSkill::AddOtherSkill(v39, v38, v37);
            }
          }
          Player::RecalcAttr(this->m_pPlayer);
          if ( pCfg->nGongGaoId > 0 )
          {
            v40 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v40, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v2 = 10002;
              goto LABEL_63;
            }
            Answer::NetPacket::writeInt32(packet, pCfg->nGongGaoId);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Answer::NetPacket::writeInt8(packet, nSlot);
            v57 = nSlot;
            v42 = std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &v57);
            Answer::NetPacket::writeInt32(packet, *v42);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v44 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v44, 0, packet);
          }
          Proc = Answer::NetPacket::getProc(inPacket);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          ConnId = Player::getConnId(this->m_pPlayer);
          v48 = Answer::Singleton<GameService>::instance();
          v2 = GameService::replySuccess(v48, ConnId, GateIndex, Proc, 0);
          goto LABEL_63;
        }
        v27 = Answer::NetPacket::getProc(inPacket);
        v28 = Player::getGateIndex(this->m_pPlayer);
        v29 = Player::getConnId(this->m_pPlayer);
        v30 = Answer::Singleton<GameService>::instance();
        v2 = GameService::replyfailure(v30, v29, v28, v27, 0, 0);
      }
      else
      {
        v2 = 2;
      }
    }
LABEL_63:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


