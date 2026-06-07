// Decompiled methods for class: proc_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl proc_log::~proc_log(proc_log *const this)
{
  proc_log::~proc_log(this);
  operator delete(this);
}


#####################################
void __cdecl proc_log::CleanUp(proc_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, byte_8E9580);
  this->cid = 0;
  std::string::operator=(&this->name, byte_8E9580);
  this->proc_id = 0;
  this->op_time = 0;
}


#####################################
void __cdecl proc_log::PackageData(proc_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->op_time);
  Answer::NetPacket::writeInt32(packet, this->proc_id);
}


#####################################
void __cdecl proc_log::UnPackageData(proc_log *const this, Answer::NetPacket *inPacket)
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
  this->op_time = Answer::NetPacket::readInt32(inPacket);
  this->proc_id = Answer::NetPacket::readInt32(inPacket);
}


