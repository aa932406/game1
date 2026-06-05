// Decompiled methods for class: CfgOutLinkFestivalTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgOutLinkFestivalTable::Add(CfgOutLinkFestivalTable *const this, const CfgOutLinkFestival *const stu)
{
  std::list<CfgOutLinkFestival>::push_back(&this->m_lFestival, stu);
}


