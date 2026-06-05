// Decompiled methods for class: PortalDBData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl PortalDBData::~PortalDBData(PortalDBData *const this)
{
  PortalDBData::~PortalDBData(this);
  operator delete(this);
}


#####################################
void __cdecl PortalDBData::CleanUp(PortalDBData *const this)
{
  std::list<PortalInfo>::clear(&this->lstPortal);
  this->nPortalId = 0;
}


#####################################
void __cdecl PortalDBData::SaveToSqlString(
        PortalDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int bClose; // r12d
  int32_t nDuration; // r13d
  int32_t v6; // r15d
  int32_t v7; // r14d
  PortalInfo *v8; // rax
  int32_t nStartTime; // [rsp+78h] [rbp-A8h]
  int32_t nDungeon; // [rsp+7Ch] [rbp-A4h]
  int32_t nPosY; // [rsp+80h] [rbp-A0h]
  int32_t nPosX; // [rsp+84h] [rbp-9Ch]
  int32_t nMapId; // [rsp+88h] [rbp-98h]
  int v14; // [rsp+8Ch] [rbp-94h]
  int32_t v15; // [rsp+90h] [rbp-90h]
  int32_t v16; // [rsp+94h] [rbp-8Ch]
  int32_t v17; // [rsp+98h] [rbp-88h]
  int32_t v18; // [rsp+9Ch] [rbp-84h]
  std::_List_iterator<PortalInfo> iter; // [rsp+C0h] [rbp-60h] BYREF
  std::_List_iterator<PortalInfo> v22; // [rsp+D0h] [rbp-50h] BYREF
  std::string __x; // [rsp+E0h] [rbp-40h] BYREF
  _BYTE v24[49]; // [rsp+EFh] [rbp-31h] BYREF

  for ( iter._M_node = std::list<PortalInfo>::begin(&this->lstPortal)._M_node;
        ;
        std::_List_iterator<PortalInfo>::operator++(&iter, 0) )
  {
    v22._M_node = std::list<PortalInfo>::end(&this->lstPortal)._M_node;
    if ( !std::_List_iterator<PortalInfo>::operator!=(&iter, &v22) )
      break;
    bzero(szSQL, 0x1000u);
    bClose = std::_List_iterator<PortalInfo>::operator->(&iter)->bClose;
    nDuration = std::_List_iterator<PortalInfo>::operator->(&iter)->nDuration;
    nStartTime = std::_List_iterator<PortalInfo>::operator->(&iter)->nStartTime;
    nDungeon = std::_List_iterator<PortalInfo>::operator->(&iter)->nDungeon;
    nPosY = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosY;
    nPosX = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosX;
    nMapId = std::_List_iterator<PortalInfo>::operator->(&iter)->nMapId;
    v14 = std::_List_iterator<PortalInfo>::operator->(&iter)->bClose;
    v15 = std::_List_iterator<PortalInfo>::operator->(&iter)->nDuration;
    v16 = std::_List_iterator<PortalInfo>::operator->(&iter)->nStartTime;
    v17 = std::_List_iterator<PortalInfo>::operator->(&iter)->nDungeon;
    v6 = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosY;
    v7 = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosX;
    v18 = std::_List_iterator<PortalInfo>::operator->(&iter)->nMapId;
    v8 = std::_List_iterator<PortalInfo>::operator->(&iter);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_char_portal` (`cid`,`id`,`map`,`x`,`y`,`dungeon`,`time`,`duration`,`close`) VALUES (%lld,%d,%d,%d"
      ",%d,%d,%d,%d,%d) ON DUPLICATE KEY UPDATE `map`=%d,`x`=%d,`y`=%d,`dungeon`=%d,`time`=%d,`duration`=%d,`close`=%d",
      nCid,
      v8->nId,
      v18,
      v7,
      v6,
      v17,
      v16,
      v15,
      v14,
      nMapId,
      nPosX,
      nPosY,
      nDungeon,
      nStartTime,
      nDuration,
      bClose);
    std::allocator<char>::allocator(v24);
    std::string::string(&__x, (char *)szSQL, v24);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(v24);
  }
}


#####################################
bool __cdecl PortalDBData::LoadFromDB(
        PortalDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  PortalInfo info; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "SELECT * FROM `mem_char_portal` WHERE `cid`=%lld AND `close`=0 ORDER BY `time`",
    nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    memset(&info, 0, sizeof(info));
    info.nId = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    info.nMapId = Answer::MySqlQuery::getIntValue(&result, "map", 0);
    info.nPosX = Answer::MySqlQuery::getIntValue(&result, "x", 0);
    info.nPosY = Answer::MySqlQuery::getIntValue(&result, "y", 0);
    info.nDungeon = Answer::MySqlQuery::getIntValue(&result, "dungeon", 0);
    info.nStartTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    info.nDuration = Answer::MySqlQuery::getIntValue(&result, "duration", 0);
    std::list<PortalInfo>::push_back(&this->lstPortal, &info);
    this->nPortalId = info.nId;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl PortalDBData::PackageData(PortalDBData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int32_t nId; // edx
  int32_t nMapId; // edx
  int32_t nPosX; // edx
  int32_t nPosY; // edx
  int32_t nDungeon; // edx
  int32_t nStartTime; // edx
  int32_t nDuration; // edx
  int8_t bClose; // dl
  std::_List_iterator<PortalInfo> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<PortalInfo> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::list<PortalInfo>::size(&this->lstPortal);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( iter._M_node = std::list<PortalInfo>::begin(&this->lstPortal)._M_node;
          ;
          std::_List_iterator<PortalInfo>::operator++(&iter, 0) )
    {
      __x._M_node = std::list<PortalInfo>::end(&this->lstPortal)._M_node;
      if ( !std::_List_iterator<PortalInfo>::operator!=(&iter, &__x) )
        break;
      nId = std::_List_iterator<PortalInfo>::operator->(&iter)->nId;
      Answer::NetPacket::writeInt32(packet, nId);
      nMapId = std::_List_iterator<PortalInfo>::operator->(&iter)->nMapId;
      Answer::NetPacket::writeInt32(packet, nMapId);
      nPosX = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosX;
      Answer::NetPacket::writeInt32(packet, nPosX);
      nPosY = std::_List_iterator<PortalInfo>::operator->(&iter)->nPosY;
      Answer::NetPacket::writeInt32(packet, nPosY);
      nDungeon = std::_List_iterator<PortalInfo>::operator->(&iter)->nDungeon;
      Answer::NetPacket::writeInt32(packet, nDungeon);
      nStartTime = std::_List_iterator<PortalInfo>::operator->(&iter)->nStartTime;
      Answer::NetPacket::writeInt32(packet, nStartTime);
      nDuration = std::_List_iterator<PortalInfo>::operator->(&iter)->nDuration;
      Answer::NetPacket::writeInt32(packet, nDuration);
      bClose = std::_List_iterator<PortalInfo>::operator->(&iter)->bClose;
      Answer::NetPacket::writeInt8(packet, bClose);
    }
    Answer::NetPacket::writeInt32(packet, this->nPortalId);
  }
}


#####################################
void __cdecl PortalDBData::UnPackageData(PortalDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  PortalInfo info; // [rsp+20h] [rbp-30h] BYREF
  int32_t nSize; // [rsp+48h] [rbp-8h]
  int32_t i; // [rsp+4Ch] [rbp-4h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      memset(&info, 0, sizeof(info));
      info.nId = Answer::NetPacket::readInt32(inPacket);
      info.nMapId = Answer::NetPacket::readInt32(inPacket);
      info.nPosX = Answer::NetPacket::readInt32(inPacket);
      info.nPosY = Answer::NetPacket::readInt32(inPacket);
      info.nDungeon = Answer::NetPacket::readInt32(inPacket);
      info.nStartTime = Answer::NetPacket::readInt32(inPacket);
      info.nDuration = Answer::NetPacket::readInt32(inPacket);
      info.bClose = Answer::NetPacket::readInt8(inPacket);
      std::list<PortalInfo>::push_back(&this->lstPortal, &info);
    }
    this->nPortalId = Answer::NetPacket::readInt32(inPacket);
  }
}


