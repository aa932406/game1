// Decompiled methods for class: PetShiHua
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl PetShiHua::~PetShiHua(PetShiHua *const this)
{
  PetShiHua::~PetShiHua(this);
  operator delete(this);
}


#####################################
int32_t __cdecl PetShiHua::effect(
        PetShiHua *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( Player::getRecord(launcher, 1153) > 0 )
    return 2;
  Player::updateRecord(launcher, 1153, this->Value);
  Player::RecalcAttr(launcher);
  Player::SetNeedSyncAround(launcher);
  Player::SetNeedSync(launcher);
  return 0;
}


#####################################
bool __cdecl PetShiHua::parseEffect(PetShiHua *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Value = atoi(v3);
  return this->Value > 0;
}


