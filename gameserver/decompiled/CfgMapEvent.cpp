// Decompiled methods for class: CfgMapEvent
// Source: gameserver.cc
// Total methods: 4

#####################################
bool __cdecl CfgMapEvent::isOpen(const CfgMapEvent *const this)
{
  return this->nOpenTime > 0 && !this->nCloseTime;
}


#####################################
bool __cdecl CfgMapEvent::isDone(const CfgMapEvent *const this)
{
  return this->nTrigTimes >= this->repeate;
}


#####################################
void __cdecl CfgMapEvent::trig(CfgMapEvent *const this, int64_t nTick)
{
  this->nTrigTime = nTick;
  ++this->nTrigTimes;
}


#####################################
void __cdecl CfgMapEvent::CleanUp(CfgMapEvent *const this)
{
  this->id = 0;
  this->mapid = 0;
  this->trigger_id = 0;
  this->trigger_type = 0;
  this->event_type = 0;
  std::string::operator=(&this->effect, &byte_8C33CF);
  this->repeate = 1;
  this->nOpenTime = 0;
  this->nTrigTime = 0;
  this->nTrigTimes = 0;
  this->nCloseTime = 0;
  this->bInitOpen = 0;
  std::vector<int>::clear(&this->trigger_param);
}


