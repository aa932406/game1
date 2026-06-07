// Decompiled methods for class: CfgGoldEgg
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgGoldEgg::CleanUp(CfgGoldEgg *const this)
{
  this->nId = 0;
  this->nGroupId = 0;
  this->nOpenTimes = 0;
  this->nCostMoney = 0;
  this->nCostGold = 0;
  std::list<CfgGoldEggItem>::clear(&this->lstItem);
}


