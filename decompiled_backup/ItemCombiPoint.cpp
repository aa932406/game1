// Decompiled methods for class: ItemCombiPoint
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ItemCombiPoint::~ItemCombiPoint(ItemCombiPoint *const this)
{
  ItemCombiPoint::~ItemCombiPoint(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ItemCombiPoint::effect(
        ItemCombiPoint *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // ebx
  CExtMagicBox *MagicBox; // rax

  if ( *count <= 0 )
    return 10002;
  v5 = *count * this->m_nValue;
  MagicBox = Player::GetMagicBox(launcher);
  if ( !CExtMagicBox::AddPoints(MagicBox, v5) )
    return 10002;
  else
    return 0;
}


#####################################
bool __cdecl ItemCombiPoint::parseEffect(ItemCombiPoint *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_nValue = atoi(v3);
  return this->m_nValue > 0;
}


