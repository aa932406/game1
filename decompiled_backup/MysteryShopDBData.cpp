// Decompiled methods for class: MysteryShopDBData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl MysteryShopDBData::~MysteryShopDBData(MysteryShopDBData *const this)
{
  MysteryShopDBData::~MysteryShopDBData(this);
  operator delete(this);
}


#####################################
void __cdecl MysteryShopDBData::SaveToSqlString(
        MysteryShopDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::_Ios_Openmode v4; // eax
  MysteryShop *v5; // rax
  __int64 v6; // rax
  const char *v7; // r12
  int32_t nAutoRefreshTime; // r15d
  int32_t nBuyFlag; // r14d
  const char *v10; // rbx
  int32_t v11; // r13d
  MysteryShop *v12; // rax
  int32_t v13; // [rsp+3Ch] [rbp-204h]
  _BYTE v16[16]; // [rsp+60h] [rbp-1E0h] BYREF
  __int64 v17; // [rsp+70h] [rbp-1D0h] BYREF
  std::string strGoods; // [rsp+1D0h] [rbp-70h] BYREF
  std::_List_iterator<MysteryShop> iter; // [rsp+1E0h] [rbp-60h] BYREF
  std::_List_iterator<MysteryShop> v20; // [rsp+1F0h] [rbp-50h] BYREF
  std::string __x; // [rsp+200h] [rbp-40h] BYREF
  char v22; // [rsp+20Bh] [rbp-35h] BYREF
  uint32_t i; // [rsp+20Ch] [rbp-34h]

  for ( iter._M_node = std::list<MysteryShop>::begin(&this->lstShop)._M_node;
        ;
        std::_List_iterator<MysteryShop>::operator++(&iter) )
  {
    v20._M_node = std::list<MysteryShop>::end(&this->lstShop)._M_node;
    if ( !std::_List_iterator<MysteryShop>::operator!=(&iter, &v20) )
      break;
    v4 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v16, (unsigned int)v4);
    for ( i = 0; i <= 3; ++i )
    {
      v5 = std::_List_iterator<MysteryShop>::operator->(&iter);
      v6 = std::ostream::operator<<(&v17, (unsigned int)v5->vGoods[i]);
      std::operator<<<std::char_traits<char>>(v6, ":");
    }
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&strGoods, v16);
    bzero(szSQL, 0x1000u);
    v7 = (const char *)std::string::c_str(&strGoods);
    nAutoRefreshTime = std::_List_iterator<MysteryShop>::operator->(&iter)->nAutoRefreshTime;
    nBuyFlag = std::_List_iterator<MysteryShop>::operator->(&iter)->nBuyFlag;
    v10 = (const char *)std::string::c_str(&strGoods);
    v11 = std::_List_iterator<MysteryShop>::operator->(&iter)->nAutoRefreshTime;
    v13 = std::_List_iterator<MysteryShop>::operator->(&iter)->nBuyFlag;
    v12 = std::_List_iterator<MysteryShop>::operator->(&iter);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_char_mystery_shop` (`cid`,`type`,`buy_flag`,`refresh_time`,`goods`) VALUES (%lld,%d,%d,%d,'%s') O"
      "N DUPLICATE KEY UPDATE `buy_flag`=%d,`refresh_time`=%d,`goods`='%s'",
      nCid,
      v12->nType,
      v13,
      v11,
      v10,
      nBuyFlag,
      nAutoRefreshTime,
      v7);
    std::allocator<char>::allocator(&v22);
    std::string::string(&__x, (char *)szSQL, &v22);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v22);
    std::string::~string(&strGoods);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v16);
  }
}


#####################################
bool __cdecl MysteryShopDBData::LoadFromDB(
        MysteryShopDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  uint32_t v8; // ebx
  std::string *v9; // rax
  const char *v10; // rax
  size_t v11; // rbx
  StringVector vGoods; // [rsp+30h] [rbp-90h] BYREF
  std::string strGoods; // [rsp+50h] [rbp-70h] BYREF
  MysteryShop shop; // [rsp+60h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-40h] BYREF
  char v20; // [rsp+9Fh] [rbp-21h] BYREF
  std::string delims; // [rsp+A0h] [rbp-20h] BYREF
  char v22; // [rsp+ABh] [rbp-15h] BYREF
  uint32_t i; // [rsp+ACh] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_mystery_shop` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    memset(&shop, 0, sizeof(shop));
    shop.nType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    shop.nBuyFlag = Answer::MySqlQuery::getIntValue(&result, "buy_flag", 0);
    shop.nAutoRefreshTime = Answer::MySqlQuery::getIntValue(&result, "refresh_time", 0);
    std::allocator<char>::allocator(&v20);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "goods", byte_8CFE00);
    std::string::string(&strGoods, StringValue, &v20);
    std::allocator<char>::~allocator(&v20);
    std::allocator<char>::allocator(&v22);
    std::string::string(&delims, ":", &v22);
    Answer::StringUtility::split(&vGoods, &strGoods, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v22);
    for ( i = 0; i <= 3; ++i )
    {
      v11 = i;
      if ( v11 >= std::vector<std::string>::size(&vGoods) )
        break;
      v8 = i;
      v9 = std::vector<std::string>::operator[](&vGoods, i);
      v10 = (const char *)std::string::c_str(v9);
      shop.vGoods[v8] = atoi(v10);
    }
    std::list<MysteryShop>::push_back(&this->lstShop, &shop);
    Answer::MySqlQuery::nextRow(&result);
    std::vector<std::string>::~vector(&vGoods);
    std::string::~string(&strGoods);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 0;
}


#####################################
void __cdecl MysteryShopDBData::PackageData(MysteryShopDBData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int8_t nType; // dl
  int32_t nBuyFlag; // edx
  int32_t nAutoRefreshTime; // edx
  MysteryShop *v6; // rax
  std::_List_iterator<MysteryShop> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<MysteryShop> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t i; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    v2 = std::list<MysteryShop>::size(&this->lstShop);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( iter._M_node = std::list<MysteryShop>::begin(&this->lstShop)._M_node;
          ;
          std::_List_iterator<MysteryShop>::operator++(&iter) )
    {
      __x._M_node = std::list<MysteryShop>::end(&this->lstShop)._M_node;
      if ( !std::_List_iterator<MysteryShop>::operator!=(&iter, &__x) )
        break;
      nType = std::_List_iterator<MysteryShop>::operator->(&iter)->nType;
      Answer::NetPacket::writeInt8(packet, nType);
      nBuyFlag = std::_List_iterator<MysteryShop>::operator->(&iter)->nBuyFlag;
      Answer::NetPacket::writeInt32(packet, nBuyFlag);
      nAutoRefreshTime = std::_List_iterator<MysteryShop>::operator->(&iter)->nAutoRefreshTime;
      Answer::NetPacket::writeInt32(packet, nAutoRefreshTime);
      for ( i = 0; i <= 3; ++i )
      {
        v6 = std::_List_iterator<MysteryShop>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v6->vGoods[i]);
      }
    }
  }
}


#####################################
void __cdecl MysteryShopDBData::UnPackageData(
        MysteryShopDBData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  int32_t v3; // ebx
  MysteryShop shop; // [rsp+20h] [rbp-40h] BYREF
  int32_t nSize; // [rsp+44h] [rbp-1Ch]
  int32_t i; // [rsp+48h] [rbp-18h]
  int32_t j; // [rsp+4Ch] [rbp-14h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      memset(&shop, 0, sizeof(shop));
      shop.nType = Answer::NetPacket::readInt8(inPacket);
      shop.nBuyFlag = Answer::NetPacket::readInt32(inPacket);
      shop.nAutoRefreshTime = Answer::NetPacket::readInt32(inPacket);
      for ( j = 0; j <= 3; ++j )
      {
        v3 = j;
        shop.vGoods[v3] = Answer::NetPacket::readInt32(inPacket);
      }
      std::list<MysteryShop>::push_back(&this->lstShop, &shop);
    }
  }
}


