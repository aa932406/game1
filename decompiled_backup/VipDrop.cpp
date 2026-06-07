// Decompiled methods for class: VipDrop
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl VipDrop::~VipDrop(VipDrop *const this)
{
  VipDrop::~VipDrop(this);
  operator delete(this);
}


#####################################
int32_t __cdecl VipDrop::effect(VipDrop *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  int32_t v5; // r12d
  int32_t m_Type; // ebx
  CVip *PlayerVip; // rax

  if ( *count <= 0 )
    return 10002;
  v5 = *count;
  m_Type = this->m_Type;
  PlayerVip = Player::GetPlayerVip(launcher);
  if ( !CVip::AddVipLuckyDrop(PlayerVip, m_Type, v5) )
    return 10002;
  else
    return 0;
}


#####################################
bool __cdecl VipDrop::parseEffect(VipDrop *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Type = atoi(v3);
  return this->m_Type > 0;
}


