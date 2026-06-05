// Decompiled methods for class: WingLevelUp
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl WingLevelUp::~WingLevelUp(WingLevelUp *const this)
{
  WingLevelUp::~WingLevelUp(this);
  operator delete(this);
}


#####################################
int32_t __cdecl WingLevelUp::effect(
        WingLevelUp *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t ItemCount; // r14d
  int32_t ItemId; // r13d
  int32_t UpLevel; // r12d
  int32_t UseWingLevel; // ebx
  CExtCharWing *CharWing; // rax

  ItemCount = this->ItemCount;
  ItemId = this->ItemId;
  UpLevel = this->UpLevel;
  UseWingLevel = this->UseWingLevel;
  CharWing = Player::GetCharWing(launcher);
  if ( CExtCharWing::LevelUp(CharWing, UseWingLevel, UpLevel, ItemId, ItemCount) )
    return 0;
  else
    return 2;
}


#####################################
bool __cdecl WingLevelUp::parseEffect(WingLevelUp *const this, int32_t id, const std::string *const strEffect)
{
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  bool v11; // bl
  StringVector params; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v16[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v16);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v16);
  if ( std::vector<std::string>::size(&params) == 4 )
  {
    v3 = std::vector<std::string>::operator[](&params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->UseWingLevel = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->UpLevel = atoi(v6);
    v7 = std::vector<std::string>::operator[](&params, 2u);
    v8 = (const char *)std::string::c_str(v7);
    this->ItemId = atoi(v8);
    v9 = std::vector<std::string>::operator[](&params, 3u);
    v10 = (const char *)std::string::c_str(v9);
    this->ItemCount = atoi(v10);
    v11 = 1;
  }
  else
  {
    v11 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v11;
}


