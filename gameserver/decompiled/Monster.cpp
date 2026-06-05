// Decompiled methods for class: Monster
// Source: gameserver.cc
// Total methods: 80

#####################################
void __cdecl Monster::~Monster(Monster *const this)
{
  Monster::~Monster(this);
  operator delete(this);
}


#####################################
bool __cdecl Monster::refresh(Monster *const this)
{
  Monster::updateState(this);
  Monster::checkHPRevive(this);
  Monster::checkLifeTime(this);
  if ( Monster::needCheckBossRank(this) )
  {
    Monster::checkEnterBossRegion(this);
    Monster::checkLeaveBossRegion(this);
    if ( this->m_DamageFlag )
    {
      Monster::refreshRank(this);
      Monster::SendAllDamageRank(this);
      this->m_DamageFlag = 0;
    }
  }
  Monster::ChangeOwner(this);
  Monster::SyncAround(this);
  if ( !Unit::isAlive(this) && this->m_state != MonsterState::MS_CORPSE && this->m_state != MonsterState::MS_GHOST )
    (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 46))(this);
  return 0;
}


#####################################
void __cdecl Monster::ChangeOwner(Monster *const this)
{
  int32_t RunnerId; // r12d
  CharId_t m_OwnerId; // rbx
  GameService *v3; // rax
  int32_t MapId; // ebx
  Player *Owner; // [rsp+18h] [rbp-18h]

  if ( this->m_ChangeOwner && this->m_OwnerLastAttack > 0 )
  {
    RunnerId = StaticObj::GetRunnerId(this);
    m_OwnerId = this->m_OwnerId;
    v3 = Answer::Singleton<GameService>::instance();
    Owner = GameService::getPlayer(v3, m_OwnerId, RunnerId, 1);
    if ( !Owner
      || (MapId = StaticObj::getMapId(Owner), MapId != Map::GetMapId(this->m_pMap))
      || Unit::getNow(this) - this->m_OwnerLastAttack > 5
      || !Unit::isAlive(Owner) )
    {
      std::string::operator=(&this->m_OwnerName, &unk_8E6560);
      this->m_OwnerId = 0;
      this->m_OwnerLastAttack = 0;
      Monster::SetNeedSyncAround(this);
    }
  }
}


#####################################
void __cdecl Monster::reset(Monster *const this)
{
  Unit::reset(this);
  this->m_lastActionTick = 0;
  this->m_standTick = 0;
  this->m_standTime = 0;
  this->m_corpseTick = 0;
  this->m_ghostTick = 0;
  this->m_attackTick = 0;
  this->m_attackTime = 0;
  this->m_nFamilyId = 0;
  this->m_lastUpdateMinute = 0;
  this->m_DieType = 0;
  this->m_bHPRevive = 0;
  this->m_delFlag = 0;
  this->m_nLastReviveHPTick = 0;
  this->m_nSyncTick = 0;
  this->m_nLastSyncTick = 0;
  this->m_nLifeTime = -1;
  this->m_nReviveTime = -1;
  this->m_nLastCheckBossTick = 0;
  this->m_DamageFlag = 0;
  this->m_nEscapeTick = 0;
  this->m_nHPPecent = 0;
  this->m_nEscapeDirection = Direction::DOWN;
  this->m_nRunTick = 0;
  std::string::operator=(&this->m_OwnerName, &unk_8E6560);
  this->m_OwnerId = 0;
  this->m_OwnerLastAttack = 0;
  this->m_NeedSyncAround = 0;
  std::map<long,PlayerScore>::clear(&this->m_PlayerScore);
  std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::clear(&this->m_ScoreRank);
  UnitHandle::clear(&this->m_target);
  UnitHandle::clear(&this->m_killer);
  std::list<long>::clear(&this->m_lDamager);
  std::vector<Position>::clear(&this->m_RevivePos);
  this->m_IsGroupMonster = 0;
  this->m_MaxRegion = 0;
  this->m_InRegion = 0;
  this->m_ChangeOwner = 1;
  this->m_nActivityId = 0;
  this->m_MonsterHp = 0;
  this->m_TunShi = 0;
  this->m_HaveItem = 1;
  std::string::operator=(&this->m_strFamilyName, &unk_8E6560);
  std::map<long,ActStruct>::clear(&this->m_ActStructMap);
  Monster::resetSkill(this);
}


#####################################
void __cdecl Monster::addDamager(Monster *const this, CharId_t cid)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<long int> v3; // rax
  CharId_t cida; // [rsp+0h] [rbp-40h] BYREF
  Monster *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<long int> __x; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<long int> v7; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  cida = cid;
  __x._M_node = std::list<long>::end(&this->m_lDamager)._M_node;
  M_node = std::list<long>::end(&this->m_lDamager)._M_node;
  v3._M_node = std::list<long>::begin(&this->m_lDamager)._M_node;
  v7._M_node = std::find<std::_List_iterator<long>,long>(v3, (std::_List_iterator<long int>)M_node, &cida)._M_node;
  if ( std::_List_iterator<long>::operator==(&v7, &__x) )
    std::list<long>::push_back(&thisa->m_lDamager, &cida);
}


#####################################
void __cdecl Monster::SetOwner(Monster *const this, CharId_t Cid, std::string *p_Name)
{
  this->m_OwnerId = Cid;
  std::string::operator=(&this->m_OwnerName, p_Name);
  this->m_OwnerLastAttack = Unit::getNow(this);
  Monster::SetNeedSyncAround(this);
}


#####################################
void __cdecl Monster::SetGroupMonster(Monster *const this, int32_t MaxRegion, int32_t InRegion)
{
  this->m_IsGroupMonster = 1;
  this->m_MaxRegion = MaxRegion;
  this->m_InRegion = InRegion;
}


#####################################
void __cdecl Monster::SetRevivePos(Monster *const this, std::vector<Position> *p_PosVector)
{
  std::vector<Position>::operator=(&this->m_RevivePos, p_PosVector);
}


#####################################
void __cdecl Monster::init(
        Monster *const this,
        const CfgMonster *const cfgMonster,
        const CfgMapMonster *const cfgMapMonster,
        MonsterState state,
        const AttrAddonVector *const vAttrAddon)
{
  int32_t ai; // ebx
  CfgData *v6; // rax
  int32_t Mid; // ebx
  CfgData *v8; // rax
  const cfgSpecialMonsterTable *SpecialMonster; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v14; // rax
  int *v15; // rax
  int v16; // ebx
  CfgData *v17; // rax
  const CfgMonsterRandTable *MonsterRandTable; // rax
  int32_t v19; // ebx
  int32_t v20; // ecx
  int32_t v21; // ebx
  int32_t v22; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i_4; // [rsp+30h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i_3; // [rsp+40h] [rbp-F0h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+50h] [rbp-E0h] BYREF
  Int32Vector vId; // [rsp+60h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > it; // [rsp+80h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+90h] [rbp-A0h] BYREF
  std::_List_iterator<int> __x; // [rsp+A0h] [rbp-90h] BYREF
  std::_List_const_iterator<int> v33; // [rsp+B0h] [rbp-80h] BYREF
  std::_List_iterator<int> v34; // [rsp+C0h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v35; // [rsp+D0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v36; // [rsp+E0h] [rbp-50h] BYREF
  CfgMonsterAI *pCfgMonsterAI; // [rsp+E8h] [rbp-48h]
  const cfgSpecialMonster *pCfgSpecialMonster; // [rsp+F0h] [rbp-40h]
  int32_t i; // [rsp+F8h] [rbp-38h]
  int32_t i_0; // [rsp+FCh] [rbp-34h]
  int32_t i_1; // [rsp+100h] [rbp-30h]
  int32_t j; // [rsp+104h] [rbp-2Ch]
  int32_t nSize; // [rsp+108h] [rbp-28h]
  int32_t i_2; // [rsp+10Ch] [rbp-24h]
  const CfgMonsterRand *pCfgRand; // [rsp+110h] [rbp-20h]
  int32_t i_5; // [rsp+11Ch] [rbp-14h]

  CfgMonster::operator=(&this->m_cfgmonster, cfgMonster);
  this->m_cfgmapmonster = *cfgMapMonster;
  this->m_MonsterHp = cfgMonster->MonsterHp;
  ai = this->m_cfgmonster.ai;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgMonsterAI = CfgData::GetMonsterAI(v6, ai);
  if ( pCfgMonsterAI )
    this->m_cfgMonsterAI = *pCfgMonsterAI;
  Mid = Monster::getMid(this);
  v8 = Answer::Singleton<CfgData>::instance();
  SpecialMonster = CfgData::GetSpecialMonster(v8);
  pCfgSpecialMonster = cfgSpecialMonsterTable::getSpecialMonster(SpecialMonster, Mid);
  if ( pCfgSpecialMonster )
    this->m_cfgSpecialMonster = *pCfgSpecialMonster;
  else
    bzero(&this->m_cfgSpecialMonster, 0x1Cu);
  for ( i = 0; i <= 49; ++i )
    Unit::SetAttrValue(this, (const CObjAttrs::Index_T)i, this->m_cfgmonster.vAttr[i]);
  for ( i_0 = 0; i_0 <= 9; ++i_0 )
  {
    this->m_vSkills[i_0].nId = this->m_cfgmonster.unique_skill[i_0].skillid;
    this->m_vSkills[i_0].nCDTime = 0;
  }
  for ( i_1 = 0; i_1 <= 9; ++i_1 )
  {
    if ( this->m_cfgmonster.random_skill[i_1].skillid > 0 )
    {
      for ( j = 0; j <= 9; ++j )
      {
        if ( !this->m_vSkills[j].nId )
          this->m_vSkills[j].nId = this->m_cfgmonster.random_skill[i_1].skillid;
      }
    }
  }
  if ( !std::vector<AttrAddon>::empty(vAttrAddon) )
  {
    for ( it._M_current = std::vector<AttrAddon>::begin(vAttrAddon)._M_current;
          ;
          __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<AttrAddon>::end(vAttrAddon)._M_current;
      if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&it, &__rhs) )
        break;
      addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it)->addon;
      index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it)->index;
      Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, addon);
    }
  }
  if ( cfgMonster->rand_count > 0 && !std::vector<int>::empty(&cfgMonster->rand_types) )
  {
    std::vector<int>::vector(&vId, &cfgMonster->rand_types);
    nSize = std::vector<int>::size(&cfgMonster->rand_types);
    if ( cfgMonster->rand_count < nSize )
    {
      nSize = cfgMonster->rand_count;
      M_current = std::vector<int>::end(&vId)._M_current;
      v14._M_current = std::vector<int>::begin(&vId)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
        v14,
        (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    }
    for ( i_2 = 0; i_2 < nSize; ++i_2 )
    {
      v15 = std::vector<int>::operator[](&vId, i_2);
      std::list<int>::push_back(&this->m_lRandType, v15);
    }
    std::vector<int>::~vector(&vId);
  }
  if ( !std::list<int>::empty(&this->m_lRandType) )
  {
    __x._M_node = std::list<int>::begin(&this->m_lRandType)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v34._M_node = std::list<int>::end(&this->m_lRandType)._M_node;
      std::_List_const_iterator<int>::_List_const_iterator(&v33, &v34);
      if ( !std::_List_const_iterator<int>::operator!=(&iter, &v33) )
        break;
      v16 = *std::_List_const_iterator<int>::operator*(&iter);
      v17 = Answer::Singleton<CfgData>::instance();
      MonsterRandTable = CfgData::GetMonsterRandTable(v17);
      pCfgRand = CfgMonsterRandTable::GetMonsterRand(MonsterRandTable, v16);
      if ( pCfgRand )
      {
        if ( !std::vector<AttrAddon>::empty(&pCfgRand->vAttrValue) )
        {
          for ( i_3._M_current = std::vector<AttrAddon>::begin(&pCfgRand->vAttrValue)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i_3) )
          {
            v35._M_current = std::vector<AttrAddon>::end(&pCfgRand->vAttrValue)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i_3, &v35) )
              break;
            v19 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_3)->addon;
            v20 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_3)->index;
            Unit::AddAttrValue(this, (const CObjAttrs::Index_T)v20, v19);
          }
        }
        if ( !std::vector<AttrAddon>::empty(&pCfgRand->vAttrRatio) )
        {
          for ( i_4._M_current = std::vector<AttrAddon>::begin(&pCfgRand->vAttrRatio)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i_4) )
          {
            v36._M_current = std::vector<AttrAddon>::end(&pCfgRand->vAttrRatio)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i_4, &v36) )
              break;
            v21 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_4)->addon;
            v22 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_4)->index;
            Unit::AddBuffAttrRatio(this, (const CObjAttrs::Index_T)v22, v21);
          }
        }
        if ( pCfgRand->nSkill > 0 )
        {
          for ( i_5 = 0; i_5 <= 9; ++i_5 )
          {
            if ( !this->m_vSkills[i_5].nId )
            {
              this->m_vSkills[i_5].nId = pCfgRand->nSkill;
              this->m_cfgmonster.unique_skill[i_5].skillid = pCfgRand->nSkill;
              this->m_cfgmonster.unique_skill[i_5].minHp = 0;
              this->m_cfgmonster.unique_skill[i_5].maxHp = 100;
              break;
            }
          }
        }
      }
      std::_List_const_iterator<int>::operator++(&iter);
    }
  }
  UnitHandle::clear(&this->m_killer);
  UnitHandle::clear(&this->m_target);
  this->m_pCfgSkill = 0;
  this->m_lastActionTick = 0;
  std::map<long,UnitHandle>::clear(&this->m_targetMap);
  this->m_standTick = 0;
  this->m_standTime = 0;
  this->m_corpseTick = 0;
  this->m_ghostTick = 0;
  this->m_reviveTick = 0;
  this->m_attackTick = 0;
  this->m_attackTime = 0;
  this->m_nHPPecent = 0;
  this->m_nEscapeTick = 0;
  this->m_nEscapeDirection = Direction::DOWN;
  this->m_IsGroupMonster = 0;
  this->m_MaxRegion = 0;
  this->m_InRegion = 0;
  std::vector<Position>::clear(&this->m_RevivePos);
  std::string::operator=(&this->m_OwnerName, &unk_8E6560);
  this->m_OwnerId = 0;
  this->m_OwnerLastAttack = 0;
  this->m_NeedSyncAround = 0;
  this->m_ChangeOwner = 1;
  this->m_TunShi = 0;
  this->m_HaveItem = 1;
  this->m_nActivityId = 0;
  std::string::operator=(&this->m_strFamilyName, &unk_8E6560);
  std::map<long,ActStruct>::clear(&this->m_ActStructMap);
  Monster::setState(this, state);
  if ( state == MonsterState::MS_STAND )
  {
    (*((void (__fastcall **)(Monster *const, __int64))this->_vptr_Entity + 22))(this, 100);
    this->m_nHPPecent = 100;
  }
}


#####################################
void __cdecl Monster::SetNeedSyncAround(Monster *const this)
{
  if ( this->m_cfgmonster.boss_sign > 0 )
    this->m_NeedSyncAround = 1;
}


#####################################
void __cdecl Monster::SyncAround(Monster *const this)
{
  GameService *v1; // rax
  int64_t v2; // rax
  uint32_t WOffset; // eax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  char v5; // [rsp+27h] [rbp-19h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_NeedSyncAround )
  {
    this->m_NeedSyncAround = 0;
    if ( this->m_pMap )
    {
      v1 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2D2Eu);
      if ( packet )
      {
        v2 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 2))(this);
        Answer::NetPacket::writeInt64(packet, v2);
        if ( this->m_cfgmonster.IsShowOwner )
        {
          Answer::NetPacket::writeUTF8(packet, &this->m_OwnerName);
        }
        else
        {
          std::allocator<char>::allocator(&v5);
          std::string::string(&val, &unk_8E6560);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          std::allocator<char>::~allocator(&v5);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Map::broadcastAreaAround(this->m_pMap, packet, this);
      }
    }
  }
}


#####################################
void __cdecl Monster::OnLevelUp(Monster *const this, const CfgMonster *const cfgMonster)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 49; ++i )
    Unit::SetAttrValue(this, (const CObjAttrs::Index_T)i, cfgMonster->vAttr[i]);
  CfgMonster::operator=(&this->m_cfgmonster, cfgMonster);
}


#####################################
bool __cdecl Monster::appendInfo(Monster *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx
  int32_t Mid; // edx
  int16_t x; // dx
  int16_t y; // dx
  int16_t v8; // dx
  int16_t v9; // dx
  int64_t v10; // rdx
  int32_t ReviveTime; // edx
  int64_t v12; // rdx
  int16_t v13; // dx
  int8_t Side; // dl
  int32_t id; // ebx
  CWorldBoss *v16; // rax
  int32_t BossLevel; // edx
  int8_t v18; // dl
  int v19; // edx
  std::_List_const_iterator<int> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<int> v22; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<int> v23; // [rsp+40h] [rbp-30h] BYREF
  std::string val; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v25[17]; // [rsp+5Fh] [rbp-11h] BYREF

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  Mid = Monster::getMid(this);
  Answer::NetPacket::writeInt32(packet, Mid);
  Answer::NetPacket::writeUTF8(packet, &this->m_strFamilyName);
  x = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, x);
  y = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, y);
  v8 = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, v8);
  v9 = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, v9);
  v10 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 19))(this);
  Answer::NetPacket::writeInt64(packet, v10);
  ReviveTime = Monster::getReviveTime(this);
  Answer::NetPacket::writeInt32(packet, ReviveTime);
  v12 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this);
  Answer::NetPacket::writeInt64(packet, v12);
  Unit::packageBuffList(this, packet);
  v13 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 28))(this);
  Answer::NetPacket::writeInt16(packet, v13);
  Side = Monster::getSide(this);
  Answer::NetPacket::writeInt8(packet, Side);
  Answer::NetPacket::writeInt64(packet, this->m_nFamilyId);
  id = this->m_cfgmapmonster.id;
  v16 = Answer::Singleton<CWorldBoss>::instance();
  BossLevel = CWorldBoss::GetBossLevel(v16, id);
  Answer::NetPacket::writeInt32(packet, BossLevel);
  v18 = std::list<int>::size(&this->m_lRandType);
  Answer::NetPacket::writeInt8(packet, v18);
  __x._M_node = std::list<int>::begin(&this->m_lRandType)._M_node;
  std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v23._M_node = std::list<int>::end(&this->m_lRandType)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&v22, &v23);
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &v22) )
      break;
    v19 = *std::_List_const_iterator<int>::operator*(&iter);
    Answer::NetPacket::writeInt32(packet, v19);
    std::_List_const_iterator<int>::operator++(&iter);
  }
  if ( this->m_cfgmonster.IsShowOwner )
  {
    Answer::NetPacket::writeUTF8(packet, &this->m_OwnerName);
  }
  else
  {
    std::allocator<char>::allocator(v25);
    std::string::string(&val, &unk_8E6560);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    std::allocator<char>::~allocator(v25);
  }
  return 1;
}


#####################################
void __cdecl Monster::Kill(Monster *const this, Player *pKiller)
{
  int v2; // edx
  __int64 src; // [rsp+20h] [rbp-20h] BYREF
  int v4; // [rsp+28h] [rbp-18h]

  Unit::setHP(this, 0);
  if ( pKiller )
  {
    src = (*((__int64 (__fastcall **)(Player *))pKiller->_vptr_Entity + 12))(pKiller);
    v4 = v2;
    if ( &this->m_killer != (UnitHandle *)&src )
      memcpy(&this->m_killer, &src, 0xCu);
  }
}


#####################################
int32_t __cdecl Monster::getReviveTime(const Monster *const this)
{
  int64_t nCurTick; // [rsp+10h] [rbp-10h]
  int32_t nNowTime; // [rsp+1Ch] [rbp-4h]

  if ( this->m_cfgmonster.revive_skin <= 0 )
    return 0;
  if ( this->m_nReviveTime >= 0 )
  {
    if ( this->m_nReviveTime > 0 )
    {
      nNowTime = Unit::getNow(this);
      if ( this->m_nReviveTime > nNowTime )
        return this->m_nReviveTime - nNowTime;
    }
  }
  else
  {
    nCurTick = Unit::getTick(this);
    if ( this->m_reviveTick > nCurTick )
      return (int)(this->m_reviveTick - nCurTick) / 1000;
  }
  return 0;
}


#####################################
bool __cdecl Monster::needDel(const Monster *const this)
{
  return this->m_delFlag && std::list<UnitAddonSkill>::empty(&this->m_lAddonSkill);
}


#####################################
void __cdecl Monster::destroy(Monster *const this)
{
  GameService *v1; // rax
  CPoolManager *v2; // rax

  v1 = Answer::Singleton<GameService>::instance();
  GameService::removeMonster(v1, this);
  v2 = Answer::Singleton<CPoolManager>::instance();
  CPoolManager::push<Monster>(v2, this);
}


#####################################
bool __cdecl Monster::isActivity(Monster *const this, int32_t Type, int32_t *const setValue)
{
  bool isFlg; // [rsp+27h] [rbp-1h]

  isFlg = 0;
  if ( this->m_cfgSpecialMonster.Type == Type )
  {
    isFlg = 1;
    *setValue = this->m_cfgSpecialMonster.Value;
  }
  return isFlg;
}


#####################################
bool __cdecl Monster::isActivity(Monster *const this, int32_t Type)
{
  return this->m_cfgSpecialMonster.Type == Type;
}


#####################################
void __cdecl Monster::SetFamilyId(Monster *const this, FamilyId_t fid, std::string *p_strFamilyName)
{
  this->m_nFamilyId = fid;
  std::string::operator=(&this->m_strFamilyName, p_strFamilyName);
  Unit::setNeedSync(this);
}


#####################################
void __cdecl Monster::broadcastIntoMap(Monster *const this)
{
  if ( this->m_pMap )
    Map::broadcastIntoMap(this->m_pMap, this);
}


#####################################
void __cdecl Monster::updateState(Monster *const this)
{
  switch ( this->m_state )
  {
    case MonsterState::MS_STAND:
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 42))(this);
      break;
    case MonsterState::MS_WALK_AROUND:
      Monster::onWalkAround(this);
      break;
    case MonsterState::MS_WALK_ATTACK:
      Monster::onWalkAttack(this);
      break;
    case MonsterState::MS_WALK_HOME:
      Monster::onWalkHome(this);
      break;
    case MonsterState::MS_ATTACK:
      Monster::onAttack(this);
      break;
    case MonsterState::MS_CORPSE:
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 43))(this);
      break;
    case MonsterState::MS_GHOST:
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 44))(this);
      break;
    case MonsterState::MS_RUN_ON_ROAD:
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 45))(this);
      break;
    case MonsterState::MS_ESCAPE:
      Monster::onEscape(this);
      break;
    case MonsterState::MS_RUN_AROUND:
      Monster::onRunAround(this);
      break;
    default:
      return;
  }
}


#####################################
void __cdecl Monster::onStand(Monster *const this)
{
  int v1; // edx
  Answer::Random *v3; // rax
  Answer::Random *v4; // rax
  Answer::Random *v5; // rax
  int32_t v6; // ebx
  Position targetTile; // [rsp+20h] [rbp-60h] BYREF
  __int64 src; // [rsp+30h] [rbp-50h] BYREF
  int v11; // [rsp+38h] [rbp-48h]
  Position pos; // [rsp+40h] [rbp-40h] BYREF
  int64_t nowTime; // [rsp+50h] [rbp-30h]
  Unit *pUnit; // [rsp+58h] [rbp-28h]
  Direction direciton; // [rsp+64h] [rbp-1Ch]
  int32_t steps; // [rsp+68h] [rbp-18h]
  int32_t i; // [rsp+6Ch] [rbp-14h]

  if ( this->m_pMap )
  {
    if ( !std::map<long,UnitHandle>::empty(&this->m_targetMap) )
      std::map<long,UnitHandle>::clear(&this->m_targetMap);
    if ( Monster::getViewRange(this) > 0 )
    {
      nowTime = Unit::getTick(this);
      if ( nowTime - this->m_attackTick >= this->m_attackTime )
      {
        this->m_attackTick = nowTime;
        pUnit = 0;
        pUnit = (Unit *)((this->m_cfgMonsterAI.style & 2) != 0
                       ? (*((__int64 (__fastcall **)(Map *, Monster *const))this->m_pMap->_vptr_Map + 26))(
                           this->m_pMap,
                           this)
                       : (*((__int64 (__fastcall **)(Map *, Monster *const))this->m_pMap->_vptr_Map + 25))(
                           this->m_pMap,
                           this));
        if ( pUnit )
        {
          src = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 12))(pUnit);
          v11 = v1;
          if ( &this->m_target != (UnitHandle *)&src )
            memcpy(&this->m_target, &src, 0xCu);
          Monster::setState(this, MonsterState::MS_ATTACK);
        }
      }
    }
    if ( Monster::getRestRange(this) > 0 && this->m_pMap && Unit::getTick(this) - this->m_standTick >= this->m_standTime )
    {
      v3 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v3, 1, 100) > this->m_cfgMonsterAI.rest_ratio )
      {
        Monster::setState(this, MonsterState::MS_STAND);
      }
      else
      {
        v4 = Answer::Singleton<Answer::Random>::instance();
        direciton = Monster::m_directions[Answer::Random::generate(v4, 0, 7)];
        v5 = Answer::Singleton<Answer::Random>::instance();
        steps = Answer::Random::generate(v5, 3, 5);
        targetTile = StaticObj::getCurrentTile(this);
        for ( i = 0; i < steps && Map::isWalkablePosition(this->m_pMap, targetTile.x, targetTile.y); ++i )
          targetTile = Map::getAroundTile(targetTile.x, targetTile.y, direciton);
        if ( Monster::getBossSign(this) <= 0
          && (Position::Position(&pos, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y),
              v6 = Position::tileDistance(&targetTile, &pos),
              v6 > Monster::getRestRange(this)) )
        {
          Monster::backHome(this);
        }
        else if ( Map::isWalkablePosition(this->m_pMap, targetTile.x, targetTile.y)
               && !Map::HaveUnit(this->m_pMap, targetTile.x, targetTile.y) )
        {
          Unit::setTargetTile(this, targetTile.x, targetTile.y);
          Monster::setState(this, MonsterState::MS_WALK_AROUND);
        }
      }
    }
  }
}


#####################################
void __cdecl Monster::onWalkAround(Monster *const this)
{
  if ( !Unit::isMoving(this) )
    Monster::setState(this, MonsterState::MS_STAND);
}


#####################################
void __cdecl Monster::onRunAround(Monster *const this)
{
  if ( !Unit::isMoving(this) )
    Monster::setState(this, MonsterState::MS_WALK_ATTACK);
}


#####################################
bool __cdecl Monster::AnyAttacks(Monster *const this, EntityId_t id)
{
  EntityId_t ida; // [rsp+0h] [rbp-30h] BYREF
  Monster *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const long int,UnitHandle> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,UnitHandle> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ida = id;
  it._M_node = std::map<long,UnitHandle>::find(&this->m_targetMap, &ida)._M_node;
  __x._M_node = std::map<long,UnitHandle>::end(&thisa->m_targetMap)._M_node;
  return std::_Rb_tree_iterator<std::pair<long const,UnitHandle>>::operator!=(&it, &__x);
}


#####################################
void __cdecl Monster::onWalkAttack(Monster *const this)
{
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v4; // rax
  Map *Map; // rbx
  int v7; // edx
  int32_t v8; // ebx
  int32_t v10; // ebx
  int32_t v12; // ebx
  bool v13; // al
  int32_t y; // r12d
  int32_t x; // eax
  Position pos; // [rsp+20h] [rbp-110h]
  __int64 src; // [rsp+30h] [rbp-100h] BYREF
  int v18; // [rsp+38h] [rbp-F8h]
  Position v19; // [rsp+40h] [rbp-F0h] BYREF
  Position v20; // [rsp+50h] [rbp-E0h] BYREF
  Position v21; // [rsp+60h] [rbp-D0h] BYREF
  Position v22; // [rsp+70h] [rbp-C0h] BYREF
  Position CurrentTile; // [rsp+80h] [rbp-B0h] BYREF
  Position v24; // [rsp+90h] [rbp-A0h] BYREF
  Position v25; // [rsp+A0h] [rbp-90h] BYREF
  Position v26; // [rsp+B0h] [rbp-80h] BYREF
  Position v27; // [rsp+C0h] [rbp-70h] BYREF
  Position v28; // [rsp+D0h] [rbp-60h] BYREF
  Position tar; // [rsp+E0h] [rbp-50h] BYREF
  Position v30; // [rsp+F0h] [rbp-40h] BYREF
  Unit *pUnit; // [rsp+F8h] [rbp-38h]
  Unit *pTarget; // [rsp+100h] [rbp-30h]
  Direction Dir; // [rsp+10Ch] [rbp-24h]

  RunnerId = StaticObj::GetRunnerId(this);
  type = this->m_target.type;
  id = this->m_target.id;
  v4 = Answer::Singleton<GameService>::instance();
  pUnit = GameService::getUnit(v4, id, type, RunnerId);
  if ( !pUnit
    || !Unit::isAlive(pUnit)
    || (Map = StaticObj::getMap(pUnit), Map != StaticObj::getMap(this))
    || !this->m_pCfgSkill )
  {
    if ( Monster::getViewRange(this) > 0
      && (pTarget = (Unit *)(*((__int64 (__fastcall **)(Map *, Monster *const))this->m_pMap->_vptr_Map + 25))(
                              this->m_pMap,
                              this)) != 0 )
    {
      src = (*((__int64 (__fastcall **)(Unit *))pTarget->_vptr_Entity + 12))(pTarget);
      v18 = v7;
      if ( &this->m_target != (UnitHandle *)&src )
        memcpy(&this->m_target, &src, 0xCu);
      Monster::setState(this, MonsterState::MS_ATTACK);
    }
    else
    {
      UnitHandle::clear(&this->m_target);
      Monster::setState(this, MonsterState::MS_STAND);
    }
  }
  else if ( Monster::getBossSign(this) <= 0
         && (Position::Position(&v19, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y),
             v20 = StaticObj::getCurrentTile(this),
             v8 = Position::tileDistance(&v20, &v19),
             v8 > Monster::getMoveRange(this)) )
  {
    Monster::backHome(this);
  }
  else if ( Monster::getBossSign(this) > 0
         && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap)
         && (Position::Position(&v21, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y),
             v22 = StaticObj::getCurrentTile(this),
             v10 = Position::tileDistance(&v22, &v21),
             v10 > Monster::getMoveRange(this)) )
  {
    Monster::flyHome(this);
  }
  else
  {
    CurrentTile = StaticObj::getCurrentTile(pUnit);
    v24 = StaticObj::getCurrentTile(this);
    if ( Position::tileDistance(&v24, &CurrentTile) )
    {
      v25 = StaticObj::getCurrentTile(pUnit);
      v26 = StaticObj::getCurrentTile(this);
      if ( Position::tileDistance(&v26, &v25) > this->m_pCfgSkill->distance )
      {
        v27 = StaticObj::getCurrentTile(pUnit);
        v28 = StaticObj::getCurrentTile(this);
        v12 = Position::tileDistance(&v28, &v27);
        if ( v12 <= Monster::getPursuitRange(this) )
        {
          v13 = Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
             || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
             || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
             || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
             || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN);
          if ( !v13 && !Unit::isMoving(this) )
          {
            tar = StaticObj::getCurrentTile(this);
            v30 = StaticObj::getCurrentTile(pUnit);
            Dir = Map::UnitDirection(&v30, &tar);
            y = StaticObj::getCurrentTile(pUnit).y;
            x = StaticObj::getCurrentTile(pUnit).x;
            pos = Map::getAroudFreeTileBuyDir(this->m_pMap, x, y, Dir);
            if ( Map::isWalkablePosition(this->m_pMap, pos.x, pos.y) )
              Unit::setTargetTile(this, pos.x, pos.y);
            else
              Monster::setState(this, MonsterState::MS_STAND);
          }
        }
        else
        {
          UnitHandle::clear(&this->m_target);
          Monster::setState(this, MonsterState::MS_STAND);
        }
      }
      else
      {
        Monster::setState(this, MonsterState::MS_ATTACK);
      }
    }
  }
}


#####################################
void __cdecl Monster::onWalkHome(Monster *const this)
{
  if ( !Unit::isMoving(this) )
  {
    if ( Monster::getSide(this) == 1 )
    {
      Unit::setAtTile(this, this->m_pMap, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
      UnitHandle::clear(&this->m_killer);
      UnitHandle::clear(&this->m_target);
      std::map<long,UnitHandle>::clear(&this->m_targetMap);
      this->m_lastActionTick = 0;
      this->m_standTick = 0;
      this->m_standTime = 0;
      this->m_corpseTick = 0;
      this->m_ghostTick = 0;
      this->m_reviveTick = 0;
      Monster::setState(this, MonsterState::MS_STAND);
    }
    else
    {
      if ( this->m_cfgmonster.hpPercent > 1000 )
      {
        UnitHandle::clear(&this->m_killer);
        UnitHandle::clear(&this->m_target);
        std::map<long,UnitHandle>::clear(&this->m_targetMap);
        this->m_lastActionTick = 0;
        this->m_standTick = 0;
        this->m_standTime = 0;
        this->m_corpseTick = 0;
        this->m_ghostTick = 0;
        (*((void (__fastcall **)(Monster *const, __int64))this->_vptr_Entity + 22))(this, 100);
        Monster::resetSkill(this);
      }
      else
      {
        UnitHandle::clear(&this->m_killer);
        UnitHandle::clear(&this->m_target);
        std::map<long,UnitHandle>::clear(&this->m_targetMap);
        this->m_lastActionTick = 0;
        this->m_standTick = 0;
        this->m_standTime = 0;
        this->m_corpseTick = 0;
        this->m_ghostTick = 0;
        this->m_pCfgSkill = 0;
      }
      Monster::setState(this, MonsterState::MS_STAND);
    }
  }
}


#####################################
void __cdecl Monster::onAttack(Monster *const this)
{
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v4; // rax
  int32_t y; // ebx
  int32_t x; // eax
  int32_t run_range; // ebx
  int32_t SkillFlag; // eax
  int32_t range; // eax
  int32_t v13; // edx
  int32_t v14; // r12d
  EntityId_t unitId; // rbx
  GameService *v16; // rax
  int32_t hpChange; // r12d
  int32_t addon_skill; // ebx
  CfgData *v19; // rax
  const CfgSkillTable *SkillTable; // rax
  void (__fastcall *v21)(Monster *const, _QWORD); // rbx
  unsigned int v22; // edx
  int v23; // edx
  UnitAddonSkill addonSkill; // [rsp+30h] [rbp-200h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > it; // [rsp+50h] [rbp-1E0h] BYREF
  UnitVector targets; // [rsp+60h] [rbp-1D0h] BYREF
  Position pos; // [rsp+80h] [rbp-1B0h]
  Position targetTile; // [rsp+90h] [rbp-1A0h] BYREF
  Position Pos; // [rsp+A0h] [rbp-190h] BYREF
  SkillResultVector results; // [rsp+B0h] [rbp-180h] BYREF
  Skill skill; // [rsp+D0h] [rbp-160h] BYREF
  Position param; // [rsp+E0h] [rbp-150h] BYREF
  Position CurrentTile; // [rsp+F0h] [rbp-140h] BYREF
  Position v34; // [rsp+100h] [rbp-130h] BYREF
  Position v35; // [rsp+110h] [rbp-120h] BYREF
  Position v36; // [rsp+120h] [rbp-110h] BYREF
  UnitHandle src; // [rsp+130h] [rbp-100h] BYREF
  Position tarPos; // [rsp+140h] [rbp-F0h] BYREF
  Position v39; // [rsp+150h] [rbp-E0h] BYREF
  Position v40; // [rsp+160h] [rbp-D0h] BYREF
  UnitHandle targetHandle; // [rsp+170h] [rbp-C0h]
  Position v42; // [rsp+180h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+190h] [rbp-A0h] BYREF
  UnitHandle launcher; // [rsp+1A0h] [rbp-90h]
  Position v45; // [rsp+1B0h] [rbp-80h] BYREF
  UnitHandle v46; // [rsp+1C0h] [rbp-70h] BYREF
  __int64 v47; // [rsp+1D0h] [rbp-60h] BYREF
  int v48; // [rsp+1D8h] [rbp-58h]
  int64_t curTick; // [rsp+1E0h] [rbp-50h]
  Unit *pTarget; // [rsp+1E8h] [rbp-48h]
  int32_t tileDistance; // [rsp+1F4h] [rbp-3Ch]
  Player *victm; // [rsp+1F8h] [rbp-38h]
  const CfgActiveSkill *pCfgSkill; // [rsp+200h] [rbp-30h]
  Unit *pNext; // [rsp+208h] [rbp-28h]
  Position v55; // 0:rax.8
  UnitHandle v56; // 0:rsi.8,8:edx.4

  curTick = Unit::getTick(this);
  if ( this->m_throwedTick > curTick || this->m_nSkillChantTime > curTick )
    return;
  if ( UnitHandle::isEmpty(&this->m_target) )
    goto LABEL_79;
  RunnerId = StaticObj::GetRunnerId(this);
  type = this->m_target.type;
  id = this->m_target.id;
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getUnit(v4, id, type, RunnerId);
  if ( !pTarget || !Unit::isAlive(pTarget) || StaticObj::getMap(pTarget) != this->m_pMap || !this->m_pCfgSkill )
  {
    if ( Monster::getViewRange(this) > 0 )
    {
      pNext = (Unit *)(*((__int64 (__fastcall **)(Map *, Monster *const))this->m_pMap->_vptr_Map + 25))(
                        this->m_pMap,
                        this);
      if ( pNext )
      {
        v47 = (*((__int64 (__fastcall **)(Unit *))pNext->_vptr_Entity + 12))(pNext);
        v48 = v23;
        if ( &this->m_target != (UnitHandle *)&v47 )
          memcpy(&this->m_target, &v47, 0xCu);
        Monster::setState(this, MonsterState::MS_ATTACK);
        return;
      }
    }
LABEL_79:
    Monster::setState(this, MonsterState::MS_STAND);
    return;
  }
  if ( !Unit::HasBuffState(this, CObjState::Index_T::OBS_CHENMO)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    param = StaticObj::getCurrentTile(pTarget);
    CurrentTile = StaticObj::getCurrentTile(this);
    if ( Position::operator==(&CurrentTile, &param) )
    {
      if ( Unit::isMoving(this) )
        return;
      y = StaticObj::getCurrentTile(this).y;
      x = StaticObj::getCurrentTile(this).x;
      Pos = Map::getAroudFreeTile(this->m_pMap, x, y);
      if ( Pos.x )
      {
        if ( Pos.y )
        {
          v34 = StaticObj::getCurrentTile(this);
          if ( Position::operator!=(&Pos, &v34) )
          {
            Unit::setTargetTile(this, Pos.x, Pos.y);
            Monster::setState(this, MonsterState::MS_WALK_ATTACK);
            return;
          }
        }
      }
    }
    v35 = StaticObj::getCurrentTile(pTarget);
    v36 = StaticObj::getCurrentTile(this);
    tileDistance = Position::tileDistance(&v36, &v35);
    if ( this->m_pCfgSkill->distance >= tileDistance )
    {
      if ( this->m_cfgMonsterAI.run_distance > 0
        && this->m_cfgMonsterAI.run_range > 0
        && this->m_cfgMonsterAI.run_distance > tileDistance
        && curTick - this->m_nRunTick >= this->m_cfgMonsterAI.run_cd )
      {
        run_range = this->m_cfgMonsterAI.run_range;
        tarPos = StaticObj::getCurrentTile(pTarget);
        targetTile = Monster::getRunPosition(this, &tarPos, run_range);
        v39 = StaticObj::getCurrentTile(this);
        if ( Position::operator!=(&targetTile, &v39) )
        {
          Unit::setTargetTile(this, targetTile.x, targetTile.y);
          Monster::setState(this, MonsterState::MS_RUN_AROUND);
          return;
        }
      }
      if ( Monster::getBossSign(this) <= 0 )
      {
        if ( curTick - this->m_lastActionTick <= 999 )
          return;
      }
      else if ( curTick - this->m_lastActionTick <= 2499 )
      {
        return;
      }
      Unit::setStand(this);
      if ( this->m_pCfgSkill->chantTime <= 0 || this->m_nSkillChantTime )
      {
        this->m_nSkillChantTime = 0;
        SkillFlag = Unit::GetSkillFlag(this, 1);
        Skill::Skill(&skill, this->m_pCfgSkill, SkillFlag);
        std::vector<SkillResult>::vector(&results);
        range = this->m_pCfgSkill->range;
        if ( range )
        {
          if ( range == 1 )
          {
            Position::Position(&v42, -1, -1);
            Skill::unitAction(&skill, this, this->m_target, &results, v42, 1);
          }
          else
          {
            pos = StaticObj::getCurrentTile(pTarget);
            if ( this->m_pCfgSkill->range == 4 || this->m_pCfgSkill->range == 2 )
              Unit::resetDirection(this, pos.x, pos.y);
            Map::getSkillTargets(&targets, this->m_pMap, this, pos, this->m_pCfgSkill);
            v55 = StaticObj::getCurrentTile(this);
            Skill::posAction(&skill, this, v55, pos, &targets, &results, 1);
            std::vector<Unit *>::~vector(&targets);
          }
        }
        else
        {
          Position::Position(&v40, -1, -1);
          targetHandle.id = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 12))(this);
          targetHandle.type = v13;
          Skill::unitAction(&skill, this, targetHandle, &results, v40, 1);
        }
        if ( !this->m_pCfgSkill->beneficial )
        {
          for ( it._M_current = std::vector<SkillResult>::begin(&results)._M_current;
                ;
                __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator++(&it) )
          {
            __rhs._M_current = std::vector<SkillResult>::end(&results)._M_current;
            if ( !__gnu_cxx::operator!=<SkillResult *,std::vector<SkillResult>>(&it, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 1 )
            {
              v14 = StaticObj::GetRunnerId(this);
              unitId = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitId;
              v16 = Answer::Singleton<GameService>::instance();
              victm = GameService::getPlayer(v16, unitId, v14, 1);
              if ( victm )
              {
                hpChange = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->hpChange;
                launcher.id = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 12))(this);
                launcher.type = v56.type;
                v56.id = launcher.id;
                Player::onDamagedEvent(victm, v56, hpChange);
              }
            }
          }
        }
        this->m_lastActionTick = curTick;
        if ( this->m_pCfgSkill->addon_skill > 0 )
        {
          addon_skill = this->m_pCfgSkill->addon_skill;
          v19 = Answer::Singleton<CfgData>::instance();
          SkillTable = CfgData::GetSkillTable(v19);
          pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, addon_skill);
          if ( pCfgSkill )
          {
            Position::Position(&v45, 0, 0);
            addonSkill.nLastTrigTime = 0;
            addonSkill.nTrigTimes = 0;
            addonSkill.sTargetPos = v45;
            addonSkill.pCfgSkill = pCfgSkill;
            addonSkill.nLastTrigTime = curTick + this->m_pCfgSkill->addon_delay;
            addonSkill.sTargetPos = StaticObj::getCurrentTile(pTarget);
            std::list<UnitAddonSkill>::push_back(&this->m_lAddonSkill, &addonSkill);
          }
        }
        if ( Monster::isTrap(this) )
        {
          v21 = (void (__fastcall *)(Monster *const, _QWORD))*((_QWORD *)this->_vptr_Entity + 21);
          v22 = -(*((int (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this);
          v21(this, v22);
        }
        else
        {
          if ( this->m_pCfgSkill->chantTime <= 0 )
            Monster::setSkillCD(this, this->m_pCfgSkill->id, this->m_pCfgSkill->cd);
          Monster::refreshSkill(this, 0);
          v46 = Monster::randHandle(this, this->m_target.id);
          if ( &this->m_target != &v46 )
            memcpy(&this->m_target, &v46, 0xCu);
          std::map<long,UnitHandle>::clear(&this->m_targetMap);
        }
        std::vector<SkillResult>::~vector(&results);
        Skill::~Skill(&skill);
      }
      else
      {
        Unit::broadcastSkillChant(this, this->m_pCfgSkill->id, this->m_pCfgSkill->chantTime);
        this->m_nSkillChantTime = curTick + this->m_pCfgSkill->chantTime;
        Monster::setSkillCD(this, this->m_pCfgSkill->id, this->m_pCfgSkill->cd);
      }
    }
    else if ( std::map<long,UnitHandle>::empty(&this->m_targetMap) )
    {
      Monster::setState(this, MonsterState::MS_WALK_ATTACK);
    }
    else
    {
      src = Monster::randHandle(this, 0);
      if ( &this->m_target != &src )
        memcpy(&this->m_target, &src, 0xCu);
      std::map<long,UnitHandle>::clear(&this->m_targetMap);
    }
  }
}


#####################################
void __cdecl Monster::onEscape(Monster *const this)
{
  if ( this->m_pMap && Unit::getTick(this) - this->m_nEscapeTick > 9999 )
  {
    if ( UnitHandle::isEmpty(&this->m_target) )
      Monster::setState(this, MonsterState::MS_STAND);
    else
      Monster::setState(this, MonsterState::MS_ATTACK);
  }
}


#####################################
void __cdecl Monster::setEscapeTarget(Monster *const this)
{
  int32_t v1; // ebx
  Position nextTile; // [rsp+10h] [rbp-50h]
  Position targetTile; // [rsp+20h] [rbp-40h] BYREF
  Position pos; // [rsp+30h] [rbp-30h] BYREF
  Position param; // [rsp+40h] [rbp-20h] BYREF

  for ( targetTile = StaticObj::getCurrentTile(this); ; targetTile = nextTile )
  {
    Position::Position(&pos, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
    v1 = Position::tileDistance(&targetTile, &pos);
    if ( v1 >= Monster::getMoveRange(this) )
      break;
    nextTile = Map::getAroundTile(targetTile.x, targetTile.y, this->m_nEscapeDirection);
    if ( !Map::isWalkablePosition(this->m_pMap, nextTile.x, nextTile.y) )
      break;
  }
  param = StaticObj::getCurrentTile(this);
  if ( Position::operator!=(&targetTile, &param) )
    Unit::setTargetTile(this, targetTile.x, targetTile.y);
}


#####################################
bool __cdecl Monster::checkSkillTarget(Monster *const this, const CfgActiveSkill *pCfg, Unit *pUnit)
{
  FamilyId_t FamilyId; // rbx
  int32_t RunnerId; // r12d
  GameService *v6; // rax
  Position pos; // [rsp+20h] [rbp-40h] BYREF
  Monster *monster; // [rsp+30h] [rbp-30h]
  CObjPet *pPet; // [rsp+38h] [rbp-28h]
  CharId_t ownerId; // [rsp+40h] [rbp-20h]
  Player *player_0; // [rsp+48h] [rbp-18h]

  if ( !pCfg || !pUnit || !this->m_pMap )
    return 0;
  if ( !Unit::isAlive(pUnit) )
    return 0;
  if ( Entity::getType(pUnit) == EntityType::ET_PLAYER )
  {
    return (this->m_cfgMonsterAI.target & 2) != 0
        && __dynamic_cast(
             pUnit,
             (const struct __class_type_info *)&`typeinfo for'Unit,
             (const struct __class_type_info *)&`typeinfo for'Player,
             0)
        && Monster::getSide(this) != 1;
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_MONSTER )
  {
    if ( (this->m_cfgMonsterAI.target & 4) != 0 )
    {
      monster = (Monster *)__dynamic_cast(
                             pUnit,
                             (const struct __class_type_info *)&`typeinfo for'Unit,
                             (const struct __class_type_info *)&`typeinfo for'Monster,
                             0);
      if ( monster )
      {
        FamilyId = Monster::GetFamilyId(this);
        return FamilyId != Monster::GetFamilyId(monster);
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_PET )
  {
    if ( (this->m_cfgMonsterAI.target & 0x10) != 0 )
    {
      pPet = (CObjPet *)__dynamic_cast(
                          pUnit,
                          (const struct __class_type_info *)&`typeinfo for'Unit,
                          (const struct __class_type_info *)&`typeinfo for'CObjPet,
                          0);
      if ( pPet )
      {
        ownerId = (*((__int64 (__fastcall **)(CObjPet *))pPet->_vptr_Entity + 4))(pPet);
        RunnerId = StaticObj::GetRunnerId(this);
        v6 = Answer::Singleton<GameService>::instance();
        player_0 = GameService::getPlayer(v6, ownerId, RunnerId, 1);
        if ( player_0 )
        {
          pos = StaticObj::getCurrentTile(player_0);
          return !Map::inSafeRegion(this->m_pMap, &pos) && Monster::getSide(this) != 1;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl Monster::onCorpse(Monster *const this)
{
  if ( Monster::isTrap(this) )
  {
    Monster::leaveMap(this);
    Monster::setState(this, MonsterState::MS_GHOST);
  }
  else if ( this->m_TunShi || Unit::getTick(this) - this->m_corpseTick >= this->m_cfgmonster.corpse_time )
  {
    Monster::leaveMap(this);
    Monster::setState(this, MonsterState::MS_GHOST);
    if ( Monster::IsShow(this) )
    {
      Unit::setAtTile(this, this->m_pMap, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
      Monster::broadcastIntoMap(this);
    }
  }
}


#####################################
void __cdecl Monster::onGhost(Monster *const this)
{
  Map *m_pMap; // r12
  int32_t id; // ebx
  CWorldBoss *v3; // rax
  Map *v4; // r12
  int32_t v5; // ebx
  CWorldBoss *v6; // rax
  int32_t MapId; // eax
  Position Pos_0; // [rsp+10h] [rbp-30h]
  Position Pos; // [rsp+20h] [rbp-20h]
  Position ReviveX; // 0:^28.8

  if ( !this->m_delFlag )
  {
    if ( this->m_nReviveTime >= 0 )
    {
      if ( this->m_nReviveTime <= 0 || Unit::getNow(this) < this->m_nReviveTime )
        return;
    }
    else if ( Unit::getTick(this) < this->m_reviveTick )
    {
      return;
    }
    ReviveX = *(Position *)&this->m_cfgmapmonster.x;
    if ( this->m_cfgmonster.boss_sign == 3 )
    {
      m_pMap = this->m_pMap;
      id = this->m_cfgmapmonster.id;
      v3 = Answer::Singleton<CWorldBoss>::instance();
      CWorldBoss::OnBossRevive(v3, id, m_pMap, this);
      this->m_nReviveTime = 0;
    }
    else
    {
      if ( this->m_cfgmonster.boss_sign )
      {
        v4 = this->m_pMap;
        v5 = this->m_cfgmapmonster.id;
        v6 = Answer::Singleton<CWorldBoss>::instance();
        Pos = CWorldBoss::OnBossRevive(v6, v5, v4, this);
        if ( Pos.x > 0 && Pos.y > 0 )
          ReviveX = Pos;
      }
      if ( this->m_IsGroupMonster )
      {
        Pos_0 = Monster::GetGroupMonsterPos(this);
        if ( Pos_0.x <= 0 || Pos_0.y <= 0 )
        {
          ReviveX = *(Position *)&this->m_cfgmapmonster.x;
          MapId = StaticObj::getMapId(this);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "groupmonster x = %d, y =%d,mid=%d,mapid=%d\n",
            Pos_0.x,
            Pos_0.y,
            this->m_cfgmonster.mid,
            MapId);
        }
        else
        {
          ReviveX = Pos_0;
        }
      }
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 47))(this);
      Unit::setAtTile(this, this->m_pMap, ReviveX.x, ReviveX.y);
      Monster::broadcastIntoMap(this);
      Monster::setState(this, MonsterState::MS_STAND);
    }
  }
}


#####################################
void __cdecl Monster::OnRevive(Monster *const this)
{
  (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 47))(this);
  Unit::setAtTile(this, this->m_pMap, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
  Monster::broadcastIntoMap(this);
  Monster::setState(this, MonsterState::MS_STAND);
}


#####################################
bool __cdecl Monster::IsShow(Monster *const this)
{
  return Unit::isAlive(this) || this->m_cfgmonster.revive_skin > 0;
}


#####################################
void __cdecl Monster::onRunOnRoad(Monster *const this)
{
  int64_t nowTime; // [rsp+10h] [rbp-10h]
  Unit *pUnit; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    if ( Monster::getViewRange(this) > 0 )
    {
      nowTime = Unit::getTick(this);
      if ( nowTime - this->m_attackTick >= this->m_attackTime )
      {
        this->m_attackTick = nowTime;
        pUnit = (Unit *)(*((__int64 (__fastcall **)(Map *, Monster *const))this->m_pMap->_vptr_Map + 25))(
                          this->m_pMap,
                          this);
        if ( pUnit )
        {
          this->m_target.id = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 2))(pUnit);
          this->m_target.type = Entity::getType(pUnit);
          Monster::setState(this, MonsterState::MS_ATTACK);
        }
      }
    }
  }
}


#####################################
bool __cdecl Monster::needSync(Monster *const this)
{
  int64_t curTick; // [rsp+18h] [rbp-8h]

  if ( this->m_nSyncTick > 0 )
  {
    if ( !Unit::needSync(this) )
      return 0;
    curTick = Unit::getTick(this);
    if ( curTick - this->m_nLastSyncTick < this->m_nSyncTick )
      return 0;
    this->m_nLastSyncTick = curTick;
  }
  return Unit::needSync(this);
}


#####################################
void __cdecl Monster::setState(Monster *const this, MonsterState state)
{
  Answer::Random *v2; // rax
  int32_t rest_time_max; // r12d
  int32_t rest_time_min; // ebx
  Answer::Random *v5; // rax
  __int64 v6; // rbx
  int64_t m_ghostTick; // rbx

  switch ( state )
  {
    case MonsterState::MS_STAND:
      this->m_attackTick = Unit::getTick(this);
      v2 = Answer::Singleton<Answer::Random>::instance();
      this->m_attackTime = Answer::Random::generate(v2, 10, 200);
      this->m_standTick = this->m_attackTick;
      rest_time_max = this->m_cfgMonsterAI.rest_time_max;
      rest_time_min = this->m_cfgMonsterAI.rest_time_min;
      v5 = Answer::Singleton<Answer::Random>::instance();
      this->m_standTime = Answer::Random::generate(v5, rest_time_min, rest_time_max);
      this->m_targetPos = StaticObj::getCurrentPixel(this);
      this->m_targetTile = StaticObj::getCurrentTile(this);
      break;
    case MonsterState::MS_WALK_AROUND:
    case MonsterState::MS_WALK_ATTACK:
    case MonsterState::MS_RUN_ON_ROAD:
      break;
    case MonsterState::MS_WALK_HOME:
      if ( this->m_cfgmonster.hpPercent > 0 )
      {
        v6 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 19))(this);
        if ( v6 < (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this) )
          this->m_bHPRevive = 1;
      }
      break;
    case MonsterState::MS_ATTACK:
      if ( !this->m_pCfgSkill )
        Monster::refreshSkill(this, 0);
      break;
    case MonsterState::MS_CORPSE:
      this->m_corpseTick = Unit::getTick(this);
      break;
    case MonsterState::MS_GHOST:
      if ( Monster::GetMonsterCfgReviveTime(this) <= 0 )
      {
        this->m_delFlag = 1;
      }
      else
      {
        this->m_ghostTick = Unit::getTick(this);
        if ( this->m_reviveTick < this->m_ghostTick )
        {
          m_ghostTick = this->m_ghostTick;
          this->m_reviveTick = m_ghostTick + Monster::GetMonsterCfgReviveTime(this);
        }
      }
      break;
    case MonsterState::MS_ESCAPE:
      this->m_nEscapeTick = Unit::getTick(this);
      Monster::setEscapeTarget(this);
      break;
    case MonsterState::MS_RUN_AROUND:
      this->m_nRunTick = Unit::getTick(this);
      break;
    default:
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Monster::setState unknown state %d\n", state);
      break;
  }
  this->m_state = state;
}


#####################################
void __cdecl Monster::onSendKillerReward(Monster *const this, Player *pPlayer)
{
  Answer::Random *v2; // rax
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t PosX; // edx
  int32_t PosY; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( pPlayer )
  {
    if ( this->m_cfgSpecialMonster.Award > 0 )
    {
      v2 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v2, 1, 10000) > this->m_cfgSpecialMonster.Portal )
      {
        ConnId = Player::getConnId(pPlayer);
        v4 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D2Cu);
        if ( packet )
        {
          PosX = StaticObj::GetPosX(this);
          Answer::NetPacket::writeInt32(packet, PosX);
          PosY = StaticObj::GetPosY(this);
          Answer::NetPacket::writeInt32(packet, PosY);
          Answer::NetPacket::writeInt32(packet, this->m_cfgSpecialMonster.Award);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(pPlayer);
          v9 = Player::getConnId(pPlayer);
          v10 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v10, v9, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl Monster::CanAddBossSocre(Monster *const this, Player *pPlayer, int32_t nAddValue)
{
  int32_t result; // eax
  CXingMai *XingMai; // rax
  int32_t AlreadyGet; // [rsp+28h] [rbp-8h]
  int CanGetMax; // [rsp+2Ch] [rbp-4h]

  if ( !pPlayer )
    return 0;
  AlreadyGet = Player::getRecord(pPlayer, 2083);
  XingMai = Player::GetXingMai(pPlayer);
  CanGetMax = CXingMai::GetMaxBossScore(XingMai);
  if ( CanGetMax <= 0 )
    return 0;
  result = nAddValue;
  if ( CanGetMax - AlreadyGet <= nAddValue )
    return CanGetMax - AlreadyGet;
  return result;
}


#####################################
void __cdecl Monster::die(Monster *const this)
{
  int8_t autoPick; // r14
  int8_t bossSign; // r13
  int32_t MonsterMid; // r12d
  ChrTask *Task; // rax
  int32_t BossSocre; // ebx
  CFestivalDoubleEleven *v7; // rax
  int32_t Record; // eax
  int32_t level; // ebx
  CNationalDayHd *CNationalDayHd; // rax
  int32_t Score; // ebx
  CFestivalDoubleEleven *v12; // rax
  int8_t ConnId; // bl
  DBService *v14; // rax
  int8_t v15; // bl
  DBService *v16; // rax
  std::pair<const long int,ActStruct> *v17; // rax
  std::pair<const long int,ActStruct> *v18; // rax
  __int64 first; // rbx
  DBService *v20; // rax
  Map *Map; // rbx
  int32_t RunnerId; // r12d
  CharId_t v23; // rbx
  GameService *v24; // rax
  Map *v25; // rbx
  char v27; // r15
  int32_t Exp; // r14d
  int32_t v29; // r13d
  int32_t GroupId; // r12d
  int32_t Mid; // eax
  char v32; // r15
  int32_t v33; // r14d
  int32_t v34; // r13d
  int32_t v35; // r12d
  int32_t v36; // eax
  int32_t v37; // ebx
  int32_t v38; // eax
  int32_t v39; // ebx
  CVip *PlayerVip; // rax
  int32_t v41; // ebx
  CVip *v42; // rax
  int8_t drop_free; // r14
  int8_t boss_sign; // r13
  int32_t v45; // r12d
  int8_t v46; // r14
  int8_t v47; // r13
  int32_t v48; // r12d
  int64_t FamilyValue; // rbx
  Player **v53; // rax
  CharId_t Cid; // r12
  int32_t id; // ebx
  CUniteServer *v56; // rax
  CharId_t v57; // r12
  int32_t v58; // ebx
  CFestivalDoubleEleven *v59; // rax
  CharId_t v60; // r12
  int32_t v61; // ebx
  COpenBeta *v62; // rax
  int32_t Mid2; // ebx
  CKaiFuHuoDong *v64; // rax
  Map *m_pMap; // r13
  int32_t v66; // ebx
  CWorldBoss *v67; // rax
  int32_t v68; // ebx
  CBossKilledReward *CBossKilledReward; // rax
  Answer::Random *v70; // rax
  int32_t PortalDuration; // r15d
  int32_t Now; // r14d
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t v75; // ebx
  CExtCharPortal *CharPortal; // rax
  int32_t nDungeon; // [rsp+34h] [rbp-2BCh]
  bossjoin_log bossJoin; // [rsp+40h] [rbp-2B0h] BYREF
  boss_log stu; // [rsp+80h] [rbp-270h] BYREF
  LogBoss logBoss; // [rsp+C0h] [rbp-230h] BYREF
  std::_List_iterator<Player*> it_0; // [rsp+F0h] [rbp-200h] BYREF
  PlayerList outPlayers; // [rsp+100h] [rbp-1F0h] BYREF
  Position CentosPos_0; // [rsp+110h] [rbp-1E0h] BYREF
  CDropItemGroup dropItemGroup_0; // [rsp+120h] [rbp-1D0h] BYREF
  std::_List_iterator<long int> iter; // [rsp+130h] [rbp-1C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActStruct> > it; // [rsp+140h] [rbp-1B0h] BYREF
  Position CentosPos; // [rsp+150h] [rbp-1A0h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+160h] [rbp-190h] BYREF
  DropItemVector dropItems_0; // [rsp+170h] [rbp-180h] BYREF
  DropItemVector dropItems; // [rsp+190h] [rbp-160h] BYREF
  std::string dropper; // [rsp+1B0h] [rbp-140h] BYREF
  char v92; // [rsp+1BFh] [rbp-131h] BYREF
  _BYTE v93[16]; // [rsp+1C0h] [rbp-130h] BYREF
  _BYTE v94[16]; // [rsp+1D0h] [rbp-120h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActStruct> > __x; // [rsp+1E0h] [rbp-110h] BYREF
  std::_List_iterator<long int> v96; // [rsp+1F0h] [rbp-100h] BYREF
  Position pos; // [rsp+200h] [rbp-F0h] BYREF
  Position CurrentTile; // [rsp+210h] [rbp-E0h] BYREF
  std::string v99; // [rsp+220h] [rbp-D0h] BYREF
  char v100; // [rsp+22Fh] [rbp-C1h] BYREF
  std::string v101; // [rsp+230h] [rbp-C0h] BYREF
  char v102; // [rsp+23Fh] [rbp-B1h] BYREF
  Position v103; // [rsp+240h] [rbp-B0h] BYREF
  std::_List_iterator<Player*> v104; // [rsp+250h] [rbp-A0h] BYREF
  std::string p_name; // [rsp+260h] [rbp-90h] BYREF
  std::string v106; // [rsp+270h] [rbp-80h] BYREF
  std::string v107; // [rsp+280h] [rbp-70h] BYREF
  Player *pKiller; // [rsp+290h] [rbp-60h]
  int32_t DropLuck; // [rsp+29Ch] [rbp-54h]
  int32_t nAddValue; // [rsp+2A0h] [rbp-50h]
  int32_t CanAddCount; // [rsp+2A4h] [rbp-4Ch]
  Player *player; // [rsp+2A8h] [rbp-48h]
  int32_t mapId; // [rsp+2B4h] [rbp-3Ch]
  int32_t JingLiValue; // [rsp+2B8h] [rbp-38h]
  int32_t deffValue; // [rsp+2BCh] [rbp-34h]

  if ( this->m_pMap )
  {
    (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 30))(this);
    Monster::setState(this, MonsterState::MS_CORPSE);
    pKiller = Monster::GetOwner(this);
    if ( pKiller )
    {
      Monster::onSendKillerReward(this, pKiller);
      if ( this->m_cfgmonster.boss_sign )
      {
        Task = Player::GetTask(pKiller);
        ChrTask::updateTaskCount(Task, 21, 0);
        if ( this->m_cfgmonster.BossSocre > 0 )
        {
          BossSocre = this->m_cfgmonster.BossSocre;
          v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
          nAddValue = CFestivalDoubleEleven::CalBossScoreAddValue(v7, BossSocre);
          CanAddCount = Monster::CanAddBossSocre(this, pKiller, nAddValue);
          if ( CanAddCount > 0
            && Player::AddCurrency(
                 pKiller,
                 CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
                 CanAddCount,
                 CURRENCY_CHANGE_REASON::SCR_KILL_BOSS,
                 0) )
          {
            Record = Player::getRecord(pKiller, 2083);
            Player::updateRecord(pKiller, 2083, CanAddCount + Record);
          }
        }
        level = this->m_cfgmonster.level;
        CNationalDayHd = Player::GetCNationalDayHd(pKiller);
        CNationalDayHd::AddNationalValue(CNationalDayHd, NATIONAL_HD_TYPE::HHT_KILL_BOSS, 1, level);
        if ( this->m_cfgmonster.Score > 0 )
        {
          Score = this->m_cfgmonster.Score;
          v12 = Answer::Singleton<CFestivalDoubleEleven>::instance();
          CFestivalDoubleEleven::UpdateMonsterScore(v12, pKiller, Score);
        }
        DropLuck = Player::getRecord(pKiller, 1908) + 10;
        if ( DropLuck > 100000 )
          DropLuck = 100000;
        Player::updateRecord(pKiller, 1908, DropLuck);
        memset(&logBoss, 0, sizeof(logBoss));
        logBoss.mid = this->m_cfgmonster.mid;
        logBoss.type = this->m_cfgmonster.boss_sign;
        logBoss.killer = Player::getCid(pKiller);
        logBoss.time = Unit::getNow(pKiller);
        logBoss.mapId = StaticObj::getMapId(this);
        logBoss.MapMonsterId = this->m_cfgmapmonster.id;
        logBoss.EntityId = Entity::getEntityId(this);
        ConnId = Player::getConnId(pKiller);
        v14 = Answer::Singleton<DBService>::instance();
        DBService::InsertBossLog(v14, ConnId, &logBoss);
        boss_log::boss_log(&stu);
        stu.log_Sid = Player::getSid(pKiller);
        stu.log_time = Unit::getNow(pKiller);
        Player::GetPassport((Player *const)v93);
        std::string::operator=(&stu.passport, v93);
        std::string::~string(v93);
        stu.cid = Player::getCid(pKiller);
        Player::getName((const Player *const)v94);
        std::string::operator=(&stu.name, v94);
        std::string::~string(v94);
        stu.kill_time = Unit::getNow(pKiller);
        stu.mid = Monster::getMid(this);
        stu.boss_id = Monster::getBossId(this);
        v15 = Player::getConnId(pKiller);
        v16 = Answer::Singleton<DBService>::instance();
        DBService::AddPlatformLog(v16, v15, PLATFORM_LOG_DATA_TYPE::PLDT_BOSS, &stu);
        for ( it._M_node = std::map<long,ActStruct>::begin(&this->m_ActStructMap)._M_node;
              ;
              std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator++(&it, 0) )
        {
          __x._M_node = std::map<long,ActStruct>::end(&this->m_ActStructMap)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator!=(&it, &__x) )
            break;
          bossjoin_log::bossjoin_log(&bossJoin);
          bossJoin.log_Sid = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it)->second.nSid;
          bossJoin.log_time = Unit::getNow(pKiller);
          v17 = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it);
          std::string::operator=(&bossJoin.passport, &v17->second.passport);
          bossJoin.cid = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it)->first;
          v18 = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it);
          std::string::operator=(&bossJoin.name, &v18->second.name);
          bossJoin.join_time = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it)->second.Time;
          bossJoin.mid = Monster::getMid(this);
          bossJoin.boss_id = Monster::getBossId(this);
          bossJoin.mapId = StaticObj::getMapId(this);
          first = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it)->first;
          bossJoin.killed = first == Player::getCid(pKiller);
          LOBYTE(first) = std::_Rb_tree_iterator<std::pair<long const,ActStruct>>::operator->(&it)->second.connid;
          v20 = Answer::Singleton<DBService>::instance();
          DBService::AddPlatformLog(v20, first, PLATFORM_LOG_DATA_TYPE::PLDT_BOSSJOIN, &bossJoin);
          bossjoin_log::~bossjoin_log(&bossJoin);
        }
        boss_log::~boss_log(&stu);
      }
      Map = StaticObj::getMap(pKiller);
      if ( Map == StaticObj::getMap(this) )
      {
        if ( this->m_cfgmonster.TaskShare )
        {
          for ( iter._M_node = std::list<long>::begin(&this->m_lDamager)._M_node;
                ;
                std::_List_iterator<long>::operator++(&iter) )
          {
            v96._M_node = std::list<long>::end(&this->m_lDamager)._M_node;
            if ( !std::_List_iterator<long>::operator!=(&iter, &v96) )
              break;
            RunnerId = StaticObj::GetRunnerId(this);
            v23 = *std::_List_iterator<long>::operator*(&iter);
            v24 = Answer::Singleton<GameService>::instance();
            player = GameService::getPlayer(v24, v23, RunnerId, 1);
            if ( player )
            {
              if ( player != pKiller )
              {
                v25 = StaticObj::getMap(player);
                if ( v25 == StaticObj::getMap(this) )
                {
                  pos = StaticObj::getCurrentTile(this);
                  CurrentTile = StaticObj::getCurrentTile(player);
                  if ( Position::tileDistance(&CurrentTile, &pos) <= 30 )
                  {
                    v27 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 17))(this);
                    Exp = Monster::getExp(this);
                    v29 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 9))(this);
                    GroupId = Monster::getGroupId(this);
                    Mid = Monster::getMid(this);
                    Player::onKillMonster(player, Mid, GroupId, v29, Exp, v27, 0);
                  }
                }
              }
            }
          }
        }
        v32 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 17))(this);
        v33 = Monster::getExp(this);
        v34 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 9))(this);
        v35 = Monster::getGroupId(this);
        v36 = Monster::getMid(this);
        Player::onKillMonster(pKiller, v36, v35, v34, v33, v32, 1);
      }
      else
      {
        mapId = StaticObj::getMapId(pKiller);
        v37 = Monster::getMid(this);
        v38 = StaticObj::getMapId(this);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_INFO,
          "monster die not the same Map by player! %d,%d,%d\n",
          v38,
          mapId,
          v37);
      }
      std::vector<DropItem>::vector(&dropItems);
      Monster::generateFightDrop(this, &dropItems, pKiller, 0);
      Monster::AddDiligenceDrop(this, pKiller, &dropItems);
      if ( (*((int (__fastcall **)(Monster *const))this->_vptr_Entity + 9))(this) > 299 )
      {
        v39 = Monster::getMid(this);
        PlayerVip = Player::GetPlayerVip(pKiller);
        CVip::GetLuckDropType(PlayerVip, v39);
        v41 = Monster::getMid(this);
        v42 = Player::GetPlayerVip(pKiller);
        CVip::GetClubDrop(v42, v41);
      }
      Monster::ActDrop(this, &dropItems);
      if ( !std::vector<DropItem>::empty(&dropItems) )
      {
        JingLiValue = Player::getRecord(pKiller, 37305);
        if ( this->m_cfgmonster.Energy <= 0 || JingLiValue > 0 )
        {
          CDropItemGroup::CDropItemGroup(&dropItemGroup_0);
          CentosPos_0 = StaticObj::getCurrentTile(this);
          if ( Monster::isActivity(this, 1) )
          {
            drop_free = this->m_cfgmonster.drop_free;
            boss_sign = this->m_cfgmonster.boss_sign;
            v45 = this->m_cfgmonster.mid;
            std::allocator<char>::allocator(&v100);
            std::string::string(&v99, &unk_8E6560);
            CDropItemGroup::init(
              &dropItemGroup_0,
              0,
              this->m_pMap,
              &CentosPos_0,
              0,
              2,
              this->m_cfgmonster.mid,
              &dropItems,
              &v99,
              v45,
              boss_sign,
              drop_free);
            std::string::~string(&v99);
            std::allocator<char>::~allocator(&v100);
          }
          else
          {
            v46 = this->m_cfgmonster.drop_free;
            v47 = this->m_cfgmonster.boss_sign;
            v48 = this->m_cfgmonster.mid;
            std::allocator<char>::allocator(&v102);
            std::string::string(&v101, &unk_8E6560);
            CDropItemGroup::init(
              &dropItemGroup_0,
              0,
              this->m_pMap,
              &CentosPos_0,
              pKiller,
              2,
              this->m_cfgmonster.mid,
              &dropItems,
              &v101,
              v48,
              v47,
              v46);
            std::string::~string(&v101);
            std::allocator<char>::~allocator(&v102);
          }
          Map::addDropItemGroup(this->m_pMap, &dropItemGroup_0);
          CDropItemGroup::~CDropItemGroup(&dropItemGroup_0);
        }
        if ( this->m_cfgmonster.Energy > 0 )
        {
          deffValue = JingLiValue - this->m_cfgmonster.Energy;
          if ( deffValue < 0 )
            deffValue = 0;
          Player::updateRecord(pKiller, 37305, deffValue);
          Player::SendJingLiValue(pKiller);
        }
      }
      if ( pKiller )
        (*((void (__fastcall **)(Map *, Monster *const, Player *, bool))this->m_pMap->_vptr_Map + 13))(
          this->m_pMap,
          this,
          pKiller,
          this->m_IsGroupMonster);
      if ( Map::IsWastelands(this->m_pMap) && this->m_cfgmonster.kill_point > 0 )
        Player::AddWastelandsValue(pKiller, 6 * this->m_cfgmonster.kill_point);
      if ( Map::IsBeastShrine(this->m_pMap) && this->m_cfgmonster.kill_point > 0 )
        Player::AddBeastShrineValue(pKiller, 6 * this->m_cfgmonster.kill_point);
      if ( this->m_cfgmonster.FamilyValue > 0
        && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
      {
        std::list<Player *>::list(&outPlayers);
        v103 = StaticObj::getCurrentTile(this);
        Map::getAreaPlayer(this->m_pMap, &outPlayers, &v103, 14);
        for ( it_0._M_node = std::list<Player *>::begin(&outPlayers)._M_node;
              ;
              std::_List_iterator<Player *>::operator++(&it_0) )
        {
          v104._M_node = std::list<Player *>::end(&outPlayers)._M_node;
          if ( !std::_List_iterator<Player *>::operator!=(&it_0, &v104) )
            break;
          FamilyValue = this->m_cfgmonster.FamilyValue;
          v53 = std::_List_iterator<Player *>::operator*(&it_0);
          Player::AddCurrency(
            *v53,
            CURRENCY_TYPE::CURRENCY_CONTRIBUTION,
            FamilyValue,
            CURRENCY_CHANGE_REASON::GCR_FAMILY_DUNGEON_CONTRIBUTION,
            0);
        }
        std::list<Player *>::~list(&outPlayers);
      }
      if ( this->m_cfgmonster.boss_sign > 0 )
      {
        Cid = Player::getCid(pKiller);
        Player::getName((const Player *const)&p_name);
        id = this->m_cfgmapmonster.id;
        v56 = Answer::Singleton<CUniteServer>::instance();
        CUniteServer::BossDie(v56, id, &p_name, Cid);
        std::string::~string(&p_name);
        v57 = Player::getCid(pKiller);
        Player::getName((const Player *const)&v106);
        v58 = this->m_cfgmapmonster.id;
        v59 = Answer::Singleton<CFestivalDoubleEleven>::instance();
        CFestivalDoubleEleven::BossDie(v59, v58, &v106, v57);
        std::string::~string(&v106);
        v60 = Player::getCid(pKiller);
        Player::getName((const Player *const)&v107);
        v61 = this->m_cfgmapmonster.id;
        v62 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::BossDie(v62, v61, &v107, v60);
        std::string::~string(&v107);
        Mid2 = this->m_cfgmonster.Mid2;
        v64 = Answer::Singleton<CKaiFuHuoDong>::instance();
        CKaiFuHuoDong::OnKilledMonster(v64, pKiller, Mid2);
        m_pMap = this->m_pMap;
        LODWORD(v60) = Unit::getNow(this);
        v66 = this->m_cfgmapmonster.id;
        v67 = Answer::Singleton<CWorldBoss>::instance();
        CWorldBoss::OnBossKilled(v67, v66, v60, m_pMap, this, pKiller);
        v68 = this->m_cfgmonster.Mid2;
        CBossKilledReward = Player::GetCBossKilledReward(pKiller);
        CBossKilledReward::AddBossKilled(CBossKilledReward, v68);
        Player::UpdateCycleTowerState(pKiller, CYCLE_TOWER_ENVET_TYPE::CTET_KILL_BOSS);
      }
      if ( this->m_IsGroupMonster )
        Monster::SetReviveTime(this, 0);
      if ( pKiller )
      {
        if ( this->m_cfgmonster.PortalRatio > 0 && this->m_cfgmonster.PortalId > 0 )
        {
          v70 = Answer::Singleton<Answer::Random>::instance();
          if ( Answer::Random::generate(v70, 1, 1000) <= this->m_cfgmonster.PortalRatio )
          {
            PortalDuration = this->m_cfgmonster.PortalDuration;
            Now = Unit::getNow(this);
            nDungeon = this->m_cfgmonster.PortalId;
            PosY = StaticObj::GetPosY(this);
            PosX = StaticObj::GetPosX(this);
            v75 = StaticObj::getMapId(this);
            CharPortal = Player::GetCharPortal(pKiller);
            CExtCharPortal::AddPortal(CharPortal, v75, PosX, PosY, nDungeon, Now, PortalDuration);
          }
        }
      }
      std::vector<DropItem>::~vector(&dropItems);
    }
    else
    {
      if ( this->m_killer.id > 0 )
      {
        std::vector<DropItem>::vector(&dropItems_0);
        Monster::generateFightDrop(this, &dropItems_0, 0, 0);
        if ( this->m_pMap && !std::vector<DropItem>::empty(&dropItems_0) )
        {
          CDropItemGroup::CDropItemGroup(&dropItemGroup);
          CentosPos = StaticObj::getCurrentTile(this);
          autoPick = this->m_cfgmonster.drop_free;
          bossSign = this->m_cfgmonster.boss_sign;
          MonsterMid = this->m_cfgmonster.mid;
          std::allocator<char>::allocator(&v92);
          std::string::string(&dropper, &unk_8E6560);
          CDropItemGroup::init(
            &dropItemGroup,
            0,
            this->m_pMap,
            &CentosPos,
            0,
            2,
            this->m_cfgmonster.mid,
            &dropItems_0,
            &dropper,
            MonsterMid,
            bossSign,
            autoPick);
          std::string::~string(&dropper);
          std::allocator<char>::~allocator(&v92);
          Map::addDropItemGroup(this->m_pMap, &dropItemGroup);
          CDropItemGroup::~CDropItemGroup(&dropItemGroup);
        }
        std::vector<DropItem>::~vector(&dropItems_0);
      }
      (*((void (__fastcall **)(Map *, Monster *const, _QWORD, bool))this->m_pMap->_vptr_Map + 13))(
        this->m_pMap,
        this,
        0,
        this->m_IsGroupMonster);
    }
  }
}


#####################################
void __cdecl Monster::ActDrop(Monster *const this, DropItemVector *const dropItems)
{
  CUniteServer *v2; // rax
  CUniteServer *v3; // rax
  int32_t v4; // eax
  ActDropItem *v5; // rax
  ActDropItem *v6; // rax
  Answer::Random *v8; // rax
  ActDropItem *v9; // rax
  COpenBeta *v10; // rax
  COpenBeta *v11; // rax
  int32_t v12; // eax
  ActDropItem *v13; // rax
  ActDropItem *v14; // rax
  Answer::Random *v16; // rax
  ActDropItem *v17; // rax
  CFestivalDoubleEleven *v18; // rax
  int32_t v19; // eax
  ActDropItem *v20; // rax
  ActDropItem *v21; // rax
  ActDropItem *v22; // rax
  ActDropItem *v23; // rax
  Answer::Random *v25; // rax
  ActDropItem *v26; // rax
  DropItem stu; // [rsp+10h] [rbp-120h] BYREF
  std::_List_iterator<ActDropItem> it_1; // [rsp+40h] [rbp-F0h] BYREF
  ActDropItemList DropItems_1; // [rsp+50h] [rbp-E0h] BYREF
  std::_List_iterator<ActDropItem> it_0; // [rsp+60h] [rbp-D0h] BYREF
  ActDropItemList DropItems_0; // [rsp+70h] [rbp-C0h] BYREF
  std::_List_iterator<ActDropItem> it; // [rsp+80h] [rbp-B0h] BYREF
  ActDropItemList DropItems; // [rsp+90h] [rbp-A0h] BYREF
  std::list<ActDropItem> __x; // [rsp+A0h] [rbp-90h] BYREF
  std::_List_iterator<ActDropItem> v35; // [rsp+B0h] [rbp-80h] BYREF
  std::list<ActDropItem> v36; // [rsp+C0h] [rbp-70h] BYREF
  std::_List_iterator<ActDropItem> v37; // [rsp+D0h] [rbp-60h] BYREF
  std::list<ActDropItem> v38; // [rsp+E0h] [rbp-50h] BYREF
  std::_List_iterator<ActDropItem> v39; // [rsp+F0h] [rbp-40h] BYREF
  int32_t nowTime; // [rsp+FCh] [rbp-34h]
  Map *pMap; // [rsp+100h] [rbp-30h]
  int32_t Level; // [rsp+108h] [rbp-28h]
  int32_t nTime; // [rsp+10Ch] [rbp-24h]
  int32_t nRand; // [rsp+110h] [rbp-20h]
  int32_t nTime_0; // [rsp+114h] [rbp-1Ch]
  int32_t nRand_0; // [rsp+118h] [rbp-18h]
  int32_t nRand_1; // [rsp+11Ch] [rbp-14h]

  nowTime = Unit::getNow(this);
  pMap = StaticObj::getMap(this);
  if ( pMap && Map::GetType(pMap) == 1 )
  {
    Level = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 9))(this);
    v2 = Answer::Singleton<CUniteServer>::instance();
    if ( CUniteServer::IsInTime(v2, Unit_Server_Activity_typ::US_COLLECT_DROP) )
    {
      v3 = Answer::Singleton<CUniteServer>::instance();
      nTime = CUniteServer::GetEndCollectDropTime(v3);
      std::list<ActDropItem>::list(&DropItems);
      v4 = (unsigned int)Answer::Singleton<CfgData>::instance();
      CfgData::GetAcrDropList((CfgData *const)&__x, v4);
      std::list<ActDropItem>::operator=(&DropItems, &__x);
      std::list<ActDropItem>::~list(&__x);
      for ( it._M_node = std::list<ActDropItem>::begin(&DropItems)._M_node;
            ;
            std::_List_iterator<ActDropItem>::operator++(&it, 0) )
      {
        v35._M_node = std::list<ActDropItem>::end(&DropItems)._M_node;
        if ( !std::_List_iterator<ActDropItem>::operator!=(&it, &v35) )
          break;
        v5 = std::_List_iterator<ActDropItem>::operator->(&it);
        if ( v5->nMinLevel <= Level )
        {
          v6 = std::_List_iterator<ActDropItem>::operator->(&it);
          if ( v6->nMaxLevel >= Level )
          {
            v8 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v8, 1, 1000000);
            v9 = std::_List_iterator<ActDropItem>::operator->(&it);
            if ( v9->nProbability > nRand )
            {
              memset(&stu, 0, sizeof(stu));
              stu.itemId = std::_List_iterator<ActDropItem>::operator->(&it)->nId;
              stu.itemCount = std::_List_iterator<ActDropItem>::operator->(&it)->nCount;
              stu.itemClass = std::_List_iterator<ActDropItem>::operator->(&it)->nClass;
              stu.bindType = std::_List_iterator<ActDropItem>::operator->(&it)->nBind;
              stu.endTime = nTime;
              std::vector<DropItem>::push_back(dropItems, &stu);
            }
          }
        }
      }
      std::list<ActDropItem>::~list(&DropItems);
    }
    v10 = Answer::Singleton<COpenBeta>::instance();
    if ( COpenBeta::IsInTime(v10, 8) )
    {
      v11 = Answer::Singleton<COpenBeta>::instance();
      nTime_0 = COpenBeta::GetEndCollectDropTime(v11);
      std::list<ActDropItem>::list(&DropItems_0);
      v12 = (unsigned int)Answer::Singleton<CfgData>::instance();
      CfgData::GetAcrDropList((CfgData *const)&v36, v12);
      std::list<ActDropItem>::operator=(&DropItems_0, &v36);
      std::list<ActDropItem>::~list(&v36);
      for ( it_0._M_node = std::list<ActDropItem>::begin(&DropItems_0)._M_node;
            ;
            std::_List_iterator<ActDropItem>::operator++(&it_0, 0) )
      {
        v37._M_node = std::list<ActDropItem>::end(&DropItems_0)._M_node;
        if ( !std::_List_iterator<ActDropItem>::operator!=(&it_0, &v37) )
          break;
        v13 = std::_List_iterator<ActDropItem>::operator->(&it_0);
        if ( v13->nMinLevel <= Level )
        {
          v14 = std::_List_iterator<ActDropItem>::operator->(&it_0);
          if ( v14->nMaxLevel >= Level )
          {
            v16 = Answer::Singleton<Answer::Random>::instance();
            nRand_0 = Answer::Random::generate(v16, 1, 1000000);
            v17 = std::_List_iterator<ActDropItem>::operator->(&it_0);
            if ( v17->nProbability > nRand_0 )
            {
              memset(&stu, 0, sizeof(stu));
              stu.itemId = std::_List_iterator<ActDropItem>::operator->(&it_0)->nId;
              stu.itemCount = std::_List_iterator<ActDropItem>::operator->(&it_0)->nCount;
              stu.itemClass = std::_List_iterator<ActDropItem>::operator->(&it_0)->nClass;
              stu.bindType = std::_List_iterator<ActDropItem>::operator->(&it_0)->nBind;
              stu.endTime = nTime_0;
              std::vector<DropItem>::push_back(dropItems, &stu);
            }
          }
        }
      }
      std::list<ActDropItem>::~list(&DropItems_0);
    }
    v18 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( CFestivalDoubleEleven::IsInTime(v18) )
    {
      std::list<ActDropItem>::list(&DropItems_1);
      v19 = (unsigned int)Answer::Singleton<CfgData>::instance();
      CfgData::GetAcrDropList((CfgData *const)&v38, v19);
      std::list<ActDropItem>::operator=(&DropItems_1, &v38);
      std::list<ActDropItem>::~list(&v38);
      for ( it_1._M_node = std::list<ActDropItem>::begin(&DropItems_1)._M_node;
            ;
            std::_List_iterator<ActDropItem>::operator++(&it_1, 0) )
      {
        v39._M_node = std::list<ActDropItem>::end(&DropItems_1)._M_node;
        if ( !std::_List_iterator<ActDropItem>::operator!=(&it_1, &v39) )
          break;
        v20 = std::_List_iterator<ActDropItem>::operator->(&it_1);
        if ( v20->nStartTime <= nowTime )
        {
          v21 = std::_List_iterator<ActDropItem>::operator->(&it_1);
          if ( v21->nEndTime >= nowTime )
          {
            v22 = std::_List_iterator<ActDropItem>::operator->(&it_1);
            if ( v22->nMinLevel <= Level )
            {
              v23 = std::_List_iterator<ActDropItem>::operator->(&it_1);
              if ( v23->nMaxLevel >= Level )
              {
                v25 = Answer::Singleton<Answer::Random>::instance();
                nRand_1 = Answer::Random::generate(v25, 1, 1000000);
                v26 = std::_List_iterator<ActDropItem>::operator->(&it_1);
                if ( v26->nProbability > nRand_1 )
                {
                  memset(&stu, 0, sizeof(stu));
                  stu.itemId = std::_List_iterator<ActDropItem>::operator->(&it_1)->nId;
                  stu.itemCount = std::_List_iterator<ActDropItem>::operator->(&it_1)->nCount;
                  stu.itemClass = std::_List_iterator<ActDropItem>::operator->(&it_1)->nClass;
                  stu.bindType = std::_List_iterator<ActDropItem>::operator->(&it_1)->nBind;
                  std::vector<DropItem>::push_back(dropItems, &stu);
                }
              }
            }
          }
        }
      }
      std::list<ActDropItem>::~list(&DropItems_1);
    }
  }
}


#####################################
void __cdecl Monster::revive(Monster *const this)
{
  GameService *v1; // rax
  int32_t Broadcast; // edx
  int32_t MapId; // edx
  uint32_t WOffset; // edx
  GameService *v5; // rax
  GameService *v6; // rax
  int32_t v7; // edx
  uint32_t v8; // edx
  Answer::NetPacket *packet; // [rsp+10h] [rbp-10h]
  Answer::NetPacket *packet_0; // [rsp+18h] [rbp-8h]

  UnitHandle::clear(&this->m_killer);
  UnitHandle::clear(&this->m_target);
  std::map<long,UnitHandle>::clear(&this->m_targetMap);
  this->m_lastActionTick = 0;
  this->m_standTick = 0;
  this->m_standTime = 0;
  this->m_corpseTick = 0;
  this->m_ghostTick = 0;
  this->m_DieType = 0;
  this->m_reviveTick = 0;
  this->m_nReviveTime = -1;
  this->m_DamageFlag = 0;
  this->m_nLastCheckBossTick = 0;
  this->m_nHPPecent = 100;
  this->m_nEscapeTick = 0;
  this->m_nEscapeDirection = Direction::DOWN;
  this->m_TunShi = 0;
  std::map<long,PlayerScore>::clear(&this->m_PlayerScore);
  this->m_HaveItem = 1;
  std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::clear(&this->m_ScoreRank);
  std::list<long>::clear(&this->m_lDamager);
  std::map<long,ActStruct>::clear(&this->m_ActStructMap);
  Monster::resetSkill(this);
  Monster::resetRandAttr(this);
  (*((void (__fastcall **)(Monster *const, __int64))this->_vptr_Entity + 22))(this, 100);
  if ( Monster::getBroadcast(this) > 0 )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return;
    Broadcast = Monster::getBroadcast(this);
    Answer::NetPacket::writeInt32(packet, Broadcast);
    Answer::NetPacket::writeInt32(packet, this->m_cfgmonster.mid);
    MapId = StaticObj::getMapId(this);
    Answer::NetPacket::writeInt32(packet, MapId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, packet);
  }
  if ( this->m_cfgmonster.boss_sign == 13 )
  {
    v6 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v6, Answer::PackType::PACK_DISPATCH, 0x2CE0u);
    if ( !packet_0 )
      return;
    Answer::NetPacket::writeInt32(packet_0, this->m_cfgmonster.mid);
    v7 = StaticObj::getMapId(this);
    Answer::NetPacket::writeInt32(packet_0, v7);
    v8 = Answer::NetPacket::getWOffset(packet_0);
    Answer::NetPacket::setSize(packet_0, v8);
    Map::broadcast(this->m_pMap, packet_0);
  }
  Monster::setState(this, MonsterState::MS_STAND);
}


#####################################
void __cdecl Monster::generateFightDrop(
        Monster *const this,
        DropItemVector *const dropItems,
        Player *pPlayer,
        int32_t DropType)
{
  int32_t id; // ebx
  CWorldBoss *v5; // rax
  int32_t Mid; // ebx
  CfgData *v7; // rax
  int8_t job; // bl
  char v9; // al
  CfgMonsterGroupDrop *v10; // rax
  int8_t hard; // bl
  int8_t quality; // bl
  CfgMonsterGroupDrop *v15; // rax
  CfgMonsterGroupDrop *v16; // rax
  Answer::Random *v19; // rax
  int32_t bind_type; // ebx
  CfgMonsterGroupDrop *v21; // rax
  CfgMonsterGroupDrop *v22; // rax
  CfgData *v23; // rax
  int32_t activity_id; // ebx
  CActivityManager *v25; // rax
  int32_t v26; // ebx
  Answer::Random *v27; // rax
  int32_t v28; // ebx
  int32_t v30; // ebx
  const std::pair<const int,CfgActivityDrop> *v31; // rax
  size_t v32; // rdx
  int32_t nParam2; // r12d
  const Param2 *v34; // rax
  DropItem dropItem; // [rsp+20h] [rbp-150h] BYREF
  std::_List_const_iterator<Param2> it_1; // [rsp+50h] [rbp-120h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivityDrop> > it_0; // [rsp+60h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop*,std::vector<CfgMonsterGroupDrop> > it; // [rsp+70h] [rbp-100h] BYREF
  Param2List groupIds; // [rsp+80h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop*,std::vector<CfgMonsterGroupDrop> > __rhs; // [rsp+90h] [rbp-E0h] BYREF
  Param2 __x; // [rsp+A0h] [rbp-D0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgActivityDrop> > __it; // [rsp+B0h] [rbp-C0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivityDrop> > v45; // [rsp+C0h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgActivityDrop> > v46; // [rsp+D0h] [rbp-A0h] BYREF
  Param2 v47; // [rsp+E0h] [rbp-90h] BYREF
  std::_List_iterator<Param2> v48; // [rsp+F0h] [rbp-80h] BYREF
  std::_List_const_iterator<Param2> v49; // [rsp+100h] [rbp-70h] BYREF
  std::_List_iterator<Param2> v50; // [rsp+110h] [rbp-60h] BYREF
  int32_t boss_level; // [rsp+124h] [rbp-4Ch]
  CfgMonsterGroupDropVector *pGroups; // [rsp+128h] [rbp-48h]
  CfgActivityDropTable *pActivityDrops; // [rsp+130h] [rbp-40h]
  int32_t nowMinute; // [rsp+13Ch] [rbp-34h]
  float PlayerDropRate; // [rsp+140h] [rbp-30h]
  int32_t i; // [rsp+144h] [rbp-2Ch]
  int32_t probability; // [rsp+148h] [rbp-28h]
  int32_t groupProbability; // [rsp+14Ch] [rbp-24h]
  Map *pMap; // [rsp+150h] [rbp-20h]
  float MapRate; // [rsp+15Ch] [rbp-14h]

  boss_level = 0;
  if ( this->m_cfgmonster.boss_sign > 0 )
  {
    id = this->m_cfgmapmonster.id;
    v5 = Answer::Singleton<CWorldBoss>::instance();
    boss_level = CWorldBoss::GetBossLevel(v5, id);
  }
  std::list<Param2>::list(&groupIds);
  Mid = Monster::getMid(this);
  v7 = Answer::Singleton<CfgData>::instance();
  pGroups = CfgData::getMonsterGroupDrop(v7, Mid);
  if ( pGroups )
  {
    nowMinute = Monster::getMinute(this);
    for ( it._M_current = std::vector<CfgMonsterGroupDrop>::begin(pGroups)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgMonsterGroupDrop>::end(pGroups)._M_current;
      if ( !__gnu_cxx::operator!=<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>(&it, &__rhs) )
        break;
      if ( __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->dropType == DropType )
      {
        PlayerDropRate = 0.0;
        if ( !pPlayer
          || ((PlayerDropRate = (float)Unit::GetAttrValue(pPlayer, CObjAttrs::Index_T::ATTR_DROP_RATE) / 1000.0,
               !__gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->job)
           || (job = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->job,
               job == Player::getJob(pPlayer))
            ? (v9 = 0)
            : (v9 = 1),
              !v9) )
        {
          v10 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
          if ( v10->grow_level <= boss_level )
          {
            if ( __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->hard <= 0
              || (hard = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->hard,
                  hard == (*((unsigned __int8 (__fastcall **)(Monster *const))this->_vptr_Entity + 40))(this)) )
            {
              if ( __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->quality <= 0
                || (quality = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->quality,
                    quality == (*((unsigned __int8 (__fastcall **)(Monster *const))this->_vptr_Entity + 41))(this)) )
              {
                v15 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                if ( v15->begin_time <= nowMinute )
                {
                  v16 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                  if ( v16->end_time >= nowMinute )
                  {
                    for ( i = 0; ; ++i )
                    {
                      v22 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                      if ( v22->repeat <= i )
                        break;
                      probability = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->probability;
                      if ( (*((unsigned __int8 (__fastcall **)(Monster *const))this->_vptr_Entity + 36))(this) != 1
                        && (*((unsigned __int8 (__fastcall **)(Monster *const))this->_vptr_Entity + 35))(this) != 1
                        && __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->DropLimit <= 0 )
                      {
                        pMap = StaticObj::getMap(this);
                        MapRate = 1.0;
                        if ( pMap )
                          MapRate = Map::GetMapRate(pMap);
                        probability = (int)(float)((float)(PlayerDropRate + 1.0) * (float)((float)probability * MapRate));
                      }
                      v19 = Answer::Singleton<Answer::Random>::instance();
                      groupProbability = Answer::Random::generate(v19, 1, 1000000);
                      if ( probability >= groupProbability )
                      {
                        bind_type = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->bind_type;
                        v21 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                        Param2::Param2(&__x, v21->group_id, bind_type);
                        std::list<Param2>::push_back(&groupIds, &__x);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  v23 = Answer::Singleton<CfgData>::instance();
  pActivityDrops = CfgData::getActivityDrops(v23);
  if ( pActivityDrops )
  {
    __it._M_node = std::map<int,CfgActivityDrop>::begin(pActivityDrops)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::_Rb_tree_const_iterator(&it_0, &__it);
    while ( 1 )
    {
      v46._M_node = std::map<int,CfgActivityDrop>::end(pActivityDrops)._M_node;
      std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::_Rb_tree_const_iterator(&v45, &v46);
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator!=(&it_0, &v45) )
        break;
      activity_id = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator->(&it_0)->second.activity_id;
      v25 = Answer::Singleton<CActivityManager>::instance();
      if ( CActivityManager::IsActivityRunning(v25, activity_id) )
      {
        v26 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator->(&it_0)->second.probability;
        v27 = Answer::Singleton<Answer::Random>::instance();
        if ( v26 >= Answer::Random::generate(v27, 1, 1000) )
        {
          v28 = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 9))(this);
          if ( v28 >= std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator->(&it_0)->second.monster_min_level )
          {
            v30 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator->(&it_0)->second.bind_type;
            v31 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator->(&it_0);
            Param2::Param2(&v47, v31->second.drop_group_id, v30);
            std::list<Param2>::push_back(&groupIds, &v47);
          }
        }
      }
      std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityDrop>>::operator++(&it_0);
    }
  }
  v32 = std::list<Param2>::size(&groupIds) + 6;
  std::vector<DropItem>::reserve(dropItems, v32);
  v48._M_node = std::list<Param2>::begin(&groupIds)._M_node;
  std::_List_const_iterator<Param2>::_List_const_iterator(&it_1, &v48);
  while ( 1 )
  {
    v50._M_node = std::list<Param2>::end(&groupIds)._M_node;
    std::_List_const_iterator<Param2>::_List_const_iterator(&v49, &v50);
    if ( !std::_List_const_iterator<Param2>::operator!=(&it_1, &v49) )
      break;
    nParam2 = std::_List_const_iterator<Param2>::operator->(&it_1)->nParam2;
    v34 = std::_List_const_iterator<Param2>::operator->(&it_1);
    Monster::dropItemFromGroup(&dropItem, this, v34->nParam1, nParam2, pPlayer);
    if ( dropItem.itemId > 0 && dropItem.itemClass > 0 )
      std::vector<DropItem>::push_back(dropItems, &dropItem);
    std::_List_const_iterator<Param2>::operator++(&it_1);
  }
  std::list<Param2>::~list(&groupIds);
}


#####################################
int32_t __cdecl Monster::getMinute(Monster *const this)
{
  tm v2; // [rsp+0h] [rbp-A0h] BYREF
  Monster *thisa; // [rsp+48h] [rbp-58h]
  tm tmnow; // [rsp+50h] [rbp-50h] BYREF

  thisa = this;
  memset(&tmnow, 0, sizeof(tmnow));
  if ( this->m_pMap )
    Map::getLocalNow(&v2, thisa->m_pMap);
  else
    Unit::getLocalNow(&v2, thisa);
  return 60 * v2.tm_hour + v2.tm_min;
}


#####################################
void __cdecl Monster::refreshSkill(Monster *const this, int32_t HPPecent)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgSkillTable *v5; // rax
  int32_t skillid; // ebx
  CfgData *v8; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t skill_id; // ebx
  CfgData *v11; // rax
  const CfgSkillTable *v12; // rax
  int32_t i; // [rsp+18h] [rbp-18h]
  int32_t i_0; // [rsp+1Ch] [rbp-14h]

  if ( HPPecent <= 0 )
  {
    for ( i_0 = 0; i_0 <= 9; ++i_0 )
    {
      if ( this->m_cfgmonster.random_skill[i_0].maxHp >= this->m_nHPPecent
        && this->m_cfgmonster.random_skill[i_0].minHp <= this->m_nHPPecent
        && !Monster::isSkillCD(this, this->m_cfgmonster.random_skill[i_0].skillid) )
      {
        skillid = this->m_cfgmonster.random_skill[i_0].skillid;
        v8 = Answer::Singleton<CfgData>::instance();
        SkillTable = CfgData::GetSkillTable(v8);
        this->m_pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, skillid);
        if ( this->m_pCfgSkill )
          return;
      }
    }
    skill_id = this->m_cfgmonster.skill_id;
    v11 = Answer::Singleton<CfgData>::instance();
    v12 = CfgData::GetSkillTable(v11);
    this->m_pCfgSkill = CfgSkillTable::GetActiveSkill(v12, skill_id);
  }
  else
  {
    for ( i = 0; i <= 9; ++i )
    {
      if ( this->m_cfgmonster.unique_skill[i].maxHp < HPPecent
        && this->m_cfgmonster.unique_skill[i].maxHp >= this->m_nHPPecent
        && this->m_cfgmonster.unique_skill[i].minHp <= this->m_nHPPecent
        && !Monster::isSkillCD(this, this->m_cfgmonster.unique_skill[i].skillid) )
      {
        v3 = this->m_cfgmonster.unique_skill[i].skillid;
        v4 = Answer::Singleton<CfgData>::instance();
        v5 = CfgData::GetSkillTable(v4);
        this->m_pCfgSkill = CfgSkillTable::GetActiveSkill(v5, v3);
        if ( this->m_pCfgSkill )
          break;
      }
    }
  }
}


#####################################
bool __cdecl Monster::isSkillCD(Monster *const this, SkillId_t nSkillId)
{
  int64_t nCDTime; // rbx
  int32_t i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; i <= 9; ++i )
  {
    if ( this->m_vSkills[i].nId == nSkillId )
    {
      nCDTime = this->m_vSkills[i].nCDTime;
      return nCDTime > Unit::getTick(this);
    }
  }
  return 0;
}


#####################################
void __cdecl Monster::setSkillCD(Monster *const this, SkillId_t nSkillId, int32_t nCDTime)
{
  int32_t i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; i <= 9; ++i )
  {
    if ( this->m_vSkills[i].nId == nSkillId )
    {
      this->m_vSkills[i].nCDTime = Unit::getTick(this) + nCDTime;
      return;
    }
  }
}


#####################################
int32_t __cdecl Monster::move(
        Monster *const this,
        int16_t currentX,
        int16_t currentY,
        int16_t targetX,
        int16_t targetY,
        int16_t finalX,
        int16_t finalY,
        Direction direction)
{
  Tile *pCurrentTile; // [rsp+28h] [rbp-28h]
  Tile *pTargetTile; // [rsp+30h] [rbp-20h]
  Tile *pFinalTile; // [rsp+38h] [rbp-18h]

  if ( !this->m_pMap )
    return 10002;
  pCurrentTile = Map::getTile(this->m_pMap, currentX, currentY);
  pTargetTile = Map::getTile(this->m_pMap, targetX, targetY);
  pFinalTile = Map::getTile(this->m_pMap, finalX, finalY);
  if ( !pCurrentTile || !pTargetTile || !pFinalTile )
    return 10002;
  Unit::setAtTile(this, this->m_pMap, targetX, targetY);
  Unit::broadcastKickOutedMove(this);
  return 0;
}


#####################################
void __cdecl Monster::flyHome(Monster *const this)
{
  UnitHandle::clear(&this->m_target);
  std::map<long,UnitHandle>::clear(&this->m_targetMap);
  if ( this->m_currentTile.x == this->m_cfgmapmonster.x && this->m_currentTile.y == this->m_cfgmapmonster.y )
  {
    Monster::setState(this, MonsterState::MS_STAND);
  }
  else
  {
    Unit::setAtTile(this, this->m_pMap, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
    Monster::setState(this, MonsterState::MS_STAND);
  }
}


#####################################
void __cdecl Monster::backHome(Monster *const this)
{
  if ( !Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    && !Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    UnitHandle::clear(&this->m_target);
    std::map<long,UnitHandle>::clear(&this->m_targetMap);
    if ( this->m_currentTile.x == this->m_cfgmapmonster.x && this->m_currentTile.y == this->m_cfgmapmonster.y )
    {
      Monster::setState(this, MonsterState::MS_STAND);
    }
    else
    {
      Unit::setTargetTile(this, this->m_cfgmapmonster.x, this->m_cfgmapmonster.y);
      Monster::setState(this, MonsterState::MS_WALK_HOME);
    }
  }
}


#####################################
void __cdecl Monster::checkHPRevive(Monster *const this)
{
  int64_t nCurTick; // [rsp+10h] [rbp-20h]
  int64_t nHP; // [rsp+18h] [rbp-18h]
  int64_t nMaxHP; // [rsp+20h] [rbp-10h]

  if ( this->m_bHPRevive && Unit::isAlive(this) && this->m_cfgmonster.hpPercent > 0 )
  {
    nCurTick = Unit::getTick(this);
    if ( nCurTick - this->m_nLastReviveHPTick > 1000 )
    {
      this->m_nLastReviveHPTick = nCurTick;
      nHP = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 19))(this);
      nMaxHP = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this);
      (*((void (__fastcall **)(Monster *const, _QWORD))this->_vptr_Entity + 21))(
        this,
        (unsigned int)(int)((double)this->m_cfgmonster.hpPercent * ((double)(int)nMaxHP / 1000.0)));
      this->m_nHPPecent = (int)(float)((float)((float)(*((int (__fastcall **)(Monster *const))this->_vptr_Entity + 19))(this)
                                             / (float)(int)nMaxHP)
                                     * 100.0);
      if ( nHP >= nMaxHP )
        this->m_bHPRevive = 0;
    }
  }
}


#####################################
void __cdecl Monster::checkLifeTime(Monster *const this)
{
  if ( this->m_nLifeTime >= 0 )
  {
    if ( Unit::getNow(this) >= this->m_nLifeTime && Unit::isAlive(this) )
      Unit::setHP(this, 0);
    if ( Unit::getNow(this) >= this->m_nLifeTime )
      Monster::setDelFlg(this);
  }
}


#####################################
void __cdecl Monster::resetSkill(Monster *const this)
{
  int32_t i; // [rsp+14h] [rbp-4h]

  this->m_pCfgSkill = 0;
  for ( i = 0; i <= 9; ++i )
    this->m_vSkills[i].nCDTime = 0;
}


#####################################
void __cdecl Monster::resetRandAttr(Monster *const this)
{
  int v1; // ebx
  CfgData *v2; // rax
  const CfgMonsterRandTable *MonsterRandTable; // rax
  int32_t v4; // ebx
  int32_t index; // ecx
  int32_t v6; // ebx
  int32_t v7; // ecx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v10; // rax
  int *v11; // rax
  int v12; // ebx
  CfgData *v13; // rax
  const CfgMonsterRandTable *v14; // rax
  int32_t addon; // ebx
  int32_t v16; // ecx
  int32_t v17; // ebx
  int32_t v18; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i_4; // [rsp+10h] [rbp-150h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i_3; // [rsp+20h] [rbp-140h] BYREF
  std::_List_const_iterator<int> iter_0; // [rsp+30h] [rbp-130h] BYREF
  Int32Vector vId; // [rsp+40h] [rbp-120h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i_0; // [rsp+60h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > i; // [rsp+70h] [rbp-F0h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+80h] [rbp-E0h] BYREF
  std::_List_iterator<int> __x; // [rsp+90h] [rbp-D0h] BYREF
  std::_List_const_iterator<int> v27; // [rsp+A0h] [rbp-C0h] BYREF
  std::_List_iterator<int> v28; // [rsp+B0h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+C0h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v30; // [rsp+D0h] [rbp-90h] BYREF
  std::_List_iterator<int> v31; // [rsp+E0h] [rbp-80h] BYREF
  std::_List_const_iterator<int> v32; // [rsp+F0h] [rbp-70h] BYREF
  std::_List_iterator<int> v33; // [rsp+100h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v34; // [rsp+110h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v35; // [rsp+120h] [rbp-40h] BYREF
  const CfgMonsterRand *pCfgRand; // [rsp+128h] [rbp-38h]
  int32_t i_1; // [rsp+134h] [rbp-2Ch]
  int32_t nSize; // [rsp+138h] [rbp-28h]
  int32_t i_2; // [rsp+13Ch] [rbp-24h]
  const CfgMonsterRand *pCfgRand_0; // [rsp+140h] [rbp-20h]
  int32_t i_5; // [rsp+14Ch] [rbp-14h]

  if ( !std::list<int>::empty(&this->m_lRandType) )
  {
    __x._M_node = std::list<int>::begin(&this->m_lRandType)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v28._M_node = std::list<int>::end(&this->m_lRandType)._M_node;
      std::_List_const_iterator<int>::_List_const_iterator(&v27, &v28);
      if ( !std::_List_const_iterator<int>::operator!=(&iter, &v27) )
        break;
      v1 = *std::_List_const_iterator<int>::operator*(&iter);
      v2 = Answer::Singleton<CfgData>::instance();
      MonsterRandTable = CfgData::GetMonsterRandTable(v2);
      pCfgRand = CfgMonsterRandTable::GetMonsterRand(MonsterRandTable, v1);
      if ( pCfgRand )
      {
        if ( !std::vector<AttrAddon>::empty(&pCfgRand->vAttrValue) )
        {
          for ( i._M_current = std::vector<AttrAddon>::begin(&pCfgRand->vAttrValue)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i) )
          {
            __rhs._M_current = std::vector<AttrAddon>::end(&pCfgRand->vAttrValue)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i, &__rhs) )
              break;
            v4 = -__gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i)->addon;
            index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i)->index;
            Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, v4);
          }
        }
        if ( !std::vector<AttrAddon>::empty(&pCfgRand->vAttrRatio) )
        {
          for ( i_0._M_current = std::vector<AttrAddon>::begin(&pCfgRand->vAttrRatio)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i_0) )
          {
            v30._M_current = std::vector<AttrAddon>::end(&pCfgRand->vAttrRatio)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i_0, &v30) )
              break;
            v6 = -__gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_0)->addon;
            v7 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_0)->index;
            Unit::AddBuffAttrRatio(this, (const CObjAttrs::Index_T)v7, v6);
          }
        }
        if ( pCfgRand->nSkill > 0 )
        {
          for ( i_1 = 0; i_1 <= 9; ++i_1 )
          {
            if ( this->m_vSkills[i_1].nId == pCfgRand->nSkill )
            {
              this->m_vSkills[i_1].nId = 0;
              this->m_cfgmonster.unique_skill[i_1].skillid = 0;
              this->m_cfgmonster.unique_skill[i_1].minHp = 0;
              this->m_cfgmonster.unique_skill[i_1].maxHp = 0;
              break;
            }
          }
        }
      }
      std::_List_const_iterator<int>::operator++(&iter);
    }
  }
  std::list<int>::clear(&this->m_lRandType);
  if ( this->m_cfgmonster.rand_count > 0 && !std::vector<int>::empty(&this->m_cfgmonster.rand_types) )
  {
    std::vector<int>::vector(&vId, &this->m_cfgmonster.rand_types);
    nSize = std::vector<int>::size(&this->m_cfgmonster.rand_types);
    if ( this->m_cfgmonster.rand_count < nSize )
    {
      nSize = this->m_cfgmonster.rand_count;
      M_current = std::vector<int>::end(&vId)._M_current;
      v10._M_current = std::vector<int>::begin(&vId)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
        v10,
        (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    }
    for ( i_2 = 0; i_2 < nSize; ++i_2 )
    {
      v11 = std::vector<int>::operator[](&vId, i_2);
      std::list<int>::push_back(&this->m_lRandType, v11);
    }
    std::vector<int>::~vector(&vId);
  }
  if ( !std::list<int>::empty(&this->m_lRandType) )
  {
    v31._M_node = std::list<int>::begin(&this->m_lRandType)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&iter_0, &v31);
    while ( 1 )
    {
      v33._M_node = std::list<int>::end(&this->m_lRandType)._M_node;
      std::_List_const_iterator<int>::_List_const_iterator(&v32, &v33);
      if ( !std::_List_const_iterator<int>::operator!=(&iter_0, &v32) )
        break;
      v12 = *std::_List_const_iterator<int>::operator*(&iter_0);
      v13 = Answer::Singleton<CfgData>::instance();
      v14 = CfgData::GetMonsterRandTable(v13);
      pCfgRand_0 = CfgMonsterRandTable::GetMonsterRand(v14, v12);
      if ( pCfgRand_0 )
      {
        if ( !std::vector<AttrAddon>::empty(&pCfgRand_0->vAttrValue) )
        {
          for ( i_3._M_current = std::vector<AttrAddon>::begin(&pCfgRand_0->vAttrValue)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i_3) )
          {
            v34._M_current = std::vector<AttrAddon>::end(&pCfgRand_0->vAttrValue)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i_3, &v34) )
              break;
            addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_3)->addon;
            v16 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_3)->index;
            Unit::AddAttrValue(this, (const CObjAttrs::Index_T)v16, addon);
          }
        }
        if ( !std::vector<AttrAddon>::empty(&pCfgRand_0->vAttrRatio) )
        {
          for ( i_4._M_current = std::vector<AttrAddon>::begin(&pCfgRand_0->vAttrRatio)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&i_4) )
          {
            v35._M_current = std::vector<AttrAddon>::end(&pCfgRand_0->vAttrRatio)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&i_4, &v35) )
              break;
            v17 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_4)->addon;
            v18 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&i_4)->index;
            Unit::AddBuffAttrRatio(this, (const CObjAttrs::Index_T)v18, v17);
          }
        }
        if ( pCfgRand_0->nSkill > 0 )
        {
          for ( i_5 = 0; i_5 <= 9; ++i_5 )
          {
            if ( !this->m_vSkills[i_5].nId )
            {
              this->m_vSkills[i_5].nId = pCfgRand_0->nSkill;
              this->m_cfgmonster.unique_skill[i_5].skillid = pCfgRand_0->nSkill;
              this->m_cfgmonster.unique_skill[i_5].minHp = 0;
              this->m_cfgmonster.unique_skill[i_5].maxHp = 100;
              break;
            }
          }
        }
      }
      std::_List_const_iterator<int>::operator++(&iter_0);
    }
  }
}


#####################################
void __cdecl Monster::updatePlayerDamage(Monster *const this, Player *player, int32_t damage)
{
  std::pair<const long int,PlayerScore> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  __int64 __x; // [rsp+28h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v7; // [rsp+30h] [rbp-10h] BYREF

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,PlayerScore>::find(&this->m_PlayerScore, &__x)._M_node;
    v7._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &v7) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      v3->second.nDamage += damage;
      std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea = 1;
    }
    else
    {
      Monster::addPlayer(this, player, damage);
    }
    this->m_DamageFlag = 1;
    Monster::updataBossDamageInfo(this, player);
  }
}


#####################################
void __cdecl Monster::checkEnterBossRegion(Monster *const this)
{
  int32_t MoveRange; // r12d
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > findIter; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-60h] BYREF
  PlayerList inPlayer; // [rsp+30h] [rbp-50h] BYREF
  Position pos; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v6; // [rsp+50h] [rbp-30h] BYREF
  __int64 __x; // [rsp+58h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v8; // [rsp+60h] [rbp-20h] BYREF
  Player *player; // [rsp+68h] [rbp-18h]

  if ( this->m_pMap )
  {
    std::list<Player *>::list(&inPlayer);
    MoveRange = Monster::getMoveRange(this);
    pos = Monster::getBornPosition(this);
    Map::getAreaPlayer(this->m_pMap, &inPlayer, &pos, MoveRange);
    if ( !std::list<Player *>::empty(&inPlayer) )
    {
      for ( iter._M_node = std::list<Player *>::begin(&inPlayer)._M_node; ; std::_List_iterator<Player *>::operator++(&iter) )
      {
        v6._M_node = std::list<Player *>::end(&inPlayer)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&iter, &v6) )
          break;
        player = *std::_List_iterator<Player *>::operator*(&iter);
        if ( player )
        {
          __x = Player::getCid(player);
          findIter._M_node = std::map<long,PlayerScore>::find(&this->m_PlayerScore, &__x)._M_node;
          v8._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&findIter, &v8) )
          {
            if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&findIter)->second.inArea )
              continue;
            std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&findIter)->second.inArea = 1;
          }
          else
          {
            Monster::addPlayer(this, player, 0);
          }
          Monster::SendAllDamageRank(this, player);
        }
      }
    }
    std::list<Player *>::~list(&inPlayer);
  }
}


#####################################
void __cdecl Monster::checkLeaveBossRegion(Monster *const this)
{
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v4; // rax
  int32_t v5; // ebx
  int32_t nTeamId; // [rsp+1Ch] [rbp-74h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+20h] [rbp-70h] BYREF
  Int32List teamClear; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > __x; // [rsp+40h] [rbp-50h] BYREF
  Position pos; // [rsp+50h] [rbp-40h] BYREF
  Position BornPosition; // [rsp+60h] [rbp-30h] BYREF
  bool isRank; // [rsp+77h] [rbp-19h]
  Player *player; // [rsp+78h] [rbp-18h]

  isRank = 0;
  std::list<int>::list(&teamClear);
  iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
  while ( 1 )
  {
    __x._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &__x) )
      break;
    RunnerId = StaticObj::GetRunnerId(this);
    nCharId = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nCharId;
    v3 = Answer::Singleton<GameService>::instance();
    player = GameService::getPlayer(v3, nCharId, RunnerId, 1);
    if ( !player )
      goto LABEL_3;
    pos = StaticObj::getCurrentTile(player);
    BornPosition = Monster::getBornPosition(this);
    v5 = Position::tileDistance(&BornPosition, &pos);
    if ( v5 <= Monster::getMoveRange(this) )
    {
LABEL_12:
      std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter);
    }
    else
    {
      if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea )
      {
        Monster::sendScorePlayerInfo(this, player, 2);
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea = 0;
      }
      nTeamId = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam;
      if ( nTeamId > 0 )
      {
        if ( Monster::checkTeamClear(this, nTeamId) )
          std::list<int>::push_back(&teamClear, &nTeamId);
        goto LABEL_12;
      }
LABEL_3:
      v4._M_node = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter, 0)._M_node;
      std::map<long,PlayerScore>::erase(&this->m_PlayerScore, v4);
      isRank = 1;
    }
  }
  if ( !std::list<int>::empty(&teamClear) )
  {
    isRank = 1;
    Monster::clearTeam(this, &teamClear);
  }
  if ( isRank )
  {
    Monster::refreshRank(this);
    Monster::SendAllDamageRank(this);
  }
  std::list<int>::~list(&teamClear);
}


#####################################
void __cdecl Monster::addPlayer(Monster *const this, Player *player, int32_t damage)
{
  CExtCharTeam *CharTeam; // rax
  PlayerScore *v4; // rax
  PlayerScore score; // [rsp+20h] [rbp-70h] BYREF
  _BYTE v7[16]; // [rsp+60h] [rbp-30h] BYREF
  _BYTE v8[32]; // [rsp+70h] [rbp-20h] BYREF

  if ( player )
  {
    PlayerScore::PlayerScore(&score);
    score.nCharId = Player::getCid(player);
    Player::getName((const Player *const)v7);
    std::string::operator=(&score.strName, v7);
    std::string::~string(v7);
    score.nDamage = damage;
    score.nTeam = Player::GetTeamId(player);
    Player::GetCharTeam(player);
    CExtCharTeam::GetLeaderName((const CExtCharTeam *const)v8);
    std::string::operator=(&score.teamName, v8);
    std::string::~string(v8);
    CharTeam = Player::GetCharTeam(player);
    score.nTeamLeaderId = CExtCharTeam::GetLeaderId(CharTeam);
    score.inArea = 1;
    v4 = std::map<long,PlayerScore>::operator[](&this->m_PlayerScore, &score.nCharId);
    PlayerScore::operator=(v4, &score);
    PlayerScore::~PlayerScore(&score);
  }
}


#####################################
void __cdecl Monster::updataBossDamageInfo(Monster *const this, Player *player)
{
  Monster::sendScorePlayerInfo(this, player, 1);
}


#####################################
void __cdecl Monster::SendAllDamageRank(Monster *const this, Player *player)
{
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  Monster::sendScorePlayerInfo(this, player, 1);
  packet = Monster::sendAllRankInfo(this);
  if ( packet )
  {
    GateIndex = Player::getGateIndex(player);
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v4, ConnId, GateIndex, packet);
  }
}


#####################################
void __cdecl Monster::sendScorePlayerInfo(Monster *const this, Player *player, int8_t status)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t Mid; // eax
  std::pair<const long int,PlayerScore> *v6; // rax
  std::pair<const int,PlayerScore> *v7; // rax
  int32_t id; // ebx
  CWorldBoss *v9; // rax
  int32_t BossRevie; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  GameService *v13; // rax
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > teamScore; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > score; // [rsp+30h] [rbp-60h] BYREF
  __int64 __x; // [rsp+38h] [rbp-58h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v18; // [rsp+40h] [rbp-50h] BYREF
  std::string val; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > v20; // [rsp+60h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+70h] [rbp-20h]
  const PlayerScore *player_score; // [rsp+78h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    score._M_node = std::map<long,PlayerScore>::find(&this->m_PlayerScore, &__x)._M_node;
    v18._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator==(&score, &v18) )
    {
      ConnId = Player::getConnId(player);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D11u);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, status);
        Mid = Monster::getMid(this);
        Answer::NetPacket::writeInt32(packet, Mid);
        player_score = &std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&score)->second;
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        v6 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&score);
        teamScore._M_node = std::map<int,PlayerScore>::find(&this->m_TeamScore, &v6->second.nTeam)._M_node;
        v20._M_node = std::map<int,PlayerScore>::end(&this->m_TeamScore)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator!=(&teamScore, &v20) )
        {
          v7 = std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator->(&teamScore);
          Answer::NetPacket::writeInt32(packet, v7->second.nIndex);
        }
        else
        {
          Answer::NetPacket::writeInt32(packet, player_score->nIndex);
        }
        Answer::NetPacket::writeInt32(packet, player_score->nDamage);
        id = this->m_cfgmapmonster.id;
        v9 = Answer::Singleton<CWorldBoss>::instance();
        BossRevie = CWorldBoss::GetBossRevie(v9, id);
        Answer::NetPacket::writeInt32(packet, BossRevie);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        LOBYTE(id) = Player::getConnId(player);
        v13 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v13, id, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl Monster::refreshRank(Monster *const this)
{
  std::pair<const long int,PlayerScore> *v2; // rax
  std::pair<const int,PlayerScore> *v3; // rbx
  int32_t nDamage; // r12d
  PlayerScore *p_second; // rbx
  std::pair<const long int,PlayerScore> *v6; // rax
  PlayerScore *v7; // rax
  PlayerScore *const *v8; // rax
  std::_Rb_tree_const_iterator<PlayerScore*> iter_1; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > iter_0; // [rsp+20h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > iter_team; // [rsp+30h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v13; // [rsp+50h] [rbp-50h] BYREF
  PlayerScore *__x; // [rsp+58h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > v15; // [rsp+60h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,PlayerScore> > v16; // [rsp+70h] [rbp-30h] BYREF
  PlayerScore *v17; // [rsp+78h] [rbp-28h] BYREF
  std::_Rb_tree_const_iterator<PlayerScore*> v18; // [rsp+80h] [rbp-20h] BYREF
  int32_t nIndex; // [rsp+8Ch] [rbp-14h]

  std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::clear(&this->m_ScoreRank);
  std::map<int,PlayerScore>::clear(&this->m_TeamScore);
  for ( iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter) )
  {
    v13._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &v13) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nDamage > 0
      && std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam <= 0 )
    {
      __x = &std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second;
      std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::insert(
        &this->m_ScoreRank,
        &__x);
    }
    else
    {
      v2 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      iter_team._M_node = std::map<int,PlayerScore>::find(&this->m_TeamScore, &v2->second.nTeam)._M_node;
      v15._M_node = std::map<int,PlayerScore>::end(&this->m_TeamScore)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator!=(&iter_team, &v15) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator->(&iter_team);
        nDamage = v3->second.nDamage;
        v3->second.nDamage = nDamage
                           + std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nDamage;
      }
      else
      {
        p_second = &std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second;
        v6 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
        v7 = std::map<int,PlayerScore>::operator[](&this->m_TeamScore, &v6->second.nTeam);
        PlayerScore::operator=(v7, p_second);
      }
    }
  }
  for ( iter_0._M_node = std::map<int,PlayerScore>::begin(&this->m_TeamScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator++(&iter_0, 0) )
  {
    v16._M_node = std::map<int,PlayerScore>::end(&this->m_TeamScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator!=(&iter_0, &v16) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator->(&iter_0)->second.nDamage > 0 )
    {
      v17 = &std::_Rb_tree_iterator<std::pair<int const,PlayerScore>>::operator->(&iter_0)->second;
      std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::insert(
        &this->m_ScoreRank,
        &v17);
    }
  }
  nIndex = 1;
  for ( iter_1._M_node = std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::begin(&this->m_ScoreRank)._M_node;
        ;
        std::_Rb_tree_const_iterator<PlayerScore *>::operator++(&iter_1) )
  {
    v18._M_node = std::multiset<PlayerScore *,PlayerScoreRankGreater,std::allocator<PlayerScore *>>::end(&this->m_ScoreRank)._M_node;
    if ( !std::_Rb_tree_const_iterator<PlayerScore *>::operator!=(&iter_1, &v18) )
      break;
    v8 = std::_Rb_tree_const_iterator<PlayerScore *>::operator*(&iter_1);
    (*v8)->nIndex = nIndex++;
  }
}


#####################################
void __cdecl Monster::setKillerBossPalyer(Monster *const this)
{
  std::pair<const long int,PlayerScore> *v1; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+20h] [rbp-10h] BYREF
  const PlayerScore *score; // [rsp+28h] [rbp-8h]

  iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
  eiter._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &eiter) )
  {
    v1 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
    score = &v1->second;
    if ( v1->second.nIndex == 1 )
    {
      this->m_killer.id = score->nCharId;
      this->m_killer.type = 1;
      return;
    }
    std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter);
  }
}


#####################################
bool __cdecl Monster::needCheckBossRank(Monster *const this)
{
  int64_t nCurTick; // [rsp+18h] [rbp-8h]

  if ( !Monster::IsRankBoss(this) )
    return 0;
  nCurTick = Unit::getTick(this);
  if ( this->m_nLastCheckBossTick + 1000 >= nCurTick )
    return 0;
  this->m_nLastCheckBossTick = nCurTick;
  return 1;
}


#####################################
void __cdecl Monster::SendAllDamageRank(Monster *const this)
{
  std::pair<const long int,PlayerScore> *v1; // rax
  GameService *v2; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  CharIdList Ranklist; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > __x; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  std::list<long>::list(&Ranklist);
  for ( iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea )
    {
      v1 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      std::list<long>::push_back(&Ranklist, &v1->second.nCharId);
    }
  }
  packet = Monster::sendAllRankInfo(this);
  if ( packet )
  {
    v2 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v2, packet, &Ranklist);
  }
  std::list<long>::~list(&Ranklist);
}


#####################################
void __cdecl Monster::UpdateRegionPlayer(Monster *const this)
{
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  std::pair<const long int,PlayerScore> *v4; // rbx
  std::pair<const long int,PlayerScore> *v5; // rax
  std::pair<const long int,PlayerScore> *v6; // rbx
  CExtCharTeam *CharTeam; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > __x; // [rsp+20h] [rbp-30h] BYREF
  char v10; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &__x) )
      break;
    RunnerId = StaticObj::GetRunnerId(this);
    nCharId = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nCharId;
    v3 = Answer::Singleton<GameService>::instance();
    player = GameService::getPlayer(v3, nCharId, RunnerId, 1);
    if ( player )
    {
      v4 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      v4->second.nTeam = Player::GetTeamId(player);
      Player::GetCharTeam(player);
      CExtCharTeam::GetLeaderName((const CExtCharTeam *const)&v10);
      v5 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      std::string::operator=(&v5->second.teamName, &v10);
      std::string::~string(&v10);
      v6 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      CharTeam = Player::GetCharTeam(player);
      v6->second.nTeamLeaderId = CExtCharTeam::GetLeaderId(CharTeam);
    }
  }
}


#####################################
bool __cdecl Monster::checkTeamClear(const Monster *const this, int32_t nTeamId)
{
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,PlayerScore> > __x; // [rsp+20h] [rbp-20h] BYREF
  Player *player; // [rsp+28h] [rbp-18h]

  for ( iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<long const,PlayerScore>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam == nTeamId
      && std::_Rb_tree_const_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea )
    {
      RunnerId = StaticObj::GetRunnerId(this);
      nCharId = std::_Rb_tree_const_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nCharId;
      v5 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v5, nCharId, RunnerId, 1);
      if ( player && Unit::isAlive(player) )
        return 0;
    }
  }
  return 1;
}


#####################################
void __cdecl Monster::clearTeam(Monster *const this, const Int32List *const tList)
{
  int32_t *p_nTeam; // r12
  const std::_List_node_base *M_node; // rbx
  std::_List_const_iterator<int> v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v5; // rax
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v7; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+30h] [rbp-30h] BYREF
  std::_List_const_iterator<int> v9; // [rsp+40h] [rbp-20h] BYREF

  iter._M_node = std::map<long,PlayerScore>::begin(&this->m_PlayerScore)._M_node;
  while ( 1 )
  {
    v7._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &v7) )
      break;
    __x._M_node = std::list<int>::end(tList)._M_node;
    p_nTeam = &std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam;
    M_node = std::list<int>::end(tList)._M_node;
    v4._M_node = std::list<int>::begin(tList)._M_node;
    v9._M_node = std::find<std::_List_const_iterator<int>,int>(v4, (std::_List_const_iterator<int>)M_node, p_nTeam)._M_node;
    if ( std::_List_const_iterator<int>::operator!=(&v9, &__x) )
    {
      if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea )
      {
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nDamage = 0;
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter);
      }
      else
      {
        v5._M_node = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter, 0)._M_node;
        std::map<long,PlayerScore>::erase(&this->m_PlayerScore, v5);
      }
    }
    else
    {
      std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl Monster::onPlayerDie(Monster *const this, Player *player)
{
  int32_t nTeamId; // [rsp+1Ch] [rbp-54h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+20h] [rbp-50h] BYREF
  Int32List teamClear; // [rsp+30h] [rbp-40h] BYREF
  __int64 __x; // [rsp+48h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v6; // [rsp+50h] [rbp-20h] BYREF
  bool bChange; // [rsp+5Fh] [rbp-11h]

  if ( player )
  {
    bChange = 0;
    std::list<int>::list(&teamClear);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,PlayerScore>::find(&this->m_PlayerScore, &__x)._M_node;
    v6._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &v6) )
    {
      nTeamId = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam;
      if ( nTeamId <= 0 )
      {
        std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nDamage = 0;
      }
      else if ( Monster::checkTeamClear(this, nTeamId) )
      {
        std::list<int>::push_back(&teamClear, &nTeamId);
      }
    }
    if ( !std::list<int>::empty(&teamClear) )
    {
      bChange = 1;
      Monster::clearTeam(this, &teamClear);
    }
    if ( bChange )
    {
      Monster::refreshRank(this);
      Monster::SendAllDamageRank(this);
    }
    std::list<int>::~list(&teamClear);
  }
}


#####################################
void __cdecl Monster::onTeamUpdate(Monster *const this, Player *player)
{
  std::pair<const long int,PlayerScore> *v2; // rbx
  std::pair<const long int,PlayerScore> *v3; // rax
  std::pair<const long int,PlayerScore> *v4; // rbx
  CExtCharTeam *CharTeam; // rax
  int32_t nTeam; // edx
  std::pair<const long int,PlayerScore> *v7; // rax
  int32_t nOldTeamId; // [rsp+1Ch] [rbp-64h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > iter; // [rsp+20h] [rbp-60h] BYREF
  Int32List teamClear; // [rsp+30h] [rbp-50h] BYREF
  __int64 __x; // [rsp+48h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,PlayerScore> > v12; // [rsp+50h] [rbp-30h] BYREF
  _BYTE v13[15]; // [rsp+60h] [rbp-20h] BYREF
  bool bChange; // [rsp+6Fh] [rbp-11h]

  if ( player )
  {
    bChange = 0;
    std::list<int>::list(&teamClear);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,PlayerScore>::find(&this->m_PlayerScore, &__x)._M_node;
    v12._M_node = std::map<long,PlayerScore>::end(&this->m_PlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator!=(&iter, &v12) )
    {
      nOldTeamId = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam;
      v2 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      v2->second.nTeam = Player::GetTeamId(player);
      Player::GetCharTeam(player);
      CExtCharTeam::GetLeaderName((const CExtCharTeam *const)v13);
      v3 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      std::string::operator=(&v3->second.teamName, v13);
      std::string::~string(v13);
      v4 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
      CharTeam = Player::GetCharTeam(player);
      v4->second.nTeamLeaderId = CExtCharTeam::GetLeaderId(CharTeam);
      if ( nOldTeamId > 0 && Monster::checkTeamClear(this, nOldTeamId) )
        std::list<int>::push_back(&teamClear, &nOldTeamId);
      if ( std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam <= 0 )
      {
        if ( !std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.inArea )
        {
          std::map<long,PlayerScore>::erase(&this->m_PlayerScore, iter);
        }
        else if ( !Unit::isAlive(player) )
        {
          std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nDamage = 0;
          bChange = 1;
        }
      }
      else
      {
        nTeam = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter)->second.nTeam;
        if ( Monster::checkTeamClear(this, nTeam) )
        {
          v7 = std::_Rb_tree_iterator<std::pair<long const,PlayerScore>>::operator->(&iter);
          std::list<int>::push_back(&teamClear, &v7->second.nTeam);
        }
      }
    }
    if ( !std::list<int>::empty(&teamClear) )
    {
      bChange = 1;
      Monster::clearTeam(this, &teamClear);
    }
    if ( bChange )
    {
      Monster::refreshRank(this);
      Monster::SendAllDamageRank(this);
    }
    std::list<int>::~list(&teamClear);
  }
}


#####################################
void __cdecl Monster::setDelFlg(Monster *const this)
{
  Monster::leaveMap(this);
  this->m_delFlag = 1;
}


#####################################
void __cdecl Monster::MonsterDamageDrop(Monster *const this, Player *pPlayer)
{
  int8_t autoPick; // r14
  int8_t bossSign; // r13
  int32_t MonsterMid; // r12d
  Position CentosPos; // [rsp+40h] [rbp-70h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+50h] [rbp-60h] BYREF
  DropItemVector dropItems; // [rsp+60h] [rbp-50h] BYREF
  std::string dropper; // [rsp+80h] [rbp-30h] BYREF
  _BYTE v10[33]; // [rsp+8Fh] [rbp-21h] BYREF

  std::vector<DropItem>::vector(&dropItems);
  Monster::generateFightDrop(this, &dropItems, pPlayer, 1);
  if ( this->m_pMap && !std::vector<DropItem>::empty(&dropItems) )
  {
    CDropItemGroup::CDropItemGroup(&dropItemGroup);
    CentosPos = StaticObj::getCurrentTile(this);
    autoPick = this->m_cfgmonster.drop_free;
    bossSign = this->m_cfgmonster.boss_sign;
    MonsterMid = this->m_cfgmonster.mid;
    std::allocator<char>::allocator(v10);
    std::string::string(&dropper, &unk_8E6560);
    CDropItemGroup::init(
      &dropItemGroup,
      0,
      this->m_pMap,
      &CentosPos,
      pPlayer,
      2,
      this->m_cfgmonster.mid,
      &dropItems,
      &dropper,
      MonsterMid,
      bossSign,
      autoPick);
    std::string::~string(&dropper);
    std::allocator<char>::~allocator(v10);
    Map::addDropItemGroup(this->m_pMap, &dropItemGroup);
    CDropItemGroup::~CDropItemGroup(&dropItemGroup);
  }
  std::vector<DropItem>::~vector(&dropItems);
}


#####################################
int32_t __cdecl Monster::getEscapeOdds(Monster *const this)
{
  if ( this->m_cfgSpecialMonster.EscapeOdds <= 0 )
    return 50;
  else
    return this->m_cfgSpecialMonster.EscapeOdds;
}


#####################################
bool __cdecl Monster::updatePosition(Monster *const this)
{
  int32_t v4; // r13d
  int32_t v5; // r12d
  EntityId_t v6; // rbx
  GameService *v7; // rax
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v12; // rax
  int32_t y; // ebx
  int32_t x; // ecx
  UnitHandle tmptar; // [rsp+20h] [rbp-90h] BYREF
  Position tartile; // [rsp+30h] [rbp-80h]
  Position oldPos; // [rsp+40h] [rbp-70h] BYREF
  Position tar; // [rsp+50h] [rbp-60h] BYREF
  Position src; // [rsp+60h] [rbp-50h] BYREF
  int64_t ticks; // [rsp+70h] [rbp-40h]
  int32_t Dir; // [rsp+7Ch] [rbp-34h]
  Unit *pTarget; // [rsp+80h] [rbp-30h]
  Unit *pTarget_0; // [rsp+88h] [rbp-28h]
  Position CurrentTile; // 0:rax.8

  if ( !Unit::isMoving(this)
    || !Unit::isAlive(this)
    || !(*((unsigned int (__fastcall **)(Monster *const))this->_vptr_Entity + 28))(this) )
  {
    return 0;
  }
  if ( !this->m_pMap )
    return 0;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 0;
  }
  ticks = Unit::getTick(this) - this->m_posUpdateTick;
  if ( ticks <= 1000 )
    return 0;
  this->m_posUpdateTick = Unit::getTick(this);
  oldPos = this->m_currentPos;
  tar = Unit::getTargetTile(this);
  src = StaticObj::getCurrentTile(this);
  Dir = Map::UnitDirection(&src, &tar);
  CurrentTile = StaticObj::getCurrentTile(this);
  tartile = Map::MoveOneTile(this->m_pMap, CurrentTile, Dir);
  if ( tartile )
  {
    this->m_currentPos = Map::tileToPixel(tartile.x, tartile.y);
    this->m_currentTile = tartile;
    if ( !UnitHandle::isEmpty(&this->m_target) )
    {
      RunnerId = StaticObj::GetRunnerId(this);
      type = this->m_target.type;
      id = this->m_target.id;
      v12 = Answer::Singleton<GameService>::instance();
      pTarget_0 = GameService::getUnit(v12, id, type, RunnerId);
      if ( pTarget_0 && Unit::isAlive(pTarget_0) && StaticObj::getMap(pTarget_0) == this->m_pMap )
      {
        this->m_targetPos = StaticObj::getCurrentPixel(pTarget_0);
        this->m_targetTile = StaticObj::getCurrentTile(pTarget_0);
      }
    }
    y = Unit::getTargetTile(this).y;
    x = Unit::getTargetTile(this).x;
    Unit::resetDirection(this, x, y);
    if ( this->m_pMap )
      Map::checkAreaChange(this->m_pMap, this, &oldPos);
    if ( Position::operator==(&this->m_currentPos, &this->m_targetPos) )
      (*((void (__fastcall **)(Monster *const))this->_vptr_Entity + 16))(this);
    if ( this->m_state == MonsterState::MS_WALK_ATTACK )
    {
      tmptar = Monster::randHandle(this, this->m_target.id);
      if ( !UnitHandle::isEmpty(&tmptar) && &this->m_target != &tmptar )
        memcpy(&this->m_target, &tmptar, 0xCu);
    }
    Unit::broadcastMoveMonster(this, tartile);
    return 1;
  }
  else
  {
    if ( !UnitHandle::isEmpty(&this->m_target) )
    {
      v4 = StaticObj::GetRunnerId(this);
      v5 = this->m_target.type;
      v6 = this->m_target.id;
      v7 = Answer::Singleton<GameService>::instance();
      pTarget = GameService::getUnit(v7, v6, v5, v4);
      if ( pTarget && Unit::isAlive(pTarget) && StaticObj::getMap(pTarget) == this->m_pMap )
      {
        this->m_targetPos = StaticObj::getCurrentPixel(pTarget);
        this->m_targetTile = StaticObj::getCurrentTile(pTarget);
      }
    }
    return 0;
  }
}


#####################################
int32_t __cdecl Monster::GetMonsterCfgReviveTime(Monster *const this)
{
  int32_t boss_sign; // r12d
  int32_t revive_time; // ebx
  CfgData *v3; // rax

  boss_sign = this->m_cfgmonster.boss_sign;
  revive_time = this->m_cfgmonster.revive_time;
  v3 = Answer::Singleton<CfgData>::instance();
  return CfgData::GetMonsterReviveTime(v3, revive_time, boss_sign);
}


#####################################
void __cdecl Monster::AddDiligenceDrop(Monster *const this, Player *pPlayer, DropItemVector *const dropItems)
{
  int32_t DiligenceType; // ebx
  CfgData *v4; // rax
  int8_t itemClass; // bl
  DropItem *v6; // rax
  int32_t DiligenceValue; // eax
  float v8; // [rsp+4h] [rbp-ACh]
  DropItem DropItemStu; // [rsp+20h] [rbp-90h] BYREF
  RateItem stu; // [rsp+50h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<DropItem*,std::vector<DropItem> > it; // [rsp+70h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<DropItem*,std::vector<DropItem> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  bool NeedClear; // [rsp+8Fh] [rbp-21h]
  DiligenceCfg *pCfg; // [rsp+90h] [rbp-20h]
  int32_t AddValue; // [rsp+9Ch] [rbp-14h]

  if ( pPlayer )
  {
    if ( this->m_cfgmonster.DiligenceType > 0 )
    {
      NeedClear = 0;
      DiligenceType = this->m_cfgmonster.DiligenceType;
      v4 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetDiligenceCfg(v4, DiligenceType);
      if ( pCfg )
      {
        for ( it._M_current = std::vector<DropItem>::begin(dropItems)._M_current;
              ;
              __gnu_cxx::__normal_iterator<DropItem *,std::vector<DropItem>>::operator++(&it, 0) )
        {
          __rhs._M_current = std::vector<DropItem>::end(dropItems)._M_current;
          if ( !__gnu_cxx::operator!=<DropItem *,std::vector<DropItem>>(&it, &__rhs) )
            break;
          itemClass = __gnu_cxx::__normal_iterator<DropItem *,std::vector<DropItem>>::operator->(&it)->itemClass;
          v6 = __gnu_cxx::__normal_iterator<DropItem *,std::vector<DropItem>>::operator->(&it);
          if ( DiligenceCfg::IsInItemList(pCfg, v6->itemId, itemClass) )
          {
            NeedClear = 1;
            break;
          }
        }
        if ( NeedClear )
        {
          Player::CleanDiligenceValue(pPlayer, this->m_cfgmonster.DiligenceType);
        }
        else if ( this->m_cfgmonster.DiligenceValue > 0 )
        {
          DiligenceValue = Player::GetDiligenceValue(pPlayer, this->m_cfgmonster.DiligenceType);
          if ( DiligenceValue + this->m_cfgmonster.DiligenceValue < pCfg->nValues )
          {
            v8 = (float)this->m_cfgmonster.DiligenceValue;
            AddValue = (int)(float)((float)((float)((float)Unit::GetAttrValue(
                                                             pPlayer,
                                                             CObjAttrs::Index_T::ATTR_DROP_RATE)
                                                  / 1000.0)
                                          + 1.0)
                                  * v8);
            Player::AddDiligenceValue(pPlayer, this->m_cfgmonster.DiligenceType, AddValue);
          }
          else
          {
            DiligenceCfg::RandItem(&stu, pCfg);
            if ( stu.nItemId > 0 && stu.nItemClass > 0 && stu.nItemCount > 0 )
            {
              Player::CleanDiligenceValue(pPlayer, this->m_cfgmonster.DiligenceType);
              memset(&DropItemStu.costType, 0, 20);
              *(_DWORD *)&DropItemStu.itemClass = (unsigned __int8)stu.nItemClass;
              DropItemStu.itemCount = stu.nItemCount;
              DropItemStu.itemId = stu.nItemId;
              *(_QWORD *)&DropItemStu.bindType = (unsigned __int8)stu.nBind;
              std::vector<DropItem>::push_back(dropItems, &DropItemStu);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Monster::AddHP(Monster *const this, int32_t nAddValue)
{
  int64_t m_MonsterHp; // rbx
  int64_t v3; // rbx

  if ( nAddValue <= 0 )
  {
    if ( this->m_MonsterHp <= 0 )
      return;
  }
  else
  {
    m_MonsterHp = this->m_MonsterHp;
    if ( m_MonsterHp == (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this) )
      return;
  }
  this->m_MonsterHp += nAddValue;
  v3 = this->m_MonsterHp;
  if ( v3 > (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this) )
    this->m_MonsterHp = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this);
  if ( this->m_MonsterHp < 0 )
    this->m_MonsterHp = 0;
  Unit::setNeedSync(this);
  Unit::setNeedSyncSelf(this);
}


#####################################
void __cdecl Monster::FillHP(Monster *const this, int32_t nPercent)
{
  __int64 hp; // rbx

  hp = this->m_unitAttr.hp;
  if ( hp != (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this) )
  {
    this->m_MonsterHp = (*((__int64 (__fastcall **)(Monster *const))this->_vptr_Entity + 20))(this);
    this->m_bDie = 0;
    Unit::setNeedSync(this);
    Unit::setNeedSyncSelf(this);
  }
}


