// Decompiled methods for class: CfgFamilyDungeonTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgFamilyDungeonTable::AddDungeon(CfgFamilyDungeonTable *const this, const CfgFamilyDungeon *const stu)
{
  *std::map<signed char,CfgFamilyDungeon>::operator[](&this->m_mDungeon, &stu->nHard) = *stu;
}


