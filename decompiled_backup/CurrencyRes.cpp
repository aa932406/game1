// Decompiled methods for class: CurrencyRes
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CurrencyRes::~CurrencyRes(CurrencyRes *const this)
{
  CurrencyRes::~CurrencyRes(this);
  operator delete(this);
}


#####################################
int32_t __cdecl CurrencyRes::effect(
        CurrencyRes *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int64_t Addon; // [rsp+28h] [rbp-18h]

  Addon = this->m_CurrecyCount;
  if ( *count > 0 )
    Addon *= *count;
  if ( !Player::AddCurrency(
          launcher,
          (const CURRENCY_TYPE)this->m_CurrecyType,
          Addon,
          CURRENCY_CHANGE_REASON::MCR_MONEY_GAIN_ITEM,
          this->m_id) )
    return 2;
  else
    return 0;
}


#####################################
bool __cdecl CurrencyRes::parseEffect(CurrencyRes *const this, int32_t id, const std::string *const strEffect)
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
  if ( std::vector<std::string>::size(&params) == 2 )
  {
    v3 = std::vector<std::string>::operator[](&params, 0);
    v4 = (const char *)std::string::c_str(v3);
    this->m_CurrecyType = atoi(v4);
    v5 = std::vector<std::string>::operator[](&params, 1u);
    v6 = (const char *)std::string::c_str(v5);
    this->m_CurrecyCount = atoi(v6);
    this->m_id = id;
    v7 = this->m_CurrecyCount > 0;
  }
  else
  {
    v7 = 0;
  }
  std::vector<std::string>::~vector(&params);
  return v7;
}


