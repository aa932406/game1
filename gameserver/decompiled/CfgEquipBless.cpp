// Decompiled methods for class: CfgEquipBless
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgEquipBless::CleanUp(CfgEquipBless *const this)
{
  this->nBless = 0;
  this->nAddRate = 0;
  this->nRemineRate = 0;
  this->nBroad = 0;
}


#####################################
int8_t __cdecl CfgEquipBless::RandomEffect(const CfgEquipBless *const this)
{
  Answer::Random *v1; // rax
  int nRand; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v1, 1, 10000);
  if ( this->nAddRate >= nRand )
    return 1;
  if ( this->nRemineRate < nRand - this->nAddRate )
    return 0;
  return 2;
}


