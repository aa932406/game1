// Decompiled methods for class: cfgEquipUpPhaseTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl cfgEquipUpPhaseTable::AddData(cfgEquipUpPhaseTable *const this, cfgEquipUpPhase *const stu)
{
  std::list<cfgEquipUpPhase>::push_back(&this->m_cfgEquipUpPhase, stu);
}


