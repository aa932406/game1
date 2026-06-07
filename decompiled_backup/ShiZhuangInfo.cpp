// Decompiled methods for class: ShiZhuangInfo
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl ShiZhuangInfo::CleanUp(ShiZhuangInfo *const this)
{
  this->m_nWear = 0;
  this->m_nLevel = 0;
  this->m_nExp = 0;
  std::map<int,int>::clear(&this->m_lActive);
}


#####################################
void __cdecl ShiZhuangInfo::ParesActiveString(ShiZhuangInfo *const this, const std::string *const strActive)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  int *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-A4h] BYREF
  StringVector ShiZhuangVt; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-80h] BYREF
  StringVector vt; // [rsp+50h] [rbp-70h] BYREF
  std::string delims; // [rsp+70h] [rbp-50h] BYREF
  char v13; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  std::string v15; // [rsp+90h] [rbp-30h] BYREF
  char v16; // [rsp+A7h] [rbp-19h] BYREF
  int32_t Now; // [rsp+A8h] [rbp-18h]
  int32_t nTime; // [rsp+ACh] [rbp-14h]

  Now = Answer::DayTime::now();
  std::map<int,int>::clear(&this->m_lActive);
  if ( (unsigned __int8)std::string::empty((std::string *)strActive) != 1 )
  {
    std::allocator<char>::allocator(&v13);
    std::string::string(&delims, "|", &v13);
    Answer::StringUtility::split(&vt, strActive, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v13);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(&v16);
      std::string::string(&v15, ":", &v16);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&ShiZhuangVt, v2, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(&v16);
      if ( std::vector<std::string>::size(&ShiZhuangVt) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&ShiZhuangVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        v5 = std::vector<std::string>::operator[](&ShiZhuangVt, 1u);
        v6 = (const char *)std::string::c_str(v5);
        nTime = atoi(v6);
        v7 = std::map<int,int>::operator[](&this->m_lActive, &nId);
        *v7 = nTime;
      }
      std::vector<std::string>::~vector(&ShiZhuangVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


#####################################
std::string __cdecl ShiZhuangInfo::GetActiveString(const ShiZhuangInfo *const this)
{
  const std::map<int,int> *v1; // rsi
  std::_Ios_Openmode v2; // eax
  const std::pair<const int,int> *v3; // rax
  const std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > iter; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF
  int32_t Now; // [rsp+19Ch] [rbp-14h]

  Now = Answer::DayTime::now();
  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( iter._M_node = std::map<int,int>::begin(v1)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,int>::end(v1)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl ShiZhuangInfo::AddTime(ShiZhuangInfo *const this, int32_t nId, int32_t nTime)
{
  int *v3; // rax
  int *v4; // rax
  int32_t nIda; // [rsp+4h] [rbp-1Ch] BYREF
  ShiZhuangInfo *thisa; // [rsp+8h] [rbp-18h]
  int32_t Now; // [rsp+1Ch] [rbp-4h]

  thisa = this;
  nIda = nId;
  if ( nTime )
  {
    Now = Answer::DayTime::now();
    if ( !ShiZhuangInfo::IsActive(thisa, nIda) )
    {
      v3 = std::map<int,int>::operator[](&thisa->m_lActive, &nIda);
      *v3 = Now + nTime;
    }
    else if ( *std::map<int,int>::operator[](&thisa->m_lActive, &nIda) > 0 )
    {
      v4 = std::map<int,int>::operator[](&thisa->m_lActive, &nIda);
      *v4 += nTime;
    }
  }
  else
  {
    *std::map<int,int>::operator[](&thisa->m_lActive, &nIda) = 0;
  }
}


#####################################
bool __cdecl ShiZhuangInfo::IsForever(ShiZhuangInfo *const this, int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  ShiZhuangInfo *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v8; // [rsp+40h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  __it._M_node = std::map<int,int>::find(&this->m_lActive, &nIda)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,int>>::_Rb_tree_const_iterator(&it, &__it);
  v8._M_node = std::map<int,int>::end(&thisa->m_lActive)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,int>>::_Rb_tree_const_iterator(&__x, &v8);
  return !std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator==(&it, &__x)
      && std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&it)->second == 0;
}


#####################################
bool __cdecl ShiZhuangInfo::IsActive(const ShiZhuangInfo *const this, int32_t nId)
{
  const std::pair<const int,int> *v3; // rax
  bool v4; // al
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  const ShiZhuangInfo *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Now; // [rsp+2Ch] [rbp-4h]

  thisa = this;
  nIda = nId;
  Now = Answer::DayTime::now();
  it._M_node = std::map<int,int>::find(&this->m_lActive, &nIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_lActive)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
    return 0;
  v4 = 1;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&it)->second )
  {
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&it);
    if ( v3->second <= Now )
      return 0;
  }
  return v4;
}


