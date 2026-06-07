// Decompiled methods for class: SuperExchange
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl SuperExchange::~SuperExchange(SuperExchange *const this)
{
  SuperExchange::~SuperExchange(this);
  operator delete(this);
}


#####################################
int32_t __cdecl SuperExchange::effect(
        SuperExchange *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t type; // eax
  int64_t v6; // rbx
  int64_t m_id; // rbx
  int64_t v8; // rdx
  int64_t v9; // rdx
  __gnu_cxx::__normal_iterator<const SuperExchangeToItem*,std::vector<SuperExchangeToItem> > it; // [rsp+20h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<SuperExchangeToItem*,std::vector<SuperExchangeToItem> > __i; // [rsp+30h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<SuperExchangeToItem*,std::vector<SuperExchangeToItem> > __rhs; // [rsp+40h] [rbp-20h] BYREF

  if ( std::vector<SuperExchangeToItem>::empty(&this->m_exchangeToItems) )
    return 10002;
  if ( !*count )
    *count = 1;
  __i._M_current = std::vector<SuperExchangeToItem>::begin(&this->m_exchangeToItems)._M_current;
  __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::__normal_iterator<SuperExchangeToItem*>(
    &it,
    &__i);
  while ( 1 )
  {
    __rhs._M_current = std::vector<SuperExchangeToItem>::end(&this->m_exchangeToItems)._M_current;
    if ( !__gnu_cxx::operator!=<SuperExchangeToItem const*,SuperExchangeToItem*,std::vector<SuperExchangeToItem>>(
            &it,
            &__rhs) )
      break;
    type = __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::operator->(&it)->type;
    if ( type == 2 )
    {
      m_id = this->m_id;
      v8 = __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::operator->(&it)->value
         * *count;
      Player::AddCurrency(launcher, CURRENCY_TYPE::CURRENCY_MONEY, v8, CURRENCY_CHANGE_REASON::MCR_SUPER_EXCHANGE, m_id);
    }
    else if ( type > 2 )
    {
      if ( type == 7 )
      {
        v9 = __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::operator->(&it)->value
           * *count;
        Player::AddCurrency(launcher, CURRENCY_TYPE::CURRENCY_CASH, v9, CURRENCY_CHANGE_REASON::GCR_SUPER_EXCHANGE, 0);
      }
    }
    else if ( type == 1 )
    {
      v6 = __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::operator->(&it)->value
         * *count;
      Player::addExp(launcher, v6, 0, 1);
    }
    __gnu_cxx::__normal_iterator<SuperExchangeToItem const*,std::vector<SuperExchangeToItem>>::operator++(&it);
  }
  return 0;
}


#####################################
bool __cdecl SuperExchange::parseEffect(SuperExchange *const this, int32_t id, const std::string *const strEffect)
{
  const std::string *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  bool v8; // bl
  SuperExchangeToItem toItem; // [rsp+20h] [rbp-B0h] BYREF
  StringVector subParams; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-80h] BYREF
  StringVector params; // [rsp+60h] [rbp-70h] BYREF
  std::string delims; // [rsp+80h] [rbp-50h] BYREF
  char v16; // [rsp+8Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __i; // [rsp+90h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+A0h] [rbp-30h] BYREF
  std::string v19; // [rsp+B0h] [rbp-20h] BYREF
  _BYTE v20[17]; // [rsp+BFh] [rbp-11h] BYREF

  this->m_id = id;
  std::allocator<char>::allocator(&v16);
  std::string::string(&delims, "|");
  Answer::StringUtility::split(&params, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v16);
  if ( std::vector<std::string>::size(&params) )
  {
    __i._M_current = std::vector<std::string>::begin(&params)._M_current;
    __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::__normal_iterator<std::string *>(
      &it,
      &__i);
    while ( 1 )
    {
      __rhs._M_current = std::vector<std::string>::end(&params)._M_current;
      if ( !__gnu_cxx::operator!=<std::string const*,std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(v20);
      std::string::string(&v19, ":");
      v3 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&subParams, v3, &v19, 0);
      std::string::~string(&v19);
      std::allocator<char>::~allocator(v20);
      if ( std::vector<std::string>::size(&subParams) == 2 )
      {
        toItem = 0;
        v4 = std::vector<std::string>::operator[](&subParams, 0);
        v5 = (const char *)std::string::c_str(v4);
        toItem.type = atoi(v5);
        v6 = std::vector<std::string>::operator[](&subParams, 1u);
        v7 = (const char *)std::string::c_str(v6);
        toItem.value = atoi(v7);
        std::vector<SuperExchangeToItem>::push_back(&this->m_exchangeToItems, &toItem);
      }
      std::vector<std::string>::~vector(&subParams);
      __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&it);
    }
    v8 = 1;
  }
  else
  {
    v8 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v8;
}


