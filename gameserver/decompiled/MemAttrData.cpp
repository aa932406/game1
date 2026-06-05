// Decompiled methods for class: MemAttrData
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl MemAttrData::~MemAttrData(MemAttrData *const this)
{
  MemAttrData::~MemAttrData(this);
  operator delete(this);
}


#####################################
void __cdecl MemAttrData::CleanUp(MemAttrData *const this)
{
  bzero(this->vAttr, 0xC8u);
}


#####################################
void __cdecl MemAttrData::SaveToSqlString(
        MemAttrData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  const char *v5; // rax
  std::string v8; // [rsp+20h] [rbp-40h] BYREF
  std::string v9; // [rsp+30h] [rbp-30h] BYREF
  std::string __x; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v11[17]; // [rsp+4Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  MemAttrData::SaveString((MemAttrData *const)&v8);
  v4 = (const char *)std::string::c_str(&v8);
  MemAttrData::SaveString((MemAttrData *const)&v9);
  v5 = (const char *)std::string::c_str(&v9);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_attr` (`cid`,`Attrs`) VALUES (%lld,'%s')  \t\t\tON DUPLICATE KEY UPDATE `Attrs`='%s'",
    nCid,
    v5,
    v4);
  std::string::~string(&v9);
  std::string::~string(&v8);
  std::allocator<char>::allocator(v11);
  std::string::string(&__x, (char *)szSQL, v11);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v11);
}


#####################################
bool __cdecl MemAttrData::LoadFromDB(
        MemAttrData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  return 0;
}


#####################################
void __cdecl MemAttrData::PackageData(MemAttrData *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 49; ++i )
    Answer::NetPacket::writeInt32(packet, this->vAttr[i]);
}


#####################################
void __cdecl MemAttrData::UnPackageData(MemAttrData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int32_t i; // [rsp+2Ch] [rbp-14h]

  for ( i = 0; i <= 49; ++i )
    this->vAttr[i] = Answer::NetPacket::readInt32(inPacket);
}


#####################################
std::string __cdecl MemAttrData::SaveString(MemAttrData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int v3; // r12d
  __int64 v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  _BYTE v8[16]; // [rsp+10h] [rbp-190h] BYREF
  __int64 v9; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v8, (unsigned int)v2);
  for ( i = 1; i <= 49; ++i )
  {
    v3 = *(_DWORD *)(v1 + 4LL * i + 8);
    v4 = std::ostream::operator<<(&v9, (unsigned int)i);
    v5 = std::operator<<<std::char_traits<char>>(v4, ":");
    v6 = std::ostream::operator<<(v5, v3);
    std::operator<<<std::char_traits<char>>(v6, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v8);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v8);
  return (std::string)this;
}


