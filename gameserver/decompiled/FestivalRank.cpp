// Decompiled methods for class: FestivalRank
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl FestivalRank::CleanUp(FestivalRank *const this)
{
  this->nIndex = 0;
  std::string::operator=(&this->strDB, byte_8CFE00);
  this->nCharId = 0;
  std::string::operator=(&this->strName, byte_8CFE00);
  this->nScore = 0;
  this->nTime = 0;
  this->bChange = 0;
}


