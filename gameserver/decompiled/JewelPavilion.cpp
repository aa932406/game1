// Decompiled methods for class: JewelPavilion
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl JewelPavilion::~JewelPavilion(JewelPavilion *const this)
{
  JewelPavilion::~JewelPavilion(this);
  operator delete(this);
}


#####################################
int32_t __cdecl JewelPavilion::effect(
        JewelPavilion *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  CSuperTeHui *CSuperTeHui; // rax

  if ( Player::getRecord(launcher, 1034) > 0 )
    return 10002;
  CSuperTeHui = Player::GetCSuperTeHui(launcher);
  CSuperTeHui::SetJewelPavilionOpen(CSuperTeHui);
  return 0;
}


