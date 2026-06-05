// Decompiled: MutiConn<DBService>
// Source: gameserver.cc

#####################################
void __cdecl MutiConn<DBService>::~MutiConn(MutiConn<DBService> *const this)
{
  MutiConn<DBService>::~MutiConn(this);
  operator delete(this);
}


#####################################
void __cdecl MutiConn<DBService>::onNetPacket(MutiConn<DBService> *const this, Answer::NetPacket *inPacket)
{
  DBService::onNetPacket(this->m_pService, this, inPacket);
}


