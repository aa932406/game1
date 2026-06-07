// Decompiled methods for class: CfgMysteryShopTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgMysteryShopTable::Add(CfgMysteryShopTable *const this, const CfgMysteryShop *const shop)
{
  *std::map<int,CfgMysteryShop>::operator[](&this->m_mMysteryShop, &shop->nId) = *shop;
  return 1;
}


