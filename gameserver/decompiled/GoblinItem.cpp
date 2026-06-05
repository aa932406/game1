// Decompiled methods for class: GoblinItem
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl GoblinItem::~GoblinItem(GoblinItem *const this)
{
  GoblinItem::~GoblinItem(this);
  operator delete(this);
}


#####################################
int32_t __cdecl GoblinItem::effect(
        GoblinItem *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int8_t nType; // bl
  CGoblin *CGoblin; // rax
  int32_t Addon; // [rsp+2Ch] [rbp-14h]

  Addon = this->Value;
  if ( *count > 0 )
    Addon *= *count;
  nType = this->nType;
  CGoblin = Player::GetCGoblin(launcher);
  if ( !CGoblin::AddGoblinRes(CGoblin, nType, Addon) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl GoblinItem::parseEffect(GoblinItem *const this, int32_t id, const std::string *const strEffect)
{
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  bool v7; // bl
  StringVector params; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v12);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v12);
  if ( std::vector<std::string>::size(&params) == 2 )
  {
    v3 = std::vector<std::string>::operator[](&params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->nType = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->Value = atoi(v6);
    v7 = 1;
  }
  else
  {
    v7 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v7;
}


