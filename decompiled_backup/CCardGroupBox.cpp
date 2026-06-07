// Decompiled methods for class: CCardGroupBox
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CCardGroupBox::Init(CCardGroupBox *const this, int32_t nId, const CardGroupList *const lst)
{
  this->m_nId = nId;
  std::list<CardGroup>::operator=(&this->m_lstCards, lst);
  CCardGroupBox::resetCardGroup(this);
}


#####################################
int32_t __cdecl CCardGroupBox::GetCard(CCardGroupBox *const this)
{
  int32_t m_nIndex; // eax
  int32_t v2; // edx

  if ( this->m_nIndex > 9999 )
    CCardGroupBox::resetCardGroup(this);
  m_nIndex = this->m_nIndex;
  v2 = *((_DWORD *)&this->m_lstCards._M_impl + m_nIndex + 5);
  this->m_nIndex = m_nIndex + 1;
  return v2;
}


#####################################
void __cdecl CCardGroupBox::resetCardGroup(CCardGroupBox *const this)
{
  const CardGroup *v2; // rdx
  const CardGroup *v3; // rax
  const CardGroup *v4; // rax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v6; // rax
  int32_t v7; // ebx
  size_t v8; // rbx
  std::_List_const_iterator<CardGroup> iter; // [rsp+10h] [rbp-80h] BYREF
  Int32Vector vIds; // [rsp+20h] [rbp-70h] BYREF
  std::_List_iterator<CardGroup> __x; // [rsp+40h] [rbp-50h] BYREF
  std::_List_const_iterator<CardGroup> v12; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<CardGroup> v13; // [rsp+60h] [rbp-30h] BYREF
  int32_t nIndx; // [rsp+74h] [rbp-1Ch]
  int32_t i_0; // [rsp+78h] [rbp-18h]
  uint32_t i; // [rsp+7Ch] [rbp-14h]

  this->m_nIndex = 0;
  bzero(this->m_vCardGroup, 0x9C40u);
  std::vector<int>::vector(&vIds);
  std::vector<int>::reserve(&vIds, 0x2710u);
  __x._M_node = std::list<CardGroup>::begin(&this->m_lstCards)._M_node;
  std::_List_const_iterator<CardGroup>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v13._M_node = std::list<CardGroup>::end(&this->m_lstCards)._M_node;
    std::_List_const_iterator<CardGroup>::_List_const_iterator(&v12, &v13);
    if ( !std::_List_const_iterator<CardGroup>::operator!=(&iter, &v12) )
      break;
    if ( std::_List_const_iterator<CardGroup>::operator->(&iter)->min >= 0
      && std::_List_const_iterator<CardGroup>::operator->(&iter)->max > 0 )
    {
      v2 = std::_List_const_iterator<CardGroup>::operator*(&iter);
      CCardGroupBox::initCardGroup(this, v2);
    }
    else
    {
      for ( i_0 = 0; ; ++i_0 )
      {
        v4 = std::_List_const_iterator<CardGroup>::operator->(&iter);
        if ( v4->count <= i_0 )
          break;
        v3 = std::_List_const_iterator<CardGroup>::operator->(&iter);
        std::vector<int>::push_back(&vIds, &v3->id);
      }
    }
    std::_List_const_iterator<CardGroup>::operator++(&iter);
  }
  M_current = std::vector<int>::end(&vIds)._M_current;
  v6._M_current = std::vector<int>::begin(&vIds)._M_current;
  std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
    v6,
    (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
  nIndx = 0;
  for ( i = 0; ; ++i )
  {
    v8 = i;
    if ( v8 >= std::vector<int>::size(&vIds) )
      break;
    nIndx = CCardGroupBox::getFirstEmptyIndex(this, nIndx, 10000);
    if ( nIndx < 0 )
      break;
    v7 = nIndx;
    *((_DWORD *)&this->m_lstCards._M_impl + v7 + 5) = *std::vector<int>::operator[](&vIds, i);
  }
  std::vector<int>::~vector(&vIds);
}


#####################################
void __cdecl CCardGroupBox::initCardGroup(CCardGroupBox *const this, const CardGroup *const group)
{
  Answer::Random *v2; // rax
  int32_t nCount; // [rsp+14h] [rbp-2Ch]
  int32_t nArea; // [rsp+18h] [rbp-28h]
  int32_t nStart; // [rsp+1Ch] [rbp-24h]
  int32_t i; // [rsp+20h] [rbp-20h]
  int32_t nMin; // [rsp+24h] [rbp-1Ch]
  int nMax; // [rsp+28h] [rbp-18h]
  int32_t nRand; // [rsp+2Ch] [rbp-14h]

  if ( group->count > 0 && group->count <= 10000 && group->min <= 100 && group->max <= 100 )
  {
    nCount = group->count;
    nArea = 10000 / nCount;
    nStart = 0;
    for ( i = 0; i < nCount; ++i )
    {
      nMin = nStart + nArea * group->min / 100;
      nMax = nStart + nArea * group->max / 100;
      if ( nMin > 10000 )
        nMin = nStart;
      if ( nMax > 10000 )
        nMax = 10000;
      v2 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v2, nMin, nMax - 1);
      if ( *((_DWORD *)&this->m_lstCards._M_impl + i + 5) )
        nRand = CCardGroupBox::getFirstEmptyIndex(this, nMin, nMax);
      if ( nRand >= 0 )
        *((_DWORD *)&this->m_lstCards._M_impl + nRand + 5) = group->id;
      nStart += nArea;
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "CCardGroup::initCardGroup() item count out of range where id=%d, count=%d\n",
      group->id,
      group->count);
  }
}


#####################################
int32_t __cdecl CCardGroupBox::getFirstEmptyIndex(CCardGroupBox *const this, int32_t nMin, int32_t nMax)
{
  while ( nMin < nMax )
  {
    if ( !*((_DWORD *)&this->m_lstCards._M_impl + nMin + 5) )
      return nMin;
    ++nMin;
  }
  return -1;
}


