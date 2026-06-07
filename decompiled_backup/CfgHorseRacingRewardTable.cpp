// Decompiled methods for class: CfgHorseRacingRewardTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgHorseRacingRewardTable::Add(
        CfgHorseRacingRewardTable *const this,
        const CfgHorseRacingReward *const reward)
{
  std::list<CfgHorseRacingReward>::push_back(&this->m_rewards, reward);
}


