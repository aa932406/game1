// Decompiled methods for class: BlessWater1
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl BlessWater1::~BlessWater1(BlessWater1 *const this)
{
  BlessWater1::~BlessWater1(this);
  operator delete(this);
}


#####################################
int32_t __cdecl BlessWater1::effect(
        BlessWater1 *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  CExtEquip *Equip; // rax
  const MemChrBag *EquipSlot; // rax
  CExtEquip *v7; // rax
  CfgData *v8; // rax
  const CfgEquipBlessTable *EquipBlessTable; // rax
  CfgData *v10; // rax
  const CfgEquipBlessTable *v11; // rax
  CExtEquip *v12; // rax
  CfgData *v13; // rax
  const CfgEquipBlessTable *v14; // rax
  int8_t ConnId; // bl
  GameService *v16; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v19; // bl
  GameService *v20; // rax
  CExtEquip *v21; // rax
  int8_t v22; // bl
  GameService *v23; // rax
  uint32_t v24; // eax
  int16_t GateIndex; // r12
  int8_t v26; // bl
  GameService *v27; // rax
  __int64 weapon; // [rsp+20h] [rbp-70h]
  int64_t weapon_24; // [rsp+38h] [rbp-58h]
  std::string val; // [rsp+40h] [rbp-50h] BYREF
  int32_t nBless; // [rsp+54h] [rbp-3Ch]
  const CfgEquipBless *pCfgBless; // [rsp+60h] [rbp-30h]
  int8_t nEffect; // [rsp+6Fh] [rbp-21h]
  Answer::NetPacket *packet; // [rsp+70h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+78h] [rbp-18h]

  Equip = Player::GetEquip(launcher);
  EquipSlot = CExtEquip::GetEquipSlot(Equip, 0);
  weapon = *(_QWORD *)&EquipSlot->itemId;
  weapon_24 = EquipSlot->srcId;
  if ( (int)*(_QWORD *)&EquipSlot->itemId <= 0 )
    return 10002;
  v7 = Player::GetEquip(launcher);
  nBless = CExtEquip::GetWeaponBless(v7);
  v8 = Answer::Singleton<CfgData>::instance();
  EquipBlessTable = CfgData::GetEquipBlessTable(v8);
  if ( !CfgEquipBlessTable::GetInfo(EquipBlessTable, nBless + 1) )
    return 10002;
  v10 = Answer::Singleton<CfgData>::instance();
  v11 = CfgData::GetEquipBlessTable(v10);
  pCfgBless = CfgEquipBlessTable::GetInfo(v11, nBless);
  if ( !pCfgBless )
    return 10002;
  nEffect = CfgEquipBless::RandomEffect(pCfgBless);
  if ( nEffect == 1 )
  {
    ++nBless;
    v12 = Player::GetEquip(launcher);
    CExtEquip::SetWeaponBless(v12, nBless);
    v13 = Answer::Singleton<CfgData>::instance();
    v14 = CfgData::GetEquipBlessTable(v13);
    pCfgBless = CfgEquipBlessTable::GetInfo(v14, nBless);
    if ( !pCfgBless )
      return 10002;
    if ( pCfgBless->nBroad > 0 )
    {
      ConnId = Player::getConnId(launcher);
      v16 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v16, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet_0 )
      {
        Answer::NetPacket::writeInt32(packet_0, pCfgBless->nBroad);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet_0, &val);
        std::string::~string(&val);
        Cid = Player::getCid(launcher);
        Answer::NetPacket::writeInt64(packet_0, Cid);
        Answer::NetPacket::writeInt32(packet_0, this->m_nId);
        Answer::NetPacket::writeInt32(packet_0, weapon);
        Answer::NetPacket::writeInt64(packet_0, weapon_24);
        Answer::NetPacket::writeInt32(packet_0, nBless);
        WOffset = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, WOffset);
        v19 = Player::getConnId(launcher);
        v20 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v20, v19, packet_0);
      }
    }
  }
  else if ( nEffect == 2 )
  {
    --nBless;
    v21 = Player::GetEquip(launcher);
    CExtEquip::SetWeaponBless(v21, nBless);
  }
  else if ( nEffect )
  {
    return 10002;
  }
  v22 = Player::getConnId(launcher);
  v23 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v23, v22, Answer::PackType::PACK_DISPATCH, 0x274Eu);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    Answer::NetPacket::writeInt8(packet, nEffect);
    Answer::NetPacket::writeInt32(packet, nBless);
    v24 = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, v24);
    GateIndex = Player::getGateIndex(launcher);
    v26 = Player::getConnId(launcher);
    v27 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v27, v26, GateIndex, packet);
  }
  return 0;
}


#####################################
bool __cdecl BlessWater1::parseEffect(BlessWater1 *const this, int32_t id, const std::string *const strEffect)
{
  this->m_nId = id;
  return 1;
}


