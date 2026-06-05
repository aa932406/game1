// Decompiled methods for class: log_abnormal
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl log_abnormal::PackageData(log_abnormal *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->nCid);
    Answer::NetPacket::writeUTF8(packet, &this->sName);
    Answer::NetPacket::writeInt8(packet, this->nType);
    Answer::NetPacket::writeInt32(packet, this->nValue);
    Answer::NetPacket::writeInt32(packet, this->nOpway);
  }
}


