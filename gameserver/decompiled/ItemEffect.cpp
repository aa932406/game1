// Decompiled methods for class: ItemEffect
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl ItemEffect::~ItemEffect(ItemEffect *const this)
{
  ItemEffect::~ItemEffect(this);
  operator delete(this);
}


