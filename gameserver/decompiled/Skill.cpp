// Decompiled methods for class: Skill
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl Skill::posAction(
        Skill *const this,
        Unit *const launcher,
        Position srcPos,
        Position pos,
        UnitVector *const targets,
        SkillResultVector *const results,
        bool bAction)
{
  int32_t v8; // eax
  Position posa; // [rsp+20h] [rbp-80h] BYREF
  Position srcPosa; // [rsp+30h] [rbp-70h] BYREF
  Unit *launchera; // [rsp+40h] [rbp-60h]
  Skill *thisa; // [rsp+48h] [rbp-58h]
  UnitHandle targetHandle; // [rsp+50h] [rbp-50h] BYREF
  Position targetPos; // [rsp+60h] [rbp-40h] BYREF
  UnitHandle v17; // [rsp+70h] [rbp-30h] BYREF
  int32_t distance; // [rsp+84h] [rbp-1Ch]
  Map *pMap; // [rsp+88h] [rbp-18h]

  thisa = this;
  launchera = launcher;
  srcPosa = srcPos;
  posa = pos;
  distance = 3;
  if ( Entity::getType(launcher) == EntityType::ET_PLAYER && StaticObj::InDungeon(launchera) )
    distance = 10;
  v8 = Position::tileDistance(&posa, &srcPosa);
  if ( v8 <= distance + thisa->m_cfg->distance )
  {
    if ( bAction )
    {
      UnitHandle::UnitHandle(&v17, -1, -1);
      Skill::broadcastAction(thisa, launchera, &posa, &v17);
    }
    if ( thisa->m_cfg->special == 1 )
    {
      pMap = StaticObj::getMap(launchera);
      if ( pMap )
      {
        if ( Map::isWalkablePosition(pMap, posa.x, posa.y) )
          Unit::setAtTile(launchera, pMap, posa.x, posa.y);
      }
    }
    Skill::posResult(thisa, launchera, posa, targets, results);
  }
  else if ( bAction )
  {
    UnitHandle::UnitHandle(&targetHandle, -1, -1);
    Position::Position(&targetPos, -1, -1);
    Skill::broadcastAction(thisa, launchera, &targetPos, &targetHandle);
  }
}


#####################################
void __cdecl Skill::posResult(
        Skill *const this,
        Unit *const launcher,
        Position pos,
        UnitVector *const targets,
        SkillResultVector *const results)
{
  Player *v5; // rax
  CExtCharCarrier *CharCarrier; // rax
  CExtCharCarrier *v8; // rax
  size_t v9; // rdx
  Player *v11; // rax
  CExtCharCarrier *v12; // rax
  CExtCharCarrier *v14; // rax
  Position posa; // [rsp+20h] [rbp-E0h] BYREF
  Unit *launchera; // [rsp+30h] [rbp-D0h]
  Skill *thisa; // [rsp+38h] [rbp-C8h]
  SkillResult result; // [rsp+40h] [rbp-C0h] BYREF
  SkillResult launcherResult; // [rsp+70h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<Unit**,std::vector<Unit*> > it; // [rsp+A0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<Unit**,std::vector<Unit*> > __rhs; // [rsp+B0h] [rbp-50h] BYREF
  Map *pMap; // [rsp+C0h] [rbp-40h]
  Unit *pLauncher; // [rsp+C8h] [rbp-38h]
  Player *pPlayer; // [rsp+D0h] [rbp-30h]
  Unit *target; // [rsp+D8h] [rbp-28h]
  Unit *pTarget; // [rsp+E0h] [rbp-20h]
  Player *pPlayer_0; // [rsp+E8h] [rbp-18h]

  thisa = this;
  launchera = launcher;
  posa = pos;
  pMap = StaticObj::getMap(launcher);
  if ( pMap )
  {
    SkillResult::SkillResult(&launcherResult, 0, 0, 0, 0, 0, 0, 0);
    launcherResult.unitId = (*((__int64 (__fastcall **)(Unit *))launchera->_vptr_Entity + 2))(launchera);
    launcherResult.unitType = Entity::getType(launchera);
    pLauncher = launchera;
    if ( Entity::getType(launchera) == EntityType::ET_PLAYER )
    {
      v5 = launchera
         ? (Player *)__dynamic_cast(
                       launchera,
                       (const struct __class_type_info *)&`typeinfo for'Unit,
                       (const struct __class_type_info *)&`typeinfo for'Player,
                       0)
         : 0LL;
      pPlayer = v5;
      if ( v5 )
      {
        CharCarrier = Player::GetCharCarrier(pPlayer);
        if ( CExtCharCarrier::IsInCarrier(CharCarrier) )
        {
          v8 = Player::GetCharCarrier(pPlayer);
          pLauncher = CExtCharCarrier::GetCarrier(v8);
        }
      }
    }
    v9 = std::vector<Unit *>::size(targets);
    std::vector<SkillResult>::reserve(results, v9);
    for ( it._M_current = std::vector<Unit *>::begin(targets)._M_current;
          ;
          __gnu_cxx::__normal_iterator<Unit **,std::vector<Unit *>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<Unit *>::end(targets)._M_current;
      if ( !__gnu_cxx::operator!=<Unit **,std::vector<Unit *>>(&it, &__rhs) )
        break;
      target = *__gnu_cxx::__normal_iterator<Unit **,std::vector<Unit *>>::operator*(&it);
      if ( target && Map::checkSkillTarget(pMap, launchera, posa, target, thisa->m_cfg) )
      {
        SkillResult::SkillResult(&result, 0, 0, 0, 0, 0, 0, 0);
        result.unitId = (*((__int64 (__fastcall **)(Unit *))target->_vptr_Entity + 2))(target);
        result.unitType = Entity::getType(target);
        pTarget = target;
        if ( Entity::getType(target) == EntityType::ET_PLAYER )
        {
          v11 = target
              ? (Player *)__dynamic_cast(
                            target,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0)
              : 0LL;
          pPlayer_0 = v11;
          if ( v11 )
          {
            v12 = Player::GetCharCarrier(pPlayer_0);
            if ( CExtCharCarrier::IsInCarrier(v12) )
            {
              v14 = Player::GetCharCarrier(pPlayer_0);
              pTarget = CExtCharCarrier::GetCarrier(v14);
            }
          }
        }
        Skill::instantResult(thisa, pLauncher, pTarget, &launcherResult, &result);
        std::vector<SkillResult>::push_back(results, &result);
      }
    }
    if ( launcherResult.hpChange > 0 && Unit::isAlive(pLauncher) )
      (*((void (__fastcall **)(Unit *, _QWORD))pLauncher->_vptr_Entity + 21))(
        pLauncher,
        (unsigned int)launcherResult.hpChange);
    Skill::broadcastResult(thisa, launchera, &launcherResult, &posa, results);
  }
}


#####################################
bool __cdecl Skill::calcDamage(
        Skill *const this,
        Unit *const launcher,
        Unit *const target,
        int64_t *const damge,
        int32_t *const attackState,
        int32_t SkillKind,
        int32_t *const Bg)
{
  Monster *v7; // rax
  Trailer *v9; // rax
  Answer::Random *v10; // rax
  Player *v11; // rax
  CExtEquip *Equip; // rax
  Monster *v15; // rax
  Player *v16; // rax
  Player *v18; // rax
  CExtEquip *v19; // rax
  Answer::Random *v20; // rax
  Answer::Random *v21; // rax
  Answer::Random *v22; // rax
  SkillId_t id; // ebx
  CfgData *v24; // rax
  Answer::Random *v25; // rax
  int32_t v26; // eax
  Player *v28; // rax
  Player *v29; // rax
  CExtCharFamily *CharFamily; // rax
  int32_t DefRdc; // eax
  float v33; // xmm0_4
  Player *v36; // rax
  Player *v37; // rax
  int64_t Currency; // rbx
  CShenWei *ShenWei; // rax
  int32_t v40; // edx
  Player *v41; // rax
  CExtEquip *v42; // rax
  int64_t Tick; // rbx
  int64_t TeJieCRI; // rax
  CExtEquip *v46; // rax
  Answer::Random *v47; // rax
  int32_t v48; // eax
  int64_t v49; // rdx
  __int128 v50; // rtt
  Monster *v51; // rax
  CObjPet *v53; // rax
  CExtCharPet *CharPet; // rax
  Param2 angry; // [rsp+40h] [rbp-190h]
  Position pos; // [rsp+50h] [rbp-180h] BYREF
  Position CurrentTile; // [rsp+60h] [rbp-170h] BYREF
  int32_t src_hit; // [rsp+70h] [rbp-160h]
  int32_t tar_agile; // [rsp+74h] [rbp-15Ch]
  int32_t dodge; // [rsp+78h] [rbp-158h]
  int32_t Dto; // [rsp+7Ch] [rbp-154h]
  int32_t Boss_Cri_Rat; // [rsp+80h] [rbp-150h]
  int32_t Boss_add_pec; // [rsp+84h] [rbp-14Ch]
  int32_t crit_rate; // [rsp+88h] [rbp-148h]
  int32_t crit_rdc; // [rsp+8Ch] [rbp-144h]
  int32_t crit; // [rsp+90h] [rbp-140h]
  int32_t fDmgAdd; // [rsp+94h] [rbp-13Ch]
  Buff *pFittingBuff; // [rsp+98h] [rbp-138h]
  int32_t XinMoAtk; // [rsp+A0h] [rbp-130h]
  int32_t XinMoDef; // [rsp+A4h] [rbp-12Ch]
  int32_t DiffDamge; // [rsp+A8h] [rbp-128h]
  bool BAdd; // [rsp+AFh] [rbp-121h]
  Monster *pMonster; // [rsp+B0h] [rbp-120h]
  Trailer *pTrailer; // [rsp+B8h] [rbp-118h]
  Player *TarPlayer; // [rsp+C0h] [rbp-110h]
  int32_t nValues; // [rsp+C8h] [rbp-108h]
  int32_t AttrBg; // [rsp+CCh] [rbp-104h]
  Monster *pMonster_0; // [rsp+D0h] [rbp-100h]
  Player *pPlayer; // [rsp+D8h] [rbp-F8h]
  float BaseDamge; // [rsp+E4h] [rbp-ECh]
  int32_t SunAndMoonLevel; // [rsp+E8h] [rbp-E8h]
  int32_t WeaponLuck; // [rsp+ECh] [rbp-E4h]
  int32_t Atk; // [rsp+F0h] [rbp-E0h]
  int32_t atkMin; // [rsp+F4h] [rbp-DCh]
  int32_t atkMax; // [rsp+F8h] [rbp-D8h]
  int32_t Luck; // [rsp+FCh] [rbp-D4h]
  int32_t tar_def_min; // [rsp+100h] [rbp-D0h]
  int32_t tar_def_max; // [rsp+104h] [rbp-CCh]
  int32_t def; // [rsp+108h] [rbp-C8h]
  int32_t Distance; // [rsp+10Ch] [rbp-C4h]
  const SpeciaSkillDistance *pSpSkDi; // [rsp+110h] [rbp-C0h]
  int32_t src_def_rdc; // [rsp+118h] [rbp-B8h]
  int32_t src_dmg_add_pec; // [rsp+11Ch] [rbp-B4h]
  int32_t tar_dmg_rdc_pec; // [rsp+120h] [rbp-B0h]
  float dmg_def; // [rsp+124h] [rbp-ACh]
  int32_t Modify; // [rsp+128h] [rbp-A8h]
  float skillModify; // [rsp+12Ch] [rbp-A4h]
  Player *pPlayer_0; // [rsp+130h] [rbp-A0h]
  int32_t PoFang; // [rsp+13Ch] [rbp-94h]
  Player *pPlayer_1; // [rsp+140h] [rbp-90h]
  Player *pTarget; // [rsp+148h] [rbp-88h]
  int32_t PkAddPec; // [rsp+154h] [rbp-7Ch]
  int32_t PkRdcPec; // [rsp+158h] [rbp-78h]
  float Pk_def; // [rsp+15Ch] [rbp-74h]
  Player *pTarget_0; // [rsp+160h] [rbp-70h]
  Player *pPlayer_2; // [rsp+168h] [rbp-68h]
  int32_t Rate; // [rsp+174h] [rbp-5Ch]
  Player *pPlayer_3; // [rsp+178h] [rbp-58h]
  int32_t nTeJie2Values; // [rsp+180h] [rbp-50h]
  int32_t nTeJie5Values; // [rsp+184h] [rbp-4Ch]
  int64_t TarCurHp; // [rsp+188h] [rbp-48h]
  int64_t TarMaxHp; // [rsp+190h] [rbp-40h]
  int32_t critValue; // [rsp+198h] [rbp-38h]
  int32_t Toughness; // [rsp+19Ch] [rbp-34h]
  Monster *pMonster_1; // [rsp+1A0h] [rbp-30h]
  bool SpecialPet; // [rsp+1AFh] [rbp-21h]
  CObjPet *Pet; // [rsp+1B0h] [rbp-20h]
  Player *pPlayer_4; // [rsp+1B8h] [rbp-18h]

  if ( Entity::getType(target) == EntityType::ET_MONSTER )
  {
    v7 = target
       ? (Monster *)__dynamic_cast(
                      target,
                      (const struct __class_type_info *)&`typeinfo for'Unit,
                      (const struct __class_type_info *)&`typeinfo for'Monster,
                      0)
       : 0LL;
    pMonster = v7;
    if ( v7 )
    {
      if ( Monster::GetPureDamage(pMonster) > 0 )
      {
        *damge = Monster::GetPureDamage(pMonster);
        return 1;
      }
    }
  }
  if ( Entity::getType(target) == EntityType::ET_TRAILER )
  {
    v9 = target
       ? (Trailer *)__dynamic_cast(
                      target,
                      (const struct __class_type_info *)&`typeinfo for'Unit,
                      (const struct __class_type_info *)&`typeinfo for'Trailer,
                      0)
       : 0LL;
    pTrailer = v9;
    if ( v9 )
    {
      if ( Trailer::GetPureDamage(pTrailer) > 0 )
      {
        *damge = Trailer::GetPureDamage(pTrailer);
        return 1;
      }
    }
  }
  src_hit = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_HIT);
  tar_agile = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_AGILE);
  dodge = 100;
  Dto = (100 * src_hit + 500000) / (tar_agile + 5000);
  if ( Dto > 74 )
    dodge = Dto;
  else
    dodge = 75;
  v10 = Answer::Singleton<Answer::Random>::instance();
  if ( Answer::Random::generate(v10, 1, 100) > dodge )
  {
    *damge = 0;
    *attackState |= 2u;
    return 0;
  }
  if ( Entity::getType(target) == EntityType::ET_PLAYER )
  {
    v11 = target
        ? (Player *)__dynamic_cast(
                      target,
                      (const struct __class_type_info *)&`typeinfo for'Unit,
                      (const struct __class_type_info *)&`typeinfo for'Player,
                      0)
        : 0LL;
    TarPlayer = v11;
    if ( v11 )
    {
      Equip = Player::GetEquip(TarPlayer);
      nValues = CExtEquip::GetTeJieValue(Equip, 89);
      if ( nValues > 0 && Player::GetTeJieDamageTimes(TarPlayer) >= nValues )
      {
        *attackState |= 0x20u;
        Player::ResetTeJieDamageTimes(TarPlayer);
        return 0;
      }
    }
  }
  Boss_Cri_Rat = 0;
  Boss_add_pec = 0;
  if ( Entity::getType(launcher) != EntityType::ET_PLAYER || Entity::getType(target) != EntityType::ET_MONSTER )
  {
    WeaponLuck = 0;
    if ( Entity::getType(launcher) == EntityType::ET_PLAYER )
    {
      v18 = launcher
          ? (Player *)__dynamic_cast(
                        launcher,
                        (const struct __class_type_info *)&`typeinfo for'Unit,
                        (const struct __class_type_info *)&`typeinfo for'Player,
                        0)
          : 0LL;
      pPlayer_0 = v18;
      if ( v18 )
      {
        v19 = Player::GetEquip(pPlayer_0);
        WeaponLuck = CExtEquip::GetWeaponBless(v19);
      }
    }
    Atk = 0;
    atkMin = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MIN);
    atkMax = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MAX);
    Luck = WeaponLuck + Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_LUCK);
    if ( Luck > 8 )
    {
      Atk = atkMax;
      goto LABEL_75;
    }
    if ( (unsigned int)Luck > 8 )
    {
      if ( (unsigned int)Luck < 0xFFFFFFF8 )
      {
        Atk = atkMin;
LABEL_75:
        tar_def_min = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_DEF_MIN);
        tar_def_max = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_DEF_MAX);
        v22 = Answer::Singleton<Answer::Random>::instance();
        def = Answer::Random::generate(v22, tar_def_min, tar_def_max);
        pos = StaticObj::getCurrentTile(target);
        CurrentTile = StaticObj::getCurrentTile(launcher);
        Distance = Position::tileDistance(&CurrentTile, &pos);
        id = this->m_cfg->id;
        v24 = Answer::Singleton<CfgData>::instance();
        pSpSkDi = CfgData::GetSpeciaSkillDistance(v24, id, Distance);
        if ( pSpSkDi && pSpSkDi->PoFang > 0 )
        {
          PoFang = pSpSkDi->PoFang;
          if ( Unit::checkBuffBySpecail(target, 115) )
            PoFang = 50 * PoFang / 100;
          def -= PoFang * def / 100;
        }
        src_def_rdc = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_DEF_RDC);
        v25 = Answer::Singleton<Answer::Random>::instance();
        v26 = Answer::Random::generate(v25, 1, 1000);
        if ( v26 <= src_def_rdc )
          def = 0;
        if ( def < 0 )
          def = 0;
        src_dmg_add_pec = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_DMG_ADD_PEC);
        tar_dmg_rdc_pec = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_DMG_RDC_PEC);
        if ( Entity::getType(target) == EntityType::ET_PLAYER && Entity::getType(launcher) == EntityType::ET_PLAYER )
        {
          v28 = launcher
              ? (Player *)__dynamic_cast(
                            launcher,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0)
              : 0LL;
          pPlayer_1 = v28;
          v29 = target
              ? (Player *)__dynamic_cast(
                            target,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0)
              : 0LL;
          pTarget = v29;
          if ( pPlayer_1 )
          {
            if ( pTarget )
            {
              CharFamily = Player::GetCharFamily(pTarget);
              DefRdc = CExtCharFamily::GetDefRdc(CharFamily, pPlayer_1);
              tar_dmg_rdc_pec += DefRdc;
            }
          }
        }
        dmg_def = (float)((float)(src_dmg_add_pec + Boss_add_pec - tar_dmg_rdc_pec) / 1000.0) + 1.0;
        *damge = Atk - def;
        if ( *damge <= 0 )
          *damge = 1;
        if ( dmg_def <= 0.0099999998 )
          dmg_def = 0.0099999998;
        Modify = this->m_cfg->attack_modify;
        if ( pSpSkDi && pSpSkDi->SkillModify > 0 )
          Modify = pSpSkDi->SkillModify;
        skillModify = (float)Modify / 10000.0;
        if ( Entity::getType(launcher) == EntityType::ET_PLAYER
          && (Entity::getType(target) == EntityType::ET_PLAYER || Entity::getType(launcher) == EntityType::ET_PET) )
        {
          PkAddPec = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_PK_ADD_PEC);
          PkRdcPec = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_PK_RDC_PEC);
          Pk_def = (float)((float)(PkAddPec - PkRdcPec) / 1000.0) + 1.0;
          if ( Pk_def <= 0.0099999998 )
            Pk_def = 0.0099999998;
          v33 = (float)((float)((float)(int)*damge * skillModify) * dmg_def) * Pk_def;
          *damge = (unsigned int)(int)(float)(v33 + v33);
        }
        else if ( Entity::getType(launcher) == EntityType::ET_MONSTER
               && (Entity::getType(target) == EntityType::ET_PLAYER || Entity::getType(launcher) == EntityType::ET_PET) )
        {
          *damge = (unsigned int)(int)(float)((float)((float)(int)*damge * skillModify) * dmg_def);
        }
        if ( Entity::getType(launcher) == EntityType::ET_PLAYER && Entity::getType(target) == EntityType::ET_PLAYER )
        {
          v36 = target
              ? (Player *)__dynamic_cast(
                            target,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0)
              : 0LL;
          pTarget_0 = v36;
          v37 = launcher
              ? (Player *)__dynamic_cast(
                            launcher,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0)
              : 0LL;
          pPlayer_2 = v37;
          if ( pTarget_0 )
          {
            if ( pPlayer_2 )
            {
              Currency = Player::GetCurrency(pTarget_0, CURRENCY_TYPE::CURRENCY_HONOR);
              ShenWei = Player::GetShenWei(pPlayer_2);
              Rate = CShenWei::GetRankAttr(ShenWei, Currency);
              if ( Rate > 0 )
              {
                if ( *damge )
                {
                  *damge += Rate * *damge / 100;
                  v40 = *attackState;
                  BYTE1(v40) = BYTE1(*attackState) | 1;
                  *attackState = v40;
                }
              }
            }
          }
        }
        goto LABEL_137;
      }
    }
    else
    {
      v20 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v20, Luck, 9) == 9 )
      {
        Atk = atkMax;
        goto LABEL_75;
      }
    }
    v21 = Answer::Singleton<Answer::Random>::instance();
    Atk = atkMin + Answer::Random::generate(v21, 1, atkMax - atkMin);
    goto LABEL_75;
  }
  AttrBg = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_BG);
  if ( AttrBg > 0 )
    *attackState |= 0x40u;
  if ( target )
    v15 = (Monster *)__dynamic_cast(
                       target,
                       (const struct __class_type_info *)&`typeinfo for'Unit,
                       (const struct __class_type_info *)&`typeinfo for'Monster,
                       0);
  else
    v15 = 0;
  pMonster_0 = v15;
  if ( launcher )
    v16 = (Player *)__dynamic_cast(
                      launcher,
                      (const struct __class_type_info *)&`typeinfo for'Unit,
                      (const struct __class_type_info *)&`typeinfo for'Player,
                      0);
  else
    v16 = 0;
  pPlayer = v16;
  if ( v16 || pMonster_0 )
  {
    if ( (*((unsigned __int8 (__fastcall **)(Monster *))pMonster_0->_vptr_Entity + 17))(pMonster_0) )
    {
      Boss_add_pec = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_BOSS_DMG_ADD_PEC);
      Boss_Cri_Rat = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_BOSS_CRI_RAT);
    }
    if ( Monster::IsSunAndMoonMonster(pMonster_0) && AttrBg > 0 )
    {
      SunAndMoonLevel = Player::getRecord(pPlayer, 37506);
      if ( SkillKind == 5 )
      {
        AttrBg *= SunAndMoonLevel;
      }
      else if ( SkillKind == 6 )
      {
        AttrBg += 1000 * SunAndMoonLevel;
      }
      *Bg = AttrBg / 1000;
    }
    BaseDamge = (float)((float)((float)(*((int (__fastcall **)(Player *))pPlayer->_vptr_Entity + 10))(pPlayer)
                              * (float)AttrBg)
                      / 10.0)
              / 1000.0;
    *damge = (unsigned int)(int)BaseDamge;
    if ( *damge <= 0 )
      *damge = 1;
  }
LABEL_137:
  crit_rate = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_CRI_RAT);
  crit_rdc = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_CRI_RDC);
  crit = crit_rate + Boss_Cri_Rat - crit_rdc;
  if ( Entity::getType(launcher) == EntityType::ET_PLAYER )
  {
    v41 = launcher
        ? (Player *)__dynamic_cast(
                      launcher,
                      (const struct __class_type_info *)&`typeinfo for'Unit,
                      (const struct __class_type_info *)&`typeinfo for'Player,
                      0)
        : 0LL;
    pPlayer_3 = v41;
    if ( v41 )
    {
      v42 = Player::GetEquip(pPlayer_3);
      nTeJie2Values = CExtEquip::GetTeJieValue(v42, 92);
      if ( nTeJie2Values > 0 )
      {
        Tick = Unit::getTick(pPlayer_3);
        TeJieCRI = Player::GetTeJieCRI(pPlayer_3);
        if ( Tick - TeJieCRI > 1000 * nTeJie2Values )
        {
          crit = 1000;
          Player::SetTeJieCRI(pPlayer_3);
        }
      }
      v46 = Player::GetEquip(pPlayer_3);
      nTeJie5Values = CExtEquip::GetTeJieValue(v46, 91);
      TarCurHp = (*((__int64 (__fastcall **)(Unit *const))target->_vptr_Entity + 19))(target);
      TarMaxHp = (*((__int64 (__fastcall **)(Unit *const))target->_vptr_Entity + 20))(target);
      if ( nTeJie5Values > 0 && 100 * TarCurHp / TarMaxHp <= 49 )
        crit += nTeJie5Values;
    }
  }
  if ( crit > 0 )
  {
    v47 = Answer::Singleton<Answer::Random>::instance();
    v48 = Answer::Random::generate(v47, 1, 1000);
    if ( v48 <= crit )
    {
      critValue = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_CRI_VAL);
      Toughness = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_TOUGHNESS);
      critValue -= Toughness;
      if ( critValue < 0 )
        critValue = 0;
      *damge = (unsigned int)(int)(float)((float)critValue + (float)(1.5 * (float)(int)*damge));
      *attackState |= 1u;
    }
  }
  v49 = 1;
  if ( *damge > 0 )
    v49 = *damge;
  *damge = v49;
  fDmgAdd = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_DMG_ADD);
  *damge += fDmgAdd;
  pFittingBuff = Unit::findBuffBySpecail(launcher, 117);
  if ( pFittingBuff )
  {
    angry = Buff::getAngry(pFittingBuff);
    if ( angry.nParam1 > 0 && angry.nParam2 > 0 )
    {
      v50 = 100 * (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 19))(launcher);
      if ( (__int64)(v50 / (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 20))(launcher)) < angry.nParam1 )
        *damge += angry.nParam2 * *damge / 100;
    }
  }
  XinMoAtk = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_XIN_MO_ATK);
  XinMoDef = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_XIN_MO_DEF);
  DiffDamge = XinMoAtk - XinMoDef;
  if ( XinMoAtk - XinMoDef < 0 )
    DiffDamge = 0;
  BAdd = 0;
  if ( Entity::getType(target) == EntityType::ET_MONSTER )
  {
    v51 = target
        ? (Monster *)__dynamic_cast(
                       target,
                       (const struct __class_type_info *)&`typeinfo for'Unit,
                       (const struct __class_type_info *)&`typeinfo for'Monster,
                       0)
        : 0LL;
    pMonster_1 = v51;
    if ( v51 && Monster::IsXinMoMonster(pMonster_1) )
    {
      SpecialPet = 0;
      if ( Entity::getType(launcher) == EntityType::ET_PET )
      {
        v53 = launcher
            ? (CObjPet *)__dynamic_cast(
                           launcher,
                           (const struct __class_type_info *)&`typeinfo for'Unit,
                           (const struct __class_type_info *)&`typeinfo for'CObjPet,
                           0)
            : 0LL;
        Pet = v53;
        if ( v53 )
        {
          pPlayer_4 = CObjPet::GetPlayer(Pet);
          if ( pPlayer_4 )
          {
            CharPet = Player::GetCharPet(pPlayer_4);
            if ( CExtCharPet::GetStar(CharPet) > 70 )
              SpecialPet = 1;
          }
        }
      }
      if ( SpecialPet )
      {
        *damge = 1000000;
        BAdd = 1;
      }
      if ( Entity::getType(launcher) == EntityType::ET_PLAYER )
      {
        *damge = 70 * DiffDamge + 5 * *damge / 100;
        BAdd = 1;
      }
    }
  }
  if ( !BAdd )
    *damge += DiffDamge;
  return 1;
}


#####################################
int32_t __cdecl Skill::calBaseRevive(int32_t atkMin, int32_t atkMax, int32_t sklModify)
{
  Answer::Random *v3; // rax
  int32_t v4; // eax
  int32_t result; // [rsp+18h] [rbp-8h]
  int resulta; // [rsp+18h] [rbp-8h]

  if ( atkMax > atkMin )
  {
    v3 = Answer::Singleton<Answer::Random>::instance();
    result = Answer::Random::generate(v3, atkMin, atkMax);
  }
  else
  {
    result = atkMax;
  }
  resulta = (int)(float)((float)result * (float)((float)sklModify / 10000.0));
  v4 = 1;
  if ( resulta > 0 )
    return resulta;
  return v4;
}


#####################################
void __cdecl Skill::instantResult(
        Skill *const this,
        Unit *const launcher,
        Unit *const target,
        SkillResult *const launcherResult,
        SkillResult *const targetResult)
{
  int32_t hpChange; // ebx
  Monster *v6; // rax
  Monster *v7; // rax
  Monster *v9; // rax
  Player *v10; // rax
  int64_t v11; // rbx
  Curse *Curse; // rax
  int32_t v13; // edx
  int32_t v14; // edx
  Player *v15; // rax
  int64_t v16; // rax
  CExtEquip *Equip; // rax
  Answer::Random *v18; // rax
  int32_t v19; // eax
  bool v20; // al
  int32_t v21; // edx
  int32_t v22; // eax
  int32_t v23; // edx
  Player *v25; // rax
  Monster *v26; // rax
  int32_t Mid; // ebx
  CKunExt *CKunExt; // rax
  CTianLing *TianLing; // rax
  int32_t v32; // eax
  Monster *v33; // rax
  Answer::Random *v35; // rax
  int v36; // eax
  CfgData *v37; // rax
  int32_t v38; // edx
  Buff *v39; // rbx
  int32_t v40; // edx
  Answer::Random *v41; // rax
  int v42; // eax
  CfgData *v43; // rax
  int32_t v44; // edx
  Buff *v45; // rbx
  int32_t v46; // edx
  Answer::Random *v47; // rax
  int v48; // eax
  CfgData *v50; // rax
  int32_t v51; // edx
  Buff *v52; // rbx
  Answer::Random *v53; // rax
  int32_t v55; // ebx
  CfgData *v56; // rax
  int32_t v59; // edx
  SkillBuff *v60; // rbx
  Player *v61; // rax
  int32_t groupid; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t bg; // [rsp+60h] [rbp-1D0h] BYREF
  int32_t attackState; // [rsp+64h] [rbp-1CCh] BYREF
  int64_t damage; // [rsp+68h] [rbp-1C8h] BYREF
  UnitHandle v70; // [rsp+70h] [rbp-1C0h]
  UnitHandle v71; // [rsp+80h] [rbp-1B0h]
  UnitHandle v72; // [rsp+90h] [rbp-1A0h]
  MemChrBag item; // [rsp+A0h] [rbp-190h] BYREF
  UnitHandle v74; // [rsp+C0h] [rbp-170h] BYREF
  UnitHandle v75; // [rsp+D0h] [rbp-160h] BYREF
  UnitHandle v76; // [rsp+E0h] [rbp-150h] BYREF
  UnitHandle v77; // [rsp+F0h] [rbp-140h] BYREF
  bool bAddBuff; // [rsp+10Fh] [rbp-121h]
  int32_t atkMin; // [rsp+110h] [rbp-120h]
  int32_t atkMax; // [rsp+114h] [rbp-11Ch]
  int32_t skillModify; // [rsp+118h] [rbp-118h]
  int32_t addValue; // [rsp+11Ch] [rbp-114h]
  int32_t backVal; // [rsp+120h] [rbp-110h]
  int32_t suckVal; // [rsp+124h] [rbp-10Ch]
  int32_t launchermid; // [rsp+128h] [rbp-108h]
  int32_t targetmid; // [rsp+12Ch] [rbp-104h]
  Monster *pMonster; // [rsp+130h] [rbp-100h]
  Monster *pMonster_0; // [rsp+138h] [rbp-F8h]
  int32_t HpDamage; // [rsp+140h] [rbp-F0h]
  int32_t KunLiDamage; // [rsp+144h] [rbp-ECh]
  bool NoDamage; // [rsp+14Bh] [rbp-E5h]
  int32_t TmpDamage; // [rsp+14Ch] [rbp-E4h]
  int32_t realDamage; // [rsp+150h] [rbp-E0h]
  float suckModify; // [rsp+154h] [rbp-DCh]
  Monster *pMonster_1; // [rsp+158h] [rbp-D8h]
  Player *pPlayer; // [rsp+160h] [rbp-D0h]
  int32_t QieGeValue; // [rsp+16Ch] [rbp-C4h]
  Player *pPlayer_0; // [rsp+170h] [rbp-C0h]
  int32_t KunLiDef; // [rsp+17Ch] [rbp-B4h]
  int32_t KunLiValue; // [rsp+180h] [rbp-B0h]
  int32_t TeJie1Param; // [rsp+184h] [rbp-ACh]
  Player *pPlayer_1; // [rsp+188h] [rbp-A8h]
  Monster *monster; // [rsp+190h] [rbp-A0h]
  Monster *pMonster_2; // [rsp+198h] [rbp-98h]
  int32_t src_ply; // [rsp+1A0h] [rbp-90h]
  int32_t src_pzn; // [rsp+1A4h] [rbp-8Ch]
  int32_t des_ply; // [rsp+1A8h] [rbp-88h]
  int32_t des_pzn; // [rsp+1ACh] [rbp-84h]
  CfgBuff *cfgBuff; // [rsp+1B0h] [rbp-80h]
  Buff *buff; // [rsp+1B8h] [rbp-78h]
  CfgBuff *cfgBuff_0; // [rsp+1C0h] [rbp-70h]
  Buff *buff_0; // [rsp+1C8h] [rbp-68h]
  int32_t XuanYun; // [rsp+1D0h] [rbp-60h]
  int32_t des_XuanYun; // [rsp+1D4h] [rbp-5Ch]
  CfgBuff *cfgBuff_1; // [rsp+1D8h] [rbp-58h]
  Buff *buff_1; // [rsp+1E0h] [rbp-50h]
  CfgBuff *cfgBuff_2; // [rsp+1E8h] [rbp-48h]
  SkillBuff *buff_2; // [rsp+1F0h] [rbp-40h]
  int32_t atkMin_0; // [rsp+1F8h] [rbp-38h]
  int32_t atkMax_0; // [rsp+1FCh] [rbp-34h]
  int32_t dmgAdd; // [rsp+200h] [rbp-30h]
  int32_t skillModify_0; // [rsp+204h] [rbp-2Ch]
  Player *pPlayer_2; // [rsp+208h] [rbp-28h]
  UnitHandle v124; // 0:r8.12
  UnitHandle v125; // 0:r8.12
  UnitHandle v126; // 0:r8.12

  switch ( this->m_cfg->special )
  {
    case 2:
      Unit::clearDebuff(target, 0);
      break;
    case 3:
      Unit::clearBuff(target, 0);
      break;
    case 4:
      (*((void (__fastcall **)(Unit *const, __int64))target->_vptr_Entity + 22))(target, 100);
      hpChange = targetResult->hpChange;
      targetResult->hpChange = hpChange + (*((__int64 (__fastcall **)(Unit *const))target->_vptr_Entity + 20))(target);
      break;
    default:
      if ( this->m_cfg->beneficial )
      {
        if ( this->m_cfg->attack_type )
        {
          atkMin = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MIN);
          atkMax = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MAX);
          skillModify = this->m_cfg->attack_modify;
          addValue = Skill::calBaseRevive(atkMin, atkMax, skillModify);
          if ( this->m_cfg->append_value > 0 )
            addValue += this->m_cfg->append_value;
          (*((void (__fastcall **)(Unit *const, _QWORD))target->_vptr_Entity + 21))(target, (unsigned int)addValue);
          targetResult->hpChange += addValue;
          targetResult->attackState = 0;
        }
      }
      else if ( this->m_cfg->attack_type )
      {
        damage = 0;
        backVal = 0;
        suckVal = 0;
        launchermid = 0;
        targetmid = 0;
        if ( Entity::getType(launcher) == EntityType::ET_MONSTER )
        {
          v6 = launcher
             ? (Monster *)__dynamic_cast(
                            launcher,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Monster,
                            0)
             : 0LL;
          pMonster = v6;
          if ( v6 )
            launchermid = Monster::getMid(pMonster);
        }
        if ( Entity::getType(target) == EntityType::ET_MONSTER )
        {
          v7 = target
             ? (Monster *)__dynamic_cast(
                            target,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Monster,
                            0)
             : 0LL;
          pMonster_0 = v7;
          if ( v7 )
            targetmid = Monster::getMid(pMonster_0);
        }
        attackState = 0;
        bg = 0;
        Skill::calcDamage(this, launcher, target, &damage, &attackState, this->m_cfg->kind, &bg);
        targetResult->Bg = bg;
        if ( (attackState & 2) != 0 )
        {
          targetResult->hpChange = 0;
          targetResult->attackState = attackState;
        }
        else
        {
          if ( damage <= 0 )
            damage = 1;
          HpDamage = 0;
          if ( Entity::getType(launcher) == EntityType::ET_PLAYER && Entity::getType(target) == EntityType::ET_MONSTER )
          {
            v9 = target
               ? (Monster *)__dynamic_cast(
                              target,
                              (const struct __class_type_info *)&`typeinfo for'Unit,
                              (const struct __class_type_info *)&`typeinfo for'Monster,
                              0)
               : 0LL;
            pMonster_1 = v9;
            v10 = launcher
                ? (Player *)__dynamic_cast(
                              launcher,
                              (const struct __class_type_info *)&`typeinfo for'Unit,
                              (const struct __class_type_info *)&`typeinfo for'Player,
                              0)
                : 0LL;
            pPlayer = v10;
            if ( pMonster_1 )
            {
              if ( pPlayer )
              {
                if ( Monster::IfCurse(pMonster_1) )
                {
                  v11 = (*((__int64 (__fastcall **)(Monster *))pMonster_1->_vptr_Entity + 20))(pMonster_1);
                  Curse = Player::GetCurse(pPlayer);
                  HpDamage = Curse::DamageValue(Curse, v11);
                  v70.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
                  v70.type = v13;
                  v124.id = v70.id;
                  v124.type = v13;
                  targetResult->CurseHp = Unit::struckDamage(
                                            target,
                                            HpDamage,
                                            &attackState,
                                            this->m_cfg->attack_type,
                                            v124,
                                            launchermid);
                }
                if ( Monster::IsQueGe(pMonster_1) )
                {
                  QieGeValue = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_QIE_GE);
                  if ( QieGeValue > 0 )
                  {
                    v71.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
                    v71.type = v14;
                    v125.id = v71.id;
                    v125.type = v14;
                    targetResult->QieGe = Unit::struckDamage(
                                            target,
                                            QieGeValue,
                                            &attackState,
                                            this->m_cfg->attack_type,
                                            v125,
                                            launchermid);
                  }
                }
              }
            }
          }
          if ( this->m_cfg->append_value > 0 )
            damage += this->m_cfg->append_value;
          KunLiDamage = 0;
          NoDamage = 0;
          if ( Entity::getType(target) == EntityType::ET_PLAYER )
          {
            v15 = target
                ? (Player *)__dynamic_cast(
                              target,
                              (const struct __class_type_info *)&`typeinfo for'Unit,
                              (const struct __class_type_info *)&`typeinfo for'Player,
                              0)
                : 0LL;
            pPlayer_0 = v15;
            if ( v15 )
            {
              v16 = (*((__int64 (__fastcall **)(Player *))pPlayer_0->_vptr_Entity + 19))(pPlayer_0);
              if ( v16 <= damage )
              {
                Equip = Player::GetEquip(pPlayer_0);
                TeJie1Param = CExtEquip::GetTeJieValue(Equip, 87);
                v20 = 0;
                if ( TeJie1Param > 0 )
                {
                  v18 = Answer::Singleton<Answer::Random>::instance();
                  v19 = Answer::Random::generate(v18, 1, 1000);
                  if ( v19 <= TeJie1Param )
                    v20 = 1;
                }
                if ( v20 && Entity::getType(launcher) == EntityType::ET_PLAYER )
                {
                  targetResult->hpChange += damage;
                  v21 = targetResult->attackState;
                  BYTE1(v21) |= 0x20u;
                  targetResult->attackState = v21;
                  (*((void (__fastcall **)(Player *, _QWORD))pPlayer_0->_vptr_Entity + 21))(
                    pPlayer_0,
                    (unsigned int)targetResult->hpChange);
                  NoDamage = 1;
                }
              }
              KunLiDef = Unit::GetAttrValue(pPlayer_0, CObjAttrs::Index_T::ATTR_KUN_LI_DEF);
              KunLiDamage = damage * KunLiDef / 1000;
              KunLiValue = (*((__int64 (__fastcall **)(Player *))pPlayer_0->_vptr_Entity + 24))(pPlayer_0);
              if ( KunLiDamage <= KunLiValue )
                v22 = KunLiDamage;
              else
                v22 = KunLiValue;
              KunLiDamage = v22;
              damage -= v22;
            }
          }
          TmpDamage = 0;
          if ( damage <= 2000000000 )
            TmpDamage = damage;
          else
            TmpDamage = 2000000000;
          realDamage = 0;
          if ( !NoDamage )
          {
            v72.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
            v72.type = v23;
            v126.id = v72.id;
            v126.type = v23;
            realDamage = Unit::struckDamage(
                           target,
                           TmpDamage,
                           &attackState,
                           this->m_cfg->attack_type,
                           v126,
                           launchermid);
            targetResult->hpChange -= realDamage;
            targetResult->attackState = attackState;
            if ( (targetResult->attackState & 8) == 0 && KunLiDamage > 0 )
              (*((void (__fastcall **)(Unit *const, _QWORD))target->_vptr_Entity + 23))(
                target,
                (unsigned int)-KunLiDamage);
          }
          Unit::checkBuffEffect(target, BUFF_EFFECT_TYPE::BET_STRUCK_DAMAGE);
          if ( Entity::getType(launcher) == EntityType::ET_PLAYER && Entity::getType(target) == EntityType::ET_MONSTER )
          {
            v25 = launcher
                ? (Player *)__dynamic_cast(
                              launcher,
                              (const struct __class_type_info *)&`typeinfo for'Unit,
                              (const struct __class_type_info *)&`typeinfo for'Player,
                              0)
                : 0LL;
            pPlayer_1 = v25;
            v26 = target
                ? (Monster *)__dynamic_cast(
                               target,
                               (const struct __class_type_info *)&`typeinfo for'Unit,
                               (const struct __class_type_info *)&`typeinfo for'Monster,
                               0)
                : 0LL;
            monster = v26;
            if ( pPlayer_1 )
            {
              if ( monster )
              {
                if ( this->m_cfg->attack_type == 7 && Monster::CanTunShi(monster) && !Unit::isAlive(monster) )
                {
                  Mid = Monster::getMid(monster);
                  CKunExt = Player::GetCKunExt(pPlayer_1);
                  if ( CKunExt::AddDanTian(CKunExt, Mid) )
                    launcherResult->TunShi = 1;
                  Monster::SetTunShi(monster);
                }
                if ( this->m_cfg->attack_type == 8 && Monster::IsSunAndMoonMonster(monster) )
                {
                  if ( Monster::HaveItem(monster) )
                  {
                    Monster::getItem(&item, monster);
                    TianLing = Player::GetTianLing(pPlayer_1);
                    if ( CTianLing::GetMonsterItem(TianLing, item) )
                      Monster::SetGetItem(monster);
                  }
                  else
                  {
                    Player::TiShiInfo(pPlayer_1, 31, 0);
                  }
                }
              }
            }
          }
          suckModify = (float)Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_VPE) / 1000.0;
          if ( suckModify > 0.0 && realDamage > 0 )
          {
            suckVal = (int)(float)((float)realDamage * suckModify);
            v32 = 1;
            if ( suckVal > 0 )
              v32 = suckVal;
            suckVal = v32;
            launcherResult->hpChange = v32;
          }
        }
      }
      break;
  }
  bAddBuff = 1;
  if ( !this->m_cfg->beneficial )
  {
    if ( !Unit::isAlive(target) )
    {
      bAddBuff = 0;
    }
    else if ( (targetResult->attackState & 2) != 0 )
    {
      bAddBuff = 0;
    }
    else if ( (targetResult->attackState & 8) != 0 )
    {
      bAddBuff = 0;
    }
    else if ( Entity::getType(target) == EntityType::ET_CARRIER )
    {
      bAddBuff = 0;
    }
    else if ( Entity::getType(target) == EntityType::ET_MONSTER )
    {
      if ( target )
        v33 = (Monster *)__dynamic_cast(
                           target,
                           (const struct __class_type_info *)&`typeinfo for'Unit,
                           (const struct __class_type_info *)&`typeinfo for'Monster,
                           0);
      else
        v33 = 0;
      pMonster_2 = v33;
      if ( v33 )
      {
        if ( Monster::getBossSign(pMonster_2) == 4 || Monster::GetPureDamage(pMonster_2) > 0 )
        {
          if ( this->m_cfg->buff > 0 )
            targetResult->attackState |= 0x20u;
          bAddBuff = 0;
        }
      }
    }
    else if ( Entity::getType(target) == EntityType::ET_TRAILER )
    {
      bAddBuff = 0;
    }
  }
  if ( bAddBuff )
  {
    src_ply = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_PLY);
    src_pzn = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_FZN);
    des_ply = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_PLY_RDC);
    des_pzn = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_FZN_RDC);
    if ( src_ply - des_ply > 0 )
    {
      if ( this->m_cfg->attack_type )
      {
        v35 = Answer::Singleton<Answer::Random>::instance();
        v36 = Answer::Random::generate(v35, 1, 1000);
        if ( v36 <= src_ply - des_ply )
        {
          v37 = Answer::Singleton<CfgData>::instance();
          cfgBuff = CfgData::getBuff(v37, 11);
          if ( cfgBuff )
          {
            v74.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
            v74.type = v38;
            v39 = (Buff *)operator new(0x60u);
            Buff::Buff(v39, target, cfgBuff, &v74, 4, 1);
            buff = v39;
            if ( v39 )
            {
              Unit::addBuff(target, buff);
              if ( Entity::getType(launcher) == EntityType::ET_PLAYER )
              {
                v40 = targetResult->attackState;
                BYTE1(v40) |= 8u;
                targetResult->attackState = v40;
              }
            }
          }
        }
      }
    }
    if ( src_pzn - des_pzn > 0 )
    {
      if ( this->m_cfg->attack_type )
      {
        v41 = Answer::Singleton<Answer::Random>::instance();
        v42 = Answer::Random::generate(v41, 1, 1000);
        if ( v42 <= src_pzn - des_pzn )
        {
          v43 = Answer::Singleton<CfgData>::instance();
          cfgBuff_0 = CfgData::getBuff(v43, 12);
          if ( cfgBuff_0 )
          {
            v75.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
            v75.type = v44;
            v45 = (Buff *)operator new(0x60u);
            Buff::Buff(v45, target, cfgBuff_0, &v75, 4, 1);
            buff_0 = v45;
            if ( v45 )
            {
              Unit::addBuff(target, buff_0);
              v46 = targetResult->attackState;
              BYTE1(v46) |= 4u;
              targetResult->attackState = v46;
            }
          }
        }
      }
    }
    if ( Entity::getType(target) == EntityType::ET_MONSTER )
    {
      XuanYun = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_XUAN_YUN);
      des_XuanYun = Unit::GetAttrValue(target, CObjAttrs::Index_T::ATTR_XUAN_YUN_DEF);
      if ( XuanYun - des_XuanYun > 0 )
      {
        v47 = Answer::Singleton<Answer::Random>::instance();
        v48 = Answer::Random::generate(v47, 1, 1000);
        if ( v48 <= XuanYun - des_XuanYun )
        {
          v50 = Answer::Singleton<CfgData>::instance();
          cfgBuff_1 = CfgData::getBuff(v50, 11);
          if ( cfgBuff_1 )
          {
            v76.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
            v76.type = v51;
            v52 = (Buff *)operator new(0x60u);
            Buff::Buff(v52, target, cfgBuff_1, &v76, 4, 1);
            buff_1 = v52;
            if ( v52 )
              Unit::addBuff(target, buff_1);
          }
        }
      }
    }
    if ( this->m_cfg->buff )
    {
      v53 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v53, 1, 100) <= this->m_cfg->buff_rate )
      {
        v55 = this->m_cfg->buff;
        v56 = Answer::Singleton<CfgData>::instance();
        cfgBuff_2 = CfgData::getBuff(v56, v55);
        if ( cfgBuff_2 )
        {
          if ( !cfgBuff_2->beneficial && Unit::HasBuffState(target, CObjState::Index_T::OBS_WUDI) )
          {
            targetResult->attackState |= 8u;
            bAddBuff = 0;
          }
          else if ( cfgBuff_2->control && Unit::HasBuffState(target, CObjState::Index_T::OBS_FREEDOM) )
          {
            targetResult->attackState |= 0x20u;
            bAddBuff = 0;
          }
          if ( bAddBuff )
          {
            v77.id = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 12))(launcher);
            v77.type = v59;
            v60 = (SkillBuff *)operator new(0x80u);
            SkillBuff::SkillBuff(v60, target, cfgBuff_2, &v77);
            buff_2 = v60;
            if ( v60 )
            {
              atkMin_0 = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MIN);
              atkMax_0 = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_MAX);
              dmgAdd = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_DMG_ADD_PEC);
              skillModify_0 = cfgBuff_2->modify;
              SkillBuff::init(
                buff_2,
                this->m_cfg->id,
                atkMin_0,
                atkMax_0,
                0,
                dmgAdd,
                skillModify_0,
                this->m_cfg->buff_time);
              if ( !Unit::addBuff(target, buff_2) )
              {
                targetResult->buffId = this->m_cfg->buff;
                targetResult->buffDuration = Buff::remainTick(buff_2);
              }
            }
          }
        }
      }
    }
  }
  if ( !this->m_cfg->beneficial
    && (targetResult->attackState & 2) == 0
    && Entity::getType(target) == EntityType::ET_PLAYER )
  {
    if ( target )
      v61 = (Player *)__dynamic_cast(
                        target,
                        (const struct __class_type_info *)&`typeinfo for'Unit,
                        (const struct __class_type_info *)&`typeinfo for'Player,
                        0);
    else
      v61 = 0;
    pPlayer_2 = v61;
    if ( v61 )
    {
      groupid = this->m_cfg->groupid;
      CharSkill = Player::GetCharSkill(pPlayer_2);
      CExtCharSkill::CheckSkillTrigBuff(CharSkill, groupid, launcher, 3);
    }
  }
}


#####################################
void __cdecl Skill::broadcastAction(
        Skill *const this,
        Unit *const launcher,
        const Position *const targetPos,
        const UnitHandle *const targetHandle)
{
  GameService *v4; // rax
  int64_t v5; // rdx
  int8_t Type; // dl
  int32_t AttrValue; // edx
  uint32_t WOffset; // edx
  Map *pMap; // [rsp+20h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  pMap = StaticObj::getMap(launcher);
  if ( pMap )
  {
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2737u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nSkillFlag);
      Answer::NetPacket::writeInt16(packet, this->m_cfg->id);
      v5 = (*((__int64 (__fastcall **)(Unit *const))launcher->_vptr_Entity + 2))(launcher);
      Answer::NetPacket::writeInt64(packet, v5);
      Type = Entity::getType(launcher);
      Answer::NetPacket::writeInt8(packet, Type);
      AttrValue = Unit::GetAttrValue(launcher, CObjAttrs::Index_T::ATTR_ATK_SPD);
      Answer::NetPacket::writeInt32(packet, AttrValue);
      Answer::NetPacket::writeInt16(packet, targetPos->x);
      Answer::NetPacket::writeInt16(packet, targetPos->y);
      Answer::NetPacket::writeInt64(packet, targetHandle->id);
      Answer::NetPacket::writeInt8(packet, targetHandle->type);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(pMap, packet, launcher);
    }
  }
}


#####################################
void __cdecl Skill::broadcastResult(
        Skill *const this,
        Unit *const launcherUnit,
        const SkillResult *const launcherResult,
        const Position *const targetPos,
        const SkillResult *const targetResult)
{
  GameService *v5; // rax
  int32_t v6; // edx
  uint32_t WOffset; // edx
  Map *pMap; // [rsp+30h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  pMap = StaticObj::getMap(launcherUnit);
  if ( pMap )
  {
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, Answer::PackType::PACK_DISPATCH, 0x2738u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nSkillFlag);
      Answer::NetPacket::writeInt16(packet, this->m_cfg->id);
      Answer::NetPacket::writeInt64(packet, launcherResult->unitId);
      Answer::NetPacket::writeInt8(packet, launcherResult->unitType);
      v6 = (*((__int64 (__fastcall **)(Unit *const))launcherUnit->_vptr_Entity + 29))(launcherUnit);
      Answer::NetPacket::writeInt32(packet, v6);
      Answer::NetPacket::writeInt32(packet, launcherResult->hpChange);
      Answer::NetPacket::writeInt32(packet, launcherResult->hpBack);
      Answer::NetPacket::writeInt16(packet, targetPos->x);
      Answer::NetPacket::writeInt16(packet, targetPos->y);
      Answer::NetPacket::writeInt8(packet, launcherResult->TunShi);
      Answer::NetPacket::writeInt16(packet, 1);
      Answer::NetPacket::writeInt64(packet, targetResult->unitId);
      Answer::NetPacket::writeInt8(packet, targetResult->unitType);
      Answer::NetPacket::writeInt32(packet, targetResult->hpChange);
      Answer::NetPacket::writeInt16(packet, targetResult->attackState);
      Answer::NetPacket::writeInt32(packet, targetResult->buffId);
      Answer::NetPacket::writeInt32(packet, targetResult->buffDuration);
      Answer::NetPacket::writeInt32(packet, targetResult->CurseHp);
      Answer::NetPacket::writeInt32(packet, targetResult->QieGe);
      Answer::NetPacket::writeInt32(packet, targetResult->Bg);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(pMap, packet, launcherUnit);
    }
  }
}


#####################################
void __cdecl Skill::broadcastResult(
        Skill *const this,
        Unit *const launcherUnit,
        const SkillResult *const launcherResult,
        const Position *const targetPos,
        const SkillResultVector *const targetsResult)
{
  GameService *v5; // rax
  int32_t AttrValue; // eax
  const SkillResult *v7; // rax
  const SkillResult *v8; // rax
  const SkillResult *v9; // rax
  const SkillResult *v10; // rax
  const SkillResult *v11; // rax
  const SkillResult *v12; // rax
  const SkillResult *v13; // rax
  const SkillResult *v14; // rax
  const SkillResult *v15; // rax
  uint32_t WOffset; // eax
  __gnu_cxx::__normal_iterator<const SkillResult*,std::vector<SkillResult> > it; // [rsp+30h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+40h] [rbp-30h] BYREF
  Map *pMap; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]
  uint32_t oldOffset; // [rsp+64h] [rbp-Ch]
  int16_t nCount; // [rsp+6Ah] [rbp-6h]
  uint32_t newOffset; // [rsp+6Ch] [rbp-4h]

  pMap = StaticObj::getMap(launcherUnit);
  if ( pMap )
  {
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, Answer::PackType::PACK_DISPATCH, 0x2738u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nSkillFlag);
      Answer::NetPacket::writeInt16(packet, this->m_cfg->id);
      Answer::NetPacket::writeInt64(packet, launcherResult->unitId);
      Answer::NetPacket::writeInt8(packet, launcherResult->unitType);
      AttrValue = Unit::GetAttrValue(launcherUnit, CObjAttrs::Index_T::ATTR_ATK_SPD);
      Answer::NetPacket::writeInt32(packet, AttrValue);
      Answer::NetPacket::writeInt32(packet, launcherResult->hpChange);
      Answer::NetPacket::writeInt32(packet, launcherResult->hpBack);
      Answer::NetPacket::writeInt16(packet, targetPos->x);
      Answer::NetPacket::writeInt16(packet, targetPos->y);
      Answer::NetPacket::writeInt8(packet, launcherResult->TunShi);
      oldOffset = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt16(packet, 0);
      for ( it._M_current = std::vector<SkillResult>::begin(targetsResult)._M_current;
            ;
            __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<SkillResult>::end(targetsResult)._M_current;
        if ( !__gnu_cxx::operator!=<SkillResult const*,std::vector<SkillResult>>(&it, &__rhs) )
          break;
        v7 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt64(packet, v7->unitId);
        v8 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v8->unitType);
        v9 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v9->hpChange);
        v10 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt16(packet, v10->attackState);
        v11 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v11->buffId);
        v12 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v12->buffDuration);
        v13 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v13->CurseHp);
        v14 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v14->QieGe);
        v15 = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v15->Bg);
        ++nCount;
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt16(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(pMap, packet, launcherUnit);
    }
  }
}


