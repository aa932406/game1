// Decompiled methods for class: Jingyandan
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl Jingyandan::~Jingyandan(Jingyandan *const this)
{
  Jingyandan::~Jingyandan(this);
  operator delete(this);
}


#####################################
int32_t __cdecl Jingyandan::effect(
        Jingyandan *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( *count )
    Player::addExp(launcher, this->m_exp * (__int64)*count, 0, 1);
  else
    Player::addExp(launcher, this->m_exp, 0, 1);
  return 0;
}


#####################################
bool __cdecl Jingyandan::parseEffect(Jingyandan *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_exp = atoi(v3);
  return this->m_exp > 0;
}


