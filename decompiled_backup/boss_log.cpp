// Decompiled methods for class: boss_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl boss_log::~boss_log(boss_log *const this)
{
  boss_log::~boss_log(this);
  operator delete(this);
}


#####################################
void __cdecl boss_log::CleanUp(boss_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, &unk_8E6560);
  this->cid = 0;
  std::string::operator=(&this->name, &unk_8E6560);
  this->kill_time = 0;
  this->mid = 0;
  this->boss_id = 0;
}


#####################################
void __cdecl boss_log::PackageData(boss_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->kill_time);
  Answer::NetPacket::writeInt32(packet, this->mid);
  Answer::NetPacket::writeInt32(packet, this->boss_id);
}


#####################################
void __cdecl boss_log::UnPackageData(boss_log *const this, Answer::NetPacket *inPacket)
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
  this->kill_time = Answer::NetPacket::readInt32(inPacket);
  this->mid = Answer::NetPacket::readInt32(inPacket);
  this->boss_id = Answer::NetPacket::readInt32(inPacket);
}


