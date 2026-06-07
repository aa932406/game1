// Decompiled methods for class: CExtCharTitle
// Source: gameserver.cc
// Total methods: 28

#####################################
void __cdecl CExtCharTitle::~CExtCharTitle(CExtCharTitle *const this)
{
  CExtCharTitle::~CExtCharTitle(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharTitle::Init(CExtCharTitle *const this, Player *pPlayer)
{
  CExtSystemBase::Init(this, pPlayer);
  CExtCharTitle::initTitleMap(this);
}


#####################################
void __cdecl CExtCharTitle::OnCleanUp(CExtCharTitle *const this)
{
  this->m_nDressTitle = 0;
  this->m_nDressNormalTitle = 0;
  this->m_nBattleRankTop = 0;
  this->m_bShowActivityTitle = 0;
  this->m_LastUpdateTick = 0;
  bzero(this->m_vDress, 0x18u);
  bzero(this->m_vActivityTitle, 0xCu);
  CExtCharTitle::resetTitleMap(this);
}


#####################################
void __cdecl CExtCharTitle::GetInterestsProtocol(CExtCharTitle *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 860;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 861;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtCharTitle::DispatchNetDatas(
        CExtCharTitle *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( !CExtCharTitle::IsFunctionOpen(this) )
    return 10002;
  if ( nProcId == 860 )
    return CExtCharTitle::onDressTitle(this, inPacket);
  if ( nProcId == 861 )
    return CExtCharTitle::onUnDressTitle(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTitle::onDressTitle(CExtCharTitle *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  int32_t nId; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( !CExtCharTitle::dressTitle(this, nId) )
    return 10002;
  CExtCharTitle::unHideTitle(this, nId);
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Player::setSyncStatusFlag(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, nId);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTitle::onUnDressTitle(CExtCharTitle *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  int32_t nId; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( !CExtCharTitle::unDressTitle(this, nId) )
    return 10002;
  CExtCharTitle::hideTitle(this, nId);
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Player::setSyncStatusFlag(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, nId);
  return 0;
}


#####################################
bool __cdecl CExtCharTitle::dressTitle(CExtCharTitle *const this, int32_t nId)
{
  int32_t m_nDressTitle; // ebx
  std::pair<const int,CharTitle> *v4; // rax
  int32_t Priority; // ebx
  int32_t v7; // ebx
  std::pair<const int,CharTitle> *v8; // rax
  int32_t nIda; // [rsp+4h] [rbp-5Ch] BYREF
  CExtCharTitle *thisa; // [rsp+8h] [rbp-58h]
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-40h] BYREF
  CharTitle *title; // [rsp+30h] [rbp-30h]
  int32_t i; // [rsp+3Ch] [rbp-24h]
  CharTitle *pTitle; // [rsp+40h] [rbp-20h]
  int32_t j; // [rsp+4Ch] [rbp-14h]

  thisa = this;
  nIda = nId;
  iter._M_node = std::map<int,CharTitle>::find(&this->m_mCharTitle, &nIda)._M_node;
  __x._M_node = std::map<int,CharTitle>::end(&thisa->m_mCharTitle)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator==(&iter, &__x) )
    return 0;
  title = &std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
  if ( thisa->m_nDressTitle > 2 )
    return 0;
  if ( !CharTitle::IsSpecialTitle(title) && thisa->m_nDressNormalTitle > 0 )
    return 0;
  if ( !CharTitle::Dress(title) )
    return 0;
  if ( !CharTitle::IsSpecialTitle(title) )
  {
    m_nDressTitle = thisa->m_nDressTitle;
    v4 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
    thisa->m_vDress[m_nDressTitle] = &v4->second;
    ++thisa->m_nDressNormalTitle;
  }
  else
  {
    for ( i = 0; thisa->m_nDressTitle > i; ++i )
    {
      pTitle = thisa->m_vDress[i];
      if ( !pTitle )
        break;
      Priority = CharTitle::GetPriority(title);
      if ( Priority < CharTitle::GetPriority(pTitle) || !CharTitle::IsSpecialTitle(pTitle) )
      {
        for ( j = thisa->m_nDressTitle; j > i; --j )
          thisa->m_vDress[j] = (CharTitle *)*((_QWORD *)&thisa->m_pPlayer + j);
        break;
      }
    }
    v7 = i;
    v8 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
    thisa->m_vDress[v7] = &v8->second;
  }
  ++thisa->m_nDressTitle;
  return 1;
}


#####################################
bool __cdecl CExtCharTitle::unDressTitle(CExtCharTitle *const this, int32_t nId)
{
  int32_t Id; // eax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CExtCharTitle *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-30h] BYREF
  CharTitle *title; // [rsp+30h] [rbp-20h]
  int32_t i; // [rsp+3Ch] [rbp-14h]
  CharTitle *pTitle; // [rsp+40h] [rbp-10h]
  int32_t j; // [rsp+4Ch] [rbp-4h]

  thisa = this;
  nIda = nId;
  iter._M_node = std::map<int,CharTitle>::find(&this->m_mCharTitle, &nIda)._M_node;
  __x._M_node = std::map<int,CharTitle>::end(&thisa->m_mCharTitle)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator==(&iter, &__x) )
    return 0;
  title = &std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
  if ( !CharTitle::UnDress(title) )
    return 0;
  for ( i = 0; thisa->m_nDressTitle > i; ++i )
  {
    pTitle = thisa->m_vDress[i];
    if ( pTitle )
    {
      Id = CharTitle::GetId(pTitle);
      if ( Id == nIda )
      {
        for ( j = i; thisa->m_nDressTitle - 1 > j; ++j )
          thisa->m_vDress[j] = thisa->m_vDress[j + 1];
        *((_QWORD *)&thisa->m_pPlayer + thisa->m_nDressTitle) = 0;
        break;
      }
    }
  }
  --thisa->m_nDressTitle;
  if ( !CharTitle::IsSpecialTitle(title) )
    --thisa->m_nDressNormalTitle;
  return 1;
}


#####################################
void __cdecl CExtCharTitle::SendTitleInfo(CExtCharTitle *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Id; // eax
  int8_t State; // al
  int32_t CardTitleParams; // eax
  int32_t Record; // eax
  int32_t v8; // eax
  int32_t v9; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __it; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > __x; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > v17; // [rsp+40h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+50h] [rbp-30h]
  int32_t nCount; // [rsp+5Ch] [rbp-24h]
  uint32_t oldOffset; // [rsp+60h] [rbp-20h]
  uint32_t offset; // [rsp+64h] [rbp-1Ch]
  const CharTitle *title; // [rsp+68h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E90u);
    if ( packet )
    {
      nCount = 0;
      oldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      __it._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
      std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&iter, &__it);
      while ( 1 )
      {
        v17._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
        std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&__x, &v17);
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
          break;
        title = &std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
        if ( CharTitle::IsGet(title) && (CharTitle::GetType(title) != 7 || CharTitle::GetCardTitleParams(title) > 0) )
        {
          Id = CharTitle::GetId(title);
          Answer::NetPacket::writeInt32(packet, Id);
          State = CharTitle::GetState(title);
          Answer::NetPacket::writeInt8(packet, State);
          if ( CharTitle::GetType(title) == 7 )
          {
            CardTitleParams = CharTitle::GetCardTitleParams(title);
            Record = Player::getRecord(this->m_pPlayer, CardTitleParams);
            Answer::NetPacket::writeInt32(packet, Record);
          }
          else if ( CharTitle::GetType(title) == 10 )
          {
            v8 = CharTitle::GetCardTitleParams(title);
            v9 = Player::getRecord(this->m_pPlayer, v8 + 31301);
            Answer::NetPacket::writeInt32(packet, v9);
          }
          else
          {
            Answer::NetPacket::writeInt32(packet, 1);
          }
          ++nCount;
        }
        std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator++(&iter);
      }
      offset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, offset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v13, v12, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharTitle::AppendDressTitle(CExtCharTitle *const this, Answer::NetPacket *packet)
{
  int32_t Id; // edx
  int32_t i; // [rsp+18h] [rbp-8h]
  int32_t i_0; // [rsp+1Ch] [rbp-4h]

  if ( this->m_bShowActivityTitle )
  {
    for ( i = 0; i <= 2; ++i )
      Answer::NetPacket::writeInt32(packet, this->m_vActivityTitle[i]);
  }
  else
  {
    for ( i_0 = 0; i_0 <= 2; ++i_0 )
    {
      if ( this->m_vDress[i_0] )
      {
        Id = CharTitle::GetId(this->m_vDress[i_0]);
        Answer::NetPacket::writeInt32(packet, Id);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 0);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTitle::AddCharAttr(CExtCharTitle *const this)
{
  const AttrAddonVector *Attr; // rdx
  const AttrAddonVector *v2; // rdx
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > v6; // [rsp+40h] [rbp-10h] BYREF
  const CharTitle *title; // [rsp+48h] [rbp-8h]

  if ( this->m_pPlayer )
  {
    __it._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&iter, &__it);
    while ( 1 )
    {
      v6._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
      std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&__x, &v6);
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
        break;
      title = &std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
      if ( CharTitle::IsGet(title) )
      {
        Attr = CharTitle::GetAttr(title);
        CExtCharTitle::addAttr(this, Attr);
        if ( CharTitle::IsDress(title) )
        {
          v2 = CharTitle::DressAttr(title);
          CExtCharTitle::addAttr(this, v2);
        }
      }
      std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl CExtCharTitle::GetTitleInfo(
        CExtCharTitle *const this,
        TitleBattleList *const GetTitleList,
        TitleBattleList *const DressTitleList)
{
  TitleBattle stu; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > iter; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CharTitle> > __x; // [rsp+50h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > v8; // [rsp+60h] [rbp-10h] BYREF
  const CharTitle *title; // [rsp+68h] [rbp-8h]

  __it._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&iter, &__it);
  while ( 1 )
  {
    v8._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::_Rb_tree_const_iterator(&__x, &v8);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
      break;
    title = &std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
    if ( CharTitle::IsGet(title) )
    {
      stu = 0;
      stu.TitleId = CharTitle::GetId(title);
      stu.Battle = CharTitle::GetTitleBattle(title);
      std::list<TitleBattle>::push_back(GetTitleList, &stu);
      if ( CharTitle::IsDress(title) )
      {
        stu.Battle = CharTitle::DressTitleBattle(title);
        std::list<TitleBattle>::push_back(DressTitleList, &stu);
      }
    }
    std::_Rb_tree_const_iterator<std::pair<int const,CharTitle>>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtCharTitle::addAttr(CExtCharTitle *const this, const AttrAddonVector *const attrAddons)
{
  int32_t addon; // ebx
  const AttrAddon *v3; // rax
  uint32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i < std::vector<AttrAddon>::size(attrAddons); ++i )
    {
      if ( std::vector<AttrAddon>::operator[](attrAddons, i)->addon > 0 )
      {
        addon = std::vector<AttrAddon>::operator[](attrAddons, i)->addon;
        v3 = std::vector<AttrAddon>::operator[](attrAddons, i);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->index, addon);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTitle::InitTitle(CExtCharTitle *const this)
{
  int8_t ConnId; // bl
  CActivityManager *v2; // rax
  FamilyId_t FamilyId; // rax
  int32_t FamilyPosition; // edx
  CharId_t Cid; // rbx
  CRankMirror *v7; // rax
  int8_t v8; // bl
  CActivityManager *v9; // rax
  CharId_t v10; // rax
  CActivityManager *v12; // rax
  CharId_t v13; // rax
  CVplan *Vplan; // rax
  CVplan *v17; // rax
  int32_t Now; // eax
  int32_t v21; // eax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  FamilyId_t winFamily; // [rsp+18h] [rbp-38h]
  CharId_t peerless; // [rsp+20h] [rbp-30h]
  CharId_t CrossTowerWinner; // [rsp+28h] [rbp-28h]
  int32_t i; // [rsp+30h] [rbp-20h]
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  int32_t i_0; // [rsp+38h] [rbp-18h]
  int32_t nRecord_0; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    if ( std::operator!=<char>(&platform, &byte_8CC8C3) )
      CExtCharTitle::CheckAddTitle(this, 5, 1);
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<CActivityManager>::instance();
    winFamily = CActivityManager::GetCityWarWinner(v2, ConnId);
    if ( winFamily > 0 )
    {
      FamilyId = Player::getFamilyId(this->m_pPlayer);
      if ( FamilyId == winFamily )
      {
        FamilyPosition = Player::getFamilyPosition(this->m_pPlayer);
        CExtCharTitle::CheckAddTitle(this, 1, FamilyPosition);
      }
    }
    Cid = Player::getCid(this->m_pPlayer);
    v7 = Answer::Singleton<CRankMirror>::instance();
    if ( CRankMirror::IsJobBattleFirst(v7, Cid) )
      CExtCharTitle::CheckAddTitle(this, 3, 1);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<CActivityManager>::instance();
    peerless = CActivityManager::GetPeerlessWarWinner(v9, v8);
    if ( peerless > 0 )
    {
      v10 = Player::getCid(this->m_pPlayer);
      if ( v10 == peerless )
        CExtCharTitle::CheckAddTitle(this, 2, 1);
    }
    v12 = Answer::Singleton<CActivityManager>::instance();
    CrossTowerWinner = CActivityManager::GetCrossTowerWinner(v12);
    if ( CrossTowerWinner > 0 )
    {
      v13 = Player::getCid(this->m_pPlayer);
      if ( v13 == CrossTowerWinner )
        CExtCharTitle::CheckAddTitle(this, 9, 1);
    }
    if ( std::operator==<char>(&platform, "w360") )
    {
      Vplan = Player::GetVplan(this->m_pPlayer);
      if ( CVplan::GetVplanType(Vplan) == 1 )
        CExtCharTitle::CheckAddTitle(this, 8, 1);
    }
    if ( std::operator==<char>(&platform, "w360") )
    {
      v17 = Player::GetVplan(this->m_pPlayer);
      if ( CVplan::GetVplanType(v17) == 2 )
      {
        CExtCharTitle::CheckAddTitle(this, 8, 1);
        CExtCharTitle::CheckAddTitle(this, 8, 2);
      }
    }
    for ( i = 1700; i <= 1898; ++i )
    {
      nRecord = Player::getRecord(this->m_pPlayer, i);
      if ( nRecord != 1 )
      {
        Now = Unit::getNow(this->m_pPlayer);
        if ( Now >= nRecord )
          continue;
      }
      CExtCharTitle::CheckAddTitle(this, 7, i);
    }
    for ( i_0 = 31301; i_0 <= 31399; ++i_0 )
    {
      nRecord_0 = Player::getRecord(this->m_pPlayer, i_0);
      if ( nRecord_0 != 1 )
      {
        v21 = Unit::getNow(this->m_pPlayer);
        if ( v21 >= nRecord_0 )
          continue;
      }
      CExtCharTitle::CheckAddTitle(this, 10, i_0 - 31301);
    }
    std::string::~string(&platform);
  }
}


#####################################
void __cdecl CExtCharTitle::CheckAddTitle(CExtCharTitle *const this, int8_t type, int32_t param)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  Job_t Job; // al
  Sex_t Sex; // al
  bool v7; // bl
  int first; // edx
  std::pair<const int,CharTitle> *v9; // rax
  int32_t Priority; // eax
  int32_t v12; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::pair<const int,CharTitle> *v14; // rax
  bool v15; // al
  int32_t Id; // edx
  int32_t v17; // edx
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-30h] BYREF
  bool bChange; // [rsp+3Fh] [rbp-21h]
  int32_t nAddNormal; // [rsp+40h] [rbp-20h]
  int32_t nNormalPriority; // [rsp+44h] [rbp-1Ch]
  CharTitle *title; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( type != 3
      || (PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer),
          CFunctionOpen::IsOpened(PlayerFunctionOpen, 25)) )
    {
      bChange = 0;
      nAddNormal = 0;
      nNormalPriority = 0;
      for ( iter._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
          break;
        title = &std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
        if ( CharTitle::GetType(title) == type )
        {
          Job = Player::getJob(this->m_pPlayer);
          if ( CharTitle::CheckJob(title, Job) )
          {
            Sex = Player::getSex(this->m_pPlayer);
            if ( CharTitle::CheckSex(title, Sex) )
            {
              Player::GetPlatform((const Player *const)&platform);
              v7 = !CharTitle::CheckPlatform(title, &platform);
              std::string::~string(&platform);
              if ( !v7 )
              {
                if ( CharTitle::IsInParams(title, param) )
                {
                  if ( !CharTitle::IsGet(title) )
                  {
                    CharTitle::Get(title);
                    if ( CharTitle::IsSpecialTitle(title) )
                    {
                      bChange = 1;
                      first = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->first;
                      CExtCharTitle::autoDressTitle(this, first);
                    }
                    else
                    {
                      bChange = 1;
                      if ( !nNormalPriority
                        || (v9 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter),
                            Priority = CharTitle::GetPriority(&v9->second),
                            Priority < nNormalPriority) )
                      {
                        v12 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->first + 30000;
                        OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
                        if ( !CExtOperateLimit::GetLimitCount(OperateLimit, v12) )
                          nAddNormal = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->first;
                        v14 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
                        nNormalPriority = CharTitle::GetPriority(&v14->second);
                      }
                    }
                  }
                }
                else
                {
                  v15 = CharTitle::GetType(title) != 7 && CharTitle::GetType(title) != 8;
                  if ( v15 && CharTitle::IsGet(title) )
                  {
                    if ( CharTitle::IsDress(title) )
                    {
                      Id = CharTitle::GetId(title);
                      CExtCharTitle::unDressTitle(this, Id);
                    }
                    v17 = CharTitle::GetId(title);
                    CExtCharTitle::unHideTitle(this, v17);
                    bChange = 1;
                    CharTitle::Lost(title);
                  }
                }
              }
            }
          }
        }
      }
      if ( nAddNormal > 0 )
        CExtCharTitle::autoDressTitle(this, nAddNormal);
      if ( bChange )
      {
        Player::recalcAttr(this->m_pPlayer, 0, 0);
        Player::setSyncStatusFlag(this->m_pPlayer);
      }
      CExtCharTitle::SendTitleInfo(this);
    }
  }
}


#####################################
void __cdecl CExtCharTitle::RemoveTitle(CExtCharTitle *const this, int32_t type, int32_t param)
{
  int32_t v3; // edx
  int32_t Id; // edx
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-20h] BYREF
  bool bChange; // [rsp+37h] [rbp-9h]
  CharTitle *title; // [rsp+38h] [rbp-8h]

  bChange = 0;
  for ( iter._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
      break;
    title = &std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
    if ( CharTitle::GetType(title) != type )
      continue;
    if ( param <= 0 )
    {
      if ( !CharTitle::IsGet(title) )
        continue;
      if ( CharTitle::IsDress(title) )
      {
        Id = CharTitle::GetId(title);
        CExtCharTitle::unDressTitle(this, Id);
      }
    }
    else
    {
      if ( !CharTitle::IsInParams(title, param) )
        continue;
      if ( CharTitle::IsDress(title) )
      {
        v3 = CharTitle::GetId(title);
        CExtCharTitle::unDressTitle(this, v3);
      }
    }
    bChange = 1;
    CharTitle::Lost(title);
  }
  if ( bChange )
  {
    Player::recalcAttr(this->m_pPlayer, 0, 0);
    Player::setSyncStatusFlag(this->m_pPlayer);
    CExtCharTitle::SendTitleInfo(this);
  }
}


#####################################
void __cdecl CExtCharTitle::OnUpdate(CExtCharTitle *const this, int64_t curTick)
{
  int i; // [rsp+10h] [rbp-10h]
  int Record; // [rsp+14h] [rbp-Ch]
  int i_0; // [rsp+18h] [rbp-8h]
  int Record_0; // [rsp+1Ch] [rbp-4h]

  if ( curTick - this->m_LastUpdateTick > 59999 )
  {
    this->m_LastUpdateTick = curTick;
    for ( i = 1700; i <= 1898; ++i )
    {
      Record = Player::getRecord(this->m_pPlayer, i);
      if ( Record >= 2 && Unit::getNow(this->m_pPlayer) > Record )
      {
        CExtCharTitle::RemoveTitle(this, 7, i);
        Player::updateRecord(this->m_pPlayer, i, 0);
      }
    }
    for ( i_0 = 31301; i_0 <= 31399; ++i_0 )
    {
      Record_0 = Player::getRecord(this->m_pPlayer, i_0);
      if ( Record_0 >= 2 && Unit::getNow(this->m_pPlayer) > Record_0 )
      {
        CExtCharTitle::RemoveTitle(this, 10, i_0 - 31301);
        Player::updateRecord(this->m_pPlayer, i_0, 0);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTitle::autoDressTitle(CExtCharTitle *const this, int32_t nId)
{
  std::pair<const int,CharTitle> *v2; // rax
  int32_t Priority; // ebx
  int32_t Id; // eax
  int32_t v7; // ebx
  int32_t v9; // eax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  CExtCharTitle *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-30h] BYREF
  bool bChange; // [rsp+37h] [rbp-19h]
  CharTitle *title; // [rsp+38h] [rbp-18h]

  thisa = this;
  nIda = nId;
  if ( this->m_pPlayer )
  {
    if ( !CExtCharTitle::isTitleHide(thisa, nIda) )
    {
      iter._M_node = std::map<int,CharTitle>::find(&thisa->m_mCharTitle, &nIda)._M_node;
      __x._M_node = std::map<int,CharTitle>::end(&thisa->m_mCharTitle)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator==(&iter, &__x) )
      {
        v2 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
        if ( CharTitle::GetType(&v2->second) != 5
          || (*((int (__fastcall **)(Player *))thisa->m_pPlayer->_vptr_Entity + 9))(thisa->m_pPlayer) <= 299 )
        {
          bChange = 0;
          title = &std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->second;
          if ( CharTitle::IsSpecialTitle(title) )
          {
            if ( thisa->m_nDressTitle > 2 )
            {
              if ( thisa->m_vDress[2] )
              {
                Priority = CharTitle::GetPriority(thisa->m_vDress[2]);
                if ( Priority > CharTitle::GetPriority(title) )
                {
                  Id = CharTitle::GetId(thisa->m_vDress[2]);
                  CExtCharTitle::unDressTitle(thisa, Id);
                  CExtCharTitle::dressTitle(thisa, nIda);
                }
              }
              return;
            }
LABEL_25:
            CExtCharTitle::dressTitle(thisa, nIda);
            return;
          }
          if ( thisa->m_nDressTitle > 2 )
            return;
          if ( thisa->m_nDressNormalTitle <= 0 )
            goto LABEL_25;
          if ( *((_QWORD *)&thisa->m_pPlayer + thisa->m_nDressTitle) )
          {
            v7 = CharTitle::GetPriority(*((const CharTitle *const *)&thisa->m_pPlayer + thisa->m_nDressTitle));
            if ( v7 > CharTitle::GetPriority(title) )
            {
              v9 = CharTitle::GetId(*((const CharTitle *const *)&thisa->m_pPlayer + thisa->m_nDressTitle));
              CExtCharTitle::unDressTitle(thisa, v9);
              CExtCharTitle::dressTitle(thisa, nIda);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharTitle::initTitleMap(CExtCharTitle *const this)
{
  CfgData *v1; // rax
  const CfgTitleTable *TitleTable; // rax
  const std::pair<const int,CfgTitle> *v3; // rax
  const std::pair<const int,CfgTitle> *v4; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTitle> > iter; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTitle> > v6; // [rsp+30h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,CharTitle> >,bool> v7; // [rsp+40h] [rbp-50h]
  std::pair<const int,CharTitle> __x; // [rsp+50h] [rbp-40h] BYREF
  CharTitle __b; // [rsp+70h] [rbp-20h] BYREF
  const CfgTitleMap *cfgTitleMap; // [rsp+88h] [rbp-8h]

  v1 = Answer::Singleton<CfgData>::instance();
  TitleTable = CfgData::GetTitleTable(v1);
  cfgTitleMap = CfgTitleTable::GetTitleMap(TitleTable);
  for ( iter._M_node = std::map<int,CfgTitle>::begin(cfgTitleMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgTitle>>::operator++(&iter) )
  {
    v6._M_node = std::map<int,CfgTitle>::end(cfgTitleMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgTitle>>::operator!=(&iter, &v6) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTitle>>::operator->(&iter);
    CharTitle::CharTitle(&__b, &v3->second);
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTitle>>::operator->(&iter);
    std::pair<int const,CharTitle>::pair(&__x, &v4->first, &__b);
    v7 = std::map<int,CharTitle>::insert(&this->m_mCharTitle, &__x);
  }
}


#####################################
void __cdecl CExtCharTitle::resetTitleMap(CExtCharTitle *const this)
{
  std::pair<const int,CharTitle> *v1; // rax
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
    CharTitle::Lost(&v1->second);
  }
}


#####################################
void __cdecl CExtCharTitle::HideActivityTitle(CExtCharTitle *const this, bool bCleanActivityTitle)
{
  this->m_bShowActivityTitle = 0;
  if ( bCleanActivityTitle )
    bzero(this->m_vActivityTitle, 0xCu);
}


#####################################
bool __cdecl CExtCharTitle::SetActivityTitle(CExtCharTitle *const this, int8_t nPos, int32_t nTitle)
{
  if ( !this->m_pPlayer )
    return 0;
  if ( (unsigned __int8)nPos > 2u )
    return 0;
  this->m_vActivityTitle[nPos] = nTitle;
  Player::setSyncStatusFlag(this->m_pPlayer);
  return 1;
}


#####################################
int32_t __cdecl CExtCharTitle::GetDressTitleId(CExtCharTitle *const this)
{
  int32_t i; // [rsp+14h] [rbp-4h]

  for ( i = 0; i <= 2; ++i )
  {
    if ( this->m_vDress[i] )
      return CharTitle::GetId(this->m_vDress[i]);
  }
  return 0;
}


#####################################
void __cdecl CExtCharTitle::OnLevelUp(CExtCharTitle *const this, int32_t nLevel)
{
  std::pair<const int,CharTitle> *v2; // rax
  std::pair<const int,CharTitle> *v3; // rax
  int first; // edx
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CharTitle> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( nLevel == 300 && this->m_pPlayer )
  {
    for ( iter._M_node = std::map<int,CharTitle>::begin(&this->m_mCharTitle)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CharTitle>::end(&this->m_mCharTitle)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator!=(&iter, &__x) )
        break;
      v2 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
      if ( CharTitle::GetType(&v2->second) == 5 )
      {
        v3 = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter);
        if ( CharTitle::IsDress(&v3->second) )
        {
          first = std::_Rb_tree_iterator<std::pair<int const,CharTitle>>::operator->(&iter)->first;
          CExtCharTitle::unDressTitle(this, first);
        }
      }
    }
    Player::setSyncStatusFlag(this->m_pPlayer);
    CExtCharTitle::SendTitleInfo(this);
  }
}


#####################################
bool __cdecl CExtCharTitle::isTitleHide(CExtCharTitle *const this, int32_t nId)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return CExtOperateLimit::GetLimitCount(OperateLimit, nId + 30000) == 1;
}


#####################################
void __cdecl CExtCharTitle::hideTitle(CExtCharTitle *const this, int32_t nId)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::UpdateLimitCount(OperateLimit, nId + 30000, 1);
  }
}


#####################################
void __cdecl CExtCharTitle::unHideTitle(CExtCharTitle *const this, int32_t nId)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::UpdateLimitCount(OperateLimit, nId + 30000, 0);
  }
}


