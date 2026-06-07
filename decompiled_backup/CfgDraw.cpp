// Decompiled methods for class: CfgDraw
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgDraw::Add(CfgDraw *const this, const CfgDrawReward *const reward)
{
  std::list<CfgDrawReward>::push_back(&this->m_rewards, reward);
  this->m_nMaxRate += reward->nRate;
}


