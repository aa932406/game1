// Decompiled methods for class: NpcActivity
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl NpcActivity::~NpcActivity(NpcActivity *const this)
{
  NpcActivity::~NpcActivity(this);
  operator delete(this);
}


#####################################
bool __cdecl NpcActivity::isLifeEnd(NpcActivity *const this)
{
  return this->m_endTime > 0 && Unit::getNow(this) >= this->m_endTime;
}


#####################################
void __cdecl NpcActivity::init(
        NpcActivity *const this,
        const CfgNpc *const cfgNpc,
        int32_t activity_id,
        int32_t lifetime)
{
  this->m_activityId = activity_id;
  this->m_endTime = lifetime + Unit::getNow(this) - 1;
  Npc::init(this, cfgNpc, this->m_endTime);
}


#####################################
void __cdecl NpcActivity::reset(NpcActivity *const this)
{
  Unit::reset(this);
  this->m_activityId = 0;
  this->m_endTime = 0;
}


