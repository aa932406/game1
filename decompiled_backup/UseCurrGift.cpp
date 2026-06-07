// Decompiled methods for class: UseCurrGift
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl UseCurrGift::~UseCurrGift(UseCurrGift *const this)
{
  UseCurrGift::~UseCurrGift(this);
  operator delete(this);
}


#####################################
int32_t __cdecl UseCurrGift::effect(
        UseCurrGift *const this,
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
  int64_t CurrValue; // rbx
  CExtCurrency *Currency; // rax
  CExtCharBag *v16; // rax
  MemChrBag item; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > it; // [rsp+40h] [rbp-50h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > __rhs; // [rsp+70h] [rbp-20h] BYREF
  CfgItemGiftVector *pGift; // [rsp+78h] [rbp-18h]

  if ( *count == 1 )
  {
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
        if ( this->CurrType )
        {
          if ( !Player::DecCurrency(
                  launcher,
                  (const CURRENCY_TYPE)this->CurrType,
                  this->CurrValue,
                  CURRENCY_CHANGE_REASON::GCR_OPEN_GIFT,
                  0) )
          {
            v4 = 2;
            goto LABEL_28;
          }
        }
        else
        {
          CurrValue = this->CurrValue;
          Currency = Player::GetCurrency(launcher);
          if ( !CExtCurrency::DecMoneyAndNoBind(Currency, CurrValue, CURRENCY_CHANGE_REASON::GCR_OPEN_GIFT, 0) )
          {
            v4 = 2;
            goto LABEL_28;
          }
        }
        v16 = Player::GetBag(launcher);
        if ( !CExtCharBag::AddItemsAndMingGe(v16, &items, ITEM_CHANGE_REASON::ICR_LIBAO) )
          v4 = 10016;
        else
          v4 = 0;
        goto LABEL_28;
      }
      Player::TiShiInfo(launcher, 2048, 0);
      v4 = 10016;
    }
LABEL_28:
    std::vector<MemChrBag>::~vector(&items);
    return v4;
  }
  return 2;
}


#####################################
bool __cdecl UseCurrGift::parseEffect(UseCurrGift *const this, int32_t id, const std::string *const strEffect)
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
    this->CurrType = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->CurrValue = atoi(v6);
    v7 = 1;
  }
  else
  {
    v7 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v7;
}


