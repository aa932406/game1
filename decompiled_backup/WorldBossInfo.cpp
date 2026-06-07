// Decompiled methods for class: WorldBossInfo
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl WorldBossInfo::PackageBossInfo(const WorldBossInfo *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, this->nBossId);
  Answer::NetPacket::writeInt32(packet, this->nLevel);
  Answer::NetPacket::writeInt32(packet, this->nExp);
  Answer::NetPacket::writeInt32(packet, this->nMid);
  Answer::NetPacket::writeInt32(packet, this->nBossType);
  Answer::NetPacket::writeInt32(packet, this->nMapId);
  Answer::NetPacket::writeInt32(packet, this->nReviveTime);
  Answer::NetPacket::writeInt8(packet, this->nState);
  for ( i = 0; i <= 4; ++i )
  {
    Answer::NetPacket::writeInt64(packet, this->vKiller[i].nCharId);
    Answer::NetPacket::writeUTF8(packet, &this->vKiller[i].strName);
    Answer::NetPacket::writeInt32(packet, this->vKiller[i].nTime);
  }
}


#####################################
void __cdecl WorldBossInfo::UnPackageBossInfo(WorldBossInfo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // r12d
  int32_t v3; // r12d
  _BYTE v4[12]; // [rsp+10h] [rbp-20h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-14h]

  this->nBossId = Answer::NetPacket::readInt32(inPacket);
  this->nLevel = Answer::NetPacket::readInt32(inPacket);
  this->nExp = Answer::NetPacket::readInt32(inPacket);
  this->nMid = Answer::NetPacket::readInt32(inPacket);
  this->nBossType = Answer::NetPacket::readInt32(inPacket);
  this->nMapId = Answer::NetPacket::readInt32(inPacket);
  this->nReviveTime = Answer::NetPacket::readInt32(inPacket);
  this->nState = Answer::NetPacket::readInt8(inPacket);
  for ( i = 0; i <= 4; ++i )
  {
    v2 = i;
    this->vKiller[v2].nCharId = Answer::NetPacket::readInt64(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v4, (bool)inPacket);
    std::string::operator=(&this->vKiller[i].strName, v4);
    std::string::~string(v4);
    v3 = i;
    this->vKiller[v3].nTime = Answer::NetPacket::readInt32(inPacket);
  }
}


#####################################
void __cdecl WorldBossInfo::AddKiller(WorldBossInfo *const this, const KillerInfo *const info)
{
  bool bFind; // [rsp+17h] [rbp-9h]
  int32_t i; // [rsp+18h] [rbp-8h]
  int32_t i_0; // [rsp+1Ch] [rbp-4h]

  bFind = 0;
  for ( i = 0; i <= 4; ++i )
  {
    if ( !this->vKiller[i].nCharId )
    {
      KillerInfo::operator=(&this->vKiller[i], info);
      bFind = 1;
      break;
    }
  }
  if ( !bFind )
  {
    for ( i_0 = 0; i_0 <= 3; ++i_0 )
      KillerInfo::operator=(&this->vKiller[i_0], &this->vKiller[i_0 + 1]);
    KillerInfo::operator=(&this->vKiller[4], info);
  }
}


#####################################
void __cdecl WorldBossInfo::PackageBossInfo(
        const WorldBossInfo *const this,
        Answer::NetPacket *packet,
        int32_t nNowTime)
{
  int32_t v3; // eax
  int32_t nCount; // [rsp+20h] [rbp-10h]
  int32_t nOldOffset; // [rsp+24h] [rbp-Ch]
  int32_t nNewOffset; // [rsp+28h] [rbp-8h]
  int32_t i; // [rsp+2Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, this->nBossId);
  Answer::NetPacket::writeInt32(packet, this->nMid);
  Answer::NetPacket::writeInt32(packet, this->nMapId);
  Answer::NetPacket::writeInt8(packet, this->nState);
  if ( this->nState )
    v3 = this->nReviveTime - nNowTime;
  else
    v3 = 0;
  Answer::NetPacket::writeInt32(packet, v3);
  nCount = 0;
  nOldOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 4; ++i )
  {
    if ( this->vKiller[i].nCharId > 0 )
    {
      Answer::NetPacket::writeInt64(packet, this->vKiller[i].nCharId);
      Answer::NetPacket::writeUTF8(packet, &this->vKiller[i].strName);
      Answer::NetPacket::writeInt32(packet, this->vKiller[i].nTime);
      ++nCount;
    }
  }
  Answer::NetPacket::writeInt32(packet, this->nLevel);
  Answer::NetPacket::writeInt32(packet, this->nExp);
  nNewOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, nOldOffset);
  Answer::NetPacket::writeInt32(packet, nCount);
  Answer::NetPacket::setWOffset(packet, nNewOffset);
}


