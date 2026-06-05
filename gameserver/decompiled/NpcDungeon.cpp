// Decompiled methods for class: NpcDungeon
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl NpcDungeon::~NpcDungeon(NpcDungeon *const this)
{
  NpcDungeon::~NpcDungeon(this);
  operator delete(this);
}


#####################################
void __cdecl NpcDungeon::init(NpcDungeon *const this, Dungeon *dungeon, const CfgNpc *const cfgNpc)
{
  if ( dungeon )
  {
    this->m_dungeon = dungeon;
    Npc::init(this, cfgNpc, 0);
  }
}


#####################################
int32_t __cdecl NpcDungeon::onEndNpc(NpcDungeon *const this, Player *player, int8_t choice)
{
  if ( !player )
    return 10002;
  Dungeon::OnNpcEnd(this->m_dungeon, this, choice);
  return 0;
}


