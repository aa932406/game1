// Decompiled methods for class: LittleHelperCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl LittleHelperCard::~LittleHelperCard(LittleHelperCard *const this)
{
  LittleHelperCard::~LittleHelperCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl LittleHelperCard::effect(
        LittleHelperCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t m_nAddTime; // r12d
  int32_t m_nLittleHelpId; // ebx
  CharLittlerHelper *CharLittlerHelper; // rax

  m_nAddTime = this->m_nAddTime;
  m_nLittleHelpId = this->m_nLittleHelpId;
  CharLittlerHelper = Player::GetCharLittlerHelper(launcher);
  return CharLittlerHelper::AddLittlerHelper(CharLittlerHelper, m_nLittleHelpId, m_nAddTime);
}


#####################################
bool __cdecl LittleHelperCard::parseEffect(
        LittleHelperCard *const this,
        int32_t id,
        const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  StringVector vParam; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+4Fh] [rbp-11h] BYREF

  this->m_nId = id;
  std::allocator<char>::allocator(v12);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&vParam, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v12);
  if ( std::vector<std::string>::size(&vParam) == 2 )
  {
    v4 = std::vector<std::string>::operator[](&vParam, 0);
    v5 = (const char *)std::string::c_str(v4);
    this->m_nLittleHelpId = atoi(v5);
    v6 = std::vector<std::string>::operator[](&vParam, 1u);
    v7 = (const char *)std::string::c_str(v6);
    this->m_nAddTime = atoi(v7);
    this->m_nAddTime *= 86400;
    v3 = 1;
  }
  else
  {
    v3 = 0;
  }
  std::vector<std::string>::~vector(&vParam);
  return v3;
}


