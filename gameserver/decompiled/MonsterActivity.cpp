// Decompiled methods for class: MonsterActivity
// Source: gameserver.cc
// Total methods: 15

#####################################
void __cdecl MonsterActivity::~MonsterActivity(MonsterActivity *const this)
{
  MonsterActivity::~MonsterActivity(this);
  operator delete(this);
}


#####################################
bool __cdecl MonsterActivity::refresh(MonsterActivity *const this)
{
  int64_t curTick; // [rsp+18h] [rbp-8h]

  if ( !this->m_pActivityMap )
    return 1;
  curTick = Map::getTick(this->m_pActivityMap);
  MonsterActivity::checkHpEvent(this, curTick);
  MonsterActivity::checkFamilyMoney(this, curTick);
  return Monster::refresh(this);
}


#####################################
void __cdecl MonsterActivity::init(
        MonsterActivity *const this,
        CActivityMap *pActMap,
        const CfgActivityMonster *const cfgActivityMonster,
        const CfgMonster *const cfgmonster,
        const CfgMapMonster *const cfgmapmonster)
{
  int32_t v5; // edx
  GameService *v6; // rax
  int32_t WorldLevel; // r13d
  int32_t mid; // r12d
  CfgData *v9; // rax
  int32_t buff; // ebx
  CfgData *v11; // rax
  int32_t v12; // edx
  Buff *v13; // rbx
  AttrAddonVector vAttrAddon; // [rsp+40h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+60h] [rbp-40h] BYREF
  CfgBuff *pCfgBuff; // [rsp+70h] [rbp-30h]
  Buff *pBuff; // [rsp+78h] [rbp-28h]

  if ( pActMap )
  {
    this->m_pActivityMap = pActMap;
    CfgActivityMonster::operator=(&this->m_cfgActivityMoster, cfgActivityMonster);
    if ( std::list<Position>::size(&this->m_cfgActivityMoster.road) )
      std::list<Position>::operator=(&this->m_road, &this->m_cfgActivityMoster.road);
    if ( this->m_cfgActivityMoster.left > 0 )
    {
      v5 = Unit::getNow(this) + this->m_cfgActivityMoster.left;
      Monster::SetLifeTime(this, v5);
    }
    v6 = Answer::Singleton<GameService>::instance();
    WorldLevel = GameService::GetWorldLevel(v6);
    mid = cfgmonster->mid;
    v9 = Answer::Singleton<CfgData>::instance();
    CfgData::GetAddMonsterAttrs(&vAttrAddon, v9, mid, WorldLevel);
    Monster::init(this, cfgmonster, cfgmapmonster, MonsterState::MS_STAND, &vAttrAddon);
    if ( this->m_cfgActivityMoster.buff > 0 )
    {
      buff = this->m_cfgActivityMoster.buff;
      v11 = Answer::Singleton<CfgData>::instance();
      pCfgBuff = CfgData::getBuff(v11, buff);
      if ( pCfgBuff )
      {
        launcher.id = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 12))(this);
        launcher.type = v12;
        v13 = (Buff *)operator new(0x60u);
        Buff::Buff(v13, this, pCfgBuff, &launcher, 3, 0);
        pBuff = v13;
        if ( v13 )
        {
          Unit::addBuff(this, pBuff);
          (*((void (__fastcall **)(MonsterActivity *const, __int64))this->_vptr_Entity + 22))(this, 100);
        }
      }
    }
    std::vector<AttrAddon>::~vector(&vAttrAddon);
  }
}


#####################################
void __cdecl MonsterActivity::reset(MonsterActivity *const this)
{
  Monster::reset(this);
  this->m_pActivityMap = 0;
  std::list<HPEvent>::clear(&this->m_hpEvents);
  std::list<Position>::clear(&this->m_road);
  this->m_nFamilyId = 0;
  this->m_nFamilyMoney = 0;
  this->m_nFamilyMoneyTick = 0;
}


#####################################
void __cdecl MonsterActivity::addEventHp(MonsterActivity *const this, const HPEvent *const hpEvent)
{
  std::list<HPEvent>::push_back(&this->m_hpEvents, hpEvent);
}


#####################################
void __cdecl MonsterActivity::die(MonsterActivity *const this)
{
  Monster::die(this);
  CActivityMap::onMonsterDie(this->m_pActivityMap, this);
  this->m_nFamilyMoney = 0;
}


#####################################
void __cdecl MonsterActivity::broadcastBasicData(MonsterActivity *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  int64_t v4; // rdx
  int64_t v5; // rdx
  int16_t v6; // dx
  int32_t v7; // edx
  uint32_t WOffset; // edx
  bool nflag; // [rsp+17h] [rbp-9h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    nflag = this->m_bDie;
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2739u);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      v4 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 19))(this);
      Answer::NetPacket::writeInt64(packet, v4);
      v5 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 20))(this);
      Answer::NetPacket::writeInt64(packet, v5);
      v6 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 28))(this);
      Answer::NetPacket::writeInt16(packet, v6);
      Answer::NetPacket::writeInt8(packet, nflag);
      v7 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 11))(this);
      Answer::NetPacket::writeInt32(packet, v7);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      if ( this->m_cfgmonster.boss_sign == 4 || this->m_cfgmonster.boss_sign == 8 )
        Map::broadcast(this->m_pMap, packet);
      else
        Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl MonsterActivity::destroy(MonsterActivity *const this)
{
  CPoolManager *v1; // rax

  v1 = Answer::Singleton<CPoolManager>::instance();
  CPoolManager::push<MonsterActivity>(v1, this);
}


#####################################
void __cdecl MonsterActivity::remove(MonsterActivity *const this)
{
  GameService *v1; // rax

  Monster::leaveMap(this);
  v1 = Answer::Singleton<GameService>::instance();
  GameService::removeMonster(v1, this);
  this->m_delFlag = 1;
}


#####################################
void __cdecl MonsterActivity::setKiller(MonsterActivity *const this, CharId_t nKiller)
{
  this->m_killer.id = nKiller;
  this->m_killer.type = 1;
}


#####################################
void __cdecl MonsterActivity::onArriveTarget(MonsterActivity *const this)
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
      if ( this->m_pActivityMap )
        CActivityMap::onMonsterArriveRoadEnd(this->m_pActivityMap, this);
    }
  }
}


#####################################
void __cdecl MonsterActivity::runOnRoad(MonsterActivity *const this)
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


#####################################
void __cdecl MonsterActivity::checkHpEvent(MonsterActivity *const this, int64_t curTick)
{
  HPEvent *v2; // rax
  HPEvent *v3; // rax
  HPEvent *v5; // rax
  std::_List_iterator<HPEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<HPEvent> __x; // [rsp+20h] [rbp-20h] BYREF
  int64_t curHp; // [rsp+28h] [rbp-18h]
  int64_t maxHp; // [rsp+30h] [rbp-10h]
  int32_t hpPercent; // [rsp+3Ch] [rbp-4h]

  if ( this->m_pActivityMap )
  {
    curHp = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 19))(this);
    maxHp = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 20))(this);
    hpPercent = roundInt((float)((float)((float)(int)curHp * 100.0) / (float)(int)maxHp));
    for ( it._M_node = std::list<HPEvent>::begin(&this->m_hpEvents)._M_node; ; std::_List_iterator<HPEvent>::operator++(&it) )
    {
      __x._M_node = std::list<HPEvent>::end(&this->m_hpEvents)._M_node;
      if ( !std::_List_iterator<HPEvent>::operator!=(&it, &__x) )
        break;
      v2 = std::_List_iterator<HPEvent>::operator->(&it);
      if ( v2->minhp <= hpPercent )
      {
        v3 = std::_List_iterator<HPEvent>::operator->(&it);
        if ( v3->maxhp > hpPercent )
        {
          v5 = std::_List_iterator<HPEvent>::operator->(&it);
          CActivityMap::onMonsterHPEvent(this->m_pActivityMap, this, v5->id);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl MonsterActivity::AddFamilyMoney(MonsterActivity *const this, int32_t nMoney)
{
  if ( !Unit::isAlive(this) )
    return 0;
  if ( !this->m_nFamilyId )
    return 0;
  this->m_nFamilyMoney += nMoney;
  return this->m_nFamilyMoney;
}


#####################################
void __cdecl MonsterActivity::checkFamilyMoney(MonsterActivity *const this, int64_t curTick)
{
  __int64 v2; // rbx
  int v3; // ebx
  int32_t v4; // eax
  int32_t needHp; // [rsp+18h] [rbp-18h]
  int32_t costMoney; // [rsp+1Ch] [rbp-14h]

  if ( curTick - this->m_nFamilyMoneyTick > 4999 && Unit::isAlive(this) && this->m_nFamilyMoney > 0 )
  {
    v2 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 19))(this);
    if ( v2 != (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 20))(this) )
    {
      v3 = (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 20))(this);
      needHp = v3 - (*((__int64 (__fastcall **)(MonsterActivity *const))this->_vptr_Entity + 19))(this);
      if ( needHp > 10000 )
        needHp = 10000;
      if ( needHp % 100 )
        v4 = needHp / 100 + 1;
      else
        v4 = needHp / 100;
      costMoney = v4;
      if ( this->m_nFamilyMoney < v4 )
        costMoney = this->m_nFamilyMoney;
      this->m_nFamilyMoney -= costMoney;
      (*((void (__fastcall **)(MonsterActivity *const, _QWORD))this->_vptr_Entity + 21))(
        this,
        (unsigned int)(100 * costMoney));
      this->m_nFamilyMoneyTick = curTick;
    }
  }
}


