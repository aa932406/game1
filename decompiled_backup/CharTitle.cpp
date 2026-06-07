// Decompiled methods for class: CharTitle
// Source: gameserver.cc
// Total methods: 9

#####################################
bool __cdecl CharTitle::CheckJob(const CharTitle *const this, Job_t nJob)
{
  return !this->cfgTitle->nJob || this->cfgTitle->nJob == nJob;
}


#####################################
bool __cdecl CharTitle::CheckSex(const CharTitle *const this, Sex_t nSex)
{
  return !this->cfgTitle->nSex || this->cfgTitle->nSex == nSex;
}


#####################################
bool __cdecl CharTitle::CheckPlatform(const CharTitle *const this, const std::string *const platform)
{
  return std::operator==<char>(&this->cfgTitle->sPlatform, "-1")
      || std::operator==<char>(&this->cfgTitle->sPlatform, platform);
}


#####################################
bool __cdecl CharTitle::IsInParams(const CharTitle *const this, int32_t nParam)
{
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > iter; // [rsp+10h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_current = std::vector<int>::begin(&this->cfgTitle->vParams)._M_current;
        ;
        __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<int>::end(&this->cfgTitle->vParams)._M_current;
    if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&iter, &__rhs) )
      break;
    if ( *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&iter) == nParam )
      return 1;
  }
  return 0;
}


#####################################
int32_t __cdecl CharTitle::GetCardTitleParams(const CharTitle *const this)
{
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > iter; // [rsp+10h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+20h] [rbp-10h] BYREF

  iter._M_current = std::vector<int>::begin(&this->cfgTitle->vParams)._M_current;
  __rhs._M_current = std::vector<int>::end(&this->cfgTitle->vParams)._M_current;
  if ( __gnu_cxx::operator!=<int const*,std::vector<int>>(&iter, &__rhs) )
    return *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&iter);
  else
    return 0;
}


#####################################
bool __cdecl CharTitle::IsGet(const CharTitle *const this)
{
  return this->nState == 1 || this->nState == 2;
}


#####################################
bool __cdecl CharTitle::Dress(CharTitle *const this)
{
  if ( this->nState != 1 )
    return 0;
  this->nState = 2;
  return 1;
}


#####################################
bool __cdecl CharTitle::UnDress(CharTitle *const this)
{
  if ( this->nState != 2 )
    return 0;
  this->nState = 1;
  return 1;
}


#####################################
void __cdecl CharTitle::Get(CharTitle *const this)
{
  if ( !this->nState )
    this->nState = 1;
}


