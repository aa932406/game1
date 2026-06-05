// Decompiled methods for class: CExtSystemBase
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CExtSystemBase::~CExtSystemBase(CExtSystemBase *const this)
{
  CExtSystemBase::~CExtSystemBase(this);
  operator delete(this);
}


