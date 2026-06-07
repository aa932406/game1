// Decompiled methods for class: MonthlyChouJiangTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl MonthlyChouJiangTable::AddMonthlyChouJiangCfg(MonthlyChouJiangTable *const this, MonthlyChouJiangCfg stu)
{
  MonthlyChouJiangCfg *v2; // rax
  MonthlyChouJiangCfg stua; // [rsp+8h] [rbp-18h] BYREF
  MonthlyChouJiangTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  stua = stu;
  v2 = std::map<int,MonthlyChouJiangCfg>::operator[](&this->m_MonthlyChouJiangCfgMap, &stua.nId);
  *v2 = stua;
}


#####################################
void __cdecl MonthlyChouJiangTable::AddMonthlyChouJiangItemMap(
        MonthlyChouJiangTable *const this,
        int32_t Monthly,
        int32_t nId,
        RateItem stu)
{
  std::map<int,RateItem> *v4; // rax
  int32_t nIda; // [rsp+0h] [rbp-10h] BYREF
  int32_t Monthlya; // [rsp+4h] [rbp-Ch] BYREF
  MonthlyChouJiangTable *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  Monthlya = Monthly;
  nIda = nId;
  v4 = std::map<int,std::map<int,RateItem>>::operator[](&this->m_MonthlyChouJiangItemMap, &Monthlya);
  *std::map<int,RateItem>::operator[](v4, &nIda) = stu;
}


