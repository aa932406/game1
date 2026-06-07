// Decompiled: BlackMarketIndex
// Source: gameserver.cc

#####################################
bool __cdecl BlackMarketIndex::operator<(const BlackMarketIndex *const this, const BlackMarketIndex *const right)
{
  Job_t nJob; // dl
  Job_t nIndex; // al

  if ( this->nDays != right->nDays )
    return this->nDays < right->nDays;
  if ( this->nIndex == right->nIndex )
  {
    nJob = this->nJob;
    nIndex = right->nJob;
  }
  else
  {
    nJob = this->nIndex;
    nIndex = right->nIndex;
  }
  return nJob < nIndex;
}


