// Decompiled methods for class: ItemData
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl ItemData::IsEmpty(const ItemData *const this)
{
  return this->m_nId <= 0 || this->m_nClass <= 0 || this->m_nCount <= 0;
}


