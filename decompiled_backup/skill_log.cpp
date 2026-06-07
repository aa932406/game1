// Decompiled methods for class: skill_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl skill_log::~skill_log(skill_log *const this)
{
  skill_log::~skill_log(this);
  operator delete(this);
}


#####################################
void __cdecl skill_log::CleanUp(skill_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, byte_8CC180);
  this->cid = 0;
  std::string::operator=(&this->name, byte_8CC180);
  this->op_time = 0;
  this->skill_id = 0;
  this->oper_id = 0;
  this->level = 0;
}


#####################################
void __cdecl skill_log::PackageData(skill_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->op_time);
  Answer::NetPacket::writeInt32(packet, this->skill_id);
  Answer::NetPacket::writeInt32(packet, this->oper_id);
  Answer::NetPacket::writeInt32(packet, this->level);
}


#####################################
void __cdecl skill_log::UnPackageData(skill_log *const this, Answer::NetPacket *inPacket)
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
  this->skill_id = Answer::NetPacket::readInt32(inPacket);
  this->oper_id = Answer::NetPacket::readInt32(inPacket);
  this->level = Answer::NetPacket::readInt32(inPacket);
}


