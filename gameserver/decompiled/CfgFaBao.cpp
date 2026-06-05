// Decompiled methods for class: CfgFaBao
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgFaBao::CleanUp(CfgFaBao *const this)
{
  this->FaBaoLevel = 0;
  this->NeedCurr = 0;
  this->nNeedLevel = 0;
  this->GongGaoId = 0;
  std::vector<AttrAddon>::clear(&this->vAttr);
}


