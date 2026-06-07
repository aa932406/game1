// Decompiled methods for class: CfgExchange
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgExchange::CleanUp(CfgExchange *const this)
{
  this->nType = 0;
  this->nIndex = 0;
  this->nLimit = 0;
  std::list<ItemData>::clear(&this->vCost);
  std::vector<MemChrBag>::clear(&this->vReward);
}


