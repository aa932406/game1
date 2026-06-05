// Decompiled methods for class: CObjAttrs
// Source: gameserver.cc
// Total methods: 2

#####################################
int32_t __cdecl CObjAttrs::GetAttr(const CObjAttrs *const this, const CObjAttrs::Index_T nIdx)
{
  if ( (unsigned int)nIdx < CObjAttrs::Index_T::MAX_INDEX )
    return this->m_vAttr[nIdx];
  else
    return 0;
}


#####################################
void __cdecl CObjAttrs::SetAttr(CObjAttrs *const this, const CObjAttrs::Index_T nIdx, const int32_t nValue)
{
  if ( (unsigned int)nIdx <= CObjAttrs::Index_T::ATTR_XUAN_YUN_DEF )
    this->m_vAttr[nIdx] = nValue;
}


