// Decompiled methods for class: XinMoExp
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl XinMoExp::~XinMoExp(XinMoExp *const this)
{
  XinMoExp::~XinMoExp(this);
  operator delete(this);
}


#####################################
int32_t __cdecl XinMoExp::effect(
        XinMoExp *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // ebx
  CXinMo *CXinMo; // rax

  if ( *count <= 0 )
    return 2;
  v5 = *count * this->m_Exp;
  CXinMo = Player::GetCXinMo(launcher);
  CXinMo::AddExp(CXinMo, v5);
  return 0;
}


#####################################
bool __cdecl XinMoExp::parseEffect(XinMoExp *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->m_nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Exp = atoi(v3);
  return this->m_Exp > 0;
}


