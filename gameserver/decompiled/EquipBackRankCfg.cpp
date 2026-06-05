// Decompiled methods for class: EquipBackRankCfg
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl EquipBackRankCfg::PackageData(EquipBackRankCfg *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->Cid);
    Answer::NetPacket::writeUTF8(packet, &this->nName);
    Answer::NetPacket::writeInt32(packet, this->Count);
    Answer::NetPacket::writeInt32(packet, this->Time);
  }
}


