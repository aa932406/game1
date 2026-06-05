// Decompiled methods for class: MemPetDBData
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl MemPetDBData::CleanUp(MemPetDBData *const this)
{
  this->nOwner = 0;
  this->nPetId = 0;
  this->nBaseId = 0;
  std::string::operator=(&this->strName, &byte_8F560F);
  std::string::operator=(&this->skills, &byte_8F560F);
  std::string::operator=(&this->equips, &byte_8F560F);
}


