// Decompiled methods for class: UpLevel
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl UpLevel::~UpLevel(UpLevel *const this)
{
  UpLevel::~UpLevel(this);
  operator delete(this);
}


#####################################
int32_t __cdecl UpLevel::effect(UpLevel *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  void (__fastcall *v6)(Player *const, _QWORD); // rbx
  unsigned int v7; // edx
  CHuoYueDu *PlayerHuoYueDu; // rax
  signed int maxLevel; // [rsp+2Ch] [rbp-14h]

  if ( *count != 1 )
    return 2;
  maxLevel = Player::GetMaxLevel(launcher);
  if ( (*((int (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher) >= maxLevel )
    return 2;
  if ( (*((int (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher) < this->m_MinLevel
    || (*((int (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher) > this->m_MaxLevel )
  {
    return 2;
  }
  if ( (int)(this->m_AddLevel + (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher)) <= maxLevel )
  {
    v6 = (void (__fastcall *)(Player *const, _QWORD))*((_QWORD *)launcher->_vptr_Entity + 33);
    v7 = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher) + this->m_AddLevel;
    v6(launcher, v7);
  }
  else
  {
    (*((void (__fastcall **)(Player *const, _QWORD))launcher->_vptr_Entity + 33))(launcher, (unsigned int)maxLevel);
  }
  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(launcher);
  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 6, 0, 0);
  return 0;
}


#####################################
bool __cdecl UpLevel::parseEffect(UpLevel *const this, int32_t id, const std::string *const strEffect)
{
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  bool v9; // bl
  StringVector params; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v14[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v14);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v14);
  if ( std::vector<std::string>::size(&params) == 3 )
  {
    v3 = std::vector<std::string>::operator[](&params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->m_MinLevel = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->m_MaxLevel = atoi(v6);
    v7 = std::vector<std::string>::operator[](&params, 2u);
    v8 = (const char *)std::string::c_str(v7);
    this->m_AddLevel = atoi(v8);
    v9 = 1;
  }
  else
  {
    v9 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v9;
}


