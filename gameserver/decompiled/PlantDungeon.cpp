// Decompiled methods for class: PlantDungeon
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl PlantDungeon::~PlantDungeon(PlantDungeon *const this)
{
  PlantDungeon::~PlantDungeon(this);
  operator delete(this);
}


#####################################
void __cdecl PlantDungeon::init(
        PlantDungeon *const this,
        Dungeon *dungeon,
        const CfgPlant *const cfgPlant,
        const CfgMapPlant *const cfgMapPlant)
{
  if ( dungeon )
  {
    this->m_dungeon = dungeon;
    Plant::init(this, dungeon, cfgPlant, cfgMapPlant, 0);
  }
}


#####################################
int32_t __cdecl PlantDungeon::onEndGather(PlantDungeon *const this, Player *player)
{
  int32_t err; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 10002;
  err = Plant::onEndGather(this, player);
  if ( !err )
    Dungeon::onPlantGather(this->m_dungeon, this);
  return err;
}


#####################################
int32_t __cdecl PlantDungeon::onBeginGather(PlantDungeon *const this, Player *player)
{
  int32_t err; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 10002;
  err = Dungeon::onBeginGather(this->m_dungeon, player);
  if ( !err )
    return Plant::onBeginGather(this, player);
  return err;
}


