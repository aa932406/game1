// Decompiled methods for class: TencentInfo
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl TencentInfo::CleanUp(TencentInfo *const this)
{
  std::string::operator=(this, byte_8CFE00);
  this->m_bYellowVip = 0;
  this->m_bYellowYearVip = 0;
  this->m_bYellowHighVip = 0;
  this->m_nYellowVipLevel = 0;
  this->m_bBlueVip = 0;
  this->m_bBlueYearVip = 0;
  this->m_bBlueHighVip = 0;
  this->m_nBlueVipLevel = 0;
  this->m_nYearVipEndTime = 0;
  this->m_nSuperVipEndTime = 0;
  this->m_nExpendVipEndTime = 0;
}


#####################################
void __cdecl TencentInfo::UnPacketInfo(TencentInfo *const this, Answer::NetPacket *packet)
{
  _BYTE v2[32]; // [rsp+10h] [rbp-20h] BYREF

  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v2, (bool)packet);
  std::string::operator=(this, v2);
  std::string::~string(v2);
  this->m_bYellowVip = Answer::NetPacket::readInt8(packet);
  this->m_bYellowYearVip = Answer::NetPacket::readInt8(packet);
  this->m_bYellowHighVip = Answer::NetPacket::readInt8(packet);
  this->m_nYellowVipLevel = Answer::NetPacket::readInt8(packet);
  this->m_bBlueVip = Answer::NetPacket::readInt8(packet);
  this->m_bBlueYearVip = Answer::NetPacket::readInt8(packet);
  this->m_bBlueHighVip = Answer::NetPacket::readInt8(packet);
  this->m_nBlueVipLevel = Answer::NetPacket::readInt8(packet);
  this->m_nYearVipEndTime = Answer::NetPacket::readInt32(packet);
  this->m_nSuperVipEndTime = Answer::NetPacket::readInt32(packet);
  this->m_nExpendVipEndTime = Answer::NetPacket::readInt32(packet);
}


#####################################
int32_t __cdecl TencentInfo::GetEndTime(const TencentInfo *const this)
{
  if ( this->m_nYearVipEndTime <= this->m_nSuperVipEndTime )
  {
    if ( this->m_nSuperVipEndTime <= this->m_nExpendVipEndTime )
      return this->m_nExpendVipEndTime;
    else
      return this->m_nSuperVipEndTime;
  }
  else if ( this->m_nYearVipEndTime <= this->m_nExpendVipEndTime )
  {
    return this->m_nExpendVipEndTime;
  }
  else
  {
    return this->m_nYearVipEndTime;
  }
}


#####################################
bool __cdecl TencentInfo::isYellowEnter(const TencentInfo *const this)
{
  return std::operator==<char>(&this->m_pf, "qzone") || std::operator==<char>(&this->m_pf, "pengyou");
}


#####################################
bool __cdecl TencentInfo::isBlueEnter(const TencentInfo *const this)
{
  return std::operator==<char>(&this->m_pf, "qqgame") || std::operator==<char>(&this->m_pf, "3366");
}


#####################################
bool __cdecl TencentInfo::isTGPEnter(const TencentInfo *const this)
{
  return std::operator==<char>(&this->m_pf, "union-10153-5") || std::operator==<char>(&this->m_pf, "qqgame");
}


#####################################
int32_t __cdecl TencentInfo::getTGPIcon(const TencentInfo *const this)
{
  if ( std::operator==<char>(&this->m_pf, "union-10153-5") )
    return 79;
  if ( std::operator==<char>(&this->m_pf, "qqgame") )
    return 81;
  return -1;
}


