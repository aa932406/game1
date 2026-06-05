// Decompiled methods for class: FaBaoRes
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl FaBaoRes::~FaBaoRes(FaBaoRes *const this)
{
  FaBaoRes::~FaBaoRes(this);
  operator delete(this);
}


#####################################
int32_t __cdecl FaBaoRes::effect(
        FaBaoRes *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int8_t m_Type; // bl
  CFaBao *PlayerFaBao; // rax
  int Values; // [rsp+2Ch] [rbp-14h]

  if ( *count <= 0 )
    return 10002;
  Values = this->m_Values * *count;
  if ( Values <= 0 )
    return 10002;
  m_Type = this->m_Type;
  PlayerFaBao = Player::GetPlayerFaBao(launcher);
  CFaBao::AddFaBaoRes(PlayerFaBao, m_Type, Values);
  return 0;
}


#####################################
bool __cdecl FaBaoRes::parseEffect(FaBaoRes *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  bool v8; // al
  StringVector strParam; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  char v13; // [rsp+4Bh] [rbp-15h] BYREF
  int32_t nSzie; // [rsp+4Ch] [rbp-14h]

  std::allocator<char>::allocator(&v13);
  std::string::string(&delims, "|");
  Answer::StringUtility::split(&strParam, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v13);
  nSzie = std::vector<std::string>::size(&strParam);
  if ( nSzie == 2 )
  {
    v4 = std::vector<std::string>::operator[](&strParam, 0);
    v5 = (const char *)std::string::c_str(v4);
    this->m_Type = atoi(v5);
    v6 = std::vector<std::string>::operator[](&strParam, 1u);
    v7 = (const char *)std::string::c_str(v6);
    this->m_Values = atoi(v7);
    v8 = !IsFaBaoType(this->m_Type) || this->m_Values <= 0;
    v3 = !v8;
  }
  else
  {
    v3 = 0;
  }
  std::vector<std::string>::~vector(&strParam);
  return v3;
}


