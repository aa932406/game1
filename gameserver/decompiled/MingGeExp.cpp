// Decompiled methods for class: MingGeExp
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl MingGeExp::~MingGeExp(MingGeExp *const this)
{
  MingGeExp::~MingGeExp(this);
  operator delete(this);
}


#####################################
int32_t __cdecl MingGeExp::effect(
        MingGeExp *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // ebx
  CMingGeExt *CMingGeExt; // rax

  v4 = *count * this->m_Chip;
  CMingGeExt = Player::GetCMingGeExt(launcher);
  if ( !CMingGeExt::AddExp(CMingGeExt, v4) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl MingGeExp::parseEffect(MingGeExp *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->m_nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Chip = atoi(v3);
  return this->m_Chip > 0;
}


