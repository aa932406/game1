// Decompiled methods for class: BlessWater2
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl BlessWater2::~BlessWater2(BlessWater2 *const this)
{
  BlessWater2::~BlessWater2(this);
  operator delete(this);
}


#####################################
int32_t __cdecl BlessWater2::effect(
        BlessWater2 *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  CExtEquip *Equip; // rax
  const MemChrBag *EquipSlot; // rax
  CExtEquip *v7; // rax
  CfgData *v8; // rax
  const CfgEquipBlessTable *EquipBlessTable; // rax
  int8_t ConnId; // bl
  GameService *v11; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v14; // bl
  GameService *v15; // rax
  CExtEquip *v16; // rax
  int8_t v17; // bl
  GameService *v18; // rax
  uint32_t v19; // eax
  int16_t GateIndex; // r12
  int8_t v21; // bl
  GameService *v22; // rax
  __int64 weapon; // [rsp+20h] [rbp-60h]
  int64_t weapon_24; // [rsp+38h] [rbp-48h]
  std::string val; // [rsp+40h] [rbp-40h] BYREF
  int32_t nBless; // [rsp+54h] [rbp-2Ch]
  const CfgEquipBless *pCfgBless; // [rsp+58h] [rbp-28h]
  Answer::NetPacket *packet; // [rsp+60h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+68h] [rbp-18h]

  Equip = Player::GetEquip(launcher);
  EquipSlot = CExtEquip::GetEquipSlot(Equip, 0);
  weapon = *(_QWORD *)&EquipSlot->itemId;
  weapon_24 = EquipSlot->srcId;
  if ( (int)*(_QWORD *)&EquipSlot->itemId <= 0 )
    return 10002;
  v7 = Player::GetEquip(launcher);
  nBless = CExtEquip::GetWeaponBless(v7) + 1;
  v8 = Answer::Singleton<CfgData>::instance();
  EquipBlessTable = CfgData::GetEquipBlessTable(v8);
  pCfgBless = CfgEquipBlessTable::GetInfo(EquipBlessTable, nBless);
  if ( !pCfgBless )
    return 10002;
  if ( pCfgBless->nBroad > 0 )
  {
    ConnId = Player::getConnId(launcher);
    v11 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v11, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
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
      v14 = Player::getConnId(launcher);
      v15 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v15, v14, packet_0);
    }
  }
  v16 = Player::GetEquip(launcher);
  CExtEquip::SetWeaponBless(v16, nBless);
  v17 = Player::getConnId(launcher);
  v18 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v18, v17, Answer::PackType::PACK_DISPATCH, 0x274Eu);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    Answer::NetPacket::writeInt8(packet, 1);
    Answer::NetPacket::writeInt32(packet, nBless);
    v19 = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, v19);
    GateIndex = Player::getGateIndex(launcher);
    v21 = Player::getConnId(launcher);
    v22 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v22, v21, GateIndex, packet);
  }
  return 0;
}


#####################################
bool __cdecl BlessWater2::parseEffect(BlessWater2 *const this, int32_t id, const std::string *const strEffect)
{
  this->m_nId = id;
  return 1;
}


