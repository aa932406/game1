// Decompiled methods for class: CfgBFZLEnterCostTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgBFZLEnterCostTable::AddEnterCost(
        CfgBFZLEnterCostTable *const this,
        int32_t nTimes,
        const ItemDataList *const vItem)
{
  std::list<ItemData> *v3; // rax
  int32_t nTimesa; // [rsp+14h] [rbp-Ch] BYREF
  CfgBFZLEnterCostTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nTimesa = nTimes;
  v3 = std::map<int,std::list<ItemData>>::operator[](&this->m_mEnterCost, &nTimesa);
  std::list<ItemData>::operator=(v3, vItem);
  return 1;
}


