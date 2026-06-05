// Decompiled: MutiConn<GameService>
// Source: gameserver.cc

#####################################
void __cdecl MutiConn<GameService>::~MutiConn(MutiConn<GameService> *const this)
{
  MutiConn<GameService>::~MutiConn(this);
  operator delete(this);
}


#####################################
void __cdecl MutiConn<GameService>::onNetPacket(MutiConn<GameService> *const this, Answer::NetPacket *inPacket)
{
  GameService::onNetPacket(this->m_pService, this, inPacket);
}


