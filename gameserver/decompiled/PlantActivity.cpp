// Decompiled methods for class: PlantActivity
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl PlantActivity::~PlantActivity(PlantActivity *const this)
{
  PlantActivity::~PlantActivity(this);
  operator delete(this);
}


#####################################
void __cdecl PlantActivity::init(
        PlantActivity *const this,
        CActivityMap *pActivityMap,
        const CfgPlant *const cfgPlant,
        const CfgMapPlant *const cfgMapPlant,
        int32_t nLifeTime)
{
  CTimer *v5; // rax

  if ( pActivityMap )
  {
    this->m_pActivityMap = pActivityMap;
    if ( nLifeTime > 0 )
    {
      v5 = Answer::Singleton<CTimer>::instance();
      this->m_nLifeTime = nLifeTime + CTimer::GetNow(v5);
    }
    Plant::init(this, pActivityMap, cfgPlant, cfgMapPlant, 0);
  }
}


#####################################
int32_t __cdecl PlantActivity::onBeginGather(PlantActivity *const this, Player *player)
{
  int32_t err; // [rsp+1Ch] [rbp-4h]

  err = Plant::onBeginGather(this, player);
  if ( !err )
    return CActivityMap::onBeginGather(this->m_pActivityMap, this, player);
  return err;
}


#####################################
int32_t __cdecl PlantActivity::onEndGather(PlantActivity *const this, Player *player)
{
  int32_t err; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 10002;
  err = Plant::onEndGather(this, player);
  if ( !err )
    CActivityMap::onPlantGather(this->m_pActivityMap, this, player);
  return err;
}


