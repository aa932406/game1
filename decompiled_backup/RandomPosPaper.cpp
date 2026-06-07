// Decompiled methods for class: RandomPosPaper
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl RandomPosPaper::~RandomPosPaper(RandomPosPaper *const this)
{
  RandomPosPaper::~RandomPosPaper(this);
  operator delete(this);
}


#####################################
int32_t __cdecl RandomPosPaper::effect(
        RandomPosPaper *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  return Player::OnRandPos(launcher);
}


#####################################
bool __cdecl RandomPosPaper::parseEffect(RandomPosPaper *const this, int32_t id, const std::string *const strEffect)
{
  this->m_itemid = id;
  return 1;
}


