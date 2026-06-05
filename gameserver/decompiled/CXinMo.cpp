// Decompiled methods for class: CXinMo
// Source: gameserver.cc
// Total methods: 36

#####################################
void __cdecl CXinMo::~CXinMo(CXinMo *const this)
{
  CXinMo::~CXinMo(this);
  operator delete(this);
}


#####################################
void __cdecl CXinMo::OnCleanUp(CXinMo *const this)
{
  this->m_Exp = 0;
  this->m_XinMoLevel = 0;
  this->m_XinMoActiveLevel = 0;
  std::map<int,int>::clear(&this->m_QiQingLevel);
  bzero(this->m_ItemList, 0x700u);
}


#####################################
void __cdecl CXinMo::OnLoadFromDB(CXinMo *const this, const PlayerDBData *const dbData)
{
  this->m_Exp = dbData->m_XinMoDBData.m_Exp;
  this->m_XinMoLevel = dbData->m_XinMoDBData.m_XinMoLevel;
  this->m_XinMoActiveLevel = dbData->m_XinMoDBData.m_XinMoActiveLevel;
  std::map<int,int>::operator=(&this->m_QiQingLevel, &dbData->m_XinMoDBData.m_QiQingLevel);
  this->m_QiQingInfo = dbData->m_XinMoDBData.m_QiQingInfo;
  memcpy(this->m_ItemList, dbData->m_XinMoDBData.m_ItemList, sizeof(this->m_ItemList));
}


#####################################
void __cdecl CXinMo::OnSaveToDB(CXinMo *const this, PlayerDBData *const dbData)
{
  dbData->m_XinMoDBData.m_Exp = this->m_Exp;
  dbData->m_XinMoDBData.m_XinMoLevel = this->m_XinMoLevel;
  dbData->m_XinMoDBData.m_XinMoActiveLevel = this->m_XinMoActiveLevel;
  std::map<int,int>::operator=(&dbData->m_XinMoDBData.m_QiQingLevel, &this->m_QiQingLevel);
  dbData->m_XinMoDBData.m_QiQingInfo = this->m_QiQingInfo;
  memcpy(dbData->m_XinMoDBData.m_ItemList, this->m_ItemList, sizeof(dbData->m_XinMoDBData.m_ItemList));
}


#####################################
void __cdecl CXinMo::GetInterestsProtocol(CXinMo *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+10h] [rbp-10h] BYREF
  unsigned __int16 v3; // [rsp+12h] [rbp-Eh] BYREF
  unsigned __int16 v4; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v5; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v6; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v7; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v8; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v9; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 302;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 303;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 304;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 306;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 307;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 308;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 309;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 310;
  std::list<unsigned short>::push_back(procList, &v9);
}


#####################################
int32_t __cdecl CXinMo::DispatchNetDatas(CXinMo *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  CfgData *v4; // rax

  if ( !inPacket )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL) + 1 <= 29 )
    return 10002;
  switch ( nProcId )
  {
    case 0x12Eu:
      result = CXinMo::OnXinMoLevel(this, inPacket);
      break;
    case 0x12Fu:
      result = CXinMo::OnActiveXinMo(this, inPacket);
      break;
    case 0x130u:
      result = CXinMo::OnJinHua(this, inPacket);
      break;
    case 0x132u:
      result = CXinMo::OnGetItem(this, inPacket);
      break;
    case 0x133u:
      result = CXinMo::OnTidy(this, inPacket);
      break;
    case 0x134u:
      result = CXinMo::OnDec(this, inPacket);
      break;
    case 0x135u:
      result = CXinMo::OnQiQingLevelUp(this, inPacket);
      break;
    case 0x136u:
      result = CXinMo::OnXinQing(this, inPacket);
      break;
    default:
      result = 10002;
      break;
  }
  return result;
}


#####################################
void __cdecl CXinMo::AddCharAttr(CXinMo *const this)
{
  int32_t m_XinMoLevel; // ebx
  CfgData *v2; // rax
  const XinMoTable *XinMoTable; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v5; // rax
  int32_t m_XinMoActiveLevel; // ebx
  CfgData *v7; // rax
  const XinMoTable *v8; // rax
  int32_t v9; // ebx
  const AddAttribute *v10; // rax
  int32_t second; // r12d
  int first; // ebx
  CfgData *v13; // rax
  const XinMoTable *v14; // rax
  int32_t v15; // ebx
  const AddAttribute *v16; // rax
  std::_List_const_iterator<AddAttribute> it_2; // [rsp+10h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it_1; // [rsp+20h] [rbp-90h] BYREF
  std::_List_const_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-80h] BYREF
  std::_List_const_iterator<AddAttribute> it; // [rsp+40h] [rbp-70h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+50h] [rbp-60h] BYREF
  std::_List_const_iterator<AddAttribute> v22; // [rsp+60h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v23; // [rsp+70h] [rbp-40h] BYREF
  std::_List_const_iterator<AddAttribute> v24; // [rsp+80h] [rbp-30h] BYREF
  const XinMoCfg *CurCfg; // [rsp+88h] [rbp-28h]
  const QiQingCfg *pQiQingCfg; // [rsp+90h] [rbp-20h]
  const XinMoQiQingLevelUpCfg *CurCfg_0; // [rsp+98h] [rbp-18h]

  m_XinMoLevel = this->m_XinMoLevel;
  v2 = Answer::Singleton<CfgData>::instance();
  XinMoTable = CfgData::GetXinMoTable(v2);
  CurCfg = XinMoTable::GetXingMoCfg(XinMoTable, m_XinMoLevel);
  if ( CurCfg )
  {
    for ( it._M_node = std::list<AddAttribute>::begin(&CurCfg->Attr)._M_node;
          ;
          std::_List_const_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&CurCfg->Attr)._M_node;
      if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v5 = std::_List_const_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->m_nAddAttrType, m_nAddAttrValue);
    }
  }
  m_XinMoActiveLevel = this->m_XinMoActiveLevel;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetXinMoTable(v7);
  pQiQingCfg = XinMoTable::GetQiQingCfg(v8, m_XinMoActiveLevel);
  if ( pQiQingCfg )
  {
    for ( it_0._M_node = std::list<AddAttribute>::begin(&pQiQingCfg->Attr)._M_node;
          ;
          std::_List_const_iterator<AddAttribute>::operator++(&it_0, 0) )
    {
      v22._M_node = std::list<AddAttribute>::end(&pQiQingCfg->Attr)._M_node;
      if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_0, &v22) )
        break;
      v9 = std::_List_const_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
      v10 = std::_List_const_iterator<AddAttribute>::operator->(&it_0);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v10->m_nAddAttrType, v9);
    }
  }
  for ( it_1._M_node = std::map<int,int>::begin(&this->m_QiQingLevel)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it_1, 0) )
  {
    v23._M_node = std::map<int,int>::end(&this->m_QiQingLevel)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it_1, &v23) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_1)->second;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_1)->first;
    v13 = Answer::Singleton<CfgData>::instance();
    v14 = CfgData::GetXinMoTable(v13);
    CurCfg_0 = XinMoTable::GetXinMoQiQingLevelUpCfg(v14, first, second);
    if ( CurCfg_0 )
    {
      for ( it_2._M_node = std::list<AddAttribute>::begin(&CurCfg_0->lAttr)._M_node;
            ;
            std::_List_const_iterator<AddAttribute>::operator++(&it_2, 0) )
      {
        v24._M_node = std::list<AddAttribute>::end(&CurCfg_0->lAttr)._M_node;
        if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_2, &v24) )
          break;
        v15 = std::_List_const_iterator<AddAttribute>::operator->(&it_2)->m_nAddAttrValue;
        v16 = std::_List_const_iterator<AddAttribute>::operator->(&it_2);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v16->m_nAddAttrType, v15);
      }
    }
  }
}


#####################################
int32_t __cdecl CXinMo::OnXinMoLevel(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t m_XinMoLevel; // ebx
  CfgData *v4; // rax
  const XinMoTable *XinMoTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const XinMoTable *v8; // rax
  CExtCurrency *Currency; // rax
  int64_t CostMoney; // rbx
  CExtCurrency *v11; // rax
  int8_t ConnId; // bl
  GameService *v13; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v16; // bl
  GameService *v17; // rax
  int64_t v18; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v21; // bl
  GameService *v22; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  const XinMoCfg *CurCfg; // [rsp+18h] [rbp-38h]
  const XinMoCfg *NextCfg; // [rsp+20h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  m_XinMoLevel = this->m_XinMoLevel;
  v4 = Answer::Singleton<CfgData>::instance();
  XinMoTable = CfgData::GetXinMoTable(v4);
  CurCfg = XinMoTable::GetXingMoCfg(XinMoTable, m_XinMoLevel);
  v6 = this->m_XinMoLevel + 1;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetXinMoTable(v7);
  NextCfg = XinMoTable::GetXingMoCfg(v8, v6);
  if ( !CurCfg || !NextCfg )
    return 10002;
  if ( CXinMo::GetActiveXinMoLevel(this) < NextCfg->NeedQiQingLevel )
    return 10002;
  if ( CurCfg->CostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < CurCfg->CostMoney )
      return 10002;
  }
  if ( CurCfg->ConstShenYaoBi > 0
    && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_VIGOUR) < CurCfg->ConstShenYaoBi )
  {
    return 10002;
  }
  if ( CurCfg->ConstExp > 0 && this->m_Exp < CurCfg->ConstExp )
    return 10002;
  if ( CurCfg->CostMoney > 0 )
  {
    CostMoney = CurCfg->CostMoney;
    v11 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v11, CostMoney, CURRENCY_CHANGE_REASON::GCR_XIN_MO_LEVEL_UP, 0) )
      return 10002;
  }
  if ( CurCfg->ConstShenYaoBi > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_VIGOUR,
          CurCfg->ConstShenYaoBi,
          CURRENCY_CHANGE_REASON::GCR_XIN_MO_LEVEL_UP,
          0) )
  {
    return 10002;
  }
  if ( CurCfg->ConstExp > 0 )
    this->m_Exp -= CurCfg->ConstExp;
  ++this->m_XinMoLevel;
  CXinMo::SendXiMoInfo(this);
  if ( NextCfg->GongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v13 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v13, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 10002;
    Answer::NetPacket::writeInt32(packet, NextCfg->GongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, this->m_XinMoLevel);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v16 = Player::getConnId(this->m_pPlayer);
    v17 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v17, v16, packet);
  }
  Player::RecalcAttr(this->m_pPlayer);
  v18 = this->m_XinMoLevel;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v21 = Player::getConnId(this->m_pPlayer);
  v22 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v22, v21, GateIndex, Proc, v18);
}


#####################################
int32_t __cdecl CXinMo::OnQiQingLevelUp(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const XinMoTable *XinMoTable; // rax
  int32_t v6; // r12d
  int32_t v7; // ebx
  CfgData *v8; // rax
  const XinMoTable *v9; // rax
  int32_t nNeedLastTypeLevel; // ebx
  ItemDataList *p_lCostList; // r12
  CExtCharBag *Bag; // rax
  int *v13; // rax
  CExtCharBag *v14; // rax
  int8_t ConnId; // bl
  GameService *v16; // rax
  CharId_t Cid; // rax
  int *v18; // rax
  uint32_t WOffset; // eax
  int8_t v20; // bl
  GameService *v21; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-60h] BYREF
  int32_t nType; // [rsp+2Ch] [rbp-44h] BYREF
  std::string val; // [rsp+30h] [rbp-40h] BYREF
  int32_t nLevel; // [rsp+44h] [rbp-2Ch]
  const XinMoQiQingLevelUpCfg *CurCfg; // [rsp+48h] [rbp-28h]
  const XinMoQiQingLevelUpCfg *NextCfg; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( this->m_pPlayer && inPacket )
  {
    nType = Answer::NetPacket::readInt32(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( this->m_XinMoActiveLevel >= nType )
    {
      nLevel = CXinMo::GetQiQingLevel(this, nType);
      v3 = nType;
      v4 = Answer::Singleton<CfgData>::instance();
      XinMoTable = CfgData::GetXinMoTable(v4);
      CurCfg = XinMoTable::GetXinMoQiQingLevelUpCfg(XinMoTable, v3, nLevel);
      v6 = nLevel + 1;
      v7 = nType;
      v8 = Answer::Singleton<CfgData>::instance();
      v9 = CfgData::GetXinMoTable(v8);
      NextCfg = XinMoTable::GetXinMoQiQingLevelUpCfg(v9, v7, v6);
      if ( CurCfg && NextCfg )
      {
        if ( nType - 1 <= 0
          || (nNeedLastTypeLevel = CurCfg->nNeedLastTypeLevel,
              nNeedLastTypeLevel <= CXinMo::GetQiQingLevel(this, nType - 1)) )
        {
          p_lCostList = &CurCfg->lCostList;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( CExtCharBag::RemoveItem(Bag, &vSlot, p_lCostList, ITEM_CHANGE_REASON::IDCR_XIN_MO_QI_QING_LEVEL_UP) )
          {
            v13 = std::map<int,int>::operator[](&this->m_QiQingLevel, &nType);
            ++*v13;
            v14 = Player::GetBag(this->m_pPlayer);
            CExtCharBag::ForceSendDirty(v14);
            CXinMo::SendXinMoQiQingLevel(this, nType);
            if ( NextCfg->GongGaoId > 0 )
            {
              ConnId = Player::getConnId(this->m_pPlayer);
              v16 = Answer::Singleton<GameService>::instance();
              packet = GameService::popNetpacket(v16, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
              if ( !packet )
              {
                v2 = 10002;
                goto LABEL_19;
              }
              Answer::NetPacket::writeInt32(packet, NextCfg->GongGaoId);
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              Cid = Player::getCid(this->m_pPlayer);
              Answer::NetPacket::writeInt64(packet, Cid);
              Answer::NetPacket::writeInt32(packet, nType);
              v18 = std::map<int,int>::operator[](&this->m_QiQingLevel, &nType);
              Answer::NetPacket::writeInt32(packet, *v18);
              WOffset = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, WOffset);
              v20 = Player::getConnId(this->m_pPlayer);
              v21 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v21, v20, packet);
            }
            Player::RecalcAttr(this->m_pPlayer);
            v2 = 0;
            goto LABEL_19;
          }
          v2 = 10002;
        }
        else
        {
          v2 = 10002;
        }
      }
      else
      {
        v2 = 10002;
      }
    }
    else
    {
      v2 = 10002;
    }
LABEL_19:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CXinMo::OnXinQing(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // eax
  CfgData *v4; // rax
  const XinMoTable *v5; // rax
  CfgData *v6; // rax
  const XinMoTable *XinMoTable; // rax
  int32_t Record; // eax
  CfgData *v9; // rax
  const XinMoTable *v10; // rax
  CExtCharBag *Bag; // rax
  int8_t ConnId; // bl
  GameService *v13; // rax
  CharId_t Cid; // rax
  int32_t v15; // eax
  uint32_t WOffset; // eax
  int8_t v17; // bl
  GameService *v18; // rax
  int64_t v19; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v22; // bl
  GameService *v23; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  int32_t nType; // [rsp+18h] [rbp-48h]
  int32_t ApperCount; // [rsp+1Ch] [rbp-44h]
  int32_t FlagCount; // [rsp+20h] [rbp-40h]
  bool BAddTimes; // [rsp+27h] [rbp-39h]
  int32_t ApperCount_0; // [rsp+28h] [rbp-38h]
  int32_t FlagCount_0; // [rsp+2Ch] [rbp-34h]
  const XinQingReward *pXinQingReward; // [rsp+30h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( CXinMo::GetXinMoLevel(this) <= 9 )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(inPacket);
  nType = Int32;
  switch ( Int32 )
  {
    case 1:
      if ( !CXinMo::IsYaoYiYao(this) )
        return 10002;
      FlagCount = CXinMo::GetFlagCount(this);
      if ( FlagCount > 6 )
        return 10002;
      BAddTimes = 1;
      if ( CXinMo::GetChangeXinQingTimes(this) <= 0 )
      {
        BAddTimes = 0;
        if ( !Player::DecCurrency(
                this->m_pPlayer,
                CURRENCY_TYPE::CURRENCY_GOLD,
                100,
                CURRENCY_CHANGE_REASON::GCR_CHANGE_XIN_QING,
                0) )
          return 10002;
      }
      if ( Player::getRecord(this->m_pPlayer, 37304) <= 19 )
      {
        v6 = Answer::Singleton<CfgData>::instance();
        XinMoTable = CfgData::GetXinMoTable(v6);
        ApperCount_0 = XinMoTable::GetAppearCount(XinMoTable, 7 - FlagCount);
        CXinMo::SetYaoYiYaoFlag(this, ApperCount_0);
      }
      else
      {
        CXinMo::SetYaoYiYaoFlag(this, 7 - FlagCount);
      }
      Record = Player::getRecord(this->m_pPlayer, 37304);
      Player::updateRecord(this->m_pPlayer, 37304, Record + 1);
      if ( BAddTimes )
        CXinMo::AddChangeXinQingTimes(this);
      break;
    case 2:
      if ( !CXinMo::IsYaoYiYao(this) )
        return 10002;
      FlagCount_0 = CXinMo::GetFlagCount(this);
      v9 = Answer::Singleton<CfgData>::instance();
      v10 = CfgData::GetXinMoTable(v9);
      pXinQingReward = XinMoTable::GetXinQingReward(v10, FlagCount_0);
      if ( !pXinQingReward )
        return 10002;
      Bag = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(Bag, &pXinQingReward->Items, ITEM_CHANGE_REASON::IDCR_XIN_MO_XIN_QING_REWARD) )
        return 10002;
      if ( pXinQingReward->GongGaoId > 0 )
      {
        ConnId = Player::getConnId(this->m_pPlayer);
        v13 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v13, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet )
          return 10002;
        Answer::NetPacket::writeInt32(packet, pXinQingReward->GongGaoId);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Cid = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, Cid);
        v15 = CXinMo::GetFlagCount(this);
        Answer::NetPacket::writeInt32(packet, v15);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v17 = Player::getConnId(this->m_pPlayer);
        v18 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v18, v17, packet);
      }
      this->m_QiQingInfo = 0;
      break;
    case 0:
      if ( CXinMo::IsYaoYiYao(this) )
        return 10002;
      if ( CXinMo::GetLeftYaoYiYaoTimes(this) <= 0 )
        return 10002;
      Player::updateRecord(this->m_pPlayer, 37304, 1);
      this->m_QiQingInfo = 0;
      v4 = Answer::Singleton<CfgData>::instance();
      v5 = CfgData::GetXinMoTable(v4);
      ApperCount = XinMoTable::GetAppearCount(v5, 7);
      CXinMo::SetFlag(this, 7);
      CXinMo::SetYaoYiYaoFlag(this, ApperCount);
      CXinMo::AddYaoYiYaoTimes(this);
      break;
  }
  CXinMo::SendXinQingInfo(this);
  v19 = nType;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v22 = Player::getConnId(this->m_pPlayer);
  v23 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v23, v22, GateIndex, Proc, v19);
  return 0;
}


#####################################
void __cdecl CXinMo::SetYaoYiYaoFlag(CXinMo *const this, int32_t nCount)
{
  int v2; // eax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v4; // rax
  int32_t v5; // edx
  Int32Vector nIdVt; // [rsp+10h] [rbp-40h] BYREF
  int32_t nNoFlagCount; // [rsp+34h] [rbp-1Ch]
  int32_t nSetCount; // [rsp+38h] [rbp-18h]
  int32_t i; // [rsp+3Ch] [rbp-14h]

  CXinMo::GetNoFlagIdList(&nIdVt, this);
  nNoFlagCount = std::vector<int>::size(&nIdVt);
  if ( nNoFlagCount <= nCount )
    v2 = nNoFlagCount;
  else
    v2 = nCount;
  nSetCount = v2;
  if ( v2 > 0 )
  {
    M_current = std::vector<int>::end(&nIdVt)._M_current;
    v4._M_current = std::vector<int>::begin(&nIdVt)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v4,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    for ( i = 0; i < nSetCount; ++i )
    {
      v5 = *std::vector<int>::operator[](&nIdVt, i);
      CXinMo::SetFlag(this, v5);
    }
  }
  std::vector<int>::~vector(&nIdVt);
}


#####################################
int32_t __cdecl CXinMo::GetFlagCount(CXinMo *const this)
{
  int32_t Count; // [rsp+10h] [rbp-10h]
  int32_t i; // [rsp+14h] [rbp-Ch]

  Count = 0;
  for ( i = 0; i <= 6; ++i )
  {
    if ( (this->m_QiQingInfo & (1 << i)) > 0 )
      ++Count;
  }
  return Count;
}


#####################################
void __cdecl CXinMo::SetFlag(CXinMo *const this, int32_t nId)
{
  if ( (unsigned int)nId < 8 )
    this->m_QiQingInfo |= 1 << nId;
}


#####################################
void __cdecl CXinMo::AddExp(CXinMo *const this, int32_t nValue)
{
  this->m_Exp += nValue;
  CXinMo::SendXiMoInfo(this);
}


#####################################
int32_t __cdecl CXinMo::OnActiveXinMo(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const XinMoTable *XinMoTable; // rax
  ItemDataList *p_CostItems; // r12
  CExtCharBag *Bag; // rax
  CExtCharBag *v8; // rax
  int8_t ConnId; // bl
  GameService *v10; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v13; // bl
  GameService *v14; // rax
  int64_t m_XinMoActiveLevel; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v18; // bl
  GameService *v19; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-60h] BYREF
  std::string val; // [rsp+30h] [rbp-40h] BYREF
  const QiQingCfg *CurCfg; // [rsp+40h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    v3 = this->m_XinMoActiveLevel + 1;
    v4 = Answer::Singleton<CfgData>::instance();
    XinMoTable = CfgData::GetXinMoTable(v4);
    CurCfg = XinMoTable::GetQiQingCfg(XinMoTable, v3);
    if ( CurCfg )
    {
      p_CostItems = &CurCfg->CostItems;
      Bag = Player::GetBag(this->m_pPlayer);
      if ( CExtCharBag::RemoveItem(Bag, &vSlot, p_CostItems, ITEM_CHANGE_REASON::IDCR_JI_HUO_XIN_MO) )
      {
        ++this->m_XinMoActiveLevel;
        v8 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::ForceSendDirty(v8);
        CXinMo::SendXiMoInfo(this);
        if ( CurCfg->GongGaoId > 0 )
        {
          ConnId = Player::getConnId(this->m_pPlayer);
          v10 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v10, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
          {
            v2 = 10002;
            goto LABEL_13;
          }
          Answer::NetPacket::writeInt32(packet, CurCfg->GongGaoId);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          Cid = Player::getCid(this->m_pPlayer);
          Answer::NetPacket::writeInt64(packet, Cid);
          Answer::NetPacket::writeInt32(packet, this->m_XinMoActiveLevel);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v13 = Player::getConnId(this->m_pPlayer);
          v14 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v14, v13, packet);
        }
        Player::RecalcAttr(this->m_pPlayer);
        m_XinMoActiveLevel = this->m_XinMoActiveLevel;
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v18 = Player::getConnId(this->m_pPlayer);
        v19 = Answer::Singleton<GameService>::instance();
        v2 = GameService::replySuccess(v19, v18, GateIndex, Proc, m_XinMoActiveLevel);
        goto LABEL_13;
      }
      v2 = 10002;
    }
    else
    {
      v2 = 10002;
    }
LABEL_13:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CXinMo::OnJinHua(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t itemId; // ebx
  CfgData *v4; // rax
  const XinMoTable *XinMoTable; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v7; // rax
  ItemDataList *p_CostItems; // r12
  CExtCharBag *Bag; // rax
  CExtCharBag *v10; // rax
  int8_t ConnId; // bl
  CEquipManager *v12; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v14; // rax
  CfgData *v15; // rax
  int8_t v16; // bl
  GameService *v17; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v20; // bl
  GameService *v21; // rax
  int64_t v22; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v25; // bl
  GameService *v26; // rax
  MemEquip equip; // [rsp+10h] [rbp-D0h] BYREF
  MemChrBag BagItem; // [rsp+50h] [rbp-90h] BYREF
  Int32Vector vSlot; // [rsp+70h] [rbp-70h] BYREF
  std::string val; // [rsp+90h] [rbp-50h] BYREF
  int32_t nPos; // [rsp+9Ch] [rbp-44h]
  const EquipJinHua *pJinHua; // [rsp+A0h] [rbp-40h]
  int32_t EquipId; // [rsp+ACh] [rbp-34h]
  const CfgEquip *pCfgEquip; // [rsp+B0h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+B8h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nPos = Answer::NetPacket::readInt32(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    Player::getBagSlotData(&BagItem, this->m_pPlayer, nPos);
    if ( BagItem.itemClass != 2 )
    {
      v2 = 10002;
LABEL_21:
      std::vector<int>::~vector(&vSlot);
      return v2;
    }
    itemId = BagItem.itemId;
    v4 = Answer::Singleton<CfgData>::instance();
    XinMoTable = CfgData::GetXinMoTable(v4);
    pJinHua = XinMoTable::GetJinHuaCfg(XinMoTable, itemId);
    if ( !pJinHua )
    {
      v2 = 10002;
      goto LABEL_21;
    }
    EquipId = EquipJinHua::GetParamRate(pJinHua);
    if ( EquipId <= 0 )
    {
      v2 = 10002;
      goto LABEL_21;
    }
    srcId = BagItem.srcId;
    v7 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v7, srcId);
    if ( equip.base > 0 )
    {
      p_CostItems = &pJinHua->CostItems;
      Bag = Player::GetBag(this->m_pPlayer);
      if ( CExtCharBag::RemoveItem(Bag, &vSlot, p_CostItems, ITEM_CHANGE_REASON::IDCR_XIN_MO_EQUIP_JIN_HUA) )
      {
        equip.base = EquipId;
        BagItem.itemId = EquipId;
        v10 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::SetSlotData(v10, nPos, &BagItem, ITEM_CHANGE_REASON::IDCR_XIN_MO_EQUIP_JIN_HUA, 0);
        ConnId = Player::getConnId(this->m_pPlayer);
        v12 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::UpdateMemEquip(v12, ConnId, &equip, 1467);
        m_pPlayer = this->m_pPlayer;
        v14 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::SendPlayerEquipInfo(v14, m_pPlayer, &equip);
        v15 = Answer::Singleton<CfgData>::instance();
        pCfgEquip = CfgData::getEquip(v15, EquipId);
        if ( pCfgEquip && pCfgEquip->m_nGrade > 7 )
        {
          v16 = Player::getConnId(this->m_pPlayer);
          v17 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v17, v16, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
          {
            v2 = 10002;
            goto LABEL_20;
          }
          Answer::NetPacket::writeInt32(packet, 548);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          Cid = Player::getCid(this->m_pPlayer);
          Answer::NetPacket::writeInt64(packet, Cid);
          Answer::NetPacket::writeInt32(packet, EquipId);
          Answer::NetPacket::writeInt32(packet, pCfgEquip->m_nGrade);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v20 = Player::getConnId(this->m_pPlayer);
          v21 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v21, v20, packet);
        }
        v22 = BagItem.itemId;
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v25 = Player::getConnId(this->m_pPlayer);
        v26 = Answer::Singleton<GameService>::instance();
        v2 = GameService::replySuccess(v26, v25, GateIndex, Proc, v22);
        goto LABEL_20;
      }
      v2 = 10002;
    }
    else
    {
      v2 = 10002;
    }
LABEL_20:
    MemEquip::~MemEquip(&equip);
    goto LABEL_21;
  }
  return 10002;
}


#####################################
void __cdecl CXinMo::SendXiMoInfo(CXinMo *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D3Eu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_Exp);
      Answer::NetPacket::writeInt32(packet, this->m_XinMoLevel);
      Answer::NetPacket::writeInt32(packet, this->m_XinMoActiveLevel);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CXinMo::SendXinQingInfo(CXinMo *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t LeftYaoYiYaoTimes; // edx
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D43u);
  if ( packet )
  {
    LeftYaoYiYaoTimes = CXinMo::GetLeftYaoYiYaoTimes(this);
    Answer::NetPacket::writeInt32(packet, LeftYaoYiYaoTimes);
    v4 = CXinMo::GetChangeXinQingTimes(this);
    Answer::NetPacket::writeInt32(packet, v4);
    Answer::NetPacket::writeInt32(packet, this->m_QiQingInfo);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v7 = Player::getConnId(this->m_pPlayer);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, GateIndex, packet);
  }
}


#####################################
void __cdecl CXinMo::SendXinMoQiQingLevel(CXinMo *const this, int32_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  int *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int32_t nTypea; // [rsp+4h] [rbp-4Ch] BYREF
  CXinMo *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  thisa = this;
  nTypea = nType;
  ConnId = Player::getConnId(this->m_pPlayer);
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D42u);
  if ( packet )
  {
    if ( nTypea )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      Answer::NetPacket::writeInt32(packet, nTypea);
      v6 = std::map<int,int>::operator[](&thisa->m_QiQingLevel, &nTypea);
      Answer::NetPacket::writeInt32(packet, *v6);
    }
    else
    {
      nSize = std::map<int,int>::size(&thisa->m_QiQingLevel);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&thisa->m_QiQingLevel)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&thisa->m_QiQingLevel)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->first);
        v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->second);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(thisa->m_pPlayer);
    v9 = Player::getConnId(thisa->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl CXinMo::OnGetItem(CXinMo *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v5; // rax
  const Map *pMap; // [rsp+10h] [rbp-10h]
  int Slot; // [rsp+18h] [rbp-8h]
  int i; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap || !Map::IsXinMoCun(pMap) )
    return 2;
  Slot = Answer::NetPacket::readInt32(inPacket);
  if ( Slot < -1 || Slot > 55 )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  if ( Slot == -1 )
  {
    for ( i = 0; i <= 55; ++i )
    {
      if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
      {
        v5 = Player::GetBag(this->m_pPlayer);
        if ( CExtCharBag::GetFreeSlotCount(v5) <= 0 )
        {
          Player::TiShiInfo(this->m_pPlayer, 2048, 0);
          return 2;
        }
        CXinMo::GetItem(this, i);
      }
    }
  }
  else
  {
    CXinMo::GetItem(this, Slot);
  }
  return 0;
}


#####################################
int32_t __cdecl CXinMo::OnDec(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::list<int> TmpList; // [rsp+10h] [rbp-30h] BYREF
  int32_t Slot[5]; // [rsp+2Ch] [rbp-14h] BYREF

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Slot[0] = Answer::NetPacket::readInt32(inPacket);
  if ( Slot[0] >= 0x38u )
    return 2;
  if ( this->m_ItemList[Slot[0]].itemCount <= 0 || this->m_ItemList[Slot[0]].itemId <= 0 )
    return 2;
  CXinMo::ResetBagSlot(this, Slot[0], 1);
  std::list<int>::list(&TmpList);
  std::list<int>::push_back(&TmpList, Slot);
  CXinMo::SendChangeItem(this, &TmpList);
  v2 = 0;
  std::list<int>::~list(&TmpList);
  return v2;
}


#####################################
int32_t __cdecl CXinMo::OnTidy(CXinMo *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rax
  MemChrBag *v4; // rax
  MemChrBag *v5; // rax
  MemChrBag *v6; // rax
  MemChrBag *v8; // rax
  MemChrBag *M_current; // rbx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v10; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v13; // rax
  int32_t *v16; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-90h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v22; // [rsp+80h] [rbp-50h] BYREF
  int32_t nBagSize; // [rsp+94h] [rbp-3Ch]
  int32_t slot; // [rsp+98h] [rbp-38h]
  int32_t i; // [rsp+9Ch] [rbp-34h]
  const MemChrBag *slotdata; // [rsp+A0h] [rbp-30h]
  bool bFind; // [rsp+AFh] [rbp-21h]
  MemChrBag *bagSlot; // [rsp+B0h] [rbp-20h]
  int32_t overlay; // [rsp+BCh] [rbp-14h]
  MemChrBag nullobj; // 0:^10.32

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  std::vector<MemChrBag>::vector(&items);
  nBagSize = 56;
  for ( i = 0; i < nBagSize; ++i )
  {
    slotdata = &this->m_ItemList[i];
    if ( this->m_ItemList[i].itemCount > 0 )
    {
      bFind = 0;
      for ( it._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&items)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        if ( v3->itemClass == slotdata->itemClass )
        {
          v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          if ( v4->itemId == slotdata->itemId )
          {
            v5 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
            if ( v5->bind == slotdata->bind )
            {
              v6 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
              if ( v6->srcId == slotdata->srcId )
              {
                v8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
                v8->itemCount += slotdata->itemCount;
                bFind = 1;
                break;
              }
            }
          }
        }
      }
      if ( !bFind )
        std::vector<MemChrBag>::push_back(&items, slotdata);
    }
  }
  M_current = std::vector<MemChrBag>::end(&items)._M_current;
  v10._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
  std::sort<__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>,bool (*)(MemChrBag const&,MemChrBag const&)>(
    v10,
    (__gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> >)M_current,
    (bool (*)(const MemChrBag *, const MemChrBag *))GreaterBagItem);
  slot = 0;
  for ( iter._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    v22._M_current = std::vector<MemChrBag>::end(&items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &v22) || slot >= nBagSize )
      break;
    bagSlot = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
    itemClass = bagSlot->itemClass;
    itemId = bagSlot->itemId;
    v13 = Answer::Singleton<CfgData>::instance();
    overlay = CfgData::getOverlay(v13, itemId, itemClass);
    if ( overlay > 0 )
    {
      while ( bagSlot->itemCount > overlay && slot < nBagSize )
      {
        nullobj = *bagSlot;
        nullobj.itemCount = overlay;
        bagSlot->itemCount -= overlay;
        this->m_ItemList[slot++] = nullobj;
      }
      if ( bagSlot->itemCount > 0 && slot < nBagSize )
        this->m_ItemList[slot++] = *bagSlot;
    }
  }
  while ( slot < nBagSize )
  {
    v16 = &this->m_QiQingInfo + 8 * slot;
    *((_QWORD *)v16 + 1) = 0;
    *((_QWORD *)v16 + 2) = 0;
    *((_QWORD *)v16 + 3) = 0;
    *((_QWORD *)v16 + 4) = 0;
    ++slot;
  }
  CXinMo::SendAllItem(this);
  v2 = 0;
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
bool __cdecl CXinMo::AddItem(CXinMo *const this, MemChrBagVector *p_Items)
{
  bool v2; // bl
  int32_t v3; // ebx
  int32_t i; // [rsp+3Ch] [rbp-44h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+40h] [rbp-40h] BYREF
  std::list<int> ItemList; // [rsp+50h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+60h] [rbp-20h] BYREF
  int32_t time; // [rsp+6Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  time = Unit::getNow(this->m_pPlayer);
  std::list<int>::list(&ItemList);
  std::list<int>::clear(&ItemList);
  for ( it._M_current = std::vector<MemChrBag>::begin(p_Items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(p_Items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
      break;
    for ( i = 0; i <= 55; ++i )
    {
      if ( this->m_ItemList[i].itemCount <= 0 || this->m_ItemList[i].itemId <= 0 )
      {
        v3 = i;
        this->m_ItemList[v3] = *__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
        CXinMo::AddXinMoBagLog(this, this->m_ItemList[i], 1, 5);
        std::list<int>::push_back(&ItemList, &i);
        break;
      }
    }
  }
  CXinMo::SendChangeItem(this, &ItemList);
  v2 = 1;
  std::list<int>::~list(&ItemList);
  return v2;
}


#####################################
void __cdecl CXinMo::GetItem(CXinMo *const this, int32_t Slot)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v3; // rax
  int32_t Slota; // [rsp+4h] [rbp-6Ch] BYREF
  CXinMo *thisa; // [rsp+8h] [rbp-68h]
  MemChrBag BagItem; // [rsp+10h] [rbp-60h] BYREF
  std::list<int> TmpList; // [rsp+30h] [rbp-40h] BYREF
  MemChrBagVector item; // [rsp+40h] [rbp-30h] BYREF

  thisa = this;
  Slota = Slot;
  if ( this->m_pPlayer )
  {
    if ( (unsigned int)Slota < 0x38 && thisa->m_ItemList[Slota].itemCount > 0 && thisa->m_ItemList[Slota].itemId > 0 )
    {
      Bag = Player::GetBag(thisa->m_pPlayer);
      if ( CExtCharBag::GetFreeSlotCount(Bag) > 0 )
      {
        BagItem = thisa->m_ItemList[Slota];
        std::vector<MemChrBag>::vector(&item);
        std::vector<MemChrBag>::push_back(&item, &BagItem);
        v3 = Player::GetBag(thisa->m_pPlayer);
        if ( CExtCharBag::AddItem(v3, &item, ITEM_CHANGE_REASON::IDCR_XIN_MO_BAG_GET) )
        {
          CXinMo::ResetBagSlot(thisa, Slota, 2);
          std::list<int>::list(&TmpList);
          std::list<int>::push_back(&TmpList, &Slota);
          CXinMo::SendChangeItem(thisa, &TmpList);
          std::list<int>::~list(&TmpList);
        }
        std::vector<MemChrBag>::~vector(&item);
      }
    }
  }
}


#####################################
void __cdecl CXinMo::SendAllItem(CXinMo *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  int32_t Count; // [rsp+20h] [rbp-20h]
  int32_t OldOffet; // [rsp+24h] [rbp-1Ch]
  int32_t NewOffet; // [rsp+28h] [rbp-18h]
  int i; // [rsp+2Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D3Fu);
    if ( packet )
    {
      Count = 0;
      OldOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( i = 0; i <= 55; ++i )
      {
        if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
        {
          ++Count;
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemId);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].itemClass);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemCount);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].bind);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].endTime);
          Answer::NetPacket::writeInt64(packet, this->m_ItemList[i].srcId);
        }
      }
      NewOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, OldOffet);
      Answer::NetPacket::writeInt32(packet, Count);
      Answer::NetPacket::setWOffset(packet, NewOffet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CXinMo::SendChangeItem(CXinMo *const this, std::list<int> *const ItemList)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int *v4; // rax
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  int *v9; // rax
  int *v10; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  Count = std::list<int>::size(ItemList);
  if ( Count > 0 )
  {
    if ( this->m_pPlayer )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D40u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, Count);
        for ( it._M_node = std::list<int>::begin(ItemList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
        {
          __x._M_node = std::list<int>::end(ItemList)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
            break;
          v4 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, *v4);
          v5 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v5].itemId);
          v6 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v6].itemClass);
          v7 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v7].itemCount);
          v8 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v8].bind);
          v9 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v9].endTime);
          v10 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt64(packet, this->m_ItemList[*v10].srcId);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v13 = Player::getConnId(this->m_pPlayer);
        v14 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v14, v13, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CXinMo::CleanXinMoBag(CXinMo *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-24h] BYREF
  std::list<int> TmpList; // [rsp+20h] [rbp-20h] BYREF

  std::list<int>::list(&TmpList);
  for ( i = 0; i <= 55; ++i )
  {
    if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
    {
      CXinMo::ResetBagSlot(this, i, 3);
      std::list<int>::push_back(&TmpList, &i);
    }
  }
  CXinMo::SendChangeItem(this, &TmpList);
  std::list<int>::~list(&TmpList);
}


#####################################
void __cdecl CXinMo::DieDropFromXinMoBag(CXinMo *const this, MemChrBagVector *const TmpVt)
{
  Answer::Random *v3; // rax
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::list<int> TmpList; // [rsp+20h] [rbp-30h] BYREF
  Map *pMap; // [rsp+30h] [rbp-20h]
  int32_t nRand; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( pMap && Map::IsXinMoMap(pMap) )
    {
      std::list<int>::list(&TmpList);
      for ( i = 0; i <= 55; ++i )
      {
        if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
        {
          v3 = Answer::Singleton<Answer::Random>::instance();
          nRand = Answer::Random::generate(v3, 1, 100);
          if ( nRand <= 20 )
            std::vector<MemChrBag>::push_back(TmpVt, &this->m_ItemList[i]);
          CXinMo::ResetBagSlot(this, i, 4);
          std::list<int>::push_back(&TmpList, &i);
        }
      }
      CXinMo::SendChangeItem(this, &TmpList);
      std::list<int>::~list(&TmpList);
    }
  }
}


#####################################
int32_t __cdecl CXinMo::GetFreeSlotCount(CXinMo *const this)
{
  int32_t nCount; // [rsp+10h] [rbp-8h]
  int32_t i; // [rsp+14h] [rbp-4h]

  nCount = 0;
  for ( i = 0; i <= 55; ++i )
  {
    if ( !this->m_ItemList[i].itemCount || !this->m_ItemList[i].itemId )
      ++nCount;
  }
  return nCount;
}


#####################################
int32_t __cdecl CXinMo::ResetBagSlot(CXinMo *const this, int32_t nSlot, int32_t Opway)
{
  CXinMo::AddXinMoBagLog(this, this->m_ItemList[nSlot], 2, Opway);
  bzero(&this->m_ItemList[nSlot], 0x20u);
  return 0;
}


#####################################
void __cdecl CXinMo::AddXinMoBagLog(CXinMo *const this, MemChrBag item, int32_t falg, int32_t Opway)
{
  CharId_t Cid; // rbx
  DBService *v5; // rax

  if ( this->m_pPlayer )
  {
    Cid = Player::getCid(this->m_pPlayer);
    v5 = Answer::Singleton<DBService>::instance();
    DBService::LogXinMoBag(v5, Cid, item, falg, Opway);
  }
}


#####################################
int32_t __cdecl CXinMo::GetQiQingLevel(CXinMo *const this, int32_t nType)
{
  int32_t nTypea; // [rsp+4h] [rbp-2Ch] BYREF
  CXinMo *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nTypea = nType;
  it._M_node = std::map<int,int>::find(&this->m_QiQingLevel, &nTypea)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_QiQingLevel)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
int32_t __cdecl CXinMo::GetLeftYaoYiYaoTimes(CXinMo *const this)
{
  if ( this->m_pPlayer )
    return 10 - Player::getRecord(this->m_pPlayer, 2122);
  else
    return 0;
}


#####################################
int32_t __cdecl CXinMo::GetChangeXinQingTimes(CXinMo *const this)
{
  if ( this->m_pPlayer )
    return 10 - Player::getRecord(this->m_pPlayer, 2123);
  else
    return 0;
}


#####################################
void __cdecl CXinMo::AddYaoYiYaoTimes(CXinMo *const this)
{
  int32_t Record; // eax

  if ( this->m_pPlayer )
  {
    Record = Player::getRecord(this->m_pPlayer, 2122);
    Player::updateRecord(this->m_pPlayer, 2122, Record + 1);
  }
}


#####################################
void __cdecl CXinMo::AddChangeXinQingTimes(CXinMo *const this)
{
  int32_t Record; // eax

  if ( this->m_pPlayer )
  {
    Record = Player::getRecord(this->m_pPlayer, 2123);
    Player::updateRecord(this->m_pPlayer, 2123, Record + 1);
  }
}


