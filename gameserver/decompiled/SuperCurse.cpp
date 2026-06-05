// Decompiled methods for class: SuperCurse
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl SuperCurse::~SuperCurse(SuperCurse *const this)
{
  SuperCurse::~SuperCurse(this);
  operator delete(this);
}


#####################################
int32_t __cdecl SuperCurse::effect(
        SuperCurse *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( Player::getRecord(launcher, 1155) > 0 )
    return 2;
  Player::updateRecord(launcher, 1155, this->Value);
  Player::RecalcAttr(launcher);
  return 0;
}


#####################################
bool __cdecl SuperCurse::parseEffect(SuperCurse *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Value = atoi(v3);
  return this->Value > 0;
}


