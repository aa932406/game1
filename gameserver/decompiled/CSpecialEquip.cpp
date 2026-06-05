// Decompiled methods for class: CSpecialEquip
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CSpecialEquip::~CSpecialEquip(CSpecialEquip *const this)
{
  CSpecialEquip::~CSpecialEquip(this);
  operator delete(this);
}


#####################################
void __cdecl CSpecialEquip::GetInterestsProtocol(CSpecialEquip *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 265;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 266;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CSpecialEquip::DispatchNetDatas(
        CSpecialEquip *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 265 )
    return CSpecialEquip::OnActivation(this, inPacket);
  if ( nProcId != 266 )
    return 2;
  CSpecialEquip::SendActivationInfo(this);
  return 0;
}


#####################################
void __cdecl CSpecialEquip::InitSkill(CSpecialEquip *const this)
{
  CfgData *v1; // rax
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int Reocrd; // [rsp+10h] [rbp-20h]
  __int64 i; // [rsp+14h] [rbp-1Ch]
  SpeciaEquipCfg *pCfg; // [rsp+18h] [rbp-18h]

  Reocrd = Player::getRecord(this->m_pPlayer, 1149);
  LODWORD(i) = 0;
  while ( (int)i <= 6 )
  {
    if ( ((Reocrd >> i) & 1) == 0 )
      goto LABEL_6;
    v1 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetSpeciaEquipCfg(v1, (int)i + 1);
    if ( pCfg )
    {
      nTalentId = pCfg->nTalentId;
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(CharSkill, nTalentId, 1);
LABEL_6:
      LODWORD(i) = i + 1;
    }
    else
    {
      i = (unsigned int)(i + 1);
    }
  }
}


#####################################
bool __cdecl CSpecialEquip::IsActivation(CSpecialEquip *const this, int32_t Day)
{
  return ((Player::getRecord(this->m_pPlayer, 1149) >> (Day - 1)) & 1) == 1;
}


#####################################
void __cdecl CSpecialEquip::GetSpecialEquipIcon(CSpecialEquip *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 181) )
    {
      CSpecialEquip::GetSpecialEquipIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CSpecialEquip::SendSpecialEquipIcon(CSpecialEquip *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    CSpecialEquip::GetSpecialEquipIcon(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
int32_t __cdecl CSpecialEquip::CanActivationCount(CSpecialEquip *const this)
{
  CfgData *v1; // rax
  CVip *v2; // rax
  CVip *PlayerVip; // rax
  int32_t Count; // [rsp+1Ch] [rbp-24h]
  int Reocrd; // [rsp+20h] [rbp-20h]
  __int64 i; // [rsp+24h] [rbp-1Ch]
  SpeciaEquipCfg *pCfg; // [rsp+28h] [rbp-18h]

  Count = 0;
  Reocrd = Player::getRecord(this->m_pPlayer, 1149);
  LODWORD(i) = 0;
  while ( (int)i <= 6 )
  {
    if ( ((Reocrd >> i) & 1) != 0 )
      goto LABEL_14;
    v1 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetSpeciaEquipCfg(v1, (int)i + 1);
    if ( pCfg )
    {
      if ( pCfg->nContinueLogin <= 0 || Player::getRecord(this->m_pPlayer, 1011) < pCfg->nContinueLogin )
      {
        if ( pCfg->nNeedVipLevel <= 0
          || (v2 = Player::GetPlayerVip(this->m_pPlayer), CVip::GetVipLevel(v2) < pCfg->nNeedVipLevel) )
        {
          if ( pCfg->nBuyLimitVipLevel <= 0
            || (PlayerVip = Player::GetPlayerVip(this->m_pPlayer), CVip::GetVipLevel(PlayerVip) < pCfg->nBuyLimitVipLevel) )
          {
LABEL_14:
            LODWORD(i) = i + 1;
          }
          else
          {
            LODWORD(i) = i + 1;
            ++Count;
          }
        }
        else
        {
          LODWORD(i) = i + 1;
          ++Count;
        }
      }
      else
      {
        LODWORD(i) = i + 1;
        ++Count;
      }
    }
    else
    {
      i = (unsigned int)(i + 1);
    }
  }
  return Count;
}


#####################################
int32_t __cdecl CSpecialEquip::OnActivation(CSpecialEquip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  GameService *v6; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v9; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  int32_t nIndex; // [rsp+24h] [rbp-2Ch]
  int32_t OldRecord; // [rsp+28h] [rbp-28h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-24h]
  SpeciaEquipCfg *pCfg; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  OldRecord = Player::getRecord(this->m_pPlayer, 1149);
  NewRecord = OldRecord | (1 << (nIndex - 1));
  if ( OldRecord == NewRecord )
    return 10002;
  if ( !CSpecialEquip::CanActivation(this, nIndex) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1149, NewRecord);
  CSpecialEquip::SendActivationInfo(this);
  Player::RecalcAttr(this->m_pPlayer);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetSpeciaEquipCfg(v3, nIndex);
  if ( !pCfg )
    return 0;
  nTalentId = pCfg->nTalentId;
  CharSkill = Player::GetCharSkill(this->m_pPlayer);
  CExtCharSkill::AddOtherSkill(CharSkill, nTalentId, 1);
  if ( pCfg->nGongGaoId > 0 )
  {
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 10002;
    Answer::NetPacket::writeInt32(packet, pCfg->nGongGaoId);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, nIndex);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, 0, packet);
  }
  CSpecialEquip::SendSpecialEquipIcon(this);
  return 0;
}


#####################################
bool __cdecl CSpecialEquip::CanActivation(CSpecialEquip *const this, int32_t nIndex)
{
  CfgData *v3; // rax
  CVip *PlayerVip; // rax
  CVip *v5; // rax
  bool v6; // al
  SpeciaEquipCfg *pCfg; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetSpeciaEquipCfg(v3, nIndex);
  if ( !pCfg )
    return 0;
  if ( pCfg->nContinueLogin > 0 && Player::getRecord(this->m_pPlayer, 1011) >= pCfg->nContinueLogin )
    return 1;
  if ( pCfg->nNeedVipLevel > 0 )
  {
    PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipLevel(PlayerVip) >= pCfg->nNeedVipLevel )
      return 1;
  }
  v6 = 0;
  if ( pCfg->nNeedGold > 0 )
  {
    v5 = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipLevel(v5) >= pCfg->nBuyLimitVipLevel )
      v6 = 1;
  }
  return v6
      && Player::DecCurrency(
           this->m_pPlayer,
           CURRENCY_TYPE::CURRENCY_GOLD,
           pCfg->nNeedGold,
           CURRENCY_CHANGE_REASON::GCR_ACT_SPECIAL_EQUIP,
           0);
}


#####################################
void __cdecl CSpecialEquip::SendActivationInfo(CSpecialEquip *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D37u);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1011);
      Answer::NetPacket::writeInt32(packet, Record);
      v4 = Player::getRecord(this->m_pPlayer, 1149);
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


