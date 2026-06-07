// Decompiled methods for class: CfgFamilyLightExpTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgFamilyLightExpTable::Add(CfgFamilyLightExpTable *const this, PassionBubbleCfg stu)
{
  if ( stu.X || stu.Y )
    std::list<PassionBubbleCfg>::push_back(&this->m_PassionBubbleCfgList, &stu);
  else
    this->m_PassionBase = stu;
}


