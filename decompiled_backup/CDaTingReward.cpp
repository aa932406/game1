// Decompiled methods for class: CDaTingReward
// Source: gameserver.cc
// Total methods: 31

#####################################
void __cdecl CDaTingReward::~CDaTingReward(CDaTingReward *const this)
{
  CDaTingReward::~CDaTingReward(this);
  operator delete(this);
}


#####################################
void __cdecl CDaTingReward::GetInterestsProtocol(CDaTingReward *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+10h] [rbp-10h] BYREF
  unsigned __int16 v3; // [rsp+12h] [rbp-Eh] BYREF
  unsigned __int16 v4; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v5; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v6; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v7; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v8; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v9; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 874;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 875;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 876;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 877;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 878;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 879;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 883;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 884;
  std::list<unsigned short>::push_back(procList, &v9);
}


#####################################
void __cdecl CDaTingReward::OnDaySwitch(CDaTingReward *const this, int32_t nDiffDays)
{
  char v2; // r12
  char v3; // r13
  char v4; // r14
  bool v5; // al
  bool v6; // r15
  CfgData *v7; // rax
  const PlatformDaTingMap *PlatformDaTingMap; // rax
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v9; // rax
  bool v10; // bl
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v11; // rax
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v12; // rax
  bool v13; // bl
  CfgData *v14; // rax
  const PlatformDaTingMap *v15; // rax
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v16; // rax
  bool v17; // bl
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v18; // rax
  std::pair<const std::pair<std::string,int>,PlatformDaTing> *v19; // rax
  PlatformDaTingMap DaTingCfgTable; // [rsp+20h] [rbp-120h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > it_0; // [rsp+50h] [rbp-F0h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > it; // [rsp+60h] [rbp-E0h] BYREF
  std::string __lhs; // [rsp+70h] [rbp-D0h] BYREF
  std::string v24; // [rsp+80h] [rbp-C0h] BYREF
  std::string v25; // [rsp+90h] [rbp-B0h] BYREF
  std::string v26; // [rsp+A0h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > __x; // [rsp+B0h] [rbp-90h] BYREF
  std::string __rhs; // [rsp+C0h] [rbp-80h] BYREF
  std::string v29; // [rsp+D0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > v30; // [rsp+E0h] [rbp-60h] BYREF
  std::string v31; // [rsp+F0h] [rbp-50h] BYREF
  int32_t NewRecord; // [rsp+100h] [rbp-40h]
  int32_t Record; // [rsp+104h] [rbp-3Ch]
  int32_t NewRecord_0; // [rsp+108h] [rbp-38h]
  int32_t Record_0; // [rsp+10Ch] [rbp-34h]

  if ( this->m_pPlayer )
  {
    v2 = 0;
    v3 = 0;
    v4 = 0;
    Player::GetPlatform((const Player *const)&__lhs);
    v5 = 1;
    if ( !std::operator==<char>(&__lhs, "yilewan") )
    {
      Player::GetPlatform((const Player *const)&v24);
      v2 = 1;
      if ( !std::operator==<char>(&v24, "wan_993h") )
      {
        Player::GetPlatform((const Player *const)&v25);
        v3 = 1;
        if ( !std::operator==<char>(&v25, "liebao_993h") )
        {
          Player::GetPlatform((const Player *const)&v26);
          v4 = 1;
          if ( !std::operator==<char>(&v26, "37wan") )
            v5 = 0;
        }
      }
    }
    v6 = v5;
    if ( v4 )
      std::string::~string(&v26);
    if ( v3 )
      std::string::~string(&v25);
    if ( v2 )
      std::string::~string(&v24);
    std::string::~string(&__lhs);
    if ( v6 )
    {
      NewRecord = 0;
      Record = Player::getRecord(this->m_pPlayer, 1106);
      v7 = Answer::Singleton<CfgData>::instance();
      PlatformDaTingMap = CfgData::GetPlatformDaTingMap(v7);
      std::map<std::pair<std::string,int>,PlatformDaTing>::map(&DaTingCfgTable, PlatformDaTingMap);
      for ( it._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::begin(&DaTingCfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::end(&DaTingCfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator!=(&it, &__x) )
          break;
        Player::GetPlatform((const Player *const)&__rhs);
        v9 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it);
        v10 = std::operator!=<char>((const std::string *const)v9 + 2, &__rhs);
        std::string::~string(&__rhs);
        if ( !v10
          && *((_DWORD *)std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
             + 7) != 7 )
        {
          v11 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it);
          if ( ((Record >> *((_DWORD *)v11 + 6)) & 1) != 0 )
          {
            v12 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it);
            NewRecord |= 1 << *((_DWORD *)v12 + 6);
          }
        }
      }
      Player::updateRecord(this->m_pPlayer, 1106, NewRecord);
      std::map<std::pair<std::string,int>,PlatformDaTing>::~map(&DaTingCfgTable);
    }
    Player::GetPlatform((const Player *const)&v29);
    v13 = std::operator==<char>(&v29, "pdsso");
    std::string::~string(&v29);
    if ( v13 )
    {
      NewRecord_0 = 0;
      Record_0 = Player::getRecord(this->m_pPlayer, 1106);
      v14 = Answer::Singleton<CfgData>::instance();
      v15 = CfgData::GetPlatformDaTingMap(v14);
      std::map<std::pair<std::string,int>,PlatformDaTing>::map(&DaTingCfgTable, v15);
      for ( it_0._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::begin(&DaTingCfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator++(&it_0, 0) )
      {
        v30._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::end(&DaTingCfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator!=(
                &it_0,
                &v30) )
          break;
        Player::GetPlatform((const Player *const)&v31);
        v16 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it_0);
        v17 = std::operator!=<char>((const std::string *const)v16 + 2, &v31);
        std::string::~string(&v31);
        if ( !v17
          && *((_DWORD *)std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it_0)
             + 7) != 2 )
        {
          v18 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it_0);
          if ( ((Record_0 >> *((_DWORD *)v18 + 6)) & 1) != 0 )
          {
            v19 = std::_Rb_tree_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it_0);
            NewRecord_0 |= 1 << *((_DWORD *)v19 + 6);
          }
        }
      }
      Player::updateRecord(this->m_pPlayer, 1106, NewRecord_0);
      std::map<std::pair<std::string,int>,PlatformDaTing>::~map(&DaTingCfgTable);
    }
    CDaTingReward::SendDaTingInfo(this);
    CDaTingReward::SendDaTingIcon(this);
    CDaTingReward::SendMiniClientIcon(this);
    CDaTingReward::SendMiniClientInfo(this);
  }
}


#####################################
int32_t __cdecl CDaTingReward::DispatchNetDatas(
        CDaTingReward *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x36Au:
      result = CDaTingReward::onRequestDaTingInfo(this, inPacket);
      break;
    case 0x36Bu:
      result = CDaTingReward::onGetDaTingReward(this, inPacket);
      break;
    case 0x36Cu:
      result = CDaTingReward::onFromDaTing(this, inPacket);
      break;
    case 0x36Du:
      result = CDaTingReward::onRequestPlatformVipInfo(this, inPacket);
      break;
    case 0x36Eu:
      result = CDaTingReward::onGetPlatformVipReward(this, inPacket);
      break;
    case 0x36Fu:
      result = CDaTingReward::onGetPlatformReward(this, inPacket);
      break;
    case 0x373u:
      result = CDaTingReward::onGetMiniClientReward(this, inPacket);
      break;
    case 0x374u:
      result = CDaTingReward::onRequestMiniClientInfo(this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
bool __cdecl CDaTingReward::HaveDaTingReward(CDaTingReward *const this)
{
  CfgData *v2; // rax
  std::string p_Platform; // [rsp+10h] [rbp-20h] BYREF
  PlatformDaTing *pDaTing; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  Player::GetPlatform((const Player *const)&p_Platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pDaTing = CfgData::GetGetPlatformDaTingCfg(v2, &p_Platform, 1);
  std::string::~string(&p_Platform);
  return pDaTing != 0;
}


#####################################
void __cdecl CDaTingReward::SendDaTingInfo(CDaTingReward *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t ContinueLoginCount; // edx
  int32_t PlatformVipLevel; // edx
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && CDaTingReward::HaveDaTingReward(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D17u);
    if ( packet )
    {
      ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ContinueLoginCount);
      PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
      Answer::NetPacket::writeInt32(packet, PlatformVipLevel);
      Record = Player::getRecord(this->m_pPlayer, 1106);
      Answer::NetPacket::writeInt32(packet, Record);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CDaTingReward::GetDaTingIconState(CDaTingReward *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CDaTingReward::HaveDaTingReward(this) )
  {
    if ( this->m_pPlayer )
    {
      CDaTingReward::GetDaTingIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CDaTingReward::SendDaTingIcon(CDaTingReward *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CDaTingReward::HaveDaTingReward(this) )
    {
      CDaTingReward::GetDaTingIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
bool __cdecl CDaTingReward::NeedDaTing(CDaTingReward *const this)
{
  bool v2; // bl
  bool v3; // bl
  bool v4; // bl
  bool v5; // bl
  std::string __lhs; // [rsp+10h] [rbp-50h] BYREF
  std::string v7; // [rsp+20h] [rbp-40h] BYREF
  std::string v8; // [rsp+30h] [rbp-30h] BYREF
  std::string v9; // [rsp+40h] [rbp-20h] BYREF

  if ( !this->m_pPlayer )
    return 1;
  Player::GetPlatform((const Player *const)&__lhs);
  v2 = std::operator==<char>(&__lhs, "yilewan");
  std::string::~string(&__lhs);
  if ( v2 )
    return 0;
  Player::GetPlatform((const Player *const)&v7);
  v3 = std::operator==<char>(&v7, "wan_993h");
  std::string::~string(&v7);
  if ( v3 )
    return 0;
  Player::GetPlatform((const Player *const)&v8);
  v4 = std::operator==<char>(&v8, "liebao_993h");
  std::string::~string(&v8);
  if ( v4 )
    return 0;
  Player::GetPlatform((const Player *const)&v9);
  v5 = std::operator==<char>(&v9, "douyu_993h");
  std::string::~string(&v9);
  return !v5;
}


#####################################
int32_t __cdecl CDaTingReward::HaveDaTingLeftGift(CDaTingReward *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const PlatformDaTingMap *PlatformDaTingMap; // rax
  const std::pair<const std::pair<std::string,int>,PlatformDaTing> *v4; // rax
  bool v5; // bl
  int v6; // ecx
  int32_t ContinueLoginCount; // ebx
  int v8; // ebx
  int32_t PlatformVipLevel; // ebx
  int32_t v10; // ebx
  int32_t v11; // ebx
  PlatformDaTingMap DaTingMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformDaTing> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::string __rhs; // [rsp+60h] [rbp-20h] BYREF
  int32_t Count; // [rsp+68h] [rbp-18h]
  int32_t Record; // [rsp+6Ch] [rbp-14h]

  if ( CDaTingReward::NeedDaTing(this) && !this->m_IsDaTingLogin )
    return 0;
  Count = 0;
  Record = Player::getRecord(this->m_pPlayer, 1106);
  v2 = Answer::Singleton<CfgData>::instance();
  PlatformDaTingMap = CfgData::GetPlatformDaTingMap(v2);
  std::map<std::pair<std::string,int>,PlatformDaTing>::map(&DaTingMap, PlatformDaTingMap);
  for ( it._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::begin(&DaTingMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<std::pair<std::string,int>,PlatformDaTing>::end(&DaTingMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator!=(
            &it,
            &__x) )
      break;
    Player::GetPlatform((const Player *const)&__rhs);
    v4 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it);
    v5 = std::operator!=<char>((const std::string *const)v4 + 2, &__rhs);
    std::string::~string(&__rhs);
    if ( !v5 )
    {
      v6 = *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
           + 6);
      if ( ((Record >> v6) & 1) == 0 )
      {
        switch ( *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                 + 7) )
        {
          case 1:
            ++Count;
            break;
          case 2:
            ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
            if ( ContinueLoginCount >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                                       + 8) )
              ++Count;
            break;
          case 3:
            v8 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
            if ( v8 >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                       + 8) )
              ++Count;
            break;
          case 6:
            PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
            if ( PlatformVipLevel >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                                     + 8) )
              ++Count;
            break;
          case 7:
            v10 = CDaTingReward::GetPlatformVipLevel(this);
            if ( v10 >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                        + 8) )
            {
              v11 = CDaTingReward::GetPlatformVipLevel(this);
              if ( v11 <= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformDaTing>>::operator->(&it)
                          + 17) )
                ++Count;
            }
            break;
          default:
            continue;
        }
      }
    }
  }
  v1 = Count;
  std::map<std::pair<std::string,int>,PlatformDaTing>::~map(&DaTingMap);
  return v1;
}


#####################################
int32_t __cdecl CDaTingReward::onRequestDaTingInfo(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  CDaTingReward::SendDaTingInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CDaTingReward::onGetDaTingReward(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  int32_t v3; // ebx
  CfgData *v4; // rax
  int32_t ContinueLoginCount; // eax
  int32_t v6; // eax
  int32_t PlatformVipLevel; // eax
  int32_t v8; // eax
  int32_t v9; // eax
  int32_t v11; // eax
  int32_t v12; // eax
  MemChrBagVector *p_vItems; // rbx
  CExtCharBag *Bag; // rax
  std::string p_Platform; // [rsp+10h] [rbp-30h] BYREF
  int8_t Index; // [rsp+1Fh] [rbp-21h]
  PlatformDaTing *pDaTing; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( CDaTingReward::NeedDaTing(this) && !this->m_IsDaTingLogin )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Index;
  Player::GetPlatform((const Player *const)&p_Platform);
  v4 = Answer::Singleton<CfgData>::instance();
  pDaTing = CfgData::GetGetPlatformDaTingCfg(v4, &p_Platform, v3);
  std::string::~string(&p_Platform);
  if ( !pDaTing )
    return 2;
  switch ( pDaTing->nType )
  {
    case 1:
    case 9:
      goto LABEL_29;
    case 2:
      ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
      if ( ContinueLoginCount >= pDaTing->nParam )
        goto LABEL_29;
      result = 2;
      break;
    case 3:
      v6 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      if ( v6 >= pDaTing->nParam )
        goto LABEL_29;
      result = 2;
      break;
    case 6:
      PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
      if ( PlatformVipLevel >= pDaTing->nParam )
        goto LABEL_29;
      result = 2;
      break;
    case 7:
      v8 = CDaTingReward::GetPlatformVipLevel(this);
      if ( v8 >= pDaTing->nParam )
      {
        v9 = CDaTingReward::GetPlatformVipLevel(this);
        if ( v9 <= pDaTing->nParam2 )
          goto LABEL_29;
      }
      result = 2;
      break;
    case 8:
      v11 = CDaTingReward::GetPlatformVipLevel(this);
      if ( v11 < pDaTing->nParam || (v12 = CDaTingReward::GetPlatformVipLevel(this), v12 > pDaTing->nParam2) )
      {
        result = 2;
      }
      else
      {
LABEL_29:
        OldRecord = Player::getRecord(this->m_pPlayer, 1106);
        NewRecord = OldRecord | (1 << Index);
        if ( OldRecord == NewRecord )
        {
          result = 2;
        }
        else
        {
          p_vItems = &pDaTing->vItems;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::AddItem(Bag, p_vItems, ITEM_CHANGE_REASON::IDCR_PALTFORM_DA_TING) )
          {
            result = 2;
          }
          else
          {
            Player::updateRecord(this->m_pPlayer, 1106, NewRecord);
            CDaTingReward::SendDaTingInfo(this);
            CDaTingReward::SendDaTingIcon(this);
            result = 0;
          }
        }
      }
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CDaTingReward::onFromDaTing(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer )
    return 10002;
  this->m_IsDaTingLogin = 1;
  CDaTingReward::SendDaTingIcon(this);
  Player::RecalcAttr(this->m_pPlayer);
  return 0;
}


#####################################
void __cdecl CDaTingReward::SendPlatformVipInfo(CDaTingReward *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t PlatformVipLevel; // edx
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && CDaTingReward::HavePlatformVipReward(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D18u);
    if ( packet )
    {
      PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
      Answer::NetPacket::writeInt32(packet, PlatformVipLevel);
      Record = Player::getRecord(this->m_pPlayer, 1107);
      Answer::NetPacket::writeInt32(packet, Record);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CDaTingReward::GetPlatformVipIconState(CDaTingReward *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CDaTingReward::HavePlatformVipReward(this) )
  {
    if ( this->m_pPlayer )
    {
      CDaTingReward::GetPlatformVipIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CDaTingReward::SendPlatformVipIcon(CDaTingReward *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CDaTingReward::HavePlatformVipReward(this) )
    {
      CDaTingReward::GetPlatformVipIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
int32_t __cdecl CDaTingReward::HavePlatformVipLeftGift(CDaTingReward *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const PlatformVipMap *PlatformVipMap; // rax
  const std::pair<const std::pair<std::string,int>,PlatformVip> *v4; // rax
  bool v5; // bl
  const std::pair<const std::pair<std::string,int>,PlatformVip> *v6; // rax
  int32_t PlatformVipLevel; // ebx
  PlatformVipMap VipMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformVip> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformVip> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::string __rhs; // [rsp+60h] [rbp-20h] BYREF
  int32_t Count; // [rsp+68h] [rbp-18h]
  int32_t Record; // [rsp+6Ch] [rbp-14h]

  if ( !this->m_IsDaTingLogin )
    return 0;
  Count = 0;
  Record = Player::getRecord(this->m_pPlayer, 1107);
  v2 = Answer::Singleton<CfgData>::instance();
  PlatformVipMap = CfgData::GetPlatformVipMap(v2);
  std::map<std::pair<std::string,int>,PlatformVip>::map(&VipMap, PlatformVipMap);
  for ( it._M_node = std::map<std::pair<std::string,int>,PlatformVip>::begin(&VipMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformVip>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<std::pair<std::string,int>,PlatformVip>::end(&VipMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformVip>>::operator!=(&it, &__x) )
      break;
    Player::GetPlatform((const Player *const)&__rhs);
    v4 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformVip>>::operator->(&it);
    v5 = std::operator!=<char>((const std::string *const)v4 + 2, &__rhs);
    std::string::~string(&__rhs);
    if ( !v5 )
    {
      v6 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformVip>>::operator->(&it);
      if ( ((Record >> *((_DWORD *)v6 + 6)) & 1) == 0 )
      {
        PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
        if ( PlatformVipLevel >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformVip>>::operator->(&it)
                                 + 7) )
          ++Count;
      }
    }
  }
  v1 = Count;
  std::map<std::pair<std::string,int>,PlatformVip>::~map(&VipMap);
  return v1;
}


#####################################
bool __cdecl CDaTingReward::HavePlatformVipReward(CDaTingReward *const this)
{
  CfgData *v2; // rax
  std::string p_Platform; // [rsp+10h] [rbp-20h] BYREF
  PlatformVip *pVip; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  Player::GetPlatform((const Player *const)&p_Platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pVip = CfgData::GetGetPlatformVipCfg(v2, &p_Platform, 1);
  std::string::~string(&p_Platform);
  return pVip != 0;
}


#####################################
int32_t __cdecl CDaTingReward::GetPlatformVipLevel(CDaTingReward *const this)
{
  CVplan *Vplan; // rax

  if ( !this->m_pPlayer )
    return 0;
  Vplan = Player::GetVplan(this->m_pPlayer);
  return CVplan::GetPlatformVipLevel(Vplan);
}


#####################################
int32_t __cdecl CDaTingReward::onRequestPlatformVipInfo(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  CDaTingReward::SendPlatformVipInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CDaTingReward::onGetPlatformVipReward(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  int32_t PlatformVipLevel; // eax
  MemChrBagVector *p_vItem; // rbx
  CExtCharBag *Bag; // rax
  std::string p_Platform; // [rsp+10h] [rbp-30h] BYREF
  int8_t Index; // [rsp+1Fh] [rbp-21h]
  PlatformVip *pVip; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Index;
  Player::GetPlatform((const Player *const)&p_Platform);
  v4 = Answer::Singleton<CfgData>::instance();
  pVip = CfgData::GetGetPlatformVipCfg(v4, &p_Platform, v3);
  std::string::~string(&p_Platform);
  if ( !pVip )
    return 2;
  PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
  if ( PlatformVipLevel < pVip->nNeedVipLevel )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1107);
  NewRecord = OldRecord | (1 << Index);
  if ( OldRecord == NewRecord )
    return 2;
  p_vItem = &pVip->vItem;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vItem, ITEM_CHANGE_REASON::IDCR_PALTFORM_VIP) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1107, NewRecord);
  CDaTingReward::SendPlatformVipInfo(this);
  CDaTingReward::SendPlatformVipIcon(this);
  return 0;
}


#####################################
void __cdecl CDaTingReward::GetPlatformRewardIconState(CDaTingReward *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  const PlatformRewardCfgMap *PlatformRewardCfgMap; // rax
  const std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *v4; // rax
  bool v5; // bl
  const std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *v6; // rax
  const std::pair<const std::pair<std::string,int>,PlatformRewardCfg> *v8; // rax
  PlatformRewardCfgMap PlatformRewardMap; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformRewardCfg> > it; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,PlatformRewardCfg> > v11; // [rsp+50h] [rbp-50h] BYREF
  std::string __rhs; // [rsp+60h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+70h] [rbp-30h] BYREF
  int32_t OldRecord; // [rsp+8Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    OldRecord = Player::getRecord(this->m_pPlayer, 1904);
    v2 = Answer::Singleton<CfgData>::instance();
    PlatformRewardCfgMap = CfgData::GetPlatformRewardCfgMap(v2);
    std::map<std::pair<std::string,int>,PlatformRewardCfg>::map(&PlatformRewardMap, PlatformRewardCfgMap);
    for ( it._M_node = std::map<std::pair<std::string,int>,PlatformRewardCfg>::begin(&PlatformRewardMap)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator++(
            &it,
            0) )
    {
      v11._M_node = std::map<std::pair<std::string,int>,PlatformRewardCfg>::end(&PlatformRewardMap)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator!=(
              &it,
              &v11) )
        break;
      Player::GetPlatform((const Player *const)&__rhs);
      v4 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator->(&it);
      v5 = std::operator!=<char>((const std::string *const)v4 + 7, &__rhs);
      std::string::~string(&__rhs);
      if ( !v5 )
      {
        if ( *((int *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator->(&it)
             + 16) > 0
          || (v6 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator->(&it),
              ((OldRecord >> (*((_BYTE *)v6 + 16) - 1)) & 1) != 1) )
        {
          v8 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,PlatformRewardCfg>>::operator->(&it);
          CDaTingReward::GetPlatformRewardIconStu(&__x, this, *((_DWORD *)v8 + 12), 1);
          std::list<ShowIcon>::push_back(IconList, &__x);
        }
      }
    }
    std::map<std::pair<std::string,int>,PlatformRewardCfg>::~map(&PlatformRewardMap);
  }
}


#####################################
void __cdecl CDaTingReward::SendPlatformRewardIcon(CDaTingReward *const this, int32_t nId)
{
  ShowIcon stu; // [rsp+10h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    CDaTingReward::GetPlatformRewardIconStu(&stu, this, nId, 0);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
int32_t __cdecl CDaTingReward::onGetPlatformReward(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  MemChrBagVector *p_vItem; // rbx
  CExtCharBag *Bag; // rax
  std::string p_Platform; // [rsp+10h] [rbp-30h] BYREF
  int32_t Index; // [rsp+1Ch] [rbp-24h]
  PlatformRewardCfg *pPlatformReward; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  Player::GetPlatform((const Player *const)&p_Platform);
  v3 = Answer::Singleton<CfgData>::instance();
  pPlatformReward = CfgData::GetGetPlatformRewardCfg(v3, &p_Platform, Index);
  std::string::~string(&p_Platform);
  if ( !pPlatformReward )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1904);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  p_vItem = &pPlatformReward->vItem;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vItem, ITEM_CHANGE_REASON::IDCR_PLATFORM_REWARD) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1904, NewRecord);
  if ( pPlatformReward->nIsAllShow <= 0 )
    CDaTingReward::SendPlatformRewardIcon(this, pPlatformReward->nIcon);
  return 0;
}


#####################################
void __cdecl CDaTingReward::GetMiniClientIconState(CDaTingReward *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CDaTingReward::HaveMiniClientReward(this) )
  {
    if ( this->m_pPlayer )
    {
      CDaTingReward::GetMiniClientStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CDaTingReward::SendMiniClientIcon(CDaTingReward *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CDaTingReward::HaveMiniClientReward(this) )
    {
      CDaTingReward::GetMiniClientStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CDaTingReward::SendMiniClientInfo(CDaTingReward *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t ContinueLoginCount; // edx
  int32_t PlatformVipLevel; // edx
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && CDaTingReward::HaveMiniClientReward(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D19u);
    if ( packet )
    {
      ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ContinueLoginCount);
      PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
      Answer::NetPacket::writeInt32(packet, PlatformVipLevel);
      Record = Player::getRecord(this->m_pPlayer, 1108);
      Answer::NetPacket::writeInt32(packet, Record);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CDaTingReward::HaveMiniClientLeftGift(CDaTingReward *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const MiniClientCfgMap *v3; // rax
  const std::pair<const std::pair<std::string,int>,MiniClientCfg> *v4; // rax
  bool v5; // bl
  int v6; // ecx
  int32_t ContinueLoginCount; // ebx
  int v8; // ebx
  int32_t PlatformVipLevel; // ebx
  int32_t v10; // ebx
  int32_t v11; // ebx
  int32_t v13; // ebx
  int32_t v14; // ebx
  MiniClientCfgMap MiniClientMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<std::string,int>,MiniClientCfg> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::string __rhs; // [rsp+60h] [rbp-20h] BYREF
  int32_t Count; // [rsp+68h] [rbp-18h]
  int32_t Record; // [rsp+6Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  if ( !Player::IsMiniClient(this->m_pPlayer) )
    return 0;
  Count = 0;
  Record = Player::getRecord(this->m_pPlayer, 1108);
  v2 = Answer::Singleton<CfgData>::instance();
  v3 = CfgData::GetMiniClientMap(v2);
  std::map<std::pair<std::string,int>,MiniClientCfg>::map(&MiniClientMap, v3);
  for ( it._M_node = std::map<std::pair<std::string,int>,MiniClientCfg>::begin(&MiniClientMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<std::pair<std::string,int>,MiniClientCfg>::end(&MiniClientMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator!=(&it, &__x) )
      break;
    Player::GetPlatform((const Player *const)&__rhs);
    v4 = std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it);
    v5 = std::operator!=<char>((const std::string *const)v4 + 2, &__rhs);
    std::string::~string(&__rhs);
    if ( !v5 )
    {
      v6 = *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
           + 6);
      if ( ((Record >> v6) & 1) == 0 )
      {
        switch ( *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                 + 7) )
        {
          case 1:
            ++Count;
            break;
          case 2:
            ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
            if ( ContinueLoginCount >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                                       + 8) )
              ++Count;
            break;
          case 3:
            v8 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
            if ( v8 >= *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                       + 8) )
              ++Count;
            break;
          case 6:
            PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
            if ( PlatformVipLevel < *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                                    + 8) )
              ++Count;
            break;
          case 7:
            v10 = CDaTingReward::GetPlatformVipLevel(this);
            if ( v10 < *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                       + 8)
              || (v11 = CDaTingReward::GetPlatformVipLevel(this),
                  v11 > *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                        + 17)) )
            {
              ++Count;
            }
            break;
          case 8:
            v13 = CDaTingReward::GetPlatformVipLevel(this);
            if ( v13 < *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                       + 8)
              || (v14 = CDaTingReward::GetPlatformVipLevel(this),
                  v14 > *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<std::string,int>,MiniClientCfg>>::operator->(&it)
                        + 17)) )
            {
              ++Count;
            }
            break;
          default:
            continue;
        }
      }
    }
  }
  v1 = Count;
  std::map<std::pair<std::string,int>,MiniClientCfg>::~map(&MiniClientMap);
  return v1;
}


#####################################
bool __cdecl CDaTingReward::HaveMiniClientReward(CDaTingReward *const this)
{
  CfgData *v2; // rax
  std::string p_Platform; // [rsp+10h] [rbp-20h] BYREF
  MiniClientCfg *pMiniClientCfg; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  Player::GetPlatform((const Player *const)&p_Platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pMiniClientCfg = CfgData::GetMiniClientCfg(v2, &p_Platform, 1);
  std::string::~string(&p_Platform);
  return pMiniClientCfg != 0;
}


#####################################
int32_t __cdecl CDaTingReward::onRequestMiniClientInfo(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  CDaTingReward::SendMiniClientInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CDaTingReward::onGetMiniClientReward(CDaTingReward *const this, Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  int32_t v3; // ebx
  CfgData *v4; // rax
  int32_t ContinueLoginCount; // eax
  int32_t v6; // eax
  int32_t PlatformVipLevel; // eax
  int32_t v8; // eax
  int32_t v9; // eax
  MemChrBagVector *p_vItems; // rbx
  CExtCharBag *Bag; // rax
  std::string p_Platform; // [rsp+10h] [rbp-30h] BYREF
  int8_t Index; // [rsp+1Fh] [rbp-21h]
  MiniClientCfg *pMiniClientCfg; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !Player::IsMiniClient(this->m_pPlayer) )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Index;
  Player::GetPlatform((const Player *const)&p_Platform);
  v4 = Answer::Singleton<CfgData>::instance();
  pMiniClientCfg = CfgData::GetMiniClientCfg(v4, &p_Platform, v3);
  std::string::~string(&p_Platform);
  if ( !pMiniClientCfg )
    return 2;
  switch ( pMiniClientCfg->nType )
  {
    case 1:
      goto LABEL_22;
    case 2:
      ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
      if ( ContinueLoginCount >= pMiniClientCfg->nParam )
        goto LABEL_22;
      result = 2;
      break;
    case 3:
      v6 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      if ( v6 >= pMiniClientCfg->nParam )
        goto LABEL_22;
      result = 2;
      break;
    case 6:
      PlatformVipLevel = CDaTingReward::GetPlatformVipLevel(this);
      if ( PlatformVipLevel >= pMiniClientCfg->nParam )
        goto LABEL_22;
      result = 2;
      break;
    case 7:
      v8 = CDaTingReward::GetPlatformVipLevel(this);
      if ( v8 < pMiniClientCfg->nParam || (v9 = CDaTingReward::GetPlatformVipLevel(this), v9 > pMiniClientCfg->nParam2) )
      {
        result = 2;
      }
      else
      {
LABEL_22:
        OldRecord = Player::getRecord(this->m_pPlayer, 1108);
        NewRecord = OldRecord | (1 << Index);
        if ( OldRecord == NewRecord )
        {
          result = 2;
        }
        else
        {
          p_vItems = &pMiniClientCfg->vItems;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::AddItem(Bag, p_vItems, ITEM_CHANGE_REASON::IDCR_PALTFORM_DA_TING) )
          {
            result = 2;
          }
          else
          {
            Player::updateRecord(this->m_pPlayer, 1108, NewRecord);
            CDaTingReward::SendMiniClientInfo(this);
            CDaTingReward::SendMiniClientIcon(this);
            result = 0;
          }
        }
      }
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


