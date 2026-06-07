// Decompiled methods for class: TradeData
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl TradeData::OnClanup(TradeData *const this)
{
  this->BagSlot = -1;
  bzero(&this->CharBagData, 0x20u);
}


