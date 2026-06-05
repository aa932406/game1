// Decompiled methods for class: ExchangeDBData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl ExchangeDBData::~ExchangeDBData(ExchangeDBData *const this)
{
  ExchangeDBData::~ExchangeDBData(this);
  operator delete(this);
}


#####################################
void __cdecl ExchangeDBData::SaveToSqlString(
        ExchangeDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t nCount; // ebx
  int nIndex; // r12d
  ExchangeRecord *v6; // rax
  std::_List_iterator<ExchangeRecord> iter; // [rsp+30h] [rbp-50h] BYREF
  std::string __x; // [rsp+40h] [rbp-40h] BYREF
  char v11; // [rsp+4Fh] [rbp-31h] BYREF
  std::_List_iterator<ExchangeRecord> v12; // [rsp+50h] [rbp-30h] BYREF
  std::string v13; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v14[17]; // [rsp+6Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_char_exchange` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator(&v11);
  std::string::string(&__x, (char *)szSQL, &v11);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v11);
  for ( iter._M_node = std::list<ExchangeRecord>::begin(&this->lstExchange)._M_node;
        ;
        std::_List_iterator<ExchangeRecord>::operator++(&iter) )
  {
    v12._M_node = std::list<ExchangeRecord>::end(&this->lstExchange)._M_node;
    if ( !std::_List_iterator<ExchangeRecord>::operator!=(&iter, &v12) )
      break;
    bzero(szSQL, 0x1000u);
    nCount = std::_List_iterator<ExchangeRecord>::operator->(&iter)->nCount;
    nIndex = std::_List_iterator<ExchangeRecord>::operator->(&iter)->nIndex;
    v6 = std::_List_iterator<ExchangeRecord>::operator->(&iter);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_char_exchange` (`cid`,`type`,`index`,`count`) VALUES (%lld,%d,%d,%d)",
      nCid,
      v6->nType,
      nIndex,
      nCount);
    std::allocator<char>::allocator(v14);
    std::string::string(&v13, (char *)szSQL, v14);
    std::list<std::string>::push_back(sqls, &v13);
    std::string::~string(&v13);
    std::allocator<char>::~allocator(v14);
  }
}


#####################################
bool __cdecl ExchangeDBData::LoadFromDB(
        ExchangeDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  ExchangeRecord shop; // [rsp+30h] [rbp-40h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_exchange` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    shop = 0;
    shop.nType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    shop.nIndex = Answer::MySqlQuery::getIntValue(&result, "index", 0);
    shop.nCount = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    std::list<ExchangeRecord>::push_back(&this->lstExchange, &shop);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 0;
}


#####################################
void __cdecl ExchangeDBData::PackageData(ExchangeDBData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int8_t nType; // dl
  int16_t nIndex; // dx
  int32_t nCount; // edx
  std::_List_iterator<ExchangeRecord> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<ExchangeRecord> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::list<ExchangeRecord>::size(&this->lstExchange);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( iter._M_node = std::list<ExchangeRecord>::begin(&this->lstExchange)._M_node;
          ;
          std::_List_iterator<ExchangeRecord>::operator++(&iter) )
    {
      __x._M_node = std::list<ExchangeRecord>::end(&this->lstExchange)._M_node;
      if ( !std::_List_iterator<ExchangeRecord>::operator!=(&iter, &__x) )
        break;
      nType = std::_List_iterator<ExchangeRecord>::operator->(&iter)->nType;
      Answer::NetPacket::writeInt8(packet, nType);
      nIndex = std::_List_iterator<ExchangeRecord>::operator->(&iter)->nIndex;
      Answer::NetPacket::writeInt16(packet, nIndex);
      nCount = std::_List_iterator<ExchangeRecord>::operator->(&iter)->nCount;
      Answer::NetPacket::writeInt32(packet, nCount);
    }
  }
}


#####################################
void __cdecl ExchangeDBData::UnPackageData(ExchangeDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  ExchangeRecord record; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+28h] [rbp-8h]
  int32_t i; // [rsp+2Ch] [rbp-4h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      record = 0;
      record.nType = Answer::NetPacket::readInt8(inPacket);
      record.nIndex = Answer::NetPacket::readInt16(inPacket);
      record.nCount = Answer::NetPacket::readInt32(inPacket);
      std::list<ExchangeRecord>::push_back(&this->lstExchange, &record);
    }
  }
}


