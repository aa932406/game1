// Decompiled methods for class: CfgBuyGift
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgBuyGift::CleanUp(CfgBuyGift *const this)
{
  this->nIndex = 0;
  this->nGold = 0;
  this->nBroad = 0;
  std::vector<MemChrBag>::clear(&this->vGift);
}


