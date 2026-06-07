// Decompiled methods for class: CExtOperateLimit
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CExtOperateLimit::~CExtOperateLimit(CExtOperateLimit *const this)
{
  CExtOperateLimit::~CExtOperateLimit(this);
  operator delete(this);
}


#####################################
void __cdecl CExtOperateLimit::OnLoadFromDB(CExtOperateLimit *const this, const PlayerDBData *const dbData)
{
  std::map<int,OperateLimit>::operator=(&this->m_mOperateLimit, &dbData->m_OperateLimit.m_mOperateLimit);
  if ( !CExtOperateLimit::CheckIsLimitedForever(this, 37205) )
    CExtOperateLimit::AddLimitCount(this, 37205, 2);
  CExtOperateLimit::checkMaintainCompensate(this);
}


#####################################
void __cdecl CExtOperateLimit::OnSaveToDB(CExtOperateLimit *const this, PlayerDBData *const dbData)
{
  OperateLimit *v2; // rax
  OperateLimit stu; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > eiter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+30h] [rbp-20h] BYREF
  int32_t start_line; // [rsp+40h] [rbp-10h]
  int32_t LimitCount; // [rsp+44h] [rbp-Ch]
  OperateLimit *limit; // [rsp+48h] [rbp-8h]

  if ( this->m_pPlayer )
  {
    start_line = 0;
    LimitCount = 0;
    iter._M_node = std::map<int,OperateLimit>::begin(&this->m_mOperateLimit)._M_node;
    eiter._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
    while ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &eiter) )
    {
      limit = &std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second;
      if ( limit->LimitId > 1000 )
      {
        LimitCount = limit->LimitCount;
        *(_QWORD *)&stu.LimitId = 0;
        *(_DWORD *)&stu.IsChaned = 0;
        stu.LimitId = limit->LimitId;
        stu.LimitCount = LimitCount;
        v2 = std::map<int,OperateLimit>::operator[](&dbData->m_OperateLimit.m_mOperateLimit, &stu.LimitId);
        *v2 = stu;
      }
      std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator++(&iter);
    }
  }
}


#####################################
int32_t __cdecl CExtOperateLimit::GetLimitCount(const CExtOperateLimit *const this, int32_t LimitId)
{
  int32_t LimitIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CExtOperateLimit *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  LimitIda = LimitId;
  iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &LimitIda)._M_node;
  __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount;
  else
    return 0;
}


#####################################
void __cdecl CExtOperateLimit::UpdateLimitCount(CExtOperateLimit *const this, int32_t LimitId, int32_t LimitCount)
{
  OperateLimit *v3; // rax
  int32_t LimitIda; // [rsp+4h] [rbp-5Ch] BYREF
  CExtOperateLimit *thisa; // [rsp+8h] [rbp-58h]
  OperateLimit limit; // [rsp+10h] [rbp-50h]
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+20h] [rbp-40h] BYREF
  Int32List updataList; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+40h] [rbp-20h] BYREF

  thisa = this;
  LimitIda = LimitId;
  std::list<int>::list(&updataList);
  iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &LimitIda)._M_node;
  __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x) )
  {
    if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount != LimitCount )
    {
      std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount = LimitCount;
      std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.IsChaned = 1;
      std::list<int>::push_back(&updataList, &LimitIda);
    }
  }
  else
  {
    *(_DWORD *)&limit.IsChaned = 1;
    *(_QWORD *)&limit.LimitId = __PAIR64__(LimitCount, LimitIda);
    v3 = std::map<int,OperateLimit>::operator[](&thisa->m_mOperateLimit, &LimitIda);
    *v3 = limit;
    std::list<int>::push_back(&updataList, &LimitIda);
  }
  CExtOperateLimit::NotifyLimitInfo(thisa, &updataList);
  std::list<int>::~list(&updataList);
}


#####################################
void __cdecl CExtOperateLimit::AddLimitCount(CExtOperateLimit *const this, int32_t LimitId, int32_t LimitCount)
{
  std::pair<const int,OperateLimit> *v3; // rax
  OperateLimit *v4; // rax
  int32_t LimitIda; // [rsp+4h] [rbp-5Ch] BYREF
  CExtOperateLimit *thisa; // [rsp+8h] [rbp-58h]
  OperateLimit limit; // [rsp+10h] [rbp-50h]
  Int32List updataList; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+40h] [rbp-20h] BYREF

  thisa = this;
  LimitIda = LimitId;
  if ( LimitCount )
  {
    iter._M_node = std::map<int,OperateLimit>::find(&thisa->m_mOperateLimit, &LimitIda)._M_node;
    __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter);
      v3->second.LimitCount += LimitCount;
      std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.IsChaned = 1;
    }
    else
    {
      *(_DWORD *)&limit.IsChaned = 1;
      *(_QWORD *)&limit.LimitId = __PAIR64__(LimitCount, LimitIda);
      v4 = std::map<int,OperateLimit>::operator[](&thisa->m_mOperateLimit, &LimitIda);
      *v4 = limit;
    }
    std::list<int>::list(&updataList);
    std::list<int>::push_back(&updataList, &LimitIda);
    CExtOperateLimit::NotifyLimitInfo(thisa, &updataList);
    std::list<int>::~list(&updataList);
  }
}


#####################################
void __cdecl CExtOperateLimit::Reset(CExtOperateLimit *const this, int32_t LimitId)
{
  std::pair<const int,OperateLimit> *v2; // rax
  int32_t LimitIda; // [rsp+4h] [rbp-4Ch] BYREF
  CExtOperateLimit *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+10h] [rbp-40h] BYREF
  Int32List updataList; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  LimitIda = LimitId;
  std::list<int>::list(&updataList);
  iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &LimitIda)._M_node;
  __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x)
    && std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount )
  {
    std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount = 0;
    std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.IsChaned = 1;
    v2 = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter);
    std::list<int>::push_back(&updataList, &v2->second.LimitId);
  }
  CExtOperateLimit::NotifyLimitInfo(thisa, &updataList);
  std::list<int>::~list(&updataList);
}


#####################################
void __cdecl CExtOperateLimit::ResetRange(CExtOperateLimit *const this, int32_t MinId, int32_t MaxId, int32_t DiffDay)
{
  std::pair<const int,OperateLimit> *v4; // rax
  OperateLimit *v5; // rax
  OperateLimit *v6; // rbx
  OperateLimit stu; // [rsp+20h] [rbp-80h] BYREF
  std::_List_iterator<OperateLimit> it; // [rsp+30h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > eiter; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+50h] [rbp-50h] BYREF
  std::list<OperateLimit> AddList; // [rsp+60h] [rbp-40h] BYREF
  Int32List updataList; // [rsp+70h] [rbp-30h] BYREF
  std::_List_iterator<OperateLimit> __x; // [rsp+80h] [rbp-20h] BYREF
  OperateLimit *limit; // [rsp+88h] [rbp-18h]

  std::list<int>::list(&updataList);
  std::list<OperateLimit>::list(&AddList);
  iter._M_node = std::map<int,OperateLimit>::begin(&this->m_mOperateLimit)._M_node;
  eiter._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &eiter) )
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter);
    limit = &v4->second;
    if ( v4->second.LimitCount && limit->LimitId >= MinId && limit->LimitId <= MaxId )
    {
      if ( DiffDay == 1 && limit->LimitId > 2999 && limit->LimitId <= 3999 )
      {
        *(_QWORD *)&stu.LimitId = 0;
        *(_DWORD *)&stu.IsChaned = 0;
        stu.LimitId = limit->LimitId + 1000;
        stu.LimitCount = limit->LimitCount;
        stu.IsChaned = 1;
        std::list<OperateLimit>::push_back(&AddList, &stu);
      }
      limit->LimitCount = 0;
      limit->IsChaned = 0;
      std::list<int>::push_back(&updataList, &limit->LimitId);
    }
    std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator++(&iter);
  }
  for ( it._M_node = std::list<OperateLimit>::begin(&AddList)._M_node; ; std::_List_iterator<OperateLimit>::operator++(&it) )
  {
    __x._M_node = std::list<OperateLimit>::end(&AddList)._M_node;
    if ( !std::_List_iterator<OperateLimit>::operator!=(&it, &__x) )
      break;
    v5 = std::_List_iterator<OperateLimit>::operator->(&it);
    v6 = std::map<int,OperateLimit>::operator[](&this->m_mOperateLimit, &v5->LimitId);
    *v6 = *std::_List_iterator<OperateLimit>::operator*(&it);
  }
  CExtOperateLimit::NotifyLimitInfo(this, &updataList);
  std::list<OperateLimit>::~list(&AddList);
  std::list<int>::~list(&updataList);
}


#####################################
bool __cdecl CExtOperateLimit::CheckCountIsLimited(
        const CExtOperateLimit *const this,
        int32_t LimitId,
        int32_t LimitCount)
{
  int32_t LimitIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CExtOperateLimit *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  LimitIda = LimitId;
  iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &LimitIda)._M_node;
  __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
  return std::_Rb_tree_const_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x)
      && std::_Rb_tree_const_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount >= LimitCount;
}


#####################################
bool __cdecl CExtOperateLimit::CheckIsLimitedForever(const CExtOperateLimit *const this, int32_t LimitId)
{
  int32_t LimitIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CExtOperateLimit *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  LimitIda = LimitId;
  iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &LimitIda)._M_node;
  __x._M_node = std::map<int,OperateLimit>::end(&thisa->m_mOperateLimit)._M_node;
  return std::_Rb_tree_const_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &__x);
}


#####################################
void __cdecl CExtOperateLimit::NotifyLimitInfo(CExtOperateLimit *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > eiter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  int32_t nCount; // [rsp+30h] [rbp-20h]
  uint32_t offset; // [rsp+34h] [rbp-1Ch]
  OperateLimit *limit; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27ADu);
    if ( packet )
    {
      nCount = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      iter._M_node = std::map<int,OperateLimit>::begin(&this->m_mOperateLimit)._M_node;
      eiter._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
      while ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &eiter) )
      {
        limit = &std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second;
        if ( CExtOperateLimit::isNeedNotify(this, limit->LimitId) || limit->LimitId == 1070 )
        {
          Answer::NetPacket::writeInt32(packet, limit->LimitId);
          Answer::NetPacket::writeInt32(packet, limit->LimitCount);
          ++nCount;
        }
        std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator++(&iter);
      }
      offset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, 0);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, offset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtOperateLimit::NotifyLimitInfo(CExtOperateLimit *const this, const Int32List *const rcList)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > findIter; // [rsp+10h] [rbp-60h] BYREF
  int32_t nLimitId; // [rsp+1Ch] [rbp-54h] BYREF
  std::_List_const_iterator<int> eiter; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > __x; // [rsp+40h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]
  int32_t nCount; // [rsp+54h] [rbp-1Ch]
  uint32_t offset; // [rsp+58h] [rbp-18h]
  int32_t nLimitCount; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer && !std::list<int>::empty(rcList) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x27ADu);
    if ( packet )
    {
      nCount = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      iter._M_node = std::list<int>::begin(rcList)._M_node;
      eiter._M_node = std::list<int>::end(rcList)._M_node;
      while ( std::_List_const_iterator<int>::operator!=(&iter, &eiter) )
      {
        nLimitId = *std::_List_const_iterator<int>::operator*(&iter);
        if ( CExtOperateLimit::isNeedNotify(this, nLimitId) )
        {
          nLimitCount = 0;
          findIter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &nLimitId)._M_node;
          __x._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&findIter, &__x) )
            nLimitCount = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&findIter)->second.LimitCount;
          Answer::NetPacket::writeInt32(packet, nLimitId);
          Answer::NetPacket::writeInt32(packet, nLimitCount);
          ++nCount;
        }
        std::_List_const_iterator<int>::operator++(&iter);
      }
      if ( nCount )
      {
        offset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, 0);
        Answer::NetPacket::writeInt32(packet, nCount);
        Answer::NetPacket::setWOffset(packet, offset);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, GateIndex, packet);
      }
      else
      {
        Answer::NetPacket::destroy(packet);
      }
    }
  }
}


#####################################
void __cdecl CExtOperateLimit::checkMaintainCompensate(CExtOperateLimit *const this)
{
  int32_t Time; // ebx
  CfgData *v2; // rax
  const CfgMaintainCompensateTable *MaintainCompensateTable; // rax
  OperateLimit *v4; // rax
  __int64 stu; // [rsp+10h] [rbp-40h]
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+20h] [rbp-30h] BYREF
  int __x; // [rsp+2Ch] [rbp-24h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > v8; // [rsp+30h] [rbp-20h] BYREF
  int __k[5]; // [rsp+3Ch] [rbp-14h] BYREF

  if ( this->m_pPlayer )
  {
    __x = 1070;
    iter._M_node = std::map<int,OperateLimit>::find(&this->m_mOperateLimit, &__x)._M_node;
    v8._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator==(&iter, &v8) )
    {
      LODWORD(stu) = 1070;
      Time = Player::getCreateTime(this->m_pPlayer);
      v2 = Answer::Singleton<CfgData>::instance();
      MaintainCompensateTable = CfgData::GetMaintainCompensateTable(v2);
      HIDWORD(stu) = CfgMaintainCompensateTable::GetInitIndex(MaintainCompensateTable, Time);
      __k[0] = 1070;
      v4 = std::map<int,OperateLimit>::operator[](&this->m_mOperateLimit, __k);
      *(_QWORD *)&v4->LimitId = stu;
      *(_DWORD *)&v4->IsChaned = 0;
    }
  }
}


#####################################
bool __cdecl CExtOperateLimit::isNeedNotify(CExtOperateLimit *const this, int32_t nLimitId)
{
  if ( nLimitId > 3000 && nLimitId <= 3998 )
    return 1;
  if ( nLimitId > 5000 && nLimitId <= 5998 )
    return 1;
  if ( nLimitId > 20000 && nLimitId <= 29998 )
    return 1;
  if ( nLimitId > 6000 && nLimitId <= 6998 )
    return 1;
  if ( nLimitId > 9000 && nLimitId <= 9998 )
    return 1;
  if ( nLimitId > 6999 && nLimitId <= 7999 )
    return 1;
  if ( nLimitId > 36999 && nLimitId <= 37199 )
    return 1;
  if ( nLimitId > 8009 && nLimitId <= 8020 )
    return 1;
  if ( nLimitId > 9999 && nLimitId <= 10100 )
    return 1;
  if ( nLimitId > 8029 && nLimitId <= 8039 )
    return 1;
  if ( nLimitId > 10100 && nLimitId <= 10200 )
    return 1;
  if ( nLimitId > 1040 && nLimitId <= 1048 )
    return 1;
  if ( nLimitId > 1907 )
  {
    if ( nLimitId > 2073 )
    {
      if ( nLimitId == 2124 )
        return 1;
      if ( nLimitId <= 2124 )
      {
        if ( nLimitId > 2110 )
        {
          if ( nLimitId < 2113 || nLimitId > 2115 && (unsigned int)(nLimitId - 2118) > 3 )
            return 0;
        }
        else if ( nLimitId < 2107 && (nLimitId < 2082 || nLimitId > 2086 && (unsigned int)(nLimitId - 2100) > 5) )
        {
          return 0;
        }
        return 1;
      }
      if ( nLimitId == 37205 )
        return 1;
      if ( nLimitId <= 37205 )
        return nLimitId >= 2129 && (nLimitId <= 2132 || (unsigned int)(nLimitId - 37200) <= 2);
      if ( nLimitId == 37401 )
        return 1;
      if ( nLimitId > 37401 )
      {
        if ( (unsigned int)(nLimitId - 37501) <= 5 )
          return 1;
      }
      else if ( (unsigned int)(nLimitId - 37209) <= 4 )
      {
        return 1;
      }
    }
    else
    {
      if ( nLimitId >= 2070 )
        return 1;
      if ( nLimitId > 2021 )
      {
        if ( nLimitId > 2040 )
        {
          if ( nLimitId > 2050 )
          {
            if ( nLimitId != 2064 && nLimitId != 2067 )
              return 0;
          }
          else if ( nLimitId < 2048 && nLimitId != 2045 )
          {
            return 0;
          }
        }
        else if ( nLimitId < 2039 && nLimitId != 2028 && nLimitId != 2032 && nLimitId != 2026 )
        {
          return 0;
        }
        return 1;
      }
      if ( nLimitId >= 2019 )
        return 1;
      if ( nLimitId <= 1925 )
        return nLimitId >= 1924 || nLimitId == 1913 || nLimitId == 1915;
      if ( nLimitId == 2013 )
        return 1;
      if ( nLimitId <= 2013 )
        return nLimitId == 2005;
      if ( (unsigned int)(nLimitId - 2015) <= 1 )
        return 1;
    }
  }
  else
  {
    if ( nLimitId >= 1906 )
      return 1;
    if ( nLimitId > 1132 )
    {
      if ( nLimitId > 1413 )
      {
        if ( nLimitId != 1615 )
        {
          if ( nLimitId > 1615 )
          {
            if ( nLimitId > 1637 )
            {
              if ( nLimitId != 1904 )
                return 0;
            }
            else if ( nLimitId < 1632 && nLimitId != 1626 )
            {
              return 0;
            }
          }
          else if ( nLimitId > 1606 )
          {
            if ( nLimitId != 1608 )
              return 0;
          }
          else if ( nLimitId < 1605 && nLimitId != 1601 )
          {
            return 0;
          }
        }
        return 1;
      }
      if ( nLimitId >= 1408 || nLimitId == 1157 )
        return 1;
      if ( nLimitId <= 1157 )
        return nLimitId >= 1147 && (nLimitId <= 1148 || (unsigned int)(nLimitId - 1150) <= 5);
      if ( nLimitId <= 1164 )
        return nLimitId >= 1163 || nLimitId == 1160;
      if ( (unsigned int)(nLimitId - 1403) <= 1 )
        return 1;
    }
    else
    {
      if ( nLimitId >= 1131 || nLimitId == 1066 )
        return 1;
      if ( nLimitId > 1066 )
      {
        if ( nLimitId > 1116 )
        {
          if ( nLimitId != 1119 && (nLimitId < 1119 || (unsigned int)(nLimitId - 1127) > 1) )
            return 0;
        }
        else if ( nLimitId < 1115 && (nLimitId < 1075 || nLimitId > 1076 && (unsigned int)(nLimitId - 1082) > 1) )
        {
          return 0;
        }
        return 1;
      }
      if ( nLimitId == 1034 )
        return 1;
      if ( nLimitId > 1034 )
      {
        if ( nLimitId == 1051 )
          return 1;
        if ( nLimitId <= 1051 )
          return nLimitId == 1039;
        if ( (unsigned int)(nLimitId - 1063) <= 1 )
          return 1;
      }
      else
      {
        if ( nLimitId == 1028 )
          return 1;
        if ( nLimitId <= 1028 )
          return nLimitId == 4;
        if ( (unsigned int)(nLimitId - 1030) <= 1 )
          return 1;
      }
    }
  }
  return 0;
}


