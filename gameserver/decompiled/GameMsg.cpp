// Decompiled methods for class: GameMsg
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl GameMsg::reset(GameMsg *const this)
{
  this->msgcode = GameMsgCode::GMC_UNKNOWN;
  this->ptr1 = 0;
  this->ptr2 = 0;
  this->ptr3 = 0;
  this->iparam1 = 0;
  this->iparam2 = 0;
  this->effecttick = 0;
}


