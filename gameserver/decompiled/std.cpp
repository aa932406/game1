// Decompiled methods for class: std
// Source: gameserver.cc
// Total methods: 3

#####################################
__int64 __cdecl std::__lg(__int64 __n)
{
  unsigned __int64 v1; // rax

  _BitScanReverse64(&v1, __n);
  return 63LL - (int)(v1 ^ 0x3F);
}


#####################################
float __cdecl std::pow(float __x, float __y)
{
  return powf(__x, __y);
}


#####################################
size_t __cdecl std::__deque_buf_size(size_t __size)
{
  if ( __size > 0x1FF )
    return 1;
  else
    return 0x200 / __size;
}


