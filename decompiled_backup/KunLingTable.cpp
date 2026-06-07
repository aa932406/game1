// Decompiled methods for class: KunLingTable
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl KunLingTable::AddKunLevelUpCfg(KunLingTable *const this, KunLevelUpCfg *p_Stu)
{
  KunLevelUpCfg *v2; // rax

  v2 = std::map<int,KunLevelUpCfg>::operator[](&this->m_KunLevelUpCfgMap, &p_Stu->nLevel);
  KunLevelUpCfg::operator=(v2, p_Stu);
}


#####################################
void __cdecl KunLingTable::AddLingZhuCfg(KunLingTable *const this, LingZhuCfg *p_Stu)
{
  LingZhuCfg *v2; // rax

  v2 = std::map<int,LingZhuCfg>::operator[](&this->m_LingZhuCfgMap, &p_Stu->nId);
  LingZhuCfg::operator=(v2, p_Stu);
}


#####################################
void __cdecl KunLingTable::AddLingZhuPos(KunLingTable *const this, LingZhuPosCfg stu)
{
  LingZhuPosCfg *v2; // rax

  v2 = std::map<int,LingZhuPosCfg>::operator[](&this->m_LingZhuPosMap, &stu.nType);
  *v2 = stu;
}


#####################################
void __cdecl KunLingTable::AddLingZhuSuit(KunLingTable *const this, LingZhuSuit *p_Stu)
{
  LingZhuSuit *v2; // rax

  v2 = std::map<int,LingZhuSuit>::operator[](&this->m_LingZhuSuitMap, &p_Stu->nSuitId);
  LingZhuSuit::operator=(v2, p_Stu);
}


#####################################
void __cdecl KunLingTable::AddDanTianCfg(KunLingTable *const this, DanTianCfg *p_Stu)
{
  DanTianCfg *v2; // rax

  v2 = std::map<int,DanTianCfg>::operator[](&this->m_DanTianCfgMap, &p_Stu->nMid);
  DanTianCfg::operator=(v2, p_Stu);
}


#####################################
void __cdecl KunLingTable::AddLingZhuSkill(KunLingTable *const this, int32_t SuitLevel, LingZhuSkill Stu)
{
  int32_t SuitLevela; // [rsp+14h] [rbp-Ch] BYREF
  KunLingTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  SuitLevela = SuitLevel;
  *std::map<int,LingZhuSkill>::operator[](&this->m_LingZhuSkillMap, &SuitLevela) = Stu;
}


