// Decompiled methods for class: MingGeItem
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl MingGeItem::~MingGeItem(MingGeItem *const this)
{
  MingGeItem::~MingGeItem(this);
  operator delete(this);
}


#####################################
int32_t __cdecl MingGeItem::effect(
        MingGeItem *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t m_Chip; // ebx
  CMingGeExt *CMingGeExt; // rax

  if ( *count > 1 )
    return 10002;
  m_Chip = this->m_Chip;
  CMingGeExt = Player::GetCMingGeExt(launcher);
  if ( !CMingGeExt::AddItem(CMingGeExt, m_Chip, ITEM_CHANGE_REASON::ICR_BAG_USE) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl MingGeItem::parseEffect(MingGeItem *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->m_nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_Chip = atoi(v3);
  return this->m_Chip > 0;
}


