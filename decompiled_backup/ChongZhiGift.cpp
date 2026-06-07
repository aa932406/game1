// Decompiled methods for class: ChongZhiGift
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ChongZhiGift::~ChongZhiGift(ChongZhiGift *const this)
{
  ChongZhiGift::~ChongZhiGift(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ChongZhiGift::effect(
        ChongZhiGift *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // ebx
  int32_t nId; // ebx
  CfgData *v6; // rax
  int32_t time; // ebx
  CfgData *v8; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  int32_t job; // ebx
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v14; // rax
  MemChrBag item; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > it; // [rsp+40h] [rbp-50h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > __rhs; // [rsp+70h] [rbp-20h] BYREF
  CfgItemGiftVector *pGift; // [rsp+78h] [rbp-18h]

  if ( *count != 1 )
    return 2;
  nId = this->nId;
  v6 = Answer::Singleton<CfgData>::instance();
  pGift = CfgData::getItemGift(v6, nId);
  if ( !pGift )
    return 2;
  std::vector<MemChrBag>::vector(&items);
  for ( it._M_current = std::vector<CfgItemGift>::begin(pGift)._M_current;
        ;
        __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<CfgItemGift>::end(pGift)._M_current;
    if ( !__gnu_cxx::operator!=<CfgItemGift *,std::vector<CfgItemGift>>(&it, &__rhs) )
      break;
    memset(&item, 0, sizeof(item));
    item.itemId = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->item;
    item.itemClass = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->type;
    item.itemCount = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->count;
    item.bind = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->bind;
    if ( __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->time > 0 )
    {
      time = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->time;
      v8 = Answer::Singleton<CfgData>::instance();
      LimitTimeTable = CfgData::GetLimitTimeTable(v8);
      item.endTime = CfgLimitTimeTable::GetLimitTime(LimitTimeTable, time);
    }
    if ( __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->job )
    {
      job = __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator->(&it)->job;
      if ( job != Player::getJob(launcher) )
        continue;
    }
    std::vector<MemChrBag>::push_back(&items, &item);
  }
  if ( std::vector<MemChrBag>::empty(&items) )
  {
    v4 = 10002;
  }
  else
  {
    Bag = Player::GetBag(launcher);
    FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
    if ( FreeSlotCount >= (int)std::vector<MemChrBag>::size(&items) )
    {
      if ( Player::GetTodayPayGold(launcher) >= this->Value )
      {
        v14 = Player::GetBag(launcher);
        if ( !CExtCharBag::AddItem(v14, &items, ITEM_CHANGE_REASON::ICR_LIBAO) )
          v4 = 10016;
        else
          v4 = 0;
      }
      else
      {
        Player::TiShiInfo(launcher, 24, 0);
        v4 = 10016;
      }
    }
    else
    {
      Player::TiShiInfo(launcher, 2048, 0);
      v4 = 10016;
    }
  }
  std::vector<MemChrBag>::~vector(&items);
  return v4;
}


#####################################
bool __cdecl ChongZhiGift::parseEffect(ChongZhiGift *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  this->nId = id;
  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Value = atoi(v3);
  return this->Value > 0;
}


