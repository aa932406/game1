// Decompiled methods for class: RechargeValueCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl RechargeValueCard::~RechargeValueCard(RechargeValueCard *const this)
{
  RechargeValueCard::~RechargeValueCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl RechargeValueCard::effect(
        RechargeValueCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( *count <= 0 )
    return 10002;
  if ( !Player::UseRechargeCard(launcher, *count * this->m_addon, 0) )
    return 10002;
  return 0;
}


#####################################
bool __cdecl RechargeValueCard::parseEffect(
        RechargeValueCard *const this,
        int32_t id,
        const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_addon = atoi(v3);
  return this->m_addon > 0;
}


