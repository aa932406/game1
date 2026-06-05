// Decompiled methods for class: AddStarVipTime
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl AddStarVipTime::~AddStarVipTime(AddStarVipTime *const this)
{
  AddStarVipTime::~AddStarVipTime(this);
  operator delete(this);
}


#####################################
int32_t __cdecl AddStarVipTime::effect(
        AddStarVipTime *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  CVip *PlayerVip; // rax
  int32_t Value; // ebx
  CVip *v7; // rax
  CVip *v8; // rax

  PlayerVip = Player::GetPlayerVip(launcher);
  if ( !CVip::HaveVipPrivilege(PlayerVip) )
    return 10002;
  Value = this->Value;
  v7 = Player::GetPlayerVip(launcher);
  CVip::AddVipTime(v7, 2, Value);
  v8 = Player::GetPlayerVip(launcher);
  CVip::SendVipInfo(v8);
  return 0;
}


#####################################
bool __cdecl AddStarVipTime::parseEffect(AddStarVipTime *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Value = atoi(v3);
  return this->Value > 0;
}


