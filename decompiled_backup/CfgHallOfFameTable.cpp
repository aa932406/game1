// Decompiled methods for class: CfgHallOfFameTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgHallOfFameTable::AddReward(CfgHallOfFameTable *const this, const HallOfFameReward *const reward)
{
  std::list<HallOfFameReward>::push_back(&this->m_rewards, reward);
}


