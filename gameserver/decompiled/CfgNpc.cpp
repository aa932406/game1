// Decompiled methods for class: CfgNpc
// Source: gameserver.cc
// Total methods: 3

#####################################
bool __cdecl CfgNpc::findMapId(const CfgNpc *const this, int32_t mapid)
{
  const int *M_current; // rbx
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > v3; // rax
  int32_t mapida; // [rsp+4h] [rbp-3Ch] BYREF
  const CfgNpc *thisa; // [rsp+8h] [rbp-38h]
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __lhs; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  mapida = mapid;
  __rhs._M_current = std::vector<int>::end(&this->mapids)._M_current;
  M_current = std::vector<int>::end(&this->mapids)._M_current;
  v3._M_current = std::vector<int>::begin(&this->mapids)._M_current;
  __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>,int>(
                       v3,
                       (__gnu_cxx::__normal_iterator<const int*,std::vector<int> >)M_current,
                       &mapida)._M_current;
  return __gnu_cxx::operator!=<int const*,std::vector<int>>(&__lhs, &__rhs);
}


#####################################
bool __cdecl CfgNpc::NearNpc(const CfgNpc *const this, int32_t mapid, int32_t TarX, int32_t TarY, int32_t diff)
{
  const int *M_current; // rbx
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > v6; // rax
  int32_t mapida; // [rsp+14h] [rbp-3Ch] BYREF
  const CfgNpc *thisa; // [rsp+18h] [rbp-38h]
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __lhs; // [rsp+30h] [rbp-20h] BYREF
  int __b; // [rsp+38h] [rbp-18h] BYREF
  int __a[5]; // [rsp+3Ch] [rbp-14h] BYREF

  thisa = this;
  mapida = mapid;
  __rhs._M_current = std::vector<int>::end(&this->mapids)._M_current;
  M_current = std::vector<int>::end(&this->mapids)._M_current;
  v6._M_current = std::vector<int>::begin(&this->mapids)._M_current;
  __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>,int>(
                       v6,
                       (__gnu_cxx::__normal_iterator<const int*,std::vector<int> >)M_current,
                       &mapida)._M_current;
  if ( __gnu_cxx::operator==<int const*,std::vector<int>>(&__lhs, &__rhs) )
    return 0;
  __b = abs32(thisa->y - TarY);
  __a[0] = abs32(thisa->x - TarX);
  return *std::max<int>(__a, &__b) <= diff;
}


#####################################
bool __cdecl CfgNpc::checkPlatform(const CfgNpc *const this, const std::string *const platform)
{
  const std::string *v3; // rax
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<const std::string*,std::vector<std::string> > __rhs; // [rsp+20h] [rbp-10h] BYREF

  if ( std::vector<std::string>::empty(&this->platforms) )
    return 1;
  for ( iter._M_current = std::vector<std::string>::begin(&this->platforms)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<std::string>::end(&this->platforms)._M_current;
    if ( !__gnu_cxx::operator!=<std::string const*,std::vector<std::string>>(&iter, &__rhs) )
      break;
    v3 = __gnu_cxx::__normal_iterator<std::string const*,std::vector<std::string>>::operator*(&iter);
    if ( std::operator==<char>(v3, platform) )
      return 1;
  }
  return 0;
}


