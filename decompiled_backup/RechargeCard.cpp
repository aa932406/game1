// Decompiled methods for class: RechargeCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl RechargeCard::~RechargeCard(RechargeCard *const this)
{
  RechargeCard::~RechargeCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl RechargeCard::effect(
        RechargeCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( *count <= 0 )
    return 10002;
  if ( !Player::UseRechargeCard(launcher, *count * this->m_addon, 1) )
    return 10002;
  return 0;
}


#####################################
bool __cdecl RechargeCard::parseEffect(RechargeCard *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_addon = atoi(v3);
  return this->m_addon > 0;
}


