// Decompiled methods for class: CRongLian
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CRongLian::~CRongLian(CRongLian *const this)
{
  CRongLian::~CRongLian(this);
  operator delete(this);
}


#####################################
void __cdecl CRongLian::broadcastStart(CRongLian *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 522);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CRongLian::sendPlayerScore(CRongLian *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E26u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      LeftTime = CActivity::getLeftTime(this);
      Answer::NetPacket::writeInt32(packet, LeftTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


