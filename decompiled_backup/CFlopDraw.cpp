// Decompiled methods for class: CFlopDraw
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CFlopDraw::~CFlopDraw(CFlopDraw *const this)
{
  CFlopDraw::~CFlopDraw(this);
  operator delete(this);
}


#####################################
void __cdecl CFlopDraw::SaveToSqlString(
        CFlopDraw *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::pair<const int,std::map<int,int> > *v4; // rax
  int second; // ebx
  int first; // r12d
  std::pair<const int,std::map<int,int> > *v7; // rax
  std::pair<const int,std::map<int,int> > *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+30h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+40h] [rbp-60h] BYREF
  std::string __x; // [rsp+50h] [rbp-50h] BYREF
  char v14; // [rsp+5Fh] [rbp-41h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > v15; // [rsp+60h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v16; // [rsp+70h] [rbp-30h] BYREF
  std::string v17; // [rsp+80h] [rbp-20h] BYREF
  _BYTE v18[17]; // [rsp+8Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_flop_draw` WHERE `cid` = %lld ", nCid);
  std::allocator<char>::allocator(&v14);
  std::string::string(&__x, (char *)szSQL, &v14);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v14);
  for ( it._M_node = std::map<int,std::map<int,int>>::begin(&this->m_FlopDrawRecordMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator++(&it, 0) )
  {
    v15._M_node = std::map<int,std::map<int,int>>::end(&this->m_FlopDrawRecordMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &v15) )
      break;
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
    for ( itFlop._M_node = std::map<int,int>::begin(&v4->second)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itFlop, 0) )
    {
      v8 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      v16._M_node = std::map<int,int>::end(&v8->second)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &v16) )
        break;
      bzero(szSQL, 0x1000u);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->second;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->first;
      v7 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_flop_draw` (cid, act_type,flop_id,result) VALUES (%lld,%d,%d,%d)",
        nCid,
        v7->first,
        first,
        second);
      std::allocator<char>::allocator(v18);
      std::string::string(&v17, (char *)szSQL, v18);
      std::list<std::string>::push_back(sqls, &v17);
      std::string::~string(&v17);
      std::allocator<char>::~allocator(v18);
    }
  }
}


#####################################
bool __cdecl CFlopDraw::LoadFromDB(
        CFlopDraw *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  std::map<int,int> *v7; // rax
  int *v8; // rax
  int32_t FlopId; // [rsp+38h] [rbp-38h] BYREF
  int32_t nType; // [rsp+3Ch] [rbp-34h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF
  int32_t ResultId; // [rsp+5Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_flop_draw` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    nType = Answer::MySqlQuery::getIntValue(&result, "act_type", 0);
    FlopId = Answer::MySqlQuery::getIntValue(&result, "flop_id", 0);
    ResultId = Answer::MySqlQuery::getIntValue(&result, "result", 0);
    v7 = std::map<int,std::map<int,int>>::operator[](&this->m_FlopDrawRecordMap, &nType);
    v8 = std::map<int,int>::operator[](v7, &FlopId);
    *v8 = ResultId;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CFlopDraw::PackageData(CFlopDraw *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int first; // edx
  std::pair<const int,std::map<int,int> > *v4; // rax
  int32_t v5; // edx
  std::pair<const int,std::map<int,int> > *v6; // rax
  int v7; // edx
  int32_t second; // edx
  std::pair<const int,std::map<int,int> > *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > v12; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+40h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::map<int,std::map<int,int>>::size(&this->m_FlopDrawRecordMap);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( it._M_node = std::map<int,std::map<int,int>>::begin(&this->m_FlopDrawRecordMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator++(&it, 0) )
    {
      v12._M_node = std::map<int,std::map<int,int>>::end(&this->m_FlopDrawRecordMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &v12) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      v5 = std::map<int,int>::size(&v4->second);
      Answer::NetPacket::writeInt32(packet, v5);
      v6 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      for ( itFlop._M_node = std::map<int,int>::begin(&v6->second)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itFlop, 0) )
      {
        v9 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
        __x._M_node = std::map<int,int>::end(&v9->second)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &__x) )
          break;
        v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->first;
        Answer::NetPacket::writeInt32(packet, v7);
        second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->second;
        Answer::NetPacket::writeInt32(packet, second);
      }
    }
  }
}


#####################################
void __cdecl CFlopDraw::UnPackageData(CFlopDraw *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int *v3; // rax
  std::map<int,int> *v4; // rax
  Int32Int32Map TmpMap; // [rsp+20h] [rbp-60h] BYREF
  int32_t FlopId; // [rsp+54h] [rbp-2Ch] BYREF
  int32_t nType; // [rsp+58h] [rbp-28h] BYREF
  int32_t nTypeSize; // [rsp+5Ch] [rbp-24h]
  int32_t i; // [rsp+60h] [rbp-20h]
  int32_t FlopSize; // [rsp+64h] [rbp-1Ch]
  int32_t j; // [rsp+68h] [rbp-18h]
  int32_t nId; // [rsp+6Ch] [rbp-14h]

  if ( inPacket )
  {
    nTypeSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nTypeSize; ++i )
    {
      nType = Answer::NetPacket::readInt32(inPacket);
      FlopSize = Answer::NetPacket::readInt32(inPacket);
      std::map<int,int>::map(&TmpMap);
      for ( j = 0; j < FlopSize; ++j )
      {
        FlopId = Answer::NetPacket::readInt32(inPacket);
        nId = Answer::NetPacket::readInt32(inPacket);
        v3 = std::map<int,int>::operator[](&TmpMap, &FlopId);
        *v3 = nId;
      }
      v4 = std::map<int,std::map<int,int>>::operator[](&this->m_FlopDrawRecordMap, &nType);
      std::map<int,int>::operator=(v4, &TmpMap);
      std::map<int,int>::~map(&TmpMap);
    }
  }
}


