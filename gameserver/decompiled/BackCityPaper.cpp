// Decompiled methods for class: BackCityPaper
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl BackCityPaper::~BackCityPaper(BackCityPaper *const this)
{
  BackCityPaper::~BackCityPaper(this);
  operator delete(this);
}


#####################################
int32_t __cdecl BackCityPaper::effect(
        BackCityPaper *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  const Map *pMap; // [rsp+28h] [rbp-8h]

  if ( !this->m_BXinMo )
    return Player::OnBackCity(launcher, 0, 1);
  pMap = StaticObj::getMap(launcher);
  if ( !pMap )
    return 10002;
  if ( !Map::IsXinMoMap(pMap) )
    return 10002;
  return Player::OnBackCity(launcher, 0, 0);
}


#####################################
bool __cdecl BackCityPaper::parseEffect(BackCityPaper *const this, int32_t id, const std::string *const strEffect)
{
  this->m_itemid = id;
  return 1;
}


