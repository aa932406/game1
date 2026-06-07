// Decompiled methods for class: ShunJianHuiXue
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ShunJianHuiXue::~ShunJianHuiXue(ShunJianHuiXue *const this)
{
  ShunJianHuiXue::~ShunJianHuiXue(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ShunJianHuiXue::effect(
        ShunJianHuiXue *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( Unit::HasBuffState(launcher, CObjState::Index_T::OBS_YUNXUAN) )
    return 10002;
  (*((void (__fastcall **)(Player *const, _QWORD))launcher->_vptr_Entity + 21))(launcher, (unsigned int)this->m_addon);
  return 0;
}


#####################################
bool __cdecl ShunJianHuiXue::parseEffect(ShunJianHuiXue *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_addon = atoi(v3);
  return this->m_addon > 0;
}


