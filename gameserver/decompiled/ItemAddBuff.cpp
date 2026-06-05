// Decompiled methods for class: ItemAddBuff
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ItemAddBuff::~ItemAddBuff(ItemAddBuff *const this)
{
  ItemAddBuff::~ItemAddBuff(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ItemAddBuff::effect(
        ItemAddBuff *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // edx
  ItemBuff *v6; // rbx
  std::_List_iterator<CfgBuff*> iter; // [rsp+30h] [rbp-70h] BYREF
  std::_List_iterator<CfgBuff*> __x; // [rsp+40h] [rbp-60h] BYREF
  UnitHandle v10; // [rsp+50h] [rbp-50h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-34h]
  CfgBuff *pCfgBuff; // [rsp+70h] [rbp-30h]
  ItemBuff *pBuff; // [rsp+78h] [rbp-28h]

  if ( std::list<CfgBuff *>::empty(&this->m_lBuffs) )
    return 10002;
  for ( i = 0; *count > i; ++i )
  {
    for ( iter._M_node = std::list<CfgBuff *>::begin(&this->m_lBuffs)._M_node;
          ;
          std::_List_iterator<CfgBuff *>::operator++(&iter) )
    {
      __x._M_node = std::list<CfgBuff *>::end(&this->m_lBuffs)._M_node;
      if ( !std::_List_iterator<CfgBuff *>::operator!=(&iter, &__x) )
        break;
      pCfgBuff = *std::_List_iterator<CfgBuff *>::operator*(&iter);
      if ( !pCfgBuff )
        return 10002;
      v10.id = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 12))(launcher);
      v10.type = v5;
      v6 = (ItemBuff *)operator new(0x68u);
      ItemBuff::ItemBuff(v6, launcher, pCfgBuff, &v10);
      pBuff = v6;
      if ( !v6 )
        return 10002;
      ItemBuff::init(pBuff, this->m_nItemId, 0);
      if ( Unit::addBuff(launcher, pBuff) )
      {
        Player::TiShiInfo(launcher, 8, 0);
        return 10002;
      }
    }
  }
  return 0;
}


#####################################
bool __cdecl ItemAddBuff::parseEffect(ItemAddBuff *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  CfgBuff *pCfgBuff; // [rsp+28h] [rbp-68h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+30h] [rbp-60h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-50h] BYREF
  std::string delims; // [rsp+60h] [rbp-30h] BYREF
  char v14; // [rsp+6Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-20h] BYREF

  this->m_nItemId = id;
  std::allocator<char>::allocator(&v14);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&vStr, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v14);
  if ( std::vector<std::string>::empty(&vStr) )
  {
    v3 = 0;
  }
  else
  {
    for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
      v5 = (const char *)std::string::c_str(v4);
      v6 = atoi(v5);
      v7 = Answer::Singleton<CfgData>::instance();
      pCfgBuff = CfgData::getBuff(v7, v6);
      if ( !pCfgBuff )
      {
        v3 = 0;
        goto LABEL_9;
      }
      std::list<CfgBuff *>::push_back(&this->m_lBuffs, &pCfgBuff);
    }
    v3 = 1;
  }
LABEL_9:
  std::vector<std::string>::~vector(&vStr);
  return v3;
}


