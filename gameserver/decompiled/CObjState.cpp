// Decompiled methods for class: CObjState
// Source: gameserver.cc
// Total methods: 3

#####################################
bool __cdecl CObjState::GetState(const CObjState *const this, const CObjState::Index_T nIdx)
{
  return (unsigned int)nIdx < CObjState::Index_T::MAX_INDEX && this->m_vState[nIdx] > 0;
}


#####################################
void __cdecl CObjState::AddState(CObjState *const this, const CObjState::Index_T nIdx)
{
  if ( (unsigned int)nIdx <= CObjState::Index_T::OBS_BLURRING )
    ++this->m_vState[nIdx];
}


#####################################
void __cdecl CObjState::RemoveState(CObjState *const this, const CObjState::Index_T nIdx)
{
  if ( (unsigned int)nIdx <= CObjState::Index_T::OBS_BLURRING )
    --this->m_vState[nIdx];
}


