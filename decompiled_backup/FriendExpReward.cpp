// Decompiled methods for class: FriendExpReward
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl FriendExpReward::~FriendExpReward(FriendExpReward *const this)
{
  FriendExpReward::~FriendExpReward(this);
  operator delete(this);
}


#####################################
void __cdecl FriendExpReward::SaveToSqlString(
        FriendExpReward *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  DieRecord *v4; // rax
  const char *v5; // rbx
  CharId_t Cid; // r13
  int32_t MonsterId; // r12d
  int32_t MapId; // r14d
  DieRecord *v9; // rax
  std::_List_iterator<DieRecord> it; // [rsp+40h] [rbp-60h] BYREF
  std::string __x; // [rsp+50h] [rbp-50h] BYREF
  char v14; // [rsp+5Fh] [rbp-41h] BYREF
  std::_List_iterator<DieRecord> v15; // [rsp+60h] [rbp-40h] BYREF
  std::string v16; // [rsp+70h] [rbp-30h] BYREF
  _BYTE v17[33]; // [rsp+7Fh] [rbp-21h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_die` WHERE `Cid`=%lld", nCid);
  std::allocator<char>::allocator(&v14);
  std::string::string(&__x, (char *)szSQL, &v14);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v14);
  for ( it._M_node = std::list<DieRecord>::begin(&this->m_DieRecord)._M_node;
        ;
        std::_List_iterator<DieRecord>::operator++(&it) )
  {
    v15._M_node = std::list<DieRecord>::end(&this->m_DieRecord)._M_node;
    if ( !std::_List_iterator<DieRecord>::operator!=(&it, &v15) )
      break;
    bzero(szSQL, 0x1000u);
    v4 = std::_List_iterator<DieRecord>::operator->(&it);
    v5 = (const char *)std::string::c_str(&v4->Name);
    Cid = std::_List_iterator<DieRecord>::operator->(&it)->Cid;
    MonsterId = std::_List_iterator<DieRecord>::operator->(&it)->MonsterId;
    MapId = std::_List_iterator<DieRecord>::operator->(&it)->MapId;
    v9 = std::_List_iterator<DieRecord>::operator->(&it);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_die` (`Cid`, `KillTime`,`MapId`,`Mid`,`KillerId`,`KillerName`) VALUES (%lld, %d, %d,%d,%lld,'%s')",
      nCid,
      v9->KillTime,
      MapId,
      MonsterId,
      Cid,
      v5);
    std::allocator<char>::allocator(v17);
    std::string::string(&v16, (char *)szSQL, v17);
    std::list<std::string>::push_back(sqls, &v16);
    std::string::~string(&v16);
    std::allocator<char>::~allocator(v17);
  }
}


#####################################
bool __cdecl FriendExpReward::LoadFromDB(
        FriendExpReward *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  DieRecord Record; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_die` WHERE `Cid`=%lld ORDER BY `KillTime` LIMIT %d", nCid, 20);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    DieRecord::DieRecord(&Record);
    Record.KillTime = Answer::MySqlQuery::getIntValue(&result, "KillTime", 0);
    Record.MapId = Answer::MySqlQuery::getIntValue(&result, "MapId", 0);
    Record.MonsterId = Answer::MySqlQuery::getIntValue(&result, "Mid", 0);
    Record.Cid = Answer::MySqlQuery::getInt64Value(&result, "KillerId", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "KillerName", byte_8CFE00);
    std::string::operator=(&Record.Name, StringValue);
    std::list<DieRecord>::push_back(&this->m_DieRecord, &Record);
    Answer::MySqlQuery::nextRow(&result);
    DieRecord::~DieRecord(&Record);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl FriendExpReward::PackageData(FriendExpReward *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int32_t KillTime; // edx
  int32_t MapId; // edx
  int32_t MonsterId; // edx
  CharId_t Cid; // rdx
  std::string *p_Name; // rdx
  std::_List_iterator<DieRecord> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<DieRecord> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::list<DieRecord>::size(&this->m_DieRecord);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( it._M_node = std::list<DieRecord>::begin(&this->m_DieRecord)._M_node;
          ;
          std::_List_iterator<DieRecord>::operator++(&it) )
    {
      __x._M_node = std::list<DieRecord>::end(&this->m_DieRecord)._M_node;
      if ( !std::_List_iterator<DieRecord>::operator!=(&it, &__x) )
        break;
      KillTime = std::_List_iterator<DieRecord>::operator->(&it)->KillTime;
      Answer::NetPacket::writeInt32(packet, KillTime);
      MapId = std::_List_iterator<DieRecord>::operator->(&it)->MapId;
      Answer::NetPacket::writeInt32(packet, MapId);
      MonsterId = std::_List_iterator<DieRecord>::operator->(&it)->MonsterId;
      Answer::NetPacket::writeInt32(packet, MonsterId);
      Cid = std::_List_iterator<DieRecord>::operator->(&it)->Cid;
      Answer::NetPacket::writeInt64(packet, Cid);
      p_Name = &std::_List_iterator<DieRecord>::operator->(&it)->Name;
      Answer::NetPacket::writeUTF8(packet, p_Name);
    }
  }
}


#####################################
void __cdecl FriendExpReward::UnPackageData(FriendExpReward *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  DieRecord Record; // [rsp+20h] [rbp-40h] BYREF
  char v4; // [rsp+40h] [rbp-20h] BYREF
  int32_t Size; // [rsp+48h] [rbp-18h]
  int32_t j; // [rsp+4Ch] [rbp-14h]

  if ( inPacket )
  {
    Size = Answer::NetPacket::readInt32(inPacket);
    for ( j = 0; j < Size; ++j )
    {
      DieRecord::DieRecord(&Record);
      Record.KillTime = Answer::NetPacket::readInt32(inPacket);
      Record.MapId = Answer::NetPacket::readInt32(inPacket);
      Record.MonsterId = Answer::NetPacket::readInt32(inPacket);
      Record.Cid = Answer::NetPacket::readInt64(inPacket);
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v4, (bool)inPacket);
      std::string::operator=(&Record.Name, &v4);
      std::string::~string(&v4);
      std::list<DieRecord>::push_back(&this->m_DieRecord, &Record);
      DieRecord::~DieRecord(&Record);
    }
  }
}


