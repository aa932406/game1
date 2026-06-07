// Decompiled methods for class: important_system_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl important_system_log::~important_system_log(important_system_log *const this)
{
  important_system_log::~important_system_log(this);
  operator delete(this);
}


#####################################
void __cdecl important_system_log::CleanUp(important_system_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, &unk_8CB200);
  this->cid = 0;
  std::string::operator=(&this->name, &unk_8CB200);
  this->up_time = 0;
  this->sys_name = 0;
  this->oper_id = 0;
  this->level = 0;
}


#####################################
void __cdecl important_system_log::PackageData(important_system_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->up_time);
  Answer::NetPacket::writeInt32(packet, this->sys_name);
  Answer::NetPacket::writeInt32(packet, this->oper_id);
  Answer::NetPacket::writeInt32(packet, this->level);
}


#####################################
void __cdecl important_system_log::UnPackageData(important_system_log *const this, Answer::NetPacket *inPacket)
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
  this->up_time = Answer::NetPacket::readInt32(inPacket);
  this->sys_name = Answer::NetPacket::readInt32(inPacket);
  this->oper_id = Answer::NetPacket::readInt32(inPacket);
  this->level = Answer::NetPacket::readInt32(inPacket);
}


