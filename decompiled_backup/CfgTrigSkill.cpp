// Decompiled methods for class: CfgTrigSkill
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgTrigSkill::isRespond(const CfgTrigSkill *const this, int32_t nGroupId)
{
  std::string *v2; // rax
  const char *v3; // rax
  bool v4; // bl
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-60h] BYREF
  StringVector vStr; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v9; // [rsp+4Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  int32_t id; // [rsp+5Ch] [rbp-14h]

  std::allocator<char>::allocator(&v9);
  std::string::string(&delims, ":", &v9);
  Answer::StringUtility::split(&vStr, &this->trigParam, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v9);
  for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
      break;
    v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&iter);
    v3 = (const char *)std::string::c_str(v2);
    id = atoi(v3);
    if ( id <= 0 || id == nGroupId )
    {
      v4 = 1;
      goto LABEL_8;
    }
  }
  v4 = 0;
LABEL_8:
  std::vector<std::string>::~vector(&vStr);
  return v4;
}


