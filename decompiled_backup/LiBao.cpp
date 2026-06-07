// Decompiled methods for class: LiBao
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl LiBao::~LiBao(LiBao *const this)
{
  LiBao::~LiBao(this);
  operator delete(this);
}


#####################################
int32_t __cdecl LiBao::effect(LiBao *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  int32_t v4; // ebx
  int32_t time; // ebx
  CfgData *v6; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  int32_t job; // ebx
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > it; // [rsp+40h] [rbp-50h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<CfgItemGift*,std::vector<CfgItemGift> > __rhs; // [rsp+70h] [rbp-20h] BYREF

  if ( std::vector<CfgItemGift>::empty(&this->m_gifts) )
    return 10002;
  std::vector<MemChrBag>::vector(&items);
  for ( it._M_current = std::vector<CfgItemGift>::begin(&this->m_gifts)._M_current;
        ;
        __gnu_cxx::__normal_iterator<CfgItemGift *,std::vector<CfgItemGift>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<CfgItemGift>::end(&this->m_gifts)._M_current;
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
      v6 = Answer::Singleton<CfgData>::instance();
      LimitTimeTable = CfgData::GetLimitTimeTable(v6);
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
    if ( !CExtCharBag::AddItemsAndMingGe(Bag, &items, ITEM_CHANGE_REASON::ICR_LIBAO) )
    {
      Player::TiShiInfo(launcher, 2048, 0);
      v4 = 10016;
    }
    else
    {
      v4 = 0;
    }
  }
  std::vector<MemChrBag>::~vector(&items);
  return v4;
}


#####################################
bool __cdecl LiBao::parseEffect(LiBao *const this, int32_t id, const std::string *const strEffect)
{
  CfgData *v3; // rax
  const std::vector<CfgItemGift> *pGift; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<CfgData>::instance();
  pGift = CfgData::getItemGift(v3, id);
  if ( !pGift )
    return 0;
  std::vector<CfgItemGift>::operator=(&this->m_gifts, pGift);
  return 1;
}


