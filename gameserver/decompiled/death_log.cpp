// Decompiled methods for class: death_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl death_log::~death_log(death_log *const this)
{
  death_log::~death_log(this);
  operator delete(this);
}


#####################################
void __cdecl death_log::CleanUp(death_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, byte_8E9580);
  this->cid = 0;
  std::string::operator=(&this->name, byte_8E9580);
  this->death_type = 0;
  this->death_time = 0;
  this->mapId = 0;
  this->level = 0;
  this->kill_id = 0;
}


#####################################
void __cdecl death_log::PackageData(death_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->death_type);
  Answer::NetPacket::writeInt32(packet, this->death_time);
  Answer::NetPacket::writeInt32(packet, this->mapId);
  Answer::NetPacket::writeInt64(packet, this->kill_id);
  Answer::NetPacket::writeInt32(packet, this->level);
  Answer::NetPacket::writeInt32(packet, this->x);
  Answer::NetPacket::writeInt32(packet, this->y);
}


#####################################
void __cdecl death_log::UnPackageData(death_log *const this, Answer::NetPacket *inPacket)
{
  _BYTE v2[16]; // [rsp+10h] [rbp-30h] BYREF
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  platform_log_base::UnPackageData(this, inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v2, (bool)inPacket);
  std::string::operator=(&this->passport, v2);
  std::string::~string(v2);
  this->cid = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
  std::string::operator=(&this->name, v3);
  std::string::~string(v3);
  this->death_type = Answer::NetPacket::readInt32(inPacket);
  this->death_time = Answer::NetPacket::readInt32(inPacket);
  this->mapId = Answer::NetPacket::readInt32(inPacket);
  this->kill_id = Answer::NetPacket::readInt64(inPacket);
  this->level = Answer::NetPacket::readInt32(inPacket);
  this->x = Answer::NetPacket::readInt32(inPacket);
  this->y = Answer::NetPacket::readInt32(inPacket);
}


