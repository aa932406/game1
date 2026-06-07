// Decompiled methods for class: CfgMysteryGiftTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgMysteryGiftTable::Add(CfgMysteryGiftTable *const this, const CfgMysteryGift *const gift)
{
  CfgMysteryGift *v2; // rax

  v2 = std::map<int,CfgMysteryGift>::operator[](&this->m_mMysteryGift, &gift->nIndex);
  CfgMysteryGift::operator=(v2, gift);
  return 1;
}


