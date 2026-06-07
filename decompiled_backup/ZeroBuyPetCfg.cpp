// Decompiled methods for class: ZeroBuyPetCfg
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl ZeroBuyPetCfg::IsEmpty(const ZeroBuyPetCfg *const this)
{
  return !this->nTime || std::vector<MemChrBag>::empty(&this->cItems) || !this->nGold || !this->nMailId;
}


