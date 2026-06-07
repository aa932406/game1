// Decompiled methods for class: SkillBuff
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl SkillBuff::~SkillBuff(SkillBuff *const this)
{
  SkillBuff::~SkillBuff(this);
  operator delete(this);
}


#####################################
void __cdecl SkillBuff::interval(SkillBuff *const this)
{
  int32_t attackState; // [rsp+20h] [rbp-20h] BYREF
  int32_t hpchange; // [rsp+24h] [rbp-1Ch]
  int32_t nDamage; // [rsp+28h] [rbp-18h]
  int32_t nRealDamage; // [rsp+2Ch] [rbp-14h]

  hpchange = 0;
  attackState = 0;
  if ( this->m_cfgBuff->beneficial )
  {
    if ( this->m_cfgBuff->modify > 0 )
      hpchange = this->m_cfgBuff->modify * (__int64)this->m_nAtkMax / 10000;
    if ( this->m_cfgBuff->hpValue > 0 )
      hpchange += this->m_cfgBuff->hpValue;
    if ( this->m_cfgBuff->hpPecent > 0 )
      hpchange += this->m_cfgBuff->hpPecent
                * (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 20))(this->m_unit)
                / 100;
    (*((void (__fastcall **)(Unit *const, _QWORD))this->m_unit->_vptr_Entity + 21))(
      this->m_unit,
      (unsigned int)hpchange);
  }
  else
  {
    nDamage = 0;
    if ( this->m_cfgBuff->modify > 0 )
      nDamage = this->m_cfgBuff->modify * (__int64)this->m_nAtkMax / 10000;
    if ( this->m_cfgBuff->hpValue > 0 )
      nDamage += this->m_cfgBuff->hpValue;
    if ( this->m_cfgBuff->hpPecent > 0 )
      nDamage += this->m_cfgBuff->hpPecent
               * (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 20))(this->m_unit)
               / 100;
    nRealDamage = Unit::struckDamage(
                    this->m_unit,
                    nDamage,
                    &attackState,
                    this->m_cfgBuff->attack_type,
                    this->m_launcher,
                    this->m_Mid);
    hpchange -= nRealDamage;
  }
  if ( hpchange )
    SkillBuff::broadcastIntervalEffect(this, hpchange, attackState);
}


#####################################
bool __cdecl SkillBuff::init(
        SkillBuff *const this,
        int32_t skillid,
        int32_t atkMin,
        int32_t atkMax,
        int32_t phaseAdd,
        int32_t dmgAdd,
        int32_t skillModify,
        int32_t nAddTime)
{
  int32_t RunnerId; // r12d
  EntityId_t id; // rbx
  GameService *v10; // rax
  const Monster *pMonster; // [rsp+28h] [rbp-18h]

  this->m_skillid = skillid;
  this->m_nAtkMin = atkMin;
  this->m_nAtkMax = atkMax;
  this->m_nPhaseAdd = phaseAdd;
  this->m_nDmgAdd = dmgAdd;
  this->m_nSkillModify = skillModify;
  if ( this->m_launcher.type == 2 )
  {
    RunnerId = StaticObj::GetRunnerId(this->m_unit);
    id = this->m_launcher.id;
    v10 = Answer::Singleton<GameService>::instance();
    pMonster = GameService::getMonster(v10, id, RunnerId);
    if ( pMonster )
      this->m_Mid = Monster::getMid(pMonster);
  }
  return 1;
}


#####################################
void __cdecl SkillBuff::broadcastIntervalEffect(SkillBuff *const this, int32_t hpchange, int32_t attackState)
{
  GameService *v3; // rax
  int16_t x; // dx
  int16_t y; // dx
  int64_t v6; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  int16_t attackStatea; // [rsp+0h] [rbp-20h]
  Map *pMap; // [rsp+10h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  attackStatea = attackState;
  pMap = StaticObj::getMap(this->m_unit);
  if ( pMap )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2738u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt16(packet, this->m_skillid);
      Answer::NetPacket::writeInt64(packet, this->m_launcher.id);
      Answer::NetPacket::writeInt8(packet, this->m_launcher.type);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      x = StaticObj::getCurrentTile(this->m_unit).x;
      Answer::NetPacket::writeInt16(packet, x);
      y = StaticObj::getCurrentTile(this->m_unit).y;
      Answer::NetPacket::writeInt16(packet, y);
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt16(packet, 1);
      v6 = (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 2))(this->m_unit);
      Answer::NetPacket::writeInt64(packet, v6);
      Type = Entity::getType(this->m_unit);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt32(packet, hpchange);
      Answer::NetPacket::writeInt16(packet, attackStatea);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      Answer::NetPacket::writeInt32(packet, 0);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(pMap, packet, this->m_unit);
    }
  }
}


