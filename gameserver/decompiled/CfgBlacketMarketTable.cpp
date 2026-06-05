// Decompiled methods for class: CfgBlacketMarketTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgBlacketMarketTable::Add(
        CfgBlacketMarketTable *const this,
        int32_t nDays,
        int8_t nIndex,
        Job_t nJob,
        const MemChrBag *const item,
        int32_t nPrice,
        int32_t nBroadcast)
{
  BlackMarketIndex index; // [rsp+60h] [rbp-10h] BYREF
  CfgBlackMarketGoods cfgblackmarketgoods; // 0:^30.40

  *(_WORD *)(&index.nJob + 1) = 0;
  index.nDays = nDays;
  index.nIndex = nIndex;
  index.nJob = nJob;
  cfgblackmarketgoods.item = *(const MemChrBag *)item;
  *(_QWORD *)&cfgblackmarketgoods.nPrice = __PAIR64__(nBroadcast, nPrice);
  *std::map<BlackMarketIndex,CfgBlackMarketGoods>::operator[](&this->m_mMarketGoods, &index) = cfgblackmarketgoods;
  return 1;
}


