// Decompiled methods for class: CfgExchangeTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgExchangeTable::Add(CfgExchangeTable *const this, const CfgExchange *const stu)
{
  std::list<CfgExchange>::push_back(&this->m_lstExchange, stu);
  return 1;
}


