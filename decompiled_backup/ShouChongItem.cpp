// Decompiled methods for class: ShouChongItem
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ShouChongItem::~ShouChongItem(ShouChongItem *const this)
{
  ShouChongItem::~ShouChongItem(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ShouChongItem::effect(
        ShouChongItem *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  if ( Player::getRecord(launcher, 37505) > 0 )
    return 2;
  Player::updateRecord(launcher, 37505, this->Value);
  Player::RecalcAttr(launcher);
  return 0;
}


#####################################
bool __cdecl ShouChongItem::parseEffect(ShouChongItem *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Value = atoi(v3);
  return this->Value > 0;
}


