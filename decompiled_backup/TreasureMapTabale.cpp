// Decompiled methods for class: TreasureMapTabale
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl TreasureMapTabale::AddTreasureMapCfg(TreasureMapTabale *const this, TreasureMapCfg *p_stu)
{
  TreasureMapCfg *v2; // rax

  v2 = std::map<int,TreasureMapCfg>::operator[](&this->m_TreasureMapCfgMap, &p_stu->m_ItemId);
  TreasureMapCfg::operator=(v2, p_stu);
}


#####################################
void __cdecl TreasureMapTabale::AddTreasureMapEventCfg(TreasureMapTabale *const this, TreasureMapEventCfg *p_stu)
{
  TreasureMapEventCfg *v2; // rax

  v2 = std::map<int,TreasureMapEventCfg>::operator[](&this->m_TreasureMapEventCfgMap, &p_stu->m_EventId);
  TreasureMapEventCfg::operator=(v2, p_stu);
}


