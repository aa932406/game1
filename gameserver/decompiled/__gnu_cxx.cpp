// Decompiled methods for class: __gnu_cxx
// Source: gameserver.cc
// Total methods: 1

#####################################
unsigned __int64 __cdecl __gnu_cxx::__stl_next_prime(unsigned __int64 __n)
{
  unsigned __int64 __na; // [rsp+8h] [rbp-28h] BYREF
  const unsigned __int64 *__first; // [rsp+18h] [rbp-18h]
  const unsigned __int64 *__last; // [rsp+20h] [rbp-10h]
  const unsigned __int64 *pos; // [rsp+28h] [rbp-8h]

  __na = __n;
  __first = __gnu_cxx::__stl_prime_list;
  __last = (const unsigned __int64 *)"bool CDBCFile::OpenFromTXT(const char*)";
  pos = std::lower_bound<unsigned long const*,unsigned long>(
          __gnu_cxx::__stl_prime_list,
          (const unsigned __int64 *)"bool CDBCFile::OpenFromTXT(const char*)",
          &__na);
  if ( pos == __last )
    return *(__last - 1);
  else
    return *pos;
}


