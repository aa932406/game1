// Decompiled methods for class: Position
// Source: gameserver.cc
// Total methods: 2

#####################################
int32_t __cdecl Position::tileDistance(const Position *const this, const Position *const pos)
{
  int __b; // [rsp+18h] [rbp-8h] BYREF
  int __a; // [rsp+1Ch] [rbp-4h] BYREF

  __b = abs32(this->y - pos->y);
  __a = abs32(this->x - pos->x);
  return *std::max<int>(&__a, &__b);
}


#####################################
double __cdecl Position::distance(const Position *const this, const Position *const pos)
{
  return sqrt((double)((pos->x - this->x) * (pos->x - this->x) + (pos->y - this->y) * (pos->y - this->y)));
}


