// Decompiled methods for class: Npc
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl Npc::~Npc(Npc *const this)
{
  Npc::~Npc(this);
  operator delete(this);
}


#####################################
void __cdecl Npc::reset(Npc *const this)
{
  Unit::reset(this);
  this->m_nOwner = 0;
}


#####################################
bool __cdecl Npc::isLifeEnd(Npc *const this)
{
  return this->m_endTime > 0 && Unit::getNow(this) >= this->m_endTime;
}


#####################################
void __cdecl Npc::onTalkByPlayer(Npc *const this, Player *player)
{
  if ( player )
    Player::taskTalkWithNpc(player, this->m_cfgNpc.id);
}


#####################################
void __cdecl Npc::init(Npc *const this, const CfgNpc *const cfgNpc, int32_t EndTime)
{
  CfgNpc::operator=(&this->m_cfgNpc, cfgNpc);
  this->m_endTime = EndTime;
}


#####################################
bool __cdecl Npc::appendInfo(Npc *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx
  int32_t PosX; // edx
  int32_t PosY; // edx
  int64_t v7; // rdx

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(Npc *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  Answer::NetPacket::writeInt32(packet, this->m_cfgNpc.id);
  PosX = StaticObj::GetPosX(this);
  Answer::NetPacket::writeInt32(packet, PosX);
  PosY = StaticObj::GetPosY(this);
  Answer::NetPacket::writeInt32(packet, PosY);
  Answer::NetPacket::writeInt32(packet, 500000);
  Answer::NetPacket::writeInt32(packet, 500000);
  Answer::NetPacket::writeInt32(packet, 0);
  v7 = (*((__int64 (__fastcall **)(Npc *const))this->_vptr_Entity + 4))(this);
  Answer::NetPacket::writeInt64(packet, v7);
  return 1;
}


#####################################
bool __cdecl Npc::CheckcheckPlatform(Npc *const this, const std::string *const platform)
{
  return CfgNpc::checkPlatform(&this->m_cfgNpc, platform);
}


