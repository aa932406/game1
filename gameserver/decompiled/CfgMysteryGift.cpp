// Decompiled methods for class: CfgMysteryGift
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgMysteryGift::CleanUp(CfgMysteryGift *const this)
{
  this->nIndex = 0;
  this->nType = 0;
  this->nCondition = 0;
  this->nBroadId = 0;
  std::vector<MemChrBag>::clear(&this->vItem);
}


