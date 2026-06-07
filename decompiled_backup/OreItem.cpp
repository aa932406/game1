// Decompiled methods for class: OreItem
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl OreItem::~OreItem(OreItem *const this)
{
  OreItem::~OreItem(this);
  operator delete(this);
}


#####################################
int32_t __cdecl OreItem::effect(OreItem *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  int32_t v4; // ebx
  CExtCharFamily *CharFamily; // rax

  v4 = *count * this->m_Exp;
  CharFamily = Player::GetCharFamily(launcher);
  if ( !CExtCharFamily::AddMedRes(CharFamily, v4) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl OreItem::parseEffect(OreItem *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->m_nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Exp = atoi(v3);
  return this->m_Exp > 0;
}


