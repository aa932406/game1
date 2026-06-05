// Decompiled methods for class: CCardGroupBoxManager
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CCardGroupBoxManager::Add(
        CCardGroupBoxManager *const this,
        int32_t nGroupId,
        const CardGroupList *const lst)
{
  CCardGroupBox box; // [rsp+20h] [rbp-9C70h] BYREF

  CCardGroupBox::CCardGroupBox(&box);
  CCardGroupBox::Init(&box, nGroupId, lst);
  std::list<CCardGroupBox>::push_back(&this->m_lCardGroupBox, &box);
  CCardGroupBox::~CCardGroupBox(&box);
}


#####################################
int32_t __cdecl CCardGroupBoxManager::GetCard(CCardGroupBoxManager *const this, int32_t nId)
{
  CCardGroupBox *v2; // rax
  CCardGroupBox *v3; // rax
  std::_List_iterator<CCardGroupBox> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CCardGroupBox> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CCardGroupBox>::begin(&this->m_lCardGroupBox)._M_node;
        ;
        std::_List_iterator<CCardGroupBox>::operator++(&iter) )
  {
    __x._M_node = std::list<CCardGroupBox>::end(&this->m_lCardGroupBox)._M_node;
    if ( !std::_List_iterator<CCardGroupBox>::operator!=(&iter, &__x) )
      break;
    v2 = std::_List_iterator<CCardGroupBox>::operator->(&iter);
    if ( CCardGroupBox::GetId(v2) == nId )
    {
      v3 = std::_List_iterator<CCardGroupBox>::operator->(&iter);
      return CCardGroupBox::GetCard(v3);
    }
  }
  return 0;
}


