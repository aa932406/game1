// Decompiled methods for class: ShowIcon
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl ShowIcon::AppendInfo(const ShowIcon *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt32(packet, this->nId);
  Answer::NetPacket::writeInt8(packet, this->nState);
  Answer::NetPacket::writeInt32(packet, this->nLeftTime);
  Answer::NetPacket::writeInt8(packet, this->nIconLeft);
  Answer::NetPacket::writeInt32(packet, this->nIconRight);
  Answer::NetPacket::writeInt8(packet, this->nEffects);
}


