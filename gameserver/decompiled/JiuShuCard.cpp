// Decompiled methods for class: JiuShuCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl JiuShuCard::~JiuShuCard(JiuShuCard *const this)
{
  JiuShuCard::~JiuShuCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl JiuShuCard::effect(
        JiuShuCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( Player::SubPkValues(launcher, this->m_addon) )
    return 0;
  else
    return 10002;
}


#####################################
bool __cdecl JiuShuCard::parseEffect(JiuShuCard *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_addon = atoi(v3);
  return this->m_addon > 0;
}


