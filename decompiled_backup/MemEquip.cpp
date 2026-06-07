// Decompiled methods for class: MemEquip
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl MemEquip::CleanUp(MemEquip *const this)
{
  this->id = 0;
  this->base = 0;
  this->owner = 0;
  this->star = 0;
  std::string::operator=(&this->name, &unk_8CA480);
  this->time = 0;
  this->MapId = 0;
  this->Mid = 0;
  this->Lucky = 0;
}


#####################################
void __cdecl MemEquip::PackageData(const MemEquip *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->id);
    Answer::NetPacket::writeInt32(packet, this->base);
    Answer::NetPacket::writeInt64(packet, this->owner);
    Answer::NetPacket::writeInt8(packet, this->star);
    Answer::NetPacket::writeInt32(packet, this->MapId);
    Answer::NetPacket::writeInt32(packet, this->Mid);
    Answer::NetPacket::writeInt32(packet, this->time);
    Answer::NetPacket::writeUTF8(packet, &this->name);
    Answer::NetPacket::writeInt32(packet, this->Lucky);
  }
}


#####################################
void __cdecl MemEquip::UnPackageData(MemEquip *const this, Answer::NetPacket *inPacket)
{
  _BYTE v2[32]; // [rsp+10h] [rbp-20h] BYREF

  if ( inPacket )
  {
    this->id = Answer::NetPacket::readInt64(inPacket);
    this->base = Answer::NetPacket::readInt32(inPacket);
    this->owner = Answer::NetPacket::readInt64(inPacket);
    this->star = Answer::NetPacket::readInt8(inPacket);
    this->MapId = Answer::NetPacket::readInt32(inPacket);
    this->Mid = Answer::NetPacket::readInt32(inPacket);
    this->time = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v2, (bool)inPacket);
    std::string::operator=(&this->name, v2);
    std::string::~string(v2);
    this->Lucky = Answer::NetPacket::readInt32(inPacket);
  }
}


#####################################
void __cdecl MemEquip::PackageClientData(const MemEquip *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->id);
    Answer::NetPacket::writeInt32(packet, this->base);
    Answer::NetPacket::writeInt8(packet, this->star);
    Answer::NetPacket::writeInt32(packet, this->MapId);
    Answer::NetPacket::writeInt32(packet, this->Mid);
    Answer::NetPacket::writeInt32(packet, this->time);
    Answer::NetPacket::writeUTF8(packet, &this->name);
    Answer::NetPacket::writeInt32(packet, this->Lucky);
  }
}


