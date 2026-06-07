// Decompiled methods for class: currency_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl currency_log::~currency_log(currency_log *const this)
{
  currency_log::~currency_log(this);
  operator delete(this);
}


#####################################
void __cdecl currency_log::CleanUp(currency_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, &unk_8CEA00);
  this->cid = 0;
  std::string::operator=(&this->name, &unk_8CEA00);
  this->time = 0;
  this->type = 0;
  this->opway = 0;
  this->value = 0;
  std::string::operator=(&this->ids, &unk_8CEA00);
  std::string::operator=(&this->couts, &unk_8CEA00);
  this->level = 0;
}


#####################################
void __cdecl currency_log::PackageData(currency_log *const this, Answer::NetPacket *packet)
{
  __int64 v2; // rax
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 v5; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  char v7; // [rsp+1Fh] [rbp-41h] BYREF
  std::string v8; // [rsp+20h] [rbp-40h] BYREF
  char v9; // [rsp+2Fh] [rbp-31h] BYREF
  std::string v10; // [rsp+30h] [rbp-30h] BYREF
  char v11; // [rsp+3Fh] [rbp-21h] BYREF
  std::string v12; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v13[17]; // [rsp+4Fh] [rbp-11h] BYREF

  platform_log_base::PackageData(this, packet);
  std::allocator<char>::allocator(&v7);
  v2 = std::string::c_str(&this->passport);
  std::string::string(&val, v2, &v7);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v7);
  Answer::NetPacket::writeInt64(packet, this->cid);
  std::allocator<char>::allocator(&v9);
  v3 = std::string::c_str(&this->name);
  std::string::string(&v8, v3, &v9);
  Answer::NetPacket::writeUTF8(packet, &v8);
  std::string::~string(&v8);
  std::allocator<char>::~allocator(&v9);
  Answer::NetPacket::writeInt32(packet, this->time);
  Answer::NetPacket::writeInt8(packet, this->type);
  Answer::NetPacket::writeInt32(packet, this->opway);
  Answer::NetPacket::writeInt64(packet, this->value);
  std::allocator<char>::allocator(&v11);
  v4 = std::string::c_str(&this->ids);
  std::string::string(&v10, v4, &v11);
  Answer::NetPacket::writeUTF8(packet, &v10);
  std::string::~string(&v10);
  std::allocator<char>::~allocator(&v11);
  std::allocator<char>::allocator(v13);
  v5 = std::string::c_str(&this->couts);
  std::string::string(&v12, v5, v13);
  Answer::NetPacket::writeUTF8(packet, &v12);
  std::string::~string(&v12);
  std::allocator<char>::~allocator(v13);
  Answer::NetPacket::writeInt32(packet, this->level);
}


#####################################
void __cdecl currency_log::UnPackageData(currency_log *const this, Answer::NetPacket *inPacket)
{
  Answer::NetPacket v2; // [rsp+10h] [rbp-50h] BYREF

  platform_log_base::UnPackageData(this, inPacket);
  Answer::NetPacket::readUTF8(&v2, (bool)inPacket);
  std::string::operator=(&this->passport, &v2);
  std::string::~string(&v2);
  this->cid = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->name, &v2.m_wOffset);
  std::string::~string(&v2.m_wOffset);
  this->time = Answer::NetPacket::readInt32(inPacket);
  this->type = Answer::NetPacket::readInt8(inPacket);
  this->opway = Answer::NetPacket::readInt32(inPacket);
  this->value = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_size, (bool)inPacket);
  std::string::operator=(&this->ids, &v2.m_size);
  std::string::~string(&v2.m_size);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_pool, (bool)inPacket);
  std::string::operator=(&this->couts, &v2.m_pool);
  std::string::~string(&v2.m_pool);
  this->level = Answer::NetPacket::readInt32(inPacket);
}


