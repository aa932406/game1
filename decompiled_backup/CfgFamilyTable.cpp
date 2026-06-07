// Decompiled methods for class: CfgFamilyTable
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CfgFamilyTable::CleanUp(CfgFamilyTable *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 9; ++i )
    CfgFamily::CleanUp(&this->m_vFamily[i]);
}


#####################################
bool __cdecl CfgFamilyTable::Add(CfgFamilyTable *const this, const CfgFamily *const family)
{
  if ( family->nLevel <= 0 || family->nLevel > 10 )
    return 0;
  this->m_vFamily[family->nLevel - 1] = *(const CfgFamily *)family;
  return 1;
}


#####################################
void __cdecl CfgFamilyTable::AddFamilyMedal(CfgFamilyTable *const this, const FamilyMedal *const stu)
{
  FamilyMedal *v2; // rax

  v2 = std::map<int,FamilyMedal>::operator[](&this->m_FamilyMedalMap, &stu->nLevel);
  FamilyMedal::operator=(v2, stu);
}


#####################################
void __cdecl CfgFamilyTable::AddFamilySelfMedal(CfgFamilyTable *const this, const FamilySelfMedal *const stu)
{
  FamilySelfMedal *v2; // rax

  v2 = std::map<int,FamilySelfMedal>::operator[](&this->m_FamilySelfMedalMap, &stu->nLevel);
  FamilySelfMedal::operator=(v2, stu);
}


#####################################
void __cdecl CfgFamilyTable::AddFamilyBoss(CfgFamilyTable *const this, const CfgFamilyBoss *const stu)
{
  *std::map<int,CfgFamilyBoss>::operator[](&this->m_mFamilyBoss, &stu->nFamilyLevel) = *stu;
  *std::map<int,CfgFamilyBoss>::operator[](&this->m_mFamilyBossByMid, &stu->BossMid) = *stu;
}


