// Decompiled methods for class: CVplanData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CVplanData::~CVplanData(CVplanData *const this)
{
  CVplanData::~CVplanData(this);
  operator delete(this);
}


#####################################
void __cdecl CVplanData::CleanUp(CVplanData *const this)
{
  this->m_VplanLevel = 0;
  this->m_VplanType = 0;
  this->m_SwVipLevel = 0;
  this->m_YYLevel = 0;
  this->m_YYVipLevel = 0;
  this->m_YySuperLevel = 0;
  this->m_SgHallLevel = 0;
  std::string::operator=(&this->m_strSGPf, byte_8CFE00);
  this->m_XlNxLevel = 0;
  this->m_PlatformSuperVip = 0;
  this->m_PlatformVip = 0;
}


#####################################
bool __cdecl CVplanData::LoadFromDB(
        CVplanData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `info_for_360` WHERE `uid`=%lld AND sid=%d", nUid, nSid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_VplanType = Answer::MySqlQuery::getIntValue(&result, "vip_type", 0);
    this->m_VplanLevel = Answer::MySqlQuery::getIntValue(&result, "vip_level", 0);
    this->m_SwVipLevel = Answer::MySqlQuery::getIntValue(&result, "sw_vip_level", 0);
    this->m_YYLevel = Answer::MySqlQuery::getIntValue(&result, "yy_level", 0);
    this->m_YYVipLevel = Answer::MySqlQuery::getIntValue(&result, "yy_vip_level", 0);
    this->m_YySuperLevel = Answer::MySqlQuery::getIntValue(&result, "yy_super_level", 0);
    this->m_SgHallLevel = Answer::MySqlQuery::getIntValue(&result, "sg_hall_level", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "sg_pf", byte_8CFE00);
    std::string::operator=(&this->m_strSGPf, StringValue);
    this->m_XlNxLevel = Answer::MySqlQuery::getIntValue(&result, "xl_nx_level", 0);
    this->m_PlatformVip = Answer::MySqlQuery::getIntValue(&result, "platform_vip", 0);
    this->m_PlatformSuperVip = Answer::MySqlQuery::getIntValue(&result, "platform_super_vip", 0);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CVplanData::PackageData(CVplanData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt8(packet, this->m_VplanType);
  Answer::NetPacket::writeInt32(packet, this->m_VplanLevel);
  Answer::NetPacket::writeInt32(packet, this->m_SwVipLevel);
  Answer::NetPacket::writeInt32(packet, this->m_YYLevel);
  Answer::NetPacket::writeInt32(packet, this->m_YYVipLevel);
  Answer::NetPacket::writeInt32(packet, this->m_YySuperLevel);
  Answer::NetPacket::writeInt32(packet, this->m_SgHallLevel);
  Answer::NetPacket::writeUTF8(packet, &this->m_strSGPf);
  Answer::NetPacket::writeInt32(packet, this->m_XlNxLevel);
  Answer::NetPacket::writeInt32(packet, this->m_PlatformVip);
  Answer::NetPacket::writeInt32(packet, this->m_PlatformSuperVip);
}


#####################################
void __cdecl CVplanData::UnPackageData(CVplanData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  this->m_VplanType = Answer::NetPacket::readInt8(inPacket);
  this->m_VplanLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_SwVipLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_YYLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_YYVipLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_YySuperLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_SgHallLevel = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
  std::string::operator=(&this->m_strSGPf, v3);
  std::string::~string(v3);
  this->m_XlNxLevel = Answer::NetPacket::readInt32(inPacket);
  this->m_PlatformVip = Answer::NetPacket::readInt32(inPacket);
  this->m_PlatformSuperVip = Answer::NetPacket::readInt32(inPacket);
}


