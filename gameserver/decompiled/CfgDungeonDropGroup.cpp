// Decompiled methods for class: CfgDungeonDropGroup
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgDungeonDropGroup::CleanUp(CfgDungeonDropGroup *const this)
{
  this->m_nMaxWight = 0;
  std::list<CfgDungeonDrop>::clear(&this->m_lstDropItems);
}


#####################################
void __cdecl CfgDungeonDropGroup::Add(CfgDungeonDropGroup *const this, CfgDungeonDrop *const drop)
{
  this->m_nMaxWight += drop->weight;
  drop->weight = this->m_nMaxWight;
  std::list<CfgDungeonDrop>::push_back(&this->m_lstDropItems, drop);
}


