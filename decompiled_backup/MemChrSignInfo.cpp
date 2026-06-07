// Decompiled methods for class: MemChrSignInfo
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl MemChrSignInfo::CleanUp(MemChrSignInfo *const this)
{
  this->sign_record = 0;
  this->refresh_time = 0;
  std::vector<signed char>::clear(&this->sign_reward);
}


