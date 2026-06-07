// Decompiled methods for class: online_user_24th_log
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl online_user_24th_log::~online_user_24th_log(online_user_24th_log *const this)
{
  online_user_24th_log::~online_user_24th_log(this);
  operator delete(this);
}


#####################################
void __cdecl online_user_24th_log::CleanUp(online_user_24th_log *const this)
{
  platform_log_base::CleanUp(this);
  std::string::operator=(&this->passport, byte_8E9580);
  this->cid = 0;
  std::string::operator=(&this->name, byte_8E9580);
  this->create_time = 0;
  this->login_time = 0;
  this->online_time = 0;
  std::string::operator=(&this->ip, byte_8E9580);
  this->job = 0;
  this->level = 0;
  this->battle = 0;
  this->huoyuedu = 0;
  this->map_id = 0;
  this->task_id = 0;
  this->recharge_sum = 0;
  this->gold = 0;
  this->cash = 0;
  this->money = 0;
  this->bind_money = 0;
}


#####################################
void __cdecl online_user_24th_log::PackageData(online_user_24th_log *const this, Answer::NetPacket *packet)
{
  __int64 v2; // rax
  __int64 v3; // rax
  __int64 v4; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  char v6; // [rsp+1Fh] [rbp-31h] BYREF
  std::string v7; // [rsp+20h] [rbp-30h] BYREF
  char v8; // [rsp+2Fh] [rbp-21h] BYREF
  std::string v9; // [rsp+30h] [rbp-20h] BYREF
  _BYTE v10[17]; // [rsp+3Fh] [rbp-11h] BYREF

  platform_log_base::PackageData(this, packet);
  std::allocator<char>::allocator(&v6);
  v2 = std::string::c_str(&this->passport);
  std::string::string(&val, v2);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v6);
  Answer::NetPacket::writeInt64(packet, this->cid);
  std::allocator<char>::allocator(&v8);
  v3 = std::string::c_str(&this->name);
  std::string::string(&v7, v3);
  Answer::NetPacket::writeUTF8(packet, &v7);
  std::string::~string(&v7);
  std::allocator<char>::~allocator(&v8);
  Answer::NetPacket::writeInt32(packet, this->create_time);
  Answer::NetPacket::writeInt32(packet, this->login_time);
  Answer::NetPacket::writeInt32(packet, this->online_time);
  std::allocator<char>::allocator(v10);
  v4 = std::string::c_str(&this->ip);
  std::string::string(&v9, v4);
  Answer::NetPacket::writeUTF8(packet, &v9);
  std::string::~string(&v9);
  std::allocator<char>::~allocator(v10);
  Answer::NetPacket::writeInt8(packet, this->job);
  Answer::NetPacket::writeInt32(packet, this->level);
  Answer::NetPacket::writeInt64(packet, this->battle);
  Answer::NetPacket::writeInt32(packet, this->huoyuedu);
  Answer::NetPacket::writeInt32(packet, this->map_id);
  Answer::NetPacket::writeInt32(packet, this->task_id);
  Answer::NetPacket::writeInt64(packet, this->recharge_sum);
  Answer::NetPacket::writeInt64(packet, this->gold);
  Answer::NetPacket::writeInt64(packet, this->cash);
  Answer::NetPacket::writeInt64(packet, this->money);
  Answer::NetPacket::writeInt64(packet, this->bind_money);
}


#####################################
void __cdecl online_user_24th_log::UnPackageData(online_user_24th_log *const this, Answer::NetPacket *inPacket)
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
  this->create_time = Answer::NetPacket::readInt32(inPacket);
  this->login_time = Answer::NetPacket::readInt32(inPacket);
  this->online_time = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_size, (bool)inPacket);
  std::string::operator=(&this->ip, &v2.m_size);
  std::string::~string(&v2.m_size);
  this->job = Answer::NetPacket::readInt8(inPacket);
  this->level = Answer::NetPacket::readInt32(inPacket);
  this->battle = Answer::NetPacket::readInt64(inPacket);
  this->huoyuedu = Answer::NetPacket::readInt32(inPacket);
  this->map_id = Answer::NetPacket::readInt32(inPacket);
  this->task_id = Answer::NetPacket::readInt32(inPacket);
  this->recharge_sum = Answer::NetPacket::readInt64(inPacket);
  this->gold = Answer::NetPacket::readInt64(inPacket);
  this->cash = Answer::NetPacket::readInt64(inPacket);
  this->money = Answer::NetPacket::readInt64(inPacket);
  this->bind_money = Answer::NetPacket::readInt64(inPacket);
}


