// Decompiled methods for class: BossDistribution
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl BossDistribution::AddBossLevelInfo(BossDistribution *const this, BossLevelInfo *p_stu)
{
  BossLevelInfo *v2; // rax

  v2 = std::map<int,BossLevelInfo>::operator[](&this->m_BossLevelInfoMap, &p_stu->BossLevel);
  BossLevelInfo::operator=(v2, p_stu);
}


#####################################
void __cdecl BossDistribution::AddMapBossInfo(BossDistribution *const this, MapBossInfo *p_stu)
{
  MapBossInfo *v2; // rax

  v2 = std::map<int,MapBossInfo>::operator[](&this->m_MapBossInfoMap, &p_stu->nId);
  MapBossInfo::operator=(v2, p_stu);
}


