// Decompiled methods for class: CExtSystemMgr
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CExtSystemMgr::~CExtSystemMgr(CExtSystemMgr *const this)
{
  CExtSystemMgr::~CExtSystemMgr(this);
  operator delete(this);
}


#####################################
void __cdecl CExtSystemMgr::Register(CExtSystemMgr *const this, CExtSystemBase *pExtSystem)
{
  CExtSystemBase *v2; // rbx
  unsigned __int16 *v3; // rax
  CExtSystemBase *pExtSystema; // [rsp+0h] [rbp-50h] BYREF
  CExtSystemMgr *thisa; // [rsp+8h] [rbp-48h]
  std::_List_iterator<short unsigned int> eiter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<short unsigned int> iter; // [rsp+20h] [rbp-30h] BYREF
  ProcIdList procList; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  pExtSystema = pExtSystem;
  if ( pExtSystem )
  {
    std::list<CExtSystemBase *>::push_back(&thisa->m_lstExtSystems, &pExtSystema);
    std::list<unsigned short>::list(&procList);
    (*((void (__fastcall **)(CExtSystemBase *, ProcIdList *))pExtSystema->_vptr_IExtSystem + 5))(pExtSystema, &procList);
    iter._M_node = std::list<unsigned short>::begin(&procList)._M_node;
    eiter._M_node = std::list<unsigned short>::end(&procList)._M_node;
    while ( std::_List_iterator<unsigned short>::operator!=(&iter, &eiter) )
    {
      v2 = pExtSystema;
      v3 = std::_List_iterator<unsigned short>::operator*(&iter);
      CExtSystemMgr::registProtocolHandler(thisa, *v3, v2);
      std::_List_iterator<unsigned short>::operator++(&iter);
    }
    std::list<unsigned short>::~list(&procList);
  }
}


#####################################
void __cdecl CExtSystemMgr::registProtocolHandler(CExtSystemMgr *const this, ProcId_t procId, CExtSystemBase *pHanlder)
{
  ProcId_t procIda; // [rsp+14h] [rbp-Ch] BYREF
  CExtSystemMgr *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  procIda = procId;
  if ( pHanlder )
    *std::map<unsigned short,CExtSystemBase *>::operator[](&thisa->m_mapProcHandler, &procIda) = pHanlder;
}


#####################################
void __cdecl CExtSystemMgr::OnLoadFromDB(CExtSystemMgr *const this, const PlayerDBData *const dbData)
{
  CExtSystemBase **v2; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*((void (__fastcall **)(CExtSystemBase *, const PlayerDBData *const))(*v2)->_vptr_IExtSystem + 3))(*v2, dbData);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtSystemMgr::OnSaveToDB(CExtSystemMgr *const this, PlayerDBData *const dbData)
{
  CExtSystemBase **v2; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*((void (__fastcall **)(CExtSystemBase *, PlayerDBData *const))(*v2)->_vptr_IExtSystem + 4))(*v2, dbData);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtSystemMgr::OnUpdate(CExtSystemMgr *const this, int64_t curTick)
{
  CExtSystemBase **v2; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*((void (__fastcall **)(CExtSystemBase *, int64_t))(*v2)->_vptr_IExtSystem + 2))(*v2, curTick);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtSystemMgr::InitSystem(CExtSystemMgr *const this)
{
  CExtSystemBase **v1; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v1 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*((void (__fastcall **)(CExtSystemBase *))(*v1)->_vptr_IExtSystem + 10))(*v1);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtSystemMgr::OnDaySwitch(CExtSystemMgr *const this, int32_t nDiffDays)
{
  CExtSystemBase **v2; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*((void (__fastcall **)(CExtSystemBase *, _QWORD))(*v2)->_vptr_IExtSystem + 1))(*v2, (unsigned int)nDiffDays);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtSystemMgr::OnCleanUp(CExtSystemMgr *const this)
{
  CExtSystemBase **v1; // rax
  std::_List_iterator<CExtSystemBase*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CExtSystemBase*> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CExtSystemBase *>::begin(&this->m_lstExtSystems)._M_node;
  eiter._M_node = std::list<CExtSystemBase *>::end(&this->m_lstExtSystems)._M_node;
  while ( std::_List_iterator<CExtSystemBase *>::operator!=(&iter, &eiter) )
  {
    v1 = std::_List_iterator<CExtSystemBase *>::operator*(&iter);
    (*(*v1)->_vptr_IExtSystem)(*v1);
    std::_List_iterator<CExtSystemBase *>::operator++(&iter);
  }
}


#####################################
int32_t __cdecl CExtSystemMgr::DispatchNetDatas(
        CExtSystemMgr *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  ProcId_t nProcIda; // [rsp+14h] [rbp-2Ch] BYREF
  CExtSystemMgr *thisa; // [rsp+18h] [rbp-28h]
  CExtSystemBase *pHandler; // [rsp+28h] [rbp-18h]

  thisa = this;
  nProcIda = nProcId;
  pHandler = *std::map<unsigned short,CExtSystemBase *>::operator[](&this->m_mapProcHandler, &nProcIda);
  if ( pHandler )
    return (*((int32_t (__fastcall **)(CExtSystemBase *, _QWORD, Answer::NetPacket *))pHandler->_vptr_IExtSystem + 6))(
             pHandler,
             nProcIda,
             inPacket);
  else
    return 10002;
}


