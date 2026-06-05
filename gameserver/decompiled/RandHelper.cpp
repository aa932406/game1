// Decompiled methods for class: RandHelper
// Source: gameserver.cc
// Total methods: 1

#####################################
int32_t __cdecl RandHelper::CalRandTimes(int32_t nTotalTimes, int32_t nRate, int32_t nTotalRate)
{
  Answer::Random *v3; // rax
  int32_t times; // [rsp+14h] [rbp-1Ch]
  int32_t i; // [rsp+18h] [rbp-18h]

  times = 0;
  for ( i = 0; i < nTotalTimes; ++i )
  {
    v3 = Answer::Singleton<Answer::Random>::instance();
    if ( Answer::Random::generate(v3, 0, nTotalRate - 1) < nRate )
      ++times;
  }
  return times;
}


