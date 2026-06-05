// Decompiled methods for class: CfgFamily
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgFamily::CleanUp(CfgFamily *const this)
{
  this->nLevel = 0;
  this->nExp = 0;
  this->nMaxMembers = 0;
  this->nMaxBossPoints = 0;
  bzero(this->vPosition, 0x10u);
}


