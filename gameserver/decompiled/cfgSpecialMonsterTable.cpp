// Decompiled methods for class: cfgSpecialMonsterTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl cfgSpecialMonsterTable::Add(cfgSpecialMonsterTable *const this, cfgSpecialMonster *const stu)
{
  *std::map<int,cfgSpecialMonster>::operator[](&this->m_specialMonster, &stu->m_mid) = *stu;
}


