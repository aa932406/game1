// Decompiled methods for class: main_task_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl main_task_log::~main_task_log(main_task_log *const this)
{
  main_task_log::~main_task_log(this);
  operator delete(this);
}


#####################################
void __cdecl main_task_log::CleanUp(main_task_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, &unk_8F1800);
  this->cid = 0;
  std::string::operator=(&this->name, &unk_8F1800);
  this->op_time = 0;
  this->task_id = 0;
  this->oper_id = 0;
}


#####################################
void __cdecl main_task_log::PackageData(main_task_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->op_time);
  Answer::NetPacket::writeInt32(packet, this->task_id);
  Answer::NetPacket::writeInt32(packet, this->oper_id);
}


#####################################
void __cdecl main_task_log::UnPackageData(main_task_log *const this, Answer::NetPacket *inPacket)
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
  this->task_id = Answer::NetPacket::readInt32(inPacket);
  this->oper_id = Answer::NetPacket::readInt32(inPacket);
}


