// Decompiled methods for class: CfgTencentTable
// Source: gameserver.cc
// Total methods: 15

#####################################
void __cdecl CfgTencentTable::SetYellowNewerGift(CfgTencentTable *const this, const MemChrBagVector *const gift)
{
  std::vector<MemChrBag>::operator=(&this->m_vYellowNewerGift, gift);
}


#####################################
void __cdecl CfgTencentTable::AddYellowDailyGift(CfgTencentTable *const this, const CfgTencentGift *const gift)
{
  CfgTencentGift *v2; // rax

  v2 = std::map<int,CfgTencentGift>::operator[](&this->m_mYellowDailyGift, &gift->nLevel);
  CfgTencentGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddYellowYearGift(CfgTencentTable *const this, const CfgTencentGift *const gift)
{
  CfgTencentGift *v2; // rax

  v2 = std::map<int,CfgTencentGift>::operator[](&this->m_mYellowYearGift, &gift->nLevel);
  CfgTencentGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddYellowLevelGift(
        CfgTencentTable *const this,
        int32_t nIndex,
        const CfgTencentGift *const gift)
{
  CfgTencentGift *v3; // rax
  int32_t nIndexa; // [rsp+14h] [rbp-Ch] BYREF
  CfgTencentTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nIndexa = nIndex;
  v3 = std::map<int,CfgTencentGift>::operator[](&this->m_mYellowLevelGift, &nIndexa);
  CfgTencentGift::operator=(v3, gift);
}


#####################################
void __cdecl CfgTencentTable::AddQQZoneGift(CfgTencentTable *const this, const CfgQQGift *const gift)
{
  CfgQQGift *v2; // rax

  v2 = std::map<int,CfgQQGift>::operator[](&this->m_mQQZoneGift, &gift->nIndex);
  CfgQQGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddQQGameGift(CfgTencentTable *const this, const CfgQQGift *const gift)
{
  CfgQQGift *v2; // rax

  v2 = std::map<int,CfgQQGift>::operator[](&this->m_mQQGameGift, &gift->nIndex);
  CfgQQGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::SetBlueNewerGift(CfgTencentTable *const this, const MemChrBagVector *const gift)
{
  std::vector<MemChrBag>::operator=(&this->m_vBlueNewerGift, gift);
}


#####################################
void __cdecl CfgTencentTable::AddBlueDailyGift(CfgTencentTable *const this, const CfgTencentGift *const gift)
{
  CfgTencentGift *v2; // rax

  v2 = std::map<int,CfgTencentGift>::operator[](&this->m_mBlueDailyGift, &gift->nLevel);
  CfgTencentGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddBlueYearGift(CfgTencentTable *const this, const CfgTencentGift *const gift)
{
  CfgTencentGift *v2; // rax

  v2 = std::map<int,CfgTencentGift>::operator[](&this->m_mBlueYearGift, &gift->nLevel);
  CfgTencentGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddBlueHighGift(CfgTencentTable *const this, const CfgTencentGift *const gift)
{
  CfgTencentGift *v2; // rax

  v2 = std::map<int,CfgTencentGift>::operator[](&this->m_mBlueHighGift, &gift->nLevel);
  CfgTencentGift::operator=(v2, gift);
}


#####################################
void __cdecl CfgTencentTable::AddBlueLevelGift(
        CfgTencentTable *const this,
        int32_t nIndex,
        const CfgTencentGift *const gift)
{
  CfgTencentGift *v3; // rax
  int32_t nIndexa; // [rsp+14h] [rbp-Ch] BYREF
  CfgTencentTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nIndexa = nIndex;
  v3 = std::map<int,CfgTencentGift>::operator[](&this->m_mBlueLevelGift, &nIndexa);
  CfgTencentGift::operator=(v3, gift);
}


#####################################
bool __cdecl CfgTencentTable::AddSevenDayLogin(CfgTencentTable *const this, const CfgTencentSevenDayLogin *const stu)
{
  CfgTencentSevenDayLogin *v2; // rax

  v2 = std::map<signed char,CfgTencentSevenDayLogin>::operator[](&this->m_mSevenDayLogin, &stu->nDays);
  CfgTencentSevenDayLogin::operator=(v2, stu);
  return 1;
}


#####################################
void __cdecl CfgTencentTable::AddTGPNewerGift(CfgTencentTable *const this, const CfgTGPGift *const gift)
{
  std::list<CfgTGPGift>::push_back(&this->m_lTGPNewerGift, gift);
}


#####################################
void __cdecl CfgTencentTable::AddTGPDailyGift(CfgTencentTable *const this, const CfgTGPGift *const gift)
{
  std::list<CfgTGPGift>::push_back(&this->m_lTGPDailyGift, gift);
}


#####################################
void __cdecl CfgTencentTable::AddTGPLevelGift(CfgTencentTable *const this, const CfgTGPGift *const gift)
{
  std::list<CfgTGPGift>::push_back(&this->m_lTGPLevelGift, gift);
}


