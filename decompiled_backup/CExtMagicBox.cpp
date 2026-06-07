// Decompiled methods for class: CExtMagicBox
// Source: gameserver.cc
// Total methods: 23

#####################################
void __cdecl CExtMagicBox::~CExtMagicBox(CExtMagicBox *const this)
{
  CExtMagicBox::~CExtMagicBox(this);
  operator delete(this);
}


#####################################
void __cdecl CExtMagicBox::OnCleanUp(CExtMagicBox *const this)
{
  this->m_nCombiPoints = 0;
  this->m_nLastReviveTime = 0;
  std::list<int>::clear(&this->m_lActiveScrolls);
  std::list<int>::clear(&this->m_lSuccessIds);
}


#####################################
void __cdecl CExtMagicBox::OnLoadFromDB(CExtMagicBox *const this, const PlayerDBData *const dbData)
{
  CExtMagicBox var30; // [rsp+10h] [rbp-30h] BYREF

  this->m_nCombiPoints = dbData->m_MagicBoxDBData.nCombiPoints;
  this->m_nLastReviveTime = dbData->m_MagicBoxDBData.nLastReviveTime;
  CExtMagicBox::loadString(&var30, (const std::string *const)this);
  std::list<int>::operator=(&this->m_lActiveScrolls, (const std::list<int> *const)&var30);
  std::list<int>::~list((std::list<int> *const)&var30);
  CExtMagicBox::loadString((CExtMagicBox *const)&var30.m_nCombiPoints, (const std::string *const)this);
  std::list<int>::operator=(&this->m_lSuccessIds, (const std::list<int> *const)&var30.m_nCombiPoints);
  std::list<int>::~list((std::list<int> *const)&var30.m_nCombiPoints);
}


#####################################
void __cdecl CExtMagicBox::OnSaveToDB(CExtMagicBox *const this, PlayerDBData *const dbData)
{
  CExtMagicBox var30; // [rsp+10h] [rbp-30h] BYREF

  dbData->m_MagicBoxDBData.nCombiPoints = this->m_nCombiPoints;
  dbData->m_MagicBoxDBData.nLastReviveTime = this->m_nLastReviveTime;
  CExtMagicBox::saveString(&var30, (const Int32List *const)this);
  std::string::operator=(&dbData->m_MagicBoxDBData.strActiveScrolls, &var30);
  std::string::~string(&var30);
  CExtMagicBox::saveString((CExtMagicBox *const)&var30.m_nCombiPoints, (const Int32List *const)this);
  std::string::operator=(&dbData->m_MagicBoxDBData.strSuccessIds, &var30.m_nCombiPoints);
  std::string::~string(&var30.m_nCombiPoints);
}


#####################################
void __cdecl CExtMagicBox::OnUpdate(CExtMagicBox *const this, int64_t curTick)
{
  int32_t v2; // edx
  int32_t nNowTime; // [rsp+18h] [rbp-8h]
  int32_t nAddTimes; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    nNowTime = Unit::getNow(this->m_pPlayer);
    if ( this->m_nLastReviveTime )
    {
      nAddTimes = (nNowTime - this->m_nLastReviveTime) / 300;
      if ( nAddTimes > 0 )
      {
        this->m_nLastReviveTime += 300 * nAddTimes;
        v2 = nAddTimes * CExtMagicBox::getPointsReviveValue(this);
        CExtMagicBox::AddPoints(this, v2);
      }
    }
    else
    {
      this->m_nCombiPoints = CExtMagicBox::getMaxPoints(this);
      CExtMagicBox::SendItemCombiPoint(this);
      this->m_nLastReviveTime = nNowTime;
    }
  }
}


#####################################
void __cdecl CExtMagicBox::GetInterestsProtocol(CExtMagicBox *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v3; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v4; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v5; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v6; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 725;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 726;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 727;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 728;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 729;
  std::list<unsigned short>::push_back(procList, &v6);
}


#####################################
int32_t __cdecl CExtMagicBox::DispatchNetDatas(CExtMagicBox *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x2D5u:
      result = CExtMagicBox::onRequestInfo(this, inPacket);
      break;
    case 0x2D6u:
      result = CExtMagicBox::onItemCombi(this, inPacket);
      break;
    case 0x2D7u:
      result = CExtMagicBox::onOrnamentCombi(this, inPacket);
      break;
    case 0x2D8u:
      result = CExtMagicBox::onEquipCombi(this, inPacket);
      break;
    case 0x2D9u:
      result = CExtMagicBox::onItemDecompose(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtMagicBox::onRequestInfo(CExtMagicBox *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CExtMagicBox::SendMagicBoxInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtMagicBox::onItemDecompose(CExtMagicBox *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CExtCharBag *Bag; // rax
  CfgData *v4; // rax
  int v5; // r12d
  std::string *v6; // rax
  const char *v7; // rax
  CfgData *v8; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t Record; // eax
  CExtCharBag *v11; // rax
  int32_t FreeSlotCount; // eax
  int64_t m_nCostMoney; // rbx
  CExtCurrency *Currency; // rax
  CExtCharBag *v15; // rax
  MemChrBagVector *p_m_vGiveItems; // rbx
  CExtCharBag *v17; // rax
  int32_t v18; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t m_nLimitValue; // ebx
  int64_t v21; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v25; // rax
  MemChrBag SlotData; // [rsp+10h] [rbp-B0h] BYREF
  StringVector vParam; // [rsp+30h] [rbp-90h] BYREF
  std::string delims; // [rsp+50h] [rbp-70h] BYREF
  char v30; // [rsp+5Fh] [rbp-61h] BYREF
  std::vector<MemChrBag> p_Items; // [rsp+60h] [rbp-60h] BYREF
  int32_t Slot; // [rsp+7Ch] [rbp-44h]
  const CfgEquipDecompose *pCfgSuitDecompose; // [rsp+80h] [rbp-40h]
  int32_t UseBagCount; // [rsp+88h] [rbp-38h]
  int32_t LeftTime; // [rsp+8Ch] [rbp-34h]
  CfgItem *pItem; // [rsp+90h] [rbp-30h]
  int32_t Time; // [rsp+9Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Slot = Answer::NetPacket::readInt32(inPacket);
  Bag = Player::GetBag(this->m_pPlayer);
  SlotData = *CExtCharBag::GetSlotData(Bag, Slot);
  if ( SlotData.itemClass <= 0 || SlotData.itemCount <= 0 || SlotData.itemId <= 0 )
    return 10002;
  if ( SlotData.itemClass != 1 )
    goto LABEL_18;
  v4 = Answer::Singleton<CfgData>::instance();
  pItem = CfgData::getItem(v4, SlotData.itemId);
  if ( !pItem )
    return 10002;
  if ( pItem->type != 169 )
    goto LABEL_18;
  std::allocator<char>::allocator(&v30);
  std::string::string(&delims, &unk_8E4778);
  Answer::StringUtility::split(&vParam, &pItem->effect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v30);
  if ( std::vector<std::string>::size(&vParam) == 2 )
  {
    v6 = std::vector<std::string>::operator[](&vParam, 1u);
    v7 = (const char *)std::string::c_str(v6);
    Time = atoi(v7);
    if ( Time <= 0 )
    {
      v5 = 1;
    }
    else
    {
      v2 = 10002;
      v5 = 0;
    }
  }
  else
  {
    v2 = 10002;
    v5 = 0;
  }
  std::vector<std::string>::~vector(&vParam);
  if ( v5 )
  {
LABEL_18:
    v8 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v8);
    pCfgSuitDecompose = CfgEquipTable::GetEquipDecompose(EquipTable, SlotData.itemClass, SlotData.itemId);
    if ( pCfgSuitDecompose )
    {
      if ( pCfgSuitDecompose->m_nLimitType <= 0
        || pCfgSuitDecompose->m_nLimitType > 20
        || pCfgSuitDecompose->m_nLimitValue <= 0
        || (Record = Player::getRecord(this->m_pPlayer, pCfgSuitDecompose->m_nLimitType + 8010),
            Record < pCfgSuitDecompose->m_nLimitValue) )
      {
        if ( pCfgSuitDecompose->m_NpcId > 0 && !Player::NearNpc(this->m_pPlayer, pCfgSuitDecompose->m_NpcId) )
        {
          return 0;
        }
        else if ( std::vector<MemChrBag>::size(&pCfgSuitDecompose->m_vGiveItems) )
        {
          std::vector<MemChrBag>::vector(&p_Items, &pCfgSuitDecompose->m_vGiveItems);
          UseBagCount = CItemHelper::NeedUseBagCount(&p_Items);
          std::vector<MemChrBag>::~vector(&p_Items);
          if ( UseBagCount > 0 )
          {
            v11 = Player::GetBag(this->m_pPlayer);
            FreeSlotCount = CExtCharBag::GetFreeSlotCount(v11);
            if ( FreeSlotCount >= UseBagCount )
            {
              if ( pCfgSuitDecompose->m_nCostMoney > 0
                && (m_nCostMoney = pCfgSuitDecompose->m_nCostMoney,
                    Currency = Player::GetCurrency(this->m_pPlayer),
                    !CExtCurrency::DecMoneyAndNoBind(
                       Currency,
                       m_nCostMoney,
                       CURRENCY_CHANGE_REASON::MCR_ITEM_DECOMPOSE,
                       0)) )
              {
                return 10002;
              }
              else
              {
                --SlotData.itemCount;
                v15 = Player::GetBag(this->m_pPlayer);
                CExtCharBag::SetSlotData(v15, Slot, &SlotData, ITEM_CHANGE_REASON::ICR_ITEM_DECOMPOSE, 0);
                p_m_vGiveItems = &pCfgSuitDecompose->m_vGiveItems;
                v17 = Player::GetBag(this->m_pPlayer);
                CExtCharBag::AddItem(v17, p_m_vGiveItems, ITEM_CHANGE_REASON::ICR_ITEM_DECOMPOSE_GIVE);
                LeftTime = -1;
                if ( pCfgSuitDecompose->m_nLimitType > 0
                  && pCfgSuitDecompose->m_nLimitType <= 20
                  && pCfgSuitDecompose->m_nLimitValue > 0 )
                {
                  v18 = pCfgSuitDecompose->m_nLimitType + 8010;
                  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
                  CExtOperateLimit::AddLimitCount(OperateLimit, v18, 1);
                  m_nLimitValue = pCfgSuitDecompose->m_nLimitValue;
                  LeftTime = m_nLimitValue - Player::getRecord(this->m_pPlayer, pCfgSuitDecompose->m_nLimitType + 8010);
                }
                v21 = LeftTime;
                Proc = Answer::NetPacket::getProc(inPacket);
                GateIndex = Player::getGateIndex(this->m_pPlayer);
                ConnId = Player::getConnId(this->m_pPlayer);
                v25 = Answer::Singleton<GameService>::instance();
                GameService::replySuccess(v25, ConnId, GateIndex, Proc, v21);
                return 0;
              }
            }
            else
            {
              return 10002;
            }
          }
          else
          {
            return 10002;
          }
        }
        else
        {
          return 10002;
        }
      }
      else
      {
        return 10002;
      }
    }
    else
    {
      return 10002;
    }
  }
  return v2;
}


#####################################
int32_t __cdecl CExtMagicBox::onItemCombi(CExtMagicBox *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgItemCombiTable *ItemCombiTable; // rax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  const ItemData *v9; // rbx
  CExtCharBag *Bag; // rax
  const ItemData *v11; // rbx
  CExtCharBag *v12; // rax
  const ItemData *v13; // rax
  const ItemData *v14; // rax
  int32_t m_nId; // r12d
  int8_t m_nClass; // bl
  CfgData *v17; // rax
  int v18; // ebx
  const ItemData *v19; // rax
  const ItemData *v20; // rax
  const ItemData *v21; // rax
  int8_t v23; // r12
  int32_t v24; // ebx
  CfgData *v25; // rax
  const ItemData *v26; // rax
  int64_t v27; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v31; // rax
  int8_t v32; // r12
  int32_t v33; // ebx
  CfgData *v34; // rax
  const MemChrBag *v35; // rax
  int8_t v36; // r12
  int32_t v37; // ebx
  CfgData *v38; // rax
  CExtCharBag *v39; // rax
  int32_t FreeSlotCount; // eax
  CExtCharBag *v41; // rax
  CExtCurrency *v42; // rax
  CExtCharBag *v43; // rax
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<int> v45; // rax
  MemChrBag backItem; // [rsp+20h] [rbp-190h] BYREF
  MemChrBag giveItem; // [rsp+40h] [rbp-170h]
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter_0; // [rsp+60h] [rbp-150h] BYREF
  ItemData stu_0; // [rsp+70h] [rbp-140h] BYREF
  ItemData stu; // [rsp+80h] [rbp-130h] BYREF
  std::_List_const_iterator<ItemData> iter; // [rsp+90h] [rbp-120h] BYREF
  MemChrBagVector vAddItem; // [rsp+A0h] [rbp-110h] BYREF
  ItemDataList lCostItem; // [rsp+C0h] [rbp-F0h] BYREF
  Int32Vector vSlot; // [rsp+D0h] [rbp-E0h] BYREF
  int32_t nId; // [rsp+ECh] [rbp-C4h] BYREF
  std::_List_const_iterator<ItemData> __x; // [rsp+F0h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+100h] [rbp-B0h] BYREF
  std::_List_iterator<int> v60; // [rsp+110h] [rbp-A0h] BYREF
  std::_List_iterator<int> v61; // [rsp+120h] [rbp-90h] BYREF
  int32_t nTimes; // [rsp+128h] [rbp-88h]
  int8_t bAutoBuy; // [rsp+12Fh] [rbp-81h]
  const CfgItemCombi *pCfgItemCombi; // [rsp+130h] [rbp-80h]
  int64_t nCostMoney; // [rsp+138h] [rbp-78h]
  int32_t nCombiBindTimes; // [rsp+140h] [rbp-70h]
  int32_t nCombiAllTimes; // [rsp+144h] [rbp-6Ch]
  int64_t nNeedGold; // [rsp+148h] [rbp-68h]
  int32_t nCleanBagSlot; // [rsp+150h] [rbp-60h]
  int32_t nUnBindTimes; // [rsp+154h] [rbp-5Ch]
  int32_t nBindTimes; // [rsp+158h] [rbp-58h]
  int32_t nSuccessTimes; // [rsp+15Ch] [rbp-54h]
  int32_t nFailTimes; // [rsp+160h] [rbp-50h]
  int32_t nGiveBind; // [rsp+164h] [rbp-4Ch]
  int32_t nGiveUnBind; // [rsp+168h] [rbp-48h]
  int32_t nNeedBagSlot; // [rsp+16Ch] [rbp-44h]
  int32_t nHaveBindCount; // [rsp+170h] [rbp-40h]
  int32_t nHaveUnBindCount; // [rsp+174h] [rbp-3Ch]
  int32_t nBindTimes_0; // [rsp+178h] [rbp-38h]
  int32_t nLayNum; // [rsp+17Ch] [rbp-34h]
  int32_t nCostAll; // [rsp+180h] [rbp-30h]
  int32_t nDiffCount; // [rsp+184h] [rbp-2Ch]
  CfgGameShop *pShop; // [rsp+188h] [rbp-28h]
  int32_t nLayNum_0; // [rsp+194h] [rbp-1Ch]
  int32_t nLayNum_1; // [rsp+198h] [rbp-18h]
  int32_t nLayNum_2; // [rsp+19Ch] [rbp-14h]

  if ( this->m_pPlayer && inPacket )
  {
    nId = Answer::NetPacket::readInt32(inPacket);
    nTimes = Answer::NetPacket::readInt32(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    bAutoBuy = Answer::NetPacket::readInt8(inPacket);
    if ( nTimes <= 0 )
    {
      v2 = 10002;
LABEL_98:
      std::vector<int>::~vector(&vSlot);
      return v2;
    }
    v3 = nId;
    v4 = Answer::Singleton<CfgData>::instance();
    ItemCombiTable = CfgData::GetItemCombiTable(v4);
    pCfgItemCombi = CfgItemCombiTable::GetItemCombi(ItemCombiTable, v3);
    if ( !pCfgItemCombi )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    if ( pCfgItemCombi->m_nCombiType )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    if ( pCfgItemCombi->m_bNeedActive > 0 && !CExtMagicBox::isActive(this, nId) )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    if ( pCfgItemCombi->m_nMoney < 0 )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    if ( std::vector<MemChrBag>::empty(&pCfgItemCombi->m_vGiveItem) )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    giveItem = *std::vector<MemChrBag>::front(&pCfgItemCombi->m_vGiveItem);
    nCostMoney = pCfgItemCombi->m_nMoney * (__int64)nTimes;
    Currency = Player::GetCurrency(this->m_pPlayer);
    MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
    if ( MoneyBindAndNoBind < nCostMoney )
    {
      v2 = 10002;
      goto LABEL_98;
    }
    nCombiBindTimes = 0;
    nCombiAllTimes = 0;
    nNeedGold = 0;
    nCleanBagSlot = 0;
    std::list<ItemData>::list(&lCostItem);
    for ( iter._M_node = std::list<ItemData>::begin(&pCfgItemCombi->m_lCostItem)._M_node;
          ;
          std::_List_const_iterator<ItemData>::operator++(&iter) )
    {
      __x._M_node = std::list<ItemData>::end(&pCfgItemCombi->m_lCostItem)._M_node;
      if ( !std::_List_const_iterator<ItemData>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_const_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
      {
        v9 = std::_List_const_iterator<ItemData>::operator*(&iter);
        Bag = Player::GetBag(this->m_pPlayer);
        nHaveBindCount = CExtCharBag::HaveItemCount(Bag, v9, 1, 0);
        v11 = std::_List_const_iterator<ItemData>::operator*(&iter);
        v12 = Player::GetBag(this->m_pPlayer);
        nHaveUnBindCount = CExtCharBag::HaveItemCount(v12, v11, 0, 0);
        v13 = std::_List_const_iterator<ItemData>::operator->(&iter);
        if ( nTimes * v13->m_nCount <= nHaveBindCount + nHaveUnBindCount )
        {
          v18 = nHaveBindCount + nHaveUnBindCount;
          nCombiAllTimes = v18 / std::_List_const_iterator<ItemData>::operator->(&iter)->m_nCount;
          if ( nCombiAllTimes > nTimes )
            nCombiAllTimes = nTimes;
          stu_0 = *std::_List_const_iterator<ItemData>::operator*(&iter);
          v19 = std::_List_const_iterator<ItemData>::operator->(&iter);
          stu_0.m_nCount = nCombiAllTimes * v19->m_nCount;
          std::list<ItemData>::push_back(&lCostItem, &stu_0);
        }
        else
        {
          if ( bAutoBuy != 1 )
          {
            v2 = 10002;
            goto LABEL_97;
          }
          v14 = std::_List_const_iterator<ItemData>::operator->(&iter);
          nDiffCount = nTimes * v14->m_nCount - (nHaveBindCount + nHaveUnBindCount);
          m_nId = std::_List_const_iterator<ItemData>::operator->(&iter)->m_nId;
          m_nClass = std::_List_const_iterator<ItemData>::operator->(&iter)->m_nClass;
          v17 = Answer::Singleton<CfgData>::instance();
          pShop = CfgData::GetGameShopItem(v17, m_nClass, m_nId);
          if ( !pShop )
          {
            v2 = 10002;
            goto LABEL_97;
          }
          nNeedGold += nDiffCount * pShop->Price;
          *(_QWORD *)&stu.m_nId = *(_QWORD *)&std::_List_const_iterator<ItemData>::operator*(&iter)->m_nId;
          stu.m_nCount = nHaveBindCount + nHaveUnBindCount;
          std::list<ItemData>::push_back(&lCostItem, &stu);
          nCombiAllTimes = nTimes;
        }
        v20 = std::_List_const_iterator<ItemData>::operator->(&iter);
        nBindTimes_0 = nHaveBindCount / v20->m_nCount;
        if ( nBindTimes_0 > nCombiBindTimes )
          nCombiBindTimes = nBindTimes_0;
        if ( nCombiAllTimes > nBindTimes_0 )
        {
          v21 = std::_List_const_iterator<ItemData>::operator->(&iter);
          if ( nHaveBindCount % v21->m_nCount )
            ++nCombiBindTimes;
        }
        v23 = std::_List_const_iterator<ItemData>::operator->(&iter)->m_nClass;
        v24 = std::_List_const_iterator<ItemData>::operator->(&iter)->m_nId;
        v25 = Answer::Singleton<CfgData>::instance();
        nLayNum = CfgData::getOverlay(v25, v24, v23);
        if ( nLayNum <= 0 )
        {
          v2 = 10002;
          goto LABEL_97;
        }
        v26 = std::_List_const_iterator<ItemData>::operator->(&iter);
        nCostAll = nCombiAllTimes * v26->m_nCount;
        nCleanBagSlot += nCostAll / nLayNum;
      }
    }
    if ( nNeedGold > 0 )
    {
      v27 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
      if ( v27 < nNeedGold )
      {
        v2 = 10002;
LABEL_97:
        std::list<ItemData>::~list(&lCostItem);
        goto LABEL_98;
      }
    }
    if ( nCombiAllTimes <= 0 )
    {
      v2 = 10002;
      goto LABEL_97;
    }
    if ( nCombiBindTimes > nCombiAllTimes )
      nCombiBindTimes = nCombiAllTimes;
    nUnBindTimes = RandHelper::CalRandTimes(
                     nCombiAllTimes - nCombiBindTimes,
                     pCfgItemCombi->m_nRate,
                     pCfgItemCombi->m_nTotalRate);
    nBindTimes = RandHelper::CalRandTimes(nCombiBindTimes, pCfgItemCombi->m_nRate, pCfgItemCombi->m_nTotalRate);
    nSuccessTimes = nBindTimes + nUnBindTimes;
    nFailTimes = nCombiAllTimes - (nBindTimes + nUnBindTimes);
    nGiveBind = nBindTimes * giveItem.itemCount;
    nGiveUnBind = nUnBindTimes * giveItem.itemCount;
    nNeedBagSlot = 0;
    std::vector<MemChrBag>::vector(&vAddItem);
    if ( nGiveBind > 0 )
    {
      *(_QWORD *)&backItem.itemId = *(_QWORD *)&giveItem.itemId;
      *(_DWORD *)&backItem.bind = *(_DWORD *)&giveItem.bind;
      *(_QWORD *)&backItem.endTime = *(_QWORD *)&giveItem.endTime;
      backItem.srcId = giveItem.srcId;
      backItem.itemCount = nGiveBind;
      backItem.bind = 1;
      std::vector<MemChrBag>::push_back(&vAddItem, &backItem);
      itemClass = giveItem.itemClass;
      itemId = giveItem.itemId;
      v31 = Answer::Singleton<CfgData>::instance();
      nLayNum_0 = CfgData::getOverlay(v31, itemId, itemClass);
      if ( nLayNum_0 <= 0 )
      {
        v2 = 10002;
LABEL_96:
        std::vector<MemChrBag>::~vector(&vAddItem);
        goto LABEL_97;
      }
      nNeedBagSlot += nGiveBind / nLayNum_0;
      if ( nGiveBind % nLayNum_0 )
        ++nNeedBagSlot;
    }
    if ( nGiveUnBind > 0 )
    {
      *(_QWORD *)&backItem.itemId = *(_QWORD *)&giveItem.itemId;
      *(_DWORD *)&backItem.bind = *(_DWORD *)&giveItem.bind;
      *(_QWORD *)&backItem.endTime = *(_QWORD *)&giveItem.endTime;
      backItem.srcId = giveItem.srcId;
      backItem.itemCount = nGiveUnBind;
      backItem.bind = 0;
      std::vector<MemChrBag>::push_back(&vAddItem, &backItem);
      v32 = giveItem.itemClass;
      v33 = giveItem.itemId;
      v34 = Answer::Singleton<CfgData>::instance();
      nLayNum_1 = CfgData::getOverlay(v34, v33, v32);
      if ( nLayNum_1 <= 0 )
      {
        v2 = 10002;
        goto LABEL_96;
      }
      nNeedBagSlot += nGiveUnBind / nLayNum_1;
      if ( nGiveUnBind % nLayNum_1 )
        ++nNeedBagSlot;
    }
    if ( nFailTimes > 0 )
    {
      for ( iter_0._M_current = std::vector<MemChrBag>::begin(&pCfgItemCombi->m_vBackItem)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter_0) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&pCfgItemCombi->m_vBackItem)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&iter_0, &__rhs) )
          break;
        backItem = *__gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter_0);
        v35 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter_0);
        backItem.itemCount = nFailTimes * v35->itemCount;
        std::vector<MemChrBag>::push_back(&vAddItem, &backItem);
        v36 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter_0)->itemClass;
        v37 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter_0)->itemId;
        v38 = Answer::Singleton<CfgData>::instance();
        nLayNum_2 = CfgData::getOverlay(v38, v37, v36);
        if ( nLayNum_2 <= 0 )
        {
          v2 = 10002;
          goto LABEL_96;
        }
        nNeedBagSlot += backItem.itemCount / nLayNum_2;
        if ( backItem.itemCount % nLayNum_2 )
          ++nNeedBagSlot;
      }
    }
    v39 = Player::GetBag(this->m_pPlayer);
    FreeSlotCount = CExtCharBag::GetFreeSlotCount(v39);
    if ( FreeSlotCount >= nNeedBagSlot - nCleanBagSlot )
    {
      v41 = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::RemoveCombiItem(v41, &lCostItem, ITEM_CHANGE_REASON::ICR_COMBINE) )
      {
        v2 = 10002;
      }
      else if ( nNeedGold > 0
             && !Player::DecCurrency(
                   this->m_pPlayer,
                   CURRENCY_TYPE::CURRENCY_GOLD,
                   nNeedGold,
                   CURRENCY_CHANGE_REASON::GCR_ITEM_COMBI_AUTO_BUY,
                   nId) )
      {
        v2 = 10002;
      }
      else if ( nCostMoney > 0
             && (v42 = Player::GetCurrency(this->m_pPlayer),
                 !CExtCurrency::DecMoneyAndNoBind(v42, nCostMoney, CURRENCY_CHANGE_REASON::MCR_COMBI_ITEM, 0)) )
      {
        v2 = 10002;
      }
      else
      {
        v43 = Player::GetBag(this->m_pPlayer);
        if ( !CExtCharBag::AddItem(v43, &vAddItem, ITEM_CHANGE_REASON::ICR_COMBINE) )
        {
          v2 = 10002;
        }
        else
        {
          if ( pCfgItemCombi->m_bBroadcast > 0 && nSuccessTimes > 0 )
            CExtMagicBox::broadcastItemCombi(this, giveItem.itemId, giveItem.itemClass);
          if ( nSuccessTimes > 0 )
          {
            v60._M_node = std::list<int>::end(&this->m_lSuccessIds)._M_node;
            M_node = std::list<int>::end(&this->m_lSuccessIds)._M_node;
            v45._M_node = std::list<int>::begin(&this->m_lSuccessIds)._M_node;
            v61._M_node = std::find<std::_List_iterator<int>,int>(v45, (std::_List_iterator<int>)M_node, &nId)._M_node;
            if ( std::_List_iterator<int>::operator==(&v61, &v60) )
              std::list<int>::push_back(&this->m_lSuccessIds, &nId);
          }
          CExtMagicBox::sendItemCombiResult(this, nId, nSuccessTimes, nFailTimes);
          v2 = 0;
        }
      }
    }
    else
    {
      Player::TiShiInfo(this->m_pPlayer, 2048, 0);
      v2 = 10002;
    }
    goto LABEL_96;
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtMagicBox::onOrnamentCombi(CExtMagicBox *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgItemCombiTable *ItemCombiTable; // rax
  CExtCharBag *Bag; // rax
  int32_t v6; // eax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  size_t v10; // rbx
  const Int32Vector *v11; // rdx
  int32_t v12; // eax
  CExtCharBag *v14; // rax
  int64_t m_nMoney; // rbx
  CExtCurrency *v16; // rax
  CExtCharBag *v18; // rax
  MemChrBag giveItem; // [rsp+10h] [rbp-D0h] BYREF
  ItemData item_0; // [rsp+30h] [rbp-B0h] BYREF
  ItemData item; // [rsp+40h] [rbp-A0h] BYREF
  int32_t nUnBindCount; // [rsp+58h] [rbp-88h] BYREF
  int32_t nBindCount; // [rsp+5Ch] [rbp-84h] BYREF
  std::_List_const_iterator<ItemData> endIter; // [rsp+60h] [rbp-80h] BYREF
  std::_List_const_iterator<ItemData> costItem; // [rsp+70h] [rbp-70h] BYREF
  Int32Vector vSlot; // [rsp+80h] [rbp-60h] BYREF
  ItemDataList lCostItem; // [rsp+A0h] [rbp-40h] BYREF
  int32_t nId; // [rsp+B8h] [rbp-28h]
  int32_t nSpecialCost; // [rsp+BCh] [rbp-24h]
  const CfgItemCombi *pCfgItemCombi; // [rsp+C0h] [rbp-20h]
  int32_t nIndex; // [rsp+C8h] [rbp-18h]
  uint32_t nSpecialIndex; // [rsp+CCh] [rbp-14h]

  if ( this->m_pPlayer && inPacket )
  {
    std::list<ItemData>::list(&lCostItem);
    nId = Answer::NetPacket::readInt32(inPacket);
    nSpecialCost = Answer::NetPacket::readInt32(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    v3 = Answer::Singleton<CfgData>::instance();
    ItemCombiTable = CfgData::GetItemCombiTable(v3);
    pCfgItemCombi = CfgItemCombiTable::GetItemCombi(ItemCombiTable, nId);
    if ( pCfgItemCombi )
    {
      Bag = Player::GetBag(this->m_pPlayer);
      if ( CExtCharBag::GetFreeSlotCount(Bag) > 0 )
      {
        if ( pCfgItemCombi->m_nCombiType == 1 || pCfgItemCombi->m_nCombiType == 2 )
        {
          if ( nSpecialCost < 0
            || (v6 = std::vector<std::vector<int>>::size(&pCfgItemCombi->m_vProbability), v6 <= nSpecialCost) )
          {
            v2 = 10002;
          }
          else if ( pCfgItemCombi->m_nMoney >= 0 && pCfgItemCombi->m_nCostPoint >= 0 )
          {
            if ( pCfgItemCombi->m_nCostPoint <= this->m_nCombiPoints )
            {
              Currency = Player::GetCurrency(this->m_pPlayer);
              MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
              if ( MoneyBindAndNoBind >= pCfgItemCombi->m_nMoney )
              {
                costItem._M_node = std::list<ItemData>::begin(&pCfgItemCombi->m_lCostItem)._M_node;
                endIter._M_node = std::list<ItemData>::end(&pCfgItemCombi->m_lCostItem)._M_node;
                while ( std::_List_const_iterator<ItemData>::operator!=(&costItem, &endIter) )
                {
                  *(_QWORD *)&item.m_nId = 0;
                  item.m_nCount = 0;
                  item.m_nId = std::_List_const_iterator<ItemData>::operator->(&costItem)->m_nId;
                  item.m_nClass = std::_List_const_iterator<ItemData>::operator->(&costItem)->m_nClass;
                  item.m_nCount = std::_List_const_iterator<ItemData>::operator->(&costItem)->m_nCount;
                  std::list<ItemData>::push_back(&lCostItem, &item);
                  std::_List_const_iterator<ItemData>::operator++(&costItem);
                }
                if ( nSpecialCost > 0 )
                {
                  nSpecialIndex = nSpecialCost - 1;
                  v10 = (unsigned int)(nSpecialCost - 1);
                  if ( v10 >= std::vector<MemChrBag>::size(&pCfgItemCombi->m_vSpecialItems) )
                  {
                    v2 = 10002;
                    goto LABEL_52;
                  }
                  *(_QWORD *)&item_0.m_nId = 0;
                  item_0.m_nCount = 0;
                  item_0.m_nId = std::vector<MemChrBag>::operator[](&pCfgItemCombi->m_vSpecialItems, nSpecialIndex)->itemId;
                  item_0.m_nClass = std::vector<MemChrBag>::operator[](&pCfgItemCombi->m_vSpecialItems, nSpecialIndex)->itemClass;
                  item_0.m_nCount = std::vector<MemChrBag>::operator[](&pCfgItemCombi->m_vSpecialItems, nSpecialIndex)->itemCount;
                  std::list<ItemData>::push_back(&lCostItem, &item_0);
                }
                v11 = std::vector<std::vector<int>>::operator[](&pCfgItemCombi->m_vProbability, nSpecialCost);
                nIndex = CExtMagicBox::randomIndex(this, v11);
                if ( nIndex < 0 || (v12 = std::vector<MemChrBag>::size(&pCfgItemCombi->m_vGiveItem), v12 <= nIndex) )
                {
                  v2 = 10002;
                }
                else
                {
                  nBindCount = 0;
                  nUnBindCount = 0;
                  v14 = Player::GetBag(this->m_pPlayer);
                  if ( !CExtCharBag::RemoveItem(
                          v14,
                          &vSlot,
                          &lCostItem,
                          ITEM_CHANGE_REASON::ICR_EQUIP_COMBINE,
                          &nBindCount,
                          &nUnBindCount) )
                  {
                    v2 = 10002;
                  }
                  else
                  {
                    giveItem = *std::vector<MemChrBag>::operator[](&pCfgItemCombi->m_vGiveItem, nIndex);
                    if ( nBindCount > 0 )
                      giveItem.bind = 1;
                    if ( pCfgItemCombi->m_nCostPoint > 0 )
                      this->m_nCombiPoints -= pCfgItemCombi->m_nCostPoint;
                    if ( pCfgItemCombi->m_nMoney > 0
                      && (m_nMoney = pCfgItemCombi->m_nMoney,
                          v16 = Player::GetCurrency(this->m_pPlayer),
                          !CExtCurrency::DecMoneyAndNoBind(v16, m_nMoney, CURRENCY_CHANGE_REASON::MCR_EQUIP_COMBI, 0)) )
                    {
                      v2 = 10002;
                    }
                    else
                    {
                      v18 = Player::GetBag(this->m_pPlayer);
                      if ( !CExtCharBag::AddItem(v18, &giveItem, ITEM_CHANGE_REASON::ICR_EQUIP_COMBI) )
                      {
                        v2 = 10002;
                      }
                      else
                      {
                        CExtMagicBox::SendItemCombiPoint(this);
                        CExtMagicBox::sendItemCombiResult(this, nId, 1, 0);
                        v2 = 0;
                      }
                    }
                  }
                }
                goto LABEL_52;
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
LABEL_52:
    std::vector<int>::~vector(&vSlot);
    std::list<ItemData>::~list(&lCostItem);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtMagicBox::onEquipCombi(CExtMagicBox *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgItemCombiTable *ItemCombiTable; // rax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  int32_t v7; // r12d
  CExtCharBag *Bag; // rax
  EquipId_t srcId; // r12
  CEquipManager *v10; // rax
  int v11; // r12d
  ItemData *v12; // rax
  ItemData *v13; // rax
  size_t v14; // r12
  CharId_t nCreaterId; // rbx
  int32_t Sid; // r13d
  int32_t itemId; // r14d
  int8_t ConnId; // r12
  CEquipManager *v19; // rax
  int64_t m_nMoney; // rbx
  CExtCurrency *v21; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v24; // rax
  int32_t v25; // ebx
  CExtCharBag *v26; // rax
  size_t v27; // rbx
  CExtCharBag *v28; // rax
  MemEquip equip; // [rsp+50h] [rbp-160h] BYREF
  MemEquip equip_0; // [rsp+90h] [rbp-120h] BYREF
  MemChrBag bagSlot; // [rsp+D0h] [rbp-E0h]
  MemChrBag giveItem; // [rsp+F0h] [rbp-C0h] BYREF
  std::_List_iterator<ItemData> iter; // [rsp+110h] [rbp-A0h] BYREF
  ItemDataList lCostItem; // [rsp+120h] [rbp-90h] BYREF
  Int32Vector vSlot; // [rsp+130h] [rbp-80h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+150h] [rbp-60h] BYREF
  std::string p_name; // [rsp+160h] [rbp-50h] BYREF
  int32_t nId; // [rsp+174h] [rbp-3Ch]
  const CfgItemCombi *pCfgItemCombi; // [rsp+178h] [rbp-38h]
  bool bBind; // [rsp+183h] [rbp-2Dh]
  int32_t nMaxStar; // [rsp+184h] [rbp-2Ch]
  uint32_t i; // [rsp+188h] [rbp-28h]
  uint32_t i_0; // [rsp+18Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  v3 = Answer::Singleton<CfgData>::instance();
  ItemCombiTable = CfgData::GetItemCombiTable(v3);
  pCfgItemCombi = CfgItemCombiTable::GetItemCombi(ItemCombiTable, nId);
  if ( pCfgItemCombi )
  {
    if ( pCfgItemCombi->m_nCombiType == 3 )
    {
      if ( pCfgItemCombi->m_nMoney >= 0 && pCfgItemCombi->m_nCostPoint >= 0 )
      {
        if ( std::vector<MemChrBag>::empty(&pCfgItemCombi->m_vGiveItem) )
        {
          v2 = 10002;
        }
        else
        {
          giveItem = *std::vector<MemChrBag>::front(&pCfgItemCombi->m_vGiveItem);
          if ( giveItem.itemClass == 2 )
          {
            if ( this->m_nCombiPoints >= pCfgItemCombi->m_nCostPoint )
            {
              if ( std::list<ItemData>::empty(&pCfgItemCombi->m_lCostItem) )
              {
                v2 = 10002;
              }
              else
              {
                Currency = Player::GetCurrency(this->m_pPlayer);
                MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
                if ( MoneyBindAndNoBind >= pCfgItemCombi->m_nMoney )
                {
                  bBind = 0;
                  nMaxStar = 0;
                  std::list<ItemData>::list(&lCostItem, &pCfgItemCombi->m_lCostItem);
                  for ( i = 0; ; ++i )
                  {
                    v14 = i;
                    if ( v14 >= std::vector<int>::size(&vSlot) )
                      break;
                    v7 = *std::vector<int>::operator[](&vSlot, i);
                    Bag = Player::GetBag(this->m_pPlayer);
                    bagSlot = *CExtCharBag::GetSlotData(Bag, v7);
                    if ( bagSlot.itemId <= 0 || bagSlot.itemClass != 2 )
                    {
                      v2 = 10002;
                      goto LABEL_65;
                    }
                    srcId = bagSlot.srcId;
                    v10 = Answer::Singleton<CEquipManager>::instance();
                    CEquipManager::GetMemEquip(&equip_0, v10, srcId);
                    if ( equip_0.base == bagSlot.itemId )
                    {
                      if ( equip_0.star > nMaxStar )
                        nMaxStar = equip_0.star;
                      if ( bagSlot.bind == 1 || bagSlot.bind == 2 )
                        bBind = 1;
                      if ( std::list<ItemData>::empty(&lCostItem) )
                      {
                        v2 = 10002;
                        v11 = 0;
                      }
                      else
                      {
                        for ( iter._M_node = std::list<ItemData>::begin(&lCostItem)._M_node;
                              ;
                              std::_List_iterator<ItemData>::operator++(&iter) )
                        {
                          __x._M_node = std::list<ItemData>::end(&lCostItem)._M_node;
                          if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
                            break;
                          v12 = std::_List_iterator<ItemData>::operator->(&iter);
                          if ( v12->m_nId == bagSlot.itemId )
                          {
                            v13 = std::_List_iterator<ItemData>::operator->(&iter);
                            --v13->m_nCount;
                            if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount <= 0 )
                            {
                              std::list<ItemData>::erase(&lCostItem, iter);
                              break;
                            }
                          }
                        }
                        v11 = 1;
                      }
                    }
                    else
                    {
                      v2 = 10002;
                      v11 = 0;
                    }
                    MemEquip::~MemEquip(&equip_0);
                    if ( !v11 )
                      goto LABEL_65;
                  }
                  nMaxStar = 0;
                  if ( !std::list<ItemData>::empty(&lCostItem) )
                  {
                    v2 = 10002;
                  }
                  else
                  {
                    Player::getName((const Player *const)&p_name);
                    nCreaterId = Player::getCid(this->m_pPlayer);
                    Sid = Player::getSid(this->m_pPlayer);
                    itemId = giveItem.itemId;
                    ConnId = Player::getConnId(this->m_pPlayer);
                    v19 = Answer::Singleton<CEquipManager>::instance();
                    CEquipManager::CreateMemEquip(
                      &equip,
                      v19,
                      ConnId,
                      6,
                      itemId,
                      Sid,
                      nCreaterId,
                      &p_name,
                      0,
                      0,
                      0,
                      0,
                      nMaxStar);
                    std::string::~string(&p_name);
                    if ( equip.id > 0 )
                    {
                      if ( pCfgItemCombi->m_nMoney > 0
                        && (m_nMoney = pCfgItemCombi->m_nMoney,
                            v21 = Player::GetCurrency(this->m_pPlayer),
                            !CExtCurrency::DecMoneyAndNoBind(v21, m_nMoney, CURRENCY_CHANGE_REASON::MCR_COMBI_ITEM, 0)) )
                      {
                        v2 = 10002;
                      }
                      else
                      {
                        m_pPlayer = this->m_pPlayer;
                        v24 = Answer::Singleton<CEquipManager>::instance();
                        CEquipManager::SendPlayerEquipInfo(v24, m_pPlayer, &equip);
                        giveItem.srcId = equip.id;
                        if ( bBind )
                          giveItem.bind = 1;
                        for ( i_0 = 0; ; ++i_0 )
                        {
                          v27 = i_0;
                          if ( v27 >= std::vector<int>::size(&vSlot) )
                            break;
                          v25 = *std::vector<int>::operator[](&vSlot, i_0);
                          v26 = Player::GetBag(this->m_pPlayer);
                          CExtCharBag::CleanSlot(v26, v25, ITEM_CHANGE_REASON::ICR_COMBINE);
                        }
                        v28 = Player::GetBag(this->m_pPlayer);
                        CExtCharBag::AddItem(v28, &giveItem, ITEM_CHANGE_REASON::ICR_COMBINE);
                        if ( pCfgItemCombi->m_nCostPoint > 0 )
                        {
                          this->m_nCombiPoints -= pCfgItemCombi->m_nCostPoint;
                          CExtMagicBox::SendItemCombiPoint(this);
                        }
                        if ( pCfgItemCombi->m_bBroadcast > 0 )
                          CExtMagicBox::broadcastItemCombi(this, giveItem.itemId, giveItem.itemClass);
                        CExtMagicBox::sendItemCombiResult(this, nId, 1, 0);
                        v2 = 0;
                      }
                    }
                    else
                    {
                      v2 = 10002;
                    }
                    MemEquip::~MemEquip(&equip);
                  }
LABEL_65:
                  std::list<ItemData>::~list(&lCostItem);
                }
                else
                {
                  v2 = 10002;
                }
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
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtMagicBox::randomIndex(CExtMagicBox *const this, const Int32Vector *const vParam)
{
  Answer::Random *v3; // rax
  int32_t nTotal; // [rsp+1Ch] [rbp-14h]
  int32_t nSize; // [rsp+20h] [rbp-10h]
  int nRand; // [rsp+24h] [rbp-Ch]
  int32_t i; // [rsp+28h] [rbp-8h]
  int32_t i_0; // [rsp+2Ch] [rbp-4h]

  nTotal = 0;
  nSize = std::vector<int>::size(vParam);
  for ( i = 0; i < nSize; ++i )
    nTotal += *std::vector<int>::operator[](vParam, i);
  if ( nTotal <= 0 )
    return 0;
  v3 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v3, 1, nTotal);
  for ( i_0 = 0; i_0 < nSize; ++i_0 )
  {
    if ( *std::vector<int>::operator[](vParam, i_0) >= nRand )
      return i_0;
    nRand -= *std::vector<int>::operator[](vParam, i_0);
  }
  return 0;
}


#####################################
bool __cdecl CExtMagicBox::AddPoints(CExtMagicBox *const this, int32_t nValue)
{
  int32_t nMaxPoints; // [rsp+1Ch] [rbp-4h]

  nMaxPoints = CExtMagicBox::getMaxPoints(this);
  if ( this->m_nCombiPoints >= nMaxPoints )
    return 0;
  this->m_nCombiPoints += nValue;
  if ( this->m_nCombiPoints > nMaxPoints )
    this->m_nCombiPoints = nMaxPoints;
  CExtMagicBox::SendItemCombiPoint(this);
  return 1;
}


#####################################
bool __cdecl CExtMagicBox::ActiveScroll(CExtMagicBox *const this, int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-Ch] BYREF
  CExtMagicBox *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  nIda = nId;
  if ( CExtMagicBox::isActive(this, nId) )
    return 0;
  std::list<int>::push_back(&thisa->m_lActiveScrolls, &nIda);
  return 1;
}


#####################################
void __cdecl CExtMagicBox::SendMagicBoxInfo(CExtMagicBox *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  int32_t *v4; // rax
  int32_t v5; // eax
  int32_t *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_const_iterator<int> iter_0; // [rsp+10h] [rbp-90h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+20h] [rbp-80h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-70h] BYREF
  std::_List_const_iterator<int> v14; // [rsp+40h] [rbp-60h] BYREF
  std::_List_iterator<int> v15; // [rsp+50h] [rbp-50h] BYREF
  std::_List_iterator<int> v16; // [rsp+60h] [rbp-40h] BYREF
  std::_List_const_iterator<int> v17; // [rsp+70h] [rbp-30h] BYREF
  std::_List_iterator<int> v18; // [rsp+80h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+88h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E1Du);
    if ( packet )
    {
      v3 = std::list<int>::size(&this->m_lActiveScrolls);
      Answer::NetPacket::writeInt32(packet, v3);
      __x._M_node = std::list<int>::begin(&this->m_lActiveScrolls)._M_node;
      std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v15._M_node = std::list<int>::end(&this->m_lActiveScrolls)._M_node;
        std::_List_const_iterator<int>::_List_const_iterator(&v14, &v15);
        if ( !std::_List_const_iterator<int>::operator!=(&iter, &v14) )
          break;
        v4 = (int32_t *)std::_List_const_iterator<int>::operator*(&iter);
        Answer::NetPacket::writeInt32(packet, *v4);
        std::_List_const_iterator<int>::operator++(&iter);
      }
      v5 = std::list<int>::size(&this->m_lSuccessIds);
      Answer::NetPacket::writeInt32(packet, v5);
      v16._M_node = std::list<int>::begin(&this->m_lSuccessIds)._M_node;
      std::_List_const_iterator<int>::_List_const_iterator(&iter_0, &v16);
      while ( 1 )
      {
        v18._M_node = std::list<int>::end(&this->m_lSuccessIds)._M_node;
        std::_List_const_iterator<int>::_List_const_iterator(&v17, &v18);
        if ( !std::_List_const_iterator<int>::operator!=(&iter_0, &v17) )
          break;
        v6 = (int32_t *)std::_List_const_iterator<int>::operator*(&iter_0);
        Answer::NetPacket::writeInt32(packet, *v6);
        std::_List_const_iterator<int>::operator++(&iter_0);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtMagicBox::SendItemCombiPoint(CExtMagicBox *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E1Eu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nCombiPoints);
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
void __cdecl CExtMagicBox::sendItemCombiResult(
        CExtMagicBox *const this,
        int32_t nId,
        int32_t nSuccessTimes,
        int32_t nFailTimes)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E1Fu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nId);
      Answer::NetPacket::writeInt32(packet, nSuccessTimes);
      Answer::NetPacket::writeInt32(packet, nFailTimes);
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
void __cdecl CExtMagicBox::broadcastItemCombi(CExtMagicBox *const this, int32_t ItemId, int8_t ItemClass)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 121);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, ItemId);
      Answer::NetPacket::writeInt8(packet, ItemClass);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtMagicBox::getMaxPoints(CExtMagicBox *const this)
{
  return 500;
}


#####################################
int32_t __cdecl CExtMagicBox::getPointsReviveValue(CExtMagicBox *const this)
{
  return 5;
}


#####################################
bool __cdecl CExtMagicBox::isActive(CExtMagicBox *const this, int32_t nId)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<int> v3; // rax
  int32_t nIda; // [rsp+4h] [rbp-3Ch] BYREF
  CExtMagicBox *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<int> __x; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<int> v8; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nIda = nId;
  __x._M_node = std::list<int>::end(&this->m_lActiveScrolls)._M_node;
  M_node = std::list<int>::end(&this->m_lActiveScrolls)._M_node;
  v3._M_node = std::list<int>::begin(&this->m_lActiveScrolls)._M_node;
  v8._M_node = std::find<std::_List_iterator<int>,int>(v3, (std::_List_iterator<int>)M_node, &nIda)._M_node;
  return std::_List_iterator<int>::operator!=(&v8, &__x);
}


#####################################
std::string __cdecl CExtMagicBox::saveString(CExtMagicBox *const this, const Int32List *const inList)
{
  const std::list<int> *v2; // rdx
  std::_Ios_Openmode v3; // eax
  const int *v4; // rax
  const std::list<int> *inLista; // [rsp+0h] [rbp-1C0h]
  _BYTE v7[16]; // [rsp+10h] [rbp-1B0h] BYREF
  _BYTE v8[352]; // [rsp+20h] [rbp-1A0h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+180h] [rbp-40h] BYREF
  char v10; // [rsp+18Fh] [rbp-31h] BYREF
  std::_List_const_iterator<int> v11; // [rsp+190h] [rbp-30h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+1A0h] [rbp-20h] BYREF

  inLista = v2;
  if ( std::list<int>::empty(v2) )
  {
    std::allocator<char>::allocator(&v10);
    std::string::string(this, byte_8E477A);
    std::allocator<char>::~allocator(&v10);
  }
  else
  {
    v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v7, (unsigned int)v3);
    for ( iter._M_node = std::list<int>::begin(inLista)._M_node; ; std::_List_const_iterator<int>::operator++(&iter) )
    {
      v11._M_node = std::list<int>::end(inLista)._M_node;
      if ( !std::_List_const_iterator<int>::operator!=(&iter, &v11) )
        break;
      __x._M_node = std::list<int>::begin(inLista)._M_node;
      if ( std::_List_const_iterator<int>::operator!=(&iter, &__x) )
        std::operator<<<std::char_traits<char>>(v8, &unk_8E4778);
      v4 = std::_List_const_iterator<int>::operator*(&iter);
      std::ostream::operator<<(v8, *(unsigned int *)v4);
    }
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v7);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v7);
  }
  return (std::string)this;
}


