// Decompiled methods for class: CharLittlerHelper
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl CharLittlerHelper::~CharLittlerHelper(CharLittlerHelper *const this)
{
  CharLittlerHelper::~CharLittlerHelper(this);
  operator delete(this);
}


#####################################
void __cdecl CharLittlerHelper::OnLoadFromDB(CharLittlerHelper *const this, const PlayerDBData *const dbData)
{
  GameService *v2; // rax
  CPoolManager *v3; // rax
  ActLittleHelperInfo *pInfo; // [rsp+18h] [rbp-18h]

  std::map<int,ActLittleHelperInfo>::operator=(&this->m_ActMap, &dbData->m_CLittleHelper.m_ActLittleHelperInfoMap);
  this->m_LittleHelperId = dbData->m_CLittleHelper.m_LittleHelperId;
  if ( this->m_LittleHelperId > 0 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 )
    {
      pInfo = CharLittlerHelper::GetActLittleHelperInfo(this, this->m_LittleHelperId);
      if ( pInfo )
      {
        v3 = Answer::Singleton<CPoolManager>::instance();
        this->m_CLittleHelper = CPoolManager::pop<CLittleHelper>(v3);
        if ( this->m_CLittleHelper )
        {
          CLittleHelper::init(this->m_CLittleHelper, this->m_pPlayer, this->m_LittleHelperId, pInfo->nSkin);
          CLittleHelper::EnterMap(this->m_CLittleHelper);
          CLittleHelper::OnWork(this->m_CLittleHelper);
        }
      }
    }
  }
}


#####################################
void __cdecl CharLittlerHelper::OnSaveToDB(CharLittlerHelper *const this, PlayerDBData *const dbData)
{
  std::map<int,ActLittleHelperInfo>::operator=(&dbData->m_CLittleHelper.m_ActLittleHelperInfoMap, &this->m_ActMap);
  dbData->m_CLittleHelper.m_LittleHelperId = this->m_LittleHelperId;
}


#####################################
void __cdecl CharLittlerHelper::GetInterestsProtocol(CharLittlerHelper *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 507;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 508;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 509;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CharLittlerHelper::DispatchNetDatas(
        CharLittlerHelper *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x1FCu:
      return CharLittlerHelper::OnRest(this, inPacket);
    case 0x1FDu:
      return CharLittlerHelper::OnBuyLittlerHelper(this, inPacket);
    case 0x1FBu:
      return CharLittlerHelper::OnWork(this, inPacket);
  }
  return 2;
}


#####################################
void __cdecl CharLittlerHelper::OnCleanUp(CharLittlerHelper *const this)
{
  CLittleHelper *m_CLittleHelper; // rbx
  CPoolManager *v2; // rax

  if ( this->m_CLittleHelper )
  {
    CLittleHelper::LeaveMap(this->m_CLittleHelper);
    m_CLittleHelper = this->m_CLittleHelper;
    v2 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<CLittleHelper>(v2, m_CLittleHelper);
    this->m_CLittleHelper = 0;
  }
  std::map<int,ActLittleHelperInfo>::clear(&this->m_ActMap);
  this->m_LittleHelperId = 0;
}


#####################################
void __cdecl CharLittlerHelper::OnUpdate(CharLittlerHelper *const this, int64_t curTick)
{
  int32_t LittleHelperId; // edx
  int32_t nTimes; // ebx
  ActLittleHelperInfo *pInfo; // [rsp+18h] [rbp-18h]

  if ( this->m_CLittleHelper )
  {
    Unit::update(this->m_CLittleHelper);
    if ( CLittleHelper::IsWork(this->m_CLittleHelper) )
    {
      LittleHelperId = CLittleHelper::OnGetLittleHelperId(this->m_CLittleHelper);
      pInfo = CharLittlerHelper::GetActLittleHelperInfo(this, LittleHelperId);
      if ( pInfo )
      {
        nTimes = pInfo->nTimes;
        if ( nTimes < Unit::getNow(this->m_pPlayer) )
        {
          CLittleHelper::LeaveMap(this->m_CLittleHelper);
          CLittleHelper::OnRest(this->m_CLittleHelper);
          CharLittlerHelper::SendCharLittlerhelper(this);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CharLittlerHelper::OnAutoWork(CharLittlerHelper *const this)
{
  return CharLittlerHelper::OnWork(this, this->m_LittleHelperId);
}


#####################################
int32_t __cdecl CharLittlerHelper::OnWork(CharLittlerHelper *const this, int32_t nId)
{
  CPoolManager *v3; // rax
  ActLittleHelperInfo *pInfo; // [rsp+10h] [rbp-20h]

  pInfo = CharLittlerHelper::GetActLittleHelperInfo(this, nId);
  if ( !pInfo )
    return 2;
  if ( pInfo->nTimes < Unit::getNow(this->m_pPlayer) )
    return 2;
  if ( this->m_CLittleHelper )
  {
    if ( CLittleHelper::OnGetLittleHelperId(this->m_CLittleHelper) == nId
      && CLittleHelper::IsWork(this->m_CLittleHelper) )
    {
      return 2;
    }
    if ( CLittleHelper::OnGetLittleHelperId(this->m_CLittleHelper) != nId )
      CLittleHelper::ChangeLittleHelperId(this->m_CLittleHelper, nId, pInfo->nSkin);
  }
  else
  {
    v3 = Answer::Singleton<CPoolManager>::instance();
    this->m_CLittleHelper = CPoolManager::pop<CLittleHelper>(v3);
    if ( !this->m_CLittleHelper )
      return 2;
    CLittleHelper::init(this->m_CLittleHelper, this->m_pPlayer, nId, pInfo->nSkin);
  }
  CLittleHelper::EnterMap(this->m_CLittleHelper);
  CLittleHelper::OnWork(this->m_CLittleHelper);
  this->m_LittleHelperId = nId;
  CharLittlerHelper::SendCharLittlerhelper(this);
  return 0;
}


#####################################
int32_t __cdecl CharLittlerHelper::OnWork(CharLittlerHelper *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax
  int32_t nId; // [rsp+14h] [rbp-2Ch]
  Map *pMap; // [rsp+18h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 2;
  if ( (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 22))(pMap) != 1 )
    return 2;
  if ( !CharLittlerHelper::OnWork(this, nId) )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v7, ConnId, GateIndex, Proc, nId);
  }
  return 0;
}


#####################################
void __cdecl CharLittlerHelper::SetTargetTile(CharLittlerHelper *const this, int32_t tx, int32_t ty, Direction dir)
{
  if ( this->m_CLittleHelper && CLittleHelper::IsWork(this->m_CLittleHelper) )
    CLittleHelper::ResetTargetTile(this->m_CLittleHelper, tx, ty, dir);
}


#####################################
void __cdecl CharLittlerHelper::AddCharAttr(CharLittlerHelper *const this)
{
  std::pair<const int,ActLittleHelperInfo> *v1; // rax
  int first; // ebx
  CfgData *v3; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v5; // rax
  std::_List_const_iterator<AddAttribute> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > it; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > v8; // [rsp+30h] [rbp-40h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+40h] [rbp-30h] BYREF
  int32_t Now; // [rsp+54h] [rbp-1Ch]
  const LittleHelperCfg *pLittleHelper; // [rsp+58h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Now = Unit::getNow(this->m_pPlayer);
    for ( it._M_node = std::map<int,ActLittleHelperInfo>::begin(&this->m_ActMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator++(&it, 0) )
    {
      v8._M_node = std::map<int,ActLittleHelperInfo>::end(&this->m_ActMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator!=(&it, &v8) )
        break;
      v1 = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it);
      if ( v1->second.nTimes > Now )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->first;
        v3 = Answer::Singleton<CfgData>::instance();
        pLittleHelper = CfgData::GetLittleHelperCfg(v3, first);
        if ( pLittleHelper )
        {
          for ( iter._M_node = std::list<AddAttribute>::begin(&pLittleHelper->lAttr)._M_node;
                ;
                std::_List_const_iterator<AddAttribute>::operator++(&iter, 0) )
          {
            __x._M_node = std::list<AddAttribute>::end(&pLittleHelper->lAttr)._M_node;
            if ( !std::_List_const_iterator<AddAttribute>::operator!=(&iter, &__x) )
              break;
            m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&iter)->m_nAddAttrValue;
            v5 = std::_List_const_iterator<AddAttribute>::operator->(&iter);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->m_nAddAttrType, m_nAddAttrValue);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CharLittlerHelper::OnRest(CharLittlerHelper *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax

  if ( !inPacket || !this->m_pPlayer || !this->m_CLittleHelper )
    return 2;
  if ( !CLittleHelper::IsWork(this->m_CLittleHelper) )
    return 10002;
  CLittleHelper::LeaveMap(this->m_CLittleHelper);
  CLittleHelper::OnRest(this->m_CLittleHelper);
  this->m_LittleHelperId = 0;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CharLittlerHelper::OnRest(CharLittlerHelper *const this)
{
  if ( !this->m_pPlayer || !this->m_CLittleHelper )
    return 2;
  if ( CLittleHelper::IsWork(this->m_CLittleHelper) )
  {
    CLittleHelper::LeaveMap(this->m_CLittleHelper);
    CLittleHelper::OnRest(this->m_CLittleHelper);
    CharLittlerHelper::SendCharLittlerhelper(this);
  }
  return 0;
}


#####################################
int32_t __cdecl CharLittlerHelper::AddLittlerHelper(CharLittlerHelper *const this, int32_t nId, int32_t nAddTime)
{
  GameService *v3; // rax
  ActLittleHelperInfo *v5; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v10; // bl
  GameService *v11; // rax
  ActLittleHelperInfo stu; // [rsp+10h] [rbp-50h] BYREF
  std::string val; // [rsp+20h] [rbp-40h] BYREF
  Map *pMap; // [rsp+28h] [rbp-38h]
  ActLittleHelperInfo *pInfo; // [rsp+30h] [rbp-30h]
  int32_t nTime; // [rsp+3Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+40h] [rbp-20h]
  int32_t DaoQiTime; // [rsp+4Ch] [rbp-14h]

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 2;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 2;
  pInfo = CharLittlerHelper::GetActLittleHelperInfo(this, nId);
  nTime = Unit::getNow(this->m_pPlayer);
  if ( pInfo )
  {
    DaoQiTime = 0;
    if ( pInfo->nTimes < nTime )
      DaoQiTime = nTime + nAddTime;
    else
      DaoQiTime = nAddTime + pInfo->nTimes;
    pInfo->nTimes = DaoQiTime;
  }
  else
  {
    *(_QWORD *)&stu.nId = (unsigned int)nId;
    stu.nTimes = nTime + nAddTime;
    v5 = std::map<int,ActLittleHelperInfo>::operator[](&this->m_ActMap, &stu.nId);
    *v5 = stu;
  }
  if ( (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 22))(pMap) )
    CharLittlerHelper::OnWork(this, nId);
  CharLittlerHelper::SendCharLittlerhelper(this);
  Player::RecalcAttr(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 3011);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v10 = Player::getConnId(this->m_pPlayer);
    v11 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v11, v10, packet);
  }
  return 0;
}


#####################################
int32_t __cdecl CharLittlerHelper::OnBuyLittlerHelper(CharLittlerHelper *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  CfgData *v4; // rax
  ActLittleHelperInfo *v5; // rax
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  int8_t v11; // bl
  GameService *v12; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  ActLittleHelperInfo stu; // [rsp+10h] [rbp-70h] BYREF
  std::string val; // [rsp+20h] [rbp-60h] BYREF
  Map *pMap; // [rsp+28h] [rbp-58h]
  int32_t nId; // [rsp+34h] [rbp-4Ch]
  ActLittleHelperInfo *pInfo; // [rsp+38h] [rbp-48h]
  const LittleHelperCfg *pLittleHelper; // [rsp+40h] [rbp-40h]
  int32_t nTime; // [rsp+4Ch] [rbp-34h]
  int32_t NeedGold; // [rsp+50h] [rbp-30h]
  int32_t DaoQiTime; // [rsp+54h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 2;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 2;
  if ( (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 22))(pMap) != 1 )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  pInfo = CharLittlerHelper::GetActLittleHelperInfo(this, nId);
  v4 = Answer::Singleton<CfgData>::instance();
  pLittleHelper = CfgData::GetLittleHelperCfg(v4, nId);
  if ( !pLittleHelper )
    return 2;
  if ( pLittleHelper->nGold <= 0 || pLittleHelper->nReGold <= 0 || pLittleHelper->nTime <= 0 )
    return 2;
  nTime = Unit::getNow(this->m_pPlayer);
  if ( pInfo )
  {
    NeedGold = 0;
    DaoQiTime = 0;
    if ( pInfo->nTimes < nTime )
    {
      NeedGold = pLittleHelper->nGold;
      DaoQiTime = nTime + pLittleHelper->nTime;
    }
    else
    {
      NeedGold = pLittleHelper->nReGold;
      DaoQiTime = pInfo->nTimes + pLittleHelper->nTime;
    }
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            NeedGold,
            CURRENCY_CHANGE_REASON::GCR_BUY_LITTLE_HELPER,
            0) )
      return 2;
    pInfo->nTimes = DaoQiTime;
  }
  else
  {
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            pLittleHelper->nGold,
            CURRENCY_CHANGE_REASON::GCR_BUY_LITTLE_HELPER,
            0) )
      return 2;
    stu.nTimes = 0;
    *(_QWORD *)&stu.nId = (unsigned int)nId;
    stu.nTimes = nTime + pLittleHelper->nTime;
    v5 = std::map<int,ActLittleHelperInfo>::operator[](&this->m_ActMap, &stu.nId);
    *v5 = stu;
  }
  CharLittlerHelper::OnWork(this, nId);
  CharLittlerHelper::SendCharLittlerhelper(this);
  Player::RecalcAttr(this->m_pPlayer);
  v6 = nId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  if ( pLittleHelper->nGongGaoId > 0 )
  {
    v11 = Player::getConnId(this->m_pPlayer);
    v12 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v12, v11, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pLittleHelper->nGongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v15 = Player::getConnId(this->m_pPlayer);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v16, v15, packet);
    }
  }
  return 0;
}


#####################################
void __cdecl CharLittlerHelper::SendCharLittlerhelper(CharLittlerHelper *const this)
{
  GameService *v1; // rax
  int32_t LittleHelperId; // eax
  std::pair<const int,ActLittleHelperInfo> *v3; // rax
  std::pair<const int,ActLittleHelperInfo> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DEAu);
    if ( packet )
    {
      if ( this->m_CLittleHelper && CLittleHelper::IsWork(this->m_CLittleHelper) )
      {
        LittleHelperId = CLittleHelper::OnGetLittleHelperId(this->m_CLittleHelper);
        Answer::NetPacket::writeInt32(packet, LittleHelperId);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 0);
      }
      nSize = std::map<int,ActLittleHelperInfo>::size(&this->m_ActMap);
      it._M_node = std::map<int,ActLittleHelperInfo>::begin(&this->m_ActMap)._M_node;
      Answer::NetPacket::writeInt32(packet, nSize);
      while ( 1 )
      {
        __x._M_node = std::map<int,ActLittleHelperInfo>::end(&this->m_ActMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->second.nId);
        v4 = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second.nTimes);
        std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator++(&it, 0);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, ConnId, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CharLittlerHelper::CanPick(CharLittlerHelper *const this, int8_t nClass, int32_t nId)
{
  bool IsPickMoney; // bl
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  CfgData *v6; // rax
  CExtCharBag *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  CExtCharBag *v12; // rax
  StringVector params; // [rsp+10h] [rbp-60h] BYREF
  std::string delims; // [rsp+30h] [rbp-40h] BYREF
  char v17; // [rsp+47h] [rbp-29h] BYREF
  const CfgEquip *pCfgEquip; // [rsp+48h] [rbp-28h]
  CfgItem *pItem; // [rsp+50h] [rbp-20h]
  int32_t CurrType; // [rsp+58h] [rbp-18h]
  int32_t CurrCount; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  if ( CharLittlerHelper::IsFilterItem(this, nClass, nId) )
    return 0;
  if ( nClass == 2 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::GetFreeSlotCount(Bag) > 0 )
    {
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgEquip = CfgData::getEquip(v5, nId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_nType <= 16 || pCfgEquip->m_nType > 28 )
        {
          if ( pCfgEquip->m_nType <= 28 || pCfgEquip->m_nType > 34 )
          {
            if ( pCfgEquip->m_nType >= 8u )
              return CharLittlerHelper::IsPickEquip(this);
            else
              return CharLittlerHelper::IsPickEquip(this)
                  && !CharLittlerHelper::IsFilterEquipGrade(this, pCfgEquip->m_nGrade);
          }
          else
          {
            return CharLittlerHelper::IsPickSpecialEquip(this);
          }
        }
        else
        {
          return CharLittlerHelper::IsPickShouHu(this);
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else if ( nClass == 1 )
  {
    v6 = Answer::Singleton<CfgData>::instance();
    pItem = CfgData::getItem(v6, nId);
    if ( pItem )
    {
      if ( pItem->type == 1 || (v7 = Player::GetBag(this->m_pPlayer), CExtCharBag::GetFreeSlotCount(v7) > 0) )
      {
        if ( pItem->type == 1 || pItem->type == 82 )
        {
          CurrType = 0;
          CurrCount = 0;
          std::allocator<char>::allocator(&v17);
          std::string::string(&delims, ":", &v17);
          Answer::StringUtility::split(&params, &pItem->effect, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v17);
          if ( std::vector<std::string>::size(&params) == 2 )
          {
            v8 = std::vector<std::string>::operator[](&params, 0);
            v9 = (const char *)std::string::c_str(v8);
            CurrType = atoi(v9);
            v10 = std::vector<std::string>::operator[](&params, 1u);
            v11 = (const char *)std::string::c_str(v10);
            CurrCount = atoi(v11);
          }
          if ( CurrType && CurrType != 6 )
            IsPickMoney = CurrType != 3 || CharLittlerHelper::IsPickSYB(this);
          else
            IsPickMoney = CharLittlerHelper::IsPickMoney(this);
          std::vector<std::string>::~vector(&params);
        }
        else
        {
          return CharLittlerHelper::IsPickImte(this);
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v12 = Player::GetBag(this->m_pPlayer);
    return CExtCharBag::GetFreeSlotCount(v12) > 0 && !CharLittlerHelper::IsFilterItem(this, nClass, nId);
  }
  return IsPickMoney;
}


#####################################
bool __cdecl CharLittlerHelper::IsFilterEquipGrade(CharLittlerHelper *const this, int32_t Grade)
{
  int32_t Gradea; // [rsp+4h] [rbp-2Ch] BYREF
  CharLittlerHelper *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<int> it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<int> __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Gradea = Grade;
  it._M_node = std::set<int>::find(&this->m_EquipFilter, &Gradea)._M_node;
  __x._M_node = std::set<int>::end(&thisa->m_EquipFilter)._M_node;
  return std::_Rb_tree_const_iterator<int>::operator!=(&it, &__x);
}


#####################################
bool __cdecl CharLittlerHelper::IsFilterItem(CharLittlerHelper *const this, int8_t nclass, int32_t nId)
{
  std::_Rb_tree_iterator<std::pair<const std::pair<signed char,int>,int> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::pair<signed char,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const std::pair<signed char,int>,int> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<signed char,int>(nclass, nId);
  iter._M_node = std::map<std::pair<signed char,int>,int>::find(&this->m_ItemFilterMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<signed char,int>,int>::end(&this->m_ItemFilterMap)._M_node;
  return std::_Rb_tree_iterator<std::pair<std::pair const<signed char,int>,int>>::operator!=(&iter, &v6);
}


#####################################
void __cdecl CharLittlerHelper::parsePickString(CharLittlerHelper *const this, std::string *p_PickString)
{
  std::string *v2; // rax
  const char *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  std::string *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  std::string *v20; // rax
  const char *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  std::string *v25; // rax
  const char *v26; // rax
  std::string *v27; // rax
  const char *v28; // rax
  std::string *v29; // rax
  const char *v30; // rax
  std::string *v31; // rax
  const char *v32; // rax
  std::string *v33; // rax
  const char *v34; // rax
  std::string *v36; // rax
  const char *v37; // rax
  int32_t v38; // ebx
  CfgData *v39; // rax
  int32_t i; // [rsp+2Ch] [rbp-124h] BYREF
  StringVector Item; // [rsp+30h] [rbp-120h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-100h] BYREF
  StringVector itemFilerVt; // [rsp+60h] [rbp-F0h] BYREF
  std::string itemFiler; // [rsp+80h] [rbp-D0h] BYREF
  StringVector vStr; // [rsp+90h] [rbp-C0h] BYREF
  std::string sep; // [rsp+B0h] [rbp-A0h] BYREF
  char v47; // [rsp+BFh] [rbp-91h] BYREF
  std::string v48; // [rsp+C0h] [rbp-90h] BYREF
  char v49; // [rsp+CFh] [rbp-81h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+D0h] [rbp-80h] BYREF
  std::string v51; // [rsp+E0h] [rbp-70h] BYREF
  char v52; // [rsp+EFh] [rbp-61h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const std::pair<signed char,int>,int> >,bool> v53; // [rsp+F0h] [rbp-60h]
  _BYTE v54[12]; // [rsp+100h] [rbp-50h] BYREF
  int __b; // [rsp+10Ch] [rbp-44h] BYREF
  std::pair<signed char,int> __a; // [rsp+110h] [rbp-40h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v57; // [rsp+120h] [rbp-30h]
  int8_t nClass; // [rsp+133h] [rbp-1Dh]
  int32_t nId; // [rsp+134h] [rbp-1Ch]
  const ShiQuCfg *pCfg; // [rsp+138h] [rbp-18h]

  std::map<std::pair<signed char,int>,int>::clear(&this->m_ItemFilterMap);
  std::set<int>::clear(&this->m_EquipFilter);
  this->m_NeedPick = 0;
  bzero(this->m_PickSetUp, 6u);
  std::allocator<char>::allocator(&v47);
  std::string::string(&sep, "|", &v47);
  Answer::StringUtility::split2(&vStr, p_PickString, &sep, 0);
  std::string::~string(&sep);
  std::allocator<char>::~allocator(&v47);
  if ( std::vector<std::string>::size(&vStr) > 0x1E )
  {
    v2 = std::vector<std::string>::operator[](&vStr, 0x19u);
    v3 = (const char *)std::string::c_str(v2);
    if ( !atoi(v3) )
      this->m_NeedPick = 0;
    v4 = std::vector<std::string>::operator[](&vStr, 0x1Au);
    v5 = (const char *)std::string::c_str(v4);
    if ( !atoi(v5) )
      this->m_PickSetUp[0] = 1;
    v6 = std::vector<std::string>::operator[](&vStr, 0x1Bu);
    v7 = (const char *)std::string::c_str(v6);
    if ( !atoi(v7) )
      this->m_PickSetUp[4] = 1;
    v8 = std::vector<std::string>::operator[](&vStr, 0x1Cu);
    v9 = (const char *)std::string::c_str(v8);
    if ( !atoi(v9) )
      this->m_PickSetUp[2] = 1;
    v10 = std::vector<std::string>::operator[](&vStr, 0x1Du);
    v11 = (const char *)std::string::c_str(v10);
    if ( !atoi(v11) )
      this->m_PickSetUp[1] = 1;
    v12 = std::vector<std::string>::operator[](&vStr, 0x1Eu);
    v13 = (const char *)std::string::c_str(v12);
    if ( !atoi(v13) )
      this->m_PickSetUp[5] = 1;
    v14 = std::vector<std::string>::operator[](&vStr, 0x1Fu);
    v15 = (const char *)std::string::c_str(v14);
    if ( !atoi(v15) )
      this->m_PickSetUp[3] = 1;
    v16 = std::vector<std::string>::operator[](&vStr, 0x13u);
    std::string::string(&itemFiler, v16);
    std::allocator<char>::allocator(&v49);
    std::string::string(&v48, ":", &v49);
    Answer::StringUtility::split2(&itemFilerVt, &itemFiler, &v48, 0);
    std::string::~string(&v48);
    std::allocator<char>::~allocator(&v49);
    for ( it._M_current = std::vector<std::string>::begin(&itemFilerVt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<std::string>::end(&itemFilerVt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v52);
      std::string::string(&v51, "$", &v52);
      v17 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split2(&Item, v17, &v51, 0);
      std::string::~string(&v51);
      std::allocator<char>::~allocator(&v52);
      if ( std::vector<std::string>::size(&Item) == 6 )
      {
        v18 = std::vector<std::string>::operator[](&Item, 1u);
        v19 = (const char *)std::string::c_str(v18);
        if ( atoi(v19) > 0 )
        {
          v20 = std::vector<std::string>::operator[](&Item, 2u);
          v21 = (const char *)std::string::c_str(v20);
          if ( atoi(v21) > 0 )
          {
            v22 = std::vector<std::string>::operator[](&Item, 5u);
            v23 = (const char *)std::string::c_str(v22);
            if ( !atoi(v23) )
            {
              v25 = std::vector<std::string>::operator[](&Item, 2u);
              v26 = (const char *)std::string::c_str(v25);
              nClass = atoi(v26);
              v27 = std::vector<std::string>::operator[](&Item, 1u);
              v28 = (const char *)std::string::c_str(v27);
              nId = atoi(v28);
              __b = 1;
              __a = std::make_pair<signed char,int>(nClass, nId);
              std::pair<std::pair const<signed char,int>,int>::pair(
                (std::pair<const std::pair<signed char,int>,int> *const)v54,
                &__a,
                &__b);
              v53 = std::map<std::pair<signed char,int>,int>::insert(
                      &this->m_ItemFilterMap,
                      (const std::pair<const std::pair<signed char,int>,int> *const)v54);
            }
          }
        }
        v29 = std::vector<std::string>::operator[](&Item, 1u);
        v30 = (const char *)std::string::c_str(v29);
        if ( !atoi(v30) )
        {
          v31 = std::vector<std::string>::operator[](&Item, 2u);
          v32 = (const char *)std::string::c_str(v31);
          if ( atoi(v32) == 2 )
          {
            v33 = std::vector<std::string>::operator[](&Item, 5u);
            v34 = (const char *)std::string::c_str(v33);
            if ( !atoi(v34) )
            {
              v36 = std::vector<std::string>::operator[](&Item, 0);
              v37 = (const char *)std::string::c_str(v36);
              v38 = atoi(v37);
              v39 = Answer::Singleton<CfgData>::instance();
              pCfg = CfgData::GetShiQuCfg(v39, v38);
              if ( pCfg )
              {
                for ( i = pCfg->nMinGrade; pCfg->nMaxGrade >= i; ++i )
                  v57 = std::set<int>::insert(&this->m_EquipFilter, &i);
              }
            }
          }
        }
      }
      std::vector<std::string>::~vector(&Item);
    }
    std::vector<std::string>::~vector(&itemFilerVt);
    std::string::~string(&itemFiler);
  }
  std::vector<std::string>::~vector(&vStr);
}


