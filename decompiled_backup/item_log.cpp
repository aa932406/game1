// Decompiled methods for class: item_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl item_log::~item_log(item_log *const this)
{
  item_log::~item_log(this);
  operator delete(this);
}


#####################################
void __cdecl item_log::CleanUp(item_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, &unk_8C2140);
  this->cid = 0;
  std::string::operator=(&this->name, &unk_8C2140);
  this->op_time = 0;
  std::string::operator=(&this->ItemId, &unk_8C2140);
  this->flag = 0;
  this->opway = 0;
  this->count = 0;
  this->level = 0;
}


#####################################
void __cdecl item_log::PackageData(item_log *const this, Answer::NetPacket *packet)
{
  platform_log_base::PackageData(this, packet);
  Answer::NetPacket::writeUTF8(packet, &this->passport);
  Answer::NetPacket::writeInt64(packet, this->cid);
  Answer::NetPacket::writeUTF8(packet, &this->name);
  Answer::NetPacket::writeInt32(packet, this->op_time);
  Answer::NetPacket::writeUTF8(packet, &this->ItemId);
  Answer::NetPacket::writeInt32(packet, this->flag);
  Answer::NetPacket::writeInt32(packet, this->opway);
  Answer::NetPacket::writeInt32(packet, this->count);
  Answer::NetPacket::writeInt32(packet, this->level);
}


#####################################
void __cdecl item_log::UnPackageData(item_log *const this, Answer::NetPacket *inPacket)
{
  Answer::NetPacket v2; // [rsp+10h] [rbp-40h] BYREF

  platform_log_base::UnPackageData(this, inPacket);
  Answer::NetPacket::readUTF8(&v2, (bool)inPacket);
  std::string::operator=(&this->passport, &v2);
  std::string::~string(&v2);
  this->cid = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->name, &v2.m_wOffset);
  std::string::~string(&v2.m_wOffset);
  this->op_time = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_size, (bool)inPacket);
  std::string::operator=(&this->ItemId, &v2.m_size);
  std::string::~string(&v2.m_size);
  this->flag = Answer::NetPacket::readInt32(inPacket);
  this->opway = Answer::NetPacket::readInt32(inPacket);
  this->count = Answer::NetPacket::readInt32(inPacket);
  this->level = Answer::NetPacket::readInt32(inPacket);
}


