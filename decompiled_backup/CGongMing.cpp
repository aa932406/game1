// Decompiled methods for class: CGongMing
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl CGongMing::~CGongMing(CGongMing *const this)
{
  CGongMing::~CGongMing(this);
  operator delete(this);
}


#####################################
void __cdecl CGongMing::GetInterestsProtocol(CGongMing *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 262;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CGongMing::DispatchNetDatas(CGongMing *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( nProcId == 262 )
    return CGongMing::OnGongMinLevelUp(this, inPacket);
  return 10002;
}


#####################################
void __cdecl CGongMing::AddCharAttr(CGongMing *const this)
{
  CfgData *v1; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t CurLevel; // [rsp+34h] [rbp-1Ch]
  GongMingCfg *CurCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CurLevel = Player::getRecord(this->m_pPlayer, 1161);
    v1 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetGongMingCfg(v1, CurLevel);
    if ( CurCfg )
    {
      for ( it._M_node = std::list<AddAttribute>::begin(&CurCfg->lAttrList)._M_node;
            ;
            std::_List_iterator<AddAttribute>::operator++(&it, 0) )
      {
        __x._M_node = std::list<AddAttribute>::end(&CurCfg->lAttrList)._M_node;
        if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
          break;
        m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
        v3 = std::_List_iterator<AddAttribute>::operator->(&it);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
      }
    }
  }
}


#####################################
void __cdecl CGongMing::AddGongMingValues(CGongMing *const this, int32_t Values)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( Values > 0 )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1162, Values);
    CGongMing::SendGongMinInfo(this);
  }
}


#####################################
int32_t __cdecl CGongMing::OnGongMinLevelUp(CGongMing *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgData *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v9; // bl
  GameService *v10; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  int32_t CurLevel; // [rsp+1Ch] [rbp-44h]
  GongMingCfg *CurCfg; // [rsp+20h] [rbp-40h]
  GongMingCfg *NextCfg; // [rsp+28h] [rbp-38h]
  int32_t HaveCurr; // [rsp+34h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CurLevel = Player::getRecord(this->m_pPlayer, 1161);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetGongMingCfg(v3, CurLevel);
  v4 = Answer::Singleton<CfgData>::instance();
  NextCfg = CfgData::GetGongMingCfg(v4, CurLevel + 1);
  HaveCurr = Player::getRecord(this->m_pPlayer, 1162);
  if ( !CurCfg || !NextCfg )
    return 10002;
  if ( CurCfg->NeedGongMingZhi > HaveCurr )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1162, HaveCurr - CurCfg->NeedGongMingZhi);
  Player::updateRecord(this->m_pPlayer, 1161, CurLevel + 1);
  if ( NextCfg->GongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 10002;
    Answer::NetPacket::writeInt32(packet, NextCfg->GongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, NextCfg->nChong);
    Answer::NetPacket::writeInt32(packet, NextCfg->nStar);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v9 = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v10, v9, packet);
  }
  Player::RecalcAttr(this->m_pPlayer);
  CGongMing::SendGongMinInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v13 = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v14, v13, GateIndex, Proc, 0);
}


#####################################
void __cdecl CGongMing::SendGongMinInfo(CGongMing *const this)
{
  CfgData *v1; // rax
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  int32_t HaveCurr; // [rsp+18h] [rbp-28h]
  int32_t CurLevel; // [rsp+1Ch] [rbp-24h]
  GongMingCfg *CurCfg; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  HaveCurr = Player::getRecord(this->m_pPlayer, 1162);
  CurLevel = Player::getRecord(this->m_pPlayer, 1161);
  v1 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetGongMingCfg(v1, CurLevel);
  if ( CurCfg )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DCCu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, CurCfg->nChong);
      Answer::NetPacket::writeInt32(packet, CurCfg->nStar);
      Answer::NetPacket::writeInt32(packet, HaveCurr);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


