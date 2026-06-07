// Decompiled methods for class: MGLog
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl MGLog::PackageData(const MGLog *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->Cid);
    Answer::NetPacket::writeInt32(packet, this->MingGeId);
    Answer::NetPacket::writeInt8(packet, this->Flag);
    Answer::NetPacket::writeInt32(packet, this->BagType);
    Answer::NetPacket::writeInt32(packet, this->Reason);
    Answer::NetPacket::writeInt32(packet, this->Time);
  }
}


