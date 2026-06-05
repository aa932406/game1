// Decompiled methods for class: MonsterDungeon
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl MonsterDungeon::~MonsterDungeon(MonsterDungeon *const this)
{
  MonsterDungeon::~MonsterDungeon(this);
  operator delete(this);
}


#####################################
bool __cdecl MonsterDungeon::refresh(MonsterDungeon *const this)
{
  HPEvent *v1; // rax
  HPEvent *v2; // rax
  HPEvent *v4; // rax
  std::_List_iterator<HPEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<HPEvent> __x; // [rsp+20h] [rbp-20h] BYREF
  int64_t curHp; // [rsp+28h] [rbp-18h]
  int64_t maxHp; // [rsp+30h] [rbp-10h]
  int32_t hpPercent; // [rsp+3Ch] [rbp-4h]

  curHp = (*((__int64 (__fastcall **)(MonsterDungeon *const))this->_vptr_Entity + 19))(this);
  maxHp = (*((__int64 (__fastcall **)(MonsterDungeon *const))this->_vptr_Entity + 20))(this);
  hpPercent = roundInt((float)((float)((float)(int)curHp * 100.0) / (float)(int)maxHp));
  for ( it._M_node = std::list<HPEvent>::begin(&this->m_eventHp)._M_node; ; std::_List_iterator<HPEvent>::operator++(&it) )
  {
    __x._M_node = std::list<HPEvent>::end(&this->m_eventHp)._M_node;
    if ( !std::_List_iterator<HPEvent>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<HPEvent>::operator->(&it);
    if ( v1->minhp <= hpPercent )
    {
      v2 = std::_List_iterator<HPEvent>::operator->(&it);
      if ( v2->maxhp > hpPercent )
      {
        v4 = std::_List_iterator<HPEvent>::operator->(&it);
        Dungeon::onMonsterHPEvent(this->m_dungeon, this, v4->id);
      }
    }
  }
  return Monster::refresh(this);
}


#####################################
void __cdecl MonsterDungeon::init(
        MonsterDungeon *const this,
        Dungeon *dungeon,
        const CfgDungeonMonster *const cfgDungeonMonster,
        const CfgMonster *const cfgmonster,
        const CfgMapMonster *const cfgmapmonster)
{
  int32_t v5; // edx
  std::vector<AttrAddon> vAttrAddon; // [rsp+30h] [rbp-30h] BYREF

  if ( dungeon )
  {
    this->m_dungeon = dungeon;
    CfgDungeonMonster::operator=(&this->m_cfgDungeonMonster, cfgDungeonMonster);
    if ( std::list<Position>::size(&this->m_cfgDungeonMonster.road) )
      std::list<Position>::operator=(&this->m_road, &this->m_cfgDungeonMonster.road);
    if ( this->m_cfgDungeonMonster.life > 0 )
    {
      v5 = Unit::getNow(this) + this->m_cfgDungeonMonster.life;
      Monster::SetLifeTime(this, v5);
    }
    std::vector<AttrAddon>::vector(&vAttrAddon);
    Monster::init(this, cfgmonster, cfgmapmonster, MonsterState::MS_STAND, &vAttrAddon);
    std::vector<AttrAddon>::~vector(&vAttrAddon);
  }
}


#####################################
void __cdecl MonsterDungeon::reset(MonsterDungeon *const this)
{
  Monster::reset(this);
  this->m_dungeon = 0;
  std::list<HPEvent>::clear(&this->m_eventHp);
  std::list<Position>::clear(&this->m_road);
}


#####################################
int8_t __cdecl MonsterDungeon::getDungeonHard(const MonsterDungeon *const this)
{
  if ( this->m_dungeon )
    return Dungeon::GetHard(this->m_dungeon);
  else
    return 0;
}


#####################################
int8_t __cdecl MonsterDungeon::getDungeonQuality(const MonsterDungeon *const this)
{
  if ( this->m_dungeon )
    return Dungeon::GetQuality(this->m_dungeon);
  else
    return 0;
}


#####################################
void __cdecl MonsterDungeon::addEventHp(MonsterDungeon *const this, const HPEvent *const hpEvent)
{
  std::list<HPEvent>::push_back(&this->m_eventHp, hpEvent);
}


#####################################
void __cdecl MonsterDungeon::die(MonsterDungeon *const this)
{
  Monster::die(this);
  Dungeon::onMonsterDie(this->m_dungeon, this);
}


#####################################
void __cdecl MonsterDungeon::destroy(MonsterDungeon *const this)
{
  CPoolManager *v1; // rax

  v1 = Answer::Singleton<CPoolManager>::instance();
  CPoolManager::push<MonsterDungeon>(v1, this);
}


#####################################
void __cdecl MonsterDungeon::remove(MonsterDungeon *const this)
{
  GameService *v1; // rax

  Monster::leaveMap(this);
  v1 = Answer::Singleton<GameService>::instance();
  GameService::removeMonster(v1, this);
  this->m_delFlag = 1;
}


#####################################
void __cdecl MonsterDungeon::onArriveTarget(MonsterDungeon *const this)
{
  Position tarPos; // [rsp+10h] [rbp-20h] BYREF
  Position curPos; // [rsp+20h] [rbp-10h] BYREF

  if ( Monster::getState(this) == MonsterState::MS_RUN_ON_ROAD )
  {
    if ( !std::list<Position>::empty(&this->m_road) )
    {
      curPos = StaticObj::getCurrentTile(this);
      tarPos = *std::list<Position>::front(&this->m_road);
      std::list<Position>::pop_front(&this->m_road);
      do
      {
        if ( !Position::operator==(&curPos, &tarPos) )
          break;
        tarPos = *std::list<Position>::front(&this->m_road);
        std::list<Position>::pop_front(&this->m_road);
      }
      while ( !std::list<Position>::empty(&this->m_road) );
      Unit::setTargetTile(this, tarPos.x, tarPos.y);
    }
    else
    {
      Monster::setState(this, MonsterState::MS_STAND);
      if ( this->m_dungeon )
        Dungeon::onMonsterArriveRoadEnd(this->m_dungeon, this);
    }
  }
}


#####################################
void __cdecl MonsterDungeon::runOnRoad(MonsterDungeon *const this)
{
  Position tarPos; // [rsp+10h] [rbp-20h] BYREF
  Position curPos; // [rsp+20h] [rbp-10h] BYREF

  if ( !std::list<Position>::empty(&this->m_road) )
  {
    UnitHandle::clear(&this->m_target);
    curPos = StaticObj::getCurrentTile(this);
    tarPos = *std::list<Position>::front(&this->m_road);
    std::list<Position>::pop_front(&this->m_road);
    do
    {
      if ( !Position::operator==(&curPos, &tarPos) )
        break;
      tarPos = *std::list<Position>::front(&this->m_road);
      std::list<Position>::pop_front(&this->m_road);
    }
    while ( !std::list<Position>::empty(&this->m_road) );
    Unit::setTargetTile(this, tarPos.x, tarPos.y);
    Monster::setState(this, MonsterState::MS_RUN_ON_ROAD);
  }
}


