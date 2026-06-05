// Decompiled methods for class: GongMingZhi
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl GongMingZhi::~GongMingZhi(GongMingZhi *const this)
{
  GongMingZhi::~GongMingZhi(this);
  operator delete(this);
}


#####################################
int32_t __cdecl GongMingZhi::effect(
        GongMingZhi *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // ebx
  CGongMing *CGongMing; // rax

  if ( *count <= 0 )
    return 10002;
  v5 = *count * this->m_Chip;
  CGongMing = Player::GetCGongMing(launcher);
  CGongMing::AddGongMingValues(CGongMing, v5);
  return 0;
}


#####################################
bool __cdecl GongMingZhi::parseEffect(GongMingZhi *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->m_nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Chip = atoi(v3);
  return this->m_Chip > 0;
}


