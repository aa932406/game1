// Decompiled methods for class: IMapEvent
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl IMapEvent::~IMapEvent(IMapEvent *const this)
{
  IMapEvent::~IMapEvent(this);
  operator delete(this);
}


#####################################
void __cdecl IMapEvent::init(IMapEvent *const this, const CfgMapEventList *const events, int64_t nTime)
{
  std::_List_iterator<CfgMapEvent> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-10h] BYREF

  std::list<CfgMapEvent>::operator=(&this->m_events, events);
  for ( iter._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
        ;
        std::_List_iterator<CfgMapEvent>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
    if ( !std::_List_iterator<CfgMapEvent>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<CfgMapEvent>::operator->(&iter)->bInitOpen )
      std::_List_iterator<CfgMapEvent>::operator->(&iter)->nOpenTime = nTime;
  }
}


#####################################
void __cdecl IMapEvent::openEvent(IMapEvent *const this, int32_t nEvent, int64_t nTick)
{
  CfgMapEvent *v3; // rax
  void (__fastcall *v5)(IMapEvent *const, CfgMapEvent *); // rbx
  CfgMapEvent *v6; // rdx
  std::_List_iterator<CfgMapEvent> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  for ( iter._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
        ;
        std::_List_iterator<CfgMapEvent>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
    if ( !std::_List_iterator<CfgMapEvent>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<CfgMapEvent>::operator->(&iter)->trigger_id == nEvent )
    {
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&iter);
      if ( !CfgMapEvent::isOpen(v3) )
      {
        std::_List_iterator<CfgMapEvent>::operator->(&iter)->nOpenTime = nTick;
        v5 = (void (__fastcall *)(IMapEvent *const, CfgMapEvent *))*((_QWORD *)this->_vptr_IMapEvent + 3);
        v6 = std::_List_iterator<CfgMapEvent>::operator*(&iter);
        v5(this, v6);
      }
    }
  }
}


#####################################
void __cdecl IMapEvent::closeEvent(IMapEvent *const this, int32_t nEvent, int64_t nTick)
{
  CfgMapEvent *v3; // rax
  std::_List_iterator<CfgMapEvent> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
        ;
        std::_List_iterator<CfgMapEvent>::operator++(&iter) )
  {
    __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
    if ( !std::_List_iterator<CfgMapEvent>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<CfgMapEvent>::operator->(&iter)->trigger_id == nEvent )
    {
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&iter);
      if ( CfgMapEvent::isOpen(v3) )
        std::_List_iterator<CfgMapEvent>::operator->(&iter)->nCloseTime = nTick;
    }
  }
}


#####################################
void __cdecl IMapEvent::openEvents(IMapEvent *const this, const Int32List *const events, int64_t nTick)
{
  int v3; // ecx
  std::_List_const_iterator<int> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<int>::begin(events)._M_node; ; std::_List_const_iterator<int>::operator++(&iter) )
  {
    __x._M_node = std::list<int>::end(events)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &__x) )
      break;
    v3 = *std::_List_const_iterator<int>::operator*(&iter);
    IMapEvent::openEvent(this, v3, nTick);
  }
}


#####################################
void __cdecl IMapEvent::closeEvents(IMapEvent *const this, const Int32List *const events, int64_t nTick)
{
  int v3; // ecx
  std::_List_const_iterator<int> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<int>::begin(events)._M_node; ; std::_List_const_iterator<int>::operator++(&iter) )
  {
    __x._M_node = std::list<int>::end(events)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &__x) )
      break;
    v3 = *std::_List_const_iterator<int>::operator*(&iter);
    IMapEvent::closeEvent(this, v3, nTick);
  }
}


