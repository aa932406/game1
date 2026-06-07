// Decompiled methods for class: ShiZhuang
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ShiZhuang::~ShiZhuang(ShiZhuang *const this)
{
  ShiZhuang::~ShiZhuang(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ShiZhuang::effect(
        ShiZhuang *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t m_nTime; // r12d
  int32_t m_nShiZhuangId; // ebx
  CShiZhuang *ShiZhuang; // rax

  if ( *count != 1 )
    return 2;
  m_nTime = this->m_nTime;
  m_nShiZhuangId = this->m_nShiZhuangId;
  ShiZhuang = Player::GetShiZhuang(launcher);
  if ( !CShiZhuang::ActiveWithItem(ShiZhuang, m_nShiZhuangId, m_nTime) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl ShiZhuang::parseEffect(ShiZhuang *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  int32_t m_nShiZhuangId; // ebx
  CfgData *v9; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  StringVector vParam; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v15; // [rsp+57h] [rbp-19h] BYREF
  const CfgShiZhuang *pShiZhuang; // [rsp+58h] [rbp-18h]

  this->m_nId = id;
  std::allocator<char>::allocator(&v15);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&vParam, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v15);
  if ( std::vector<std::string>::size(&vParam) == 2 )
  {
    v4 = std::vector<std::string>::operator[](&vParam, 0);
    v5 = (const char *)std::string::c_str(v4);
    this->m_nShiZhuangId = atoi(v5);
    v6 = std::vector<std::string>::operator[](&vParam, 1u);
    v7 = (const char *)std::string::c_str(v6);
    this->m_nTime = atoi(v7);
    m_nShiZhuangId = this->m_nShiZhuangId;
    v9 = Answer::Singleton<CfgData>::instance();
    ShiZhuangTable = CfgData::GetShiZhuangTable(v9);
    pShiZhuang = CfgShiZhuangTable::GetShiZhuang(ShiZhuangTable, m_nShiZhuangId);
    v3 = pShiZhuang != 0;
  }
  else
  {
    v3 = 0;
  }
  std::vector<std::string>::~vector(&vParam);
  return v3;
}


