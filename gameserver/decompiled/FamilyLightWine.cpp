// Decompiled methods for class: FamilyLightWine
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl FamilyLightWine::~FamilyLightWine(FamilyLightWine *const this)
{
  FamilyLightWine::~FamilyLightWine(this);
  operator delete(this);
}


#####################################
int32_t __cdecl FamilyLightWine::effect(
        FamilyLightWine *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // edx
  ItemBuff *v5; // rbx
  Map *Map; // rax
  CActivityMap *v8; // rax
  CActivity *Activity; // rax
  CFamilyLight *v10; // rax
  UnitHandle v12; // [rsp+30h] [rbp-50h] BYREF
  CActivityMap *pMap; // [rsp+40h] [rbp-40h]
  int32_t i; // [rsp+4Ch] [rbp-34h]
  ItemBuff *pBuff; // [rsp+50h] [rbp-30h]
  CFamilyLight *pAct; // [rsp+58h] [rbp-28h]

  for ( i = 0; *count > i; ++i )
  {
    v12.id = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 12))(launcher);
    v12.type = v4;
    v5 = (ItemBuff *)operator new(0x68u);
    ItemBuff::ItemBuff(v5, launcher, this->m_cfgBuff, &v12);
    pBuff = v5;
    if ( !v5 )
      return 10002;
    ItemBuff::init(pBuff, this->m_itemid, 0);
    Unit::addBuff(launcher, pBuff);
  }
  Map = StaticObj::getMap(launcher);
  if ( Map )
    v8 = (CActivityMap *)__dynamic_cast(
                           Map,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                           0);
  else
    v8 = 0;
  pMap = v8;
  if ( v8 )
  {
    Activity = CActivityMap::GetActivity(pMap);
    if ( Activity )
      v10 = (CFamilyLight *)__dynamic_cast(
                              Activity,
                              (const struct __class_type_info *)&`typeinfo for'CActivity,
                              (const struct __class_type_info *)&`typeinfo for'CFamilyLight,
                              0);
    else
      v10 = 0;
    pAct = v10;
    if ( v10 )
    {
      if ( CActivity::IsRuning(pAct) )
        CFamilyLight::DrinkWine(pAct, launcher, *count);
    }
  }
  return 0;
}


#####################################
bool __cdecl FamilyLightWine::parseEffect(FamilyLightWine *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax

  this->m_itemid = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  v4 = atoi(v3);
  v5 = Answer::Singleton<CfgData>::instance();
  this->m_cfgBuff = CfgData::getBuff(v5, v4);
  return this->m_cfgBuff != 0;
}


