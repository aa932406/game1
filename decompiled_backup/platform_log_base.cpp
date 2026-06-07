// Decompiled methods for class: platform_log_base
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl platform_log_base::~platform_log_base(platform_log_base *const this)
{
  platform_log_base::~platform_log_base(this);
  operator delete(this);
}


#####################################
void __cdecl platform_log_base::PackageData(platform_log_base *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt32(packet, this->log_time);
  Answer::NetPacket::writeInt32(packet, this->log_Sid);
}


#####################################
void __cdecl platform_log_base::UnPackageData(platform_log_base *const this, Answer::NetPacket *inPacket)
{
  this->log_time = Answer::NetPacket::readInt32(inPacket);
  this->log_Sid = Answer::NetPacket::readInt32(inPacket);
}


