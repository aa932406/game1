// Decompiled methods for class: YanHua
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl YanHua::~YanHua(YanHua *const this)
{
  YanHua::~YanHua(this);
  operator delete(this);
}


#####################################
int32_t __cdecl YanHua::effect(YanHua *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  GameService *v4; // rax
  int32_t v5; // ebx
  int32_t nId; // ebx
  CfgData *v7; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  Answer::Random *v11; // rax
  int8_t job; // bl
  int32_t v14; // ebx
  int32_t v15; // ebx
  Answer::Random *v17; // rax
  int32_t v18; // ebx
  CfgItemGiftRandom *v19; // rax
  CfgItemGiftRandom *v20; // rax
  CExtCharBag *Bag; // rax
  int32_t YanHuaValue; // ebx
  COpenBeta *v23; // rax
  COpenBeta *v24; // rax
  MemChrBag item; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGiftRandom*,std::vector<CfgItemGiftRandom> > it; // [rsp+40h] [rbp-80h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-70h] BYREF
  CfgItemGiftRandomVector gift; // [rsp+70h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGiftRandom*,std::vector<CfgItemGiftRandom> > __rhs; // [rsp+90h] [rbp-30h] BYREF
  CfgItemGiftRandomVector *pCfg; // [rsp+98h] [rbp-28h]
  int32_t bagslot; // [rsp+A4h] [rbp-1Ch]
  int32_t roll; // [rsp+A8h] [rbp-18h]
  bool find; // [rsp+AFh] [rbp-11h]

  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( StaticObj::getMapId(launcher) != 50001 )
    return 10002;
  std::vector<CfgItemGiftRandom>::vector(&gift);
  nId = this->nId;
  v7 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::getItemGiftRandom(v7, nId);
  if ( pCfg )
  {
    std::vector<CfgItemGiftRandom>::operator=(&gift, pCfg);
    if ( std::vector<CfgItemGiftRandom>::empty(&gift) )
    {
      v5 = 10002;
    }
    else
    {
      bagslot = Player::getFirstFreeSlot(launcher);
      if ( bagslot >= 0 )
      {
        std::vector<MemChrBag>::vector(&items);
        v11 = Answer::Singleton<Answer::Random>::instance();
        roll = Answer::Random::generate(v11, 1, 1000);
        find = 0;
        for ( it._M_current = std::vector<CfgItemGiftRandom>::begin(&gift)._M_current;
              ;
              __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<CfgItemGiftRandom>::end(&gift)._M_current;
          if ( !__gnu_cxx::operator!=<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>(&it, &__rhs) )
            break;
          if ( __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->job )
          {
            job = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->job;
            if ( job != Player::getJob(launcher) )
              continue;
          }
          v14 = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher);
          if ( v14 >= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->MinLevel )
          {
            v15 = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher);
            if ( v15 <= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->MaxLevel )
            {
              if ( __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->static_probability <= 0 )
              {
                v19 = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it);
                if ( v19->sum_probability < roll )
                {
                  v20 = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it);
                  roll -= v20->sum_probability;
                }
                else if ( !find )
                {
                  memset(&item, 0, sizeof(item));
                  item.itemId = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->item;
                  item.itemClass = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->type;
                  item.itemCount = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->count;
                  item.bind = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->bind;
                  std::vector<MemChrBag>::push_back(&items, &item);
                  find = 1;
                }
              }
              else
              {
                v17 = Answer::Singleton<Answer::Random>::instance();
                v18 = Answer::Random::generate(v17, 1, 1000);
                if ( v18 <= __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->static_probability )
                {
                  memset(&item, 0, sizeof(item));
                  item.itemId = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->item;
                  item.itemClass = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->type;
                  item.itemCount = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->count;
                  item.bind = __gnu_cxx::__normal_iterator<CfgItemGiftRandom *,std::vector<CfgItemGiftRandom>>::operator->(&it)->bind;
                  std::vector<MemChrBag>::push_back(&items, &item);
                }
              }
            }
          }
        }
        if ( std::vector<MemChrBag>::size(&items) )
        {
          Bag = Player::GetBag(launcher);
          if ( CExtCharBag::AddItemsAndMingGe(Bag, &items, ITEM_CHANGE_REASON::ICR_SUIJILIBAO) )
          {
            YanHuaValue = this->YanHuaValue;
            v23 = Answer::Singleton<COpenBeta>::instance();
            COpenBeta::AddYanHuaPoint(v23, YanHuaValue);
            Player::BroadcastYanHua(launcher, this->YanHuaType);
            v24 = Answer::Singleton<COpenBeta>::instance();
            COpenBeta::SendActivityInfo(v24, launcher);
            v5 = 0;
          }
          else
          {
            v5 = 10016;
          }
        }
        else
        {
          v5 = 10002;
        }
        std::vector<MemChrBag>::~vector(&items);
      }
      else
      {
        GateIndex = Player::getGateIndex(launcher);
        ConnId = Player::getConnId(launcher);
        v10 = Answer::Singleton<GameService>::instance();
        v5 = GameService::replyfailure(v10, ConnId, GateIndex, 0x59u, 10054, 0);
      }
    }
  }
  else
  {
    v5 = 0;
  }
  std::vector<CfgItemGiftRandom>::~vector(&gift);
  return v5;
}


#####################################
bool __cdecl YanHua::parseEffect(YanHua *const this, int32_t id, const std::string *const strEffect)
{
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  bool v7; // bl
  StringVector params; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v12);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v12);
  this->nId = id;
  if ( std::vector<std::string>::size(&params) == 2 )
  {
    v3 = std::vector<std::string>::operator[](&params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->YanHuaValue = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->YanHuaType = atoi(v6);
    v7 = 1;
  }
  else
  {
    v7 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v7;
}


