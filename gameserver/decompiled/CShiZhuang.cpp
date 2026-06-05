// Decompiled methods for class: CShiZhuang
// Source: gameserver.cc
// Total methods: 26

#####################################
void __cdecl CShiZhuang::~CShiZhuang(CShiZhuang *const this)
{
  CShiZhuang::~CShiZhuang(this);
  operator delete(this);
}


#####################################
void __cdecl CShiZhuang::OnCleanUp(CShiZhuang *const this)
{
  int8_t i; // [rsp+1Fh] [rbp-1h]

  for ( i = 0; i <= 2; ++i )
    ShiZhuangInfo::CleanUp(&this->m_vShiZhuang[i]);
  this->m_LastUpdateTick = 0;
  std::map<int,int>::clear(&this->m_ShiZhuangLevel);
  std::map<int,SuitInfo>::clear(&this->m_SuitInfoMap);
  this->m_EffectId = 0;
}


#####################################
void __cdecl CShiZhuang::OnLoadFromDB(CShiZhuang *const this, const PlayerDBData *const dbData)
{
  int8_t i; // [rsp+1Fh] [rbp-1h]

  for ( i = 0; i <= 2; ++i )
    ShiZhuangInfo::operator=(&this->m_vShiZhuang[i], &dbData->m_ShiZhuangData.m_vShiZhuang[(__int64)i]);
  std::map<int,int>::operator=(&this->m_ShiZhuangLevel, &dbData->m_ShiZhuangData.m_ShiZhuangLevel);
  this->m_EffectId = dbData->m_ShiZhuangData.m_EffectId;
  CShiZhuang::CheckSuitInfo(this);
  CShiZhuang::CheckSuitEffect(this);
}


#####################################
void __cdecl CShiZhuang::OnSaveToDB(CShiZhuang *const this, PlayerDBData *const dbData)
{
  int8_t i; // [rsp+1Fh] [rbp-1h]

  for ( i = 0; i <= 2; ++i )
    ShiZhuangInfo::operator=(&dbData->m_ShiZhuangData.m_vShiZhuang[(__int64)i], &this->m_vShiZhuang[i]);
  std::map<int,int>::operator=(&dbData->m_ShiZhuangData.m_ShiZhuangLevel, &this->m_ShiZhuangLevel);
  dbData->m_ShiZhuangData.m_EffectId = this->m_EffectId;
}


#####################################
void __cdecl CShiZhuang::OnUpdate(CShiZhuang *const this, int64_t curTick)
{
  std::pair<const int,int> *v2; // rax
  std::pair<const int,int> *v4; // rax
  std::_Ios_Openmode v5; // eax
  std::pair<const int,int> *v6; // rax
  CharId_t Cid; // rbx
  DBService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > v9; // rax
  _BYTE v10[16]; // [rsp+10h] [rbp-1B0h] BYREF
  _BYTE v11[352]; // [rsp+20h] [rbp-1A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-30h] BYREF
  std::string Param; // [rsp+1A0h] [rbp-20h] BYREF
  int32_t Now; // [rsp+1A8h] [rbp-18h]
  int8_t i; // [rsp+1AFh] [rbp-11h]

  if ( this->m_pPlayer && curTick - this->m_LastUpdateTick > 59999 )
  {
    this->m_LastUpdateTick = curTick;
    Now = Unit::getNow(this->m_pPlayer);
    for ( i = 0; i <= 2; ++i )
    {
      it._M_node = std::map<int,int>::begin(&this->m_vShiZhuang[i].m_lActive)._M_node;
      while ( 1 )
      {
        __x._M_node = std::map<int,int>::end(&this->m_vShiZhuang[i].m_lActive)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second
          && (v2 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it), v2->second < Now) )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          if ( v4->first == this->m_vShiZhuang[i].m_nWear )
          {
            CShiZhuang::wear(this, i, 0);
            CShiZhuang::sendShiZhuangInfo(this, i);
          }
          v5 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
            v10,
            (unsigned int)v5);
          v6 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
          std::ostream::operator<<(v11, (unsigned int)v6->first);
          std::operator<<<std::char_traits<char>>(v11, &unk_8F0A40);
          std::ostream::operator<<(v11, (unsigned int)i);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, v10);
          Cid = Player::getCid(this->m_pPlayer);
          v8 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v8, 0, Cid, 6396, &Param, 0);
          std::string::~string(&Param);
          v9._M_node = std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0)._M_node;
          std::map<int,int>::erase(&this->m_vShiZhuang[i].m_lActive, v9);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v10);
        }
        else
        {
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0);
        }
      }
    }
  }
}


#####################################
void __cdecl CShiZhuang::GetInterestsProtocol(CShiZhuang *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v3; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v4; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v5; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 960;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 961;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 962;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 963;
  std::list<unsigned short>::push_back(procList, &v5);
}


#####################################
int32_t __cdecl CShiZhuang::DispatchNetDatas(CShiZhuang *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( nProcId == 961 )
    return CShiZhuang::onPeiYang(this, inPacket);
  if ( nProcId > 0x3C1u )
  {
    if ( nProcId == 962 )
      return CShiZhuang::onWear(this, inPacket);
    if ( nProcId == 963 )
      return CShiZhuang::onLevelUp(this, inPacket);
  }
  else if ( nProcId == 960 )
  {
    return CShiZhuang::onRequestInfo(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CShiZhuang::onRequestInfo(CShiZhuang *const this, Answer::NetPacket *inPacket)
{
  int8_t nType; // [rsp+1Fh] [rbp-1h]

  if ( !inPacket )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)nType > 2u )
    return 2;
  CShiZhuang::sendShiZhuangInfo(this, nType);
  return 0;
}


#####################################
int32_t __cdecl CShiZhuang::onPeiYang(CShiZhuang *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CVip *PlayerVip; // rax
  int32_t m_nLevel; // r12d
  int8_t v6; // bl
  CfgData *v7; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  int32_t v9; // r12d
  int8_t v10; // bl
  CfgData *v11; // rax
  const CfgShiZhuangTable *v12; // rax
  int32_t v13; // eax
  CExtCharBag *v14; // rax
  CfgData *v15; // rax
  int64_t Currency; // rax
  CExtCharBag *v17; // rax
  CExtCurrency *v19; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v21; // rax
  Answer::Random *v22; // rax
  ItemData costItem; // [rsp+10h] [rbp-90h] BYREF
  Int32Vector vSlot; // [rsp+20h] [rbp-80h] BYREF
  int8_t nType; // [rsp+3Ah] [rbp-66h]
  int8_t nAutoBuy; // [rsp+3Bh] [rbp-65h]
  int32_t nCount; // [rsp+3Ch] [rbp-64h]
  const CfgShiZhuangLevel *pCfgLevel; // [rsp+40h] [rbp-60h]
  const CfgShiZhuangLevel *pCfgNextLevel; // [rsp+48h] [rbp-58h]
  int8_t nCrit; // [rsp+57h] [rbp-49h]
  int32_t nTimes; // [rsp+58h] [rbp-48h]
  int32_t nAddExp; // [rsp+5Ch] [rbp-44h]
  int32_t nBuyCount; // [rsp+60h] [rbp-40h]
  int32_t nItemCount; // [rsp+64h] [rbp-3Ch]
  int32_t nCostGold; // [rsp+68h] [rbp-38h]
  int32_t nShopId; // [rsp+6Ch] [rbp-34h]
  CfgGameShop *pCfgGameShop; // [rsp+70h] [rbp-30h]
  int32_t i; // [rsp+78h] [rbp-28h]
  int32_t nRand; // [rsp+7Ch] [rbp-24h]

  if ( inPacket && this->m_pPlayer )
  {
    nType = Answer::NetPacket::readInt8(inPacket);
    nAutoBuy = Answer::NetPacket::readInt8(inPacket);
    nCount = Answer::NetPacket::readInt32(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( (unsigned __int8)nType <= 2u )
    {
      if ( std::map<int,int>::empty(&this->m_vShiZhuang[nType].m_lActive) )
      {
        v2 = 2;
      }
      else if ( nCount > 0 )
      {
        if ( nCount > 1 && (PlayerVip = Player::GetPlayerVip(this->m_pPlayer), CVip::GetVipLevel(PlayerVip) <= 0) )
        {
          v2 = 2;
        }
        else
        {
          m_nLevel = this->m_vShiZhuang[nType].m_nLevel;
          v6 = nType;
          v7 = Answer::Singleton<CfgData>::instance();
          ShiZhuangTable = CfgData::GetShiZhuangTable(v7);
          pCfgLevel = CfgShiZhuangTable::GetShiZhuangLevel(ShiZhuangTable, v6, m_nLevel);
          v9 = this->m_vShiZhuang[nType].m_nLevel + 1;
          v10 = nType;
          v11 = Answer::Singleton<CfgData>::instance();
          v12 = CfgData::GetShiZhuangTable(v11);
          pCfgNextLevel = CfgShiZhuangTable::GetShiZhuangLevel(v12, v10, v9);
          if ( pCfgLevel && pCfgNextLevel )
          {
            if ( pCfgLevel->nLevelExp > 0 )
            {
              v13 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
              if ( v13 >= pCfgLevel->nNeedLevel )
              {
                *(_QWORD *)&costItem.m_nId = 0x100000000LL;
                costItem.m_nCount = 0;
                costItem.m_nId = pCfgLevel->nCostItem;
                costItem.m_nCount = nCount;
                if ( nAutoBuy <= 0 )
                {
                  Bag = Player::GetBag(this->m_pPlayer);
                  if ( !CExtCharBag::RemoveItem(Bag, &vSlot, &costItem, ITEM_CHANGE_REASON::IDCR_SHI_ZHUANG_PEI_YANG) )
                  {
                    v2 = 2;
                    goto LABEL_56;
                  }
                  v21 = Player::GetBag(this->m_pPlayer);
                  CExtCharBag::ForceSendDirty(v21);
                }
                else
                {
                  nBuyCount = 0;
                  v14 = Player::GetBag(this->m_pPlayer);
                  nItemCount = CExtCharBag::GetItemCount(v14, &vSlot, costItem.m_nClass, costItem.m_nId);
                  if ( costItem.m_nCount > nItemCount )
                  {
                    nBuyCount = costItem.m_nCount - nItemCount;
                    costItem.m_nCount = nItemCount;
                  }
                  nCostGold = 0;
                  nShopId = 0;
                  if ( nBuyCount > 0 )
                  {
                    v15 = Answer::Singleton<CfgData>::instance();
                    pCfgGameShop = CfgData::GetGameShopItem(v15, costItem.m_nClass, costItem.m_nId);
                    if ( !pCfgGameShop )
                    {
                      v2 = 2;
                      goto LABEL_56;
                    }
                    nShopId = pCfgGameShop->ShopId;
                    nCostGold = nBuyCount * pCfgGameShop->Price;
                    if ( nCostGold <= 0 )
                    {
                      v2 = 2;
                      goto LABEL_56;
                    }
                    Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
                    if ( Currency < nCostGold )
                    {
                      v2 = 2;
                      goto LABEL_56;
                    }
                  }
                  if ( costItem.m_nCount > 0 )
                  {
                    v17 = Player::GetBag(this->m_pPlayer);
                    if ( !CExtCharBag::RemoveItem(v17, &vSlot, &costItem, ITEM_CHANGE_REASON::IDCR_SHI_ZHUANG_PEI_YANG) )
                    {
                      v2 = 2;
                      goto LABEL_56;
                    }
                  }
                  if ( nCostGold > 0 )
                  {
                    if ( !Player::DecCurrency(
                            this->m_pPlayer,
                            CURRENCY_TYPE::CURRENCY_GOLD,
                            nCostGold,
                            CURRENCY_CHANGE_REASON::GCR_SHI_ZHUANG_PEI_YANG,
                            nShopId) )
                    {
                      v2 = 2;
                      goto LABEL_56;
                    }
                    v19 = Player::GetCurrency(this->m_pPlayer);
                    CExtCurrency::SynCurrency(v19);
                  }
                }
                nCrit = 0;
                nTimes = 0;
                for ( i = 0; i < nCount; ++i )
                {
                  v22 = Answer::Singleton<Answer::Random>::instance();
                  nRand = Answer::Random::generate(v22, 0, 10000);
                  if ( pCfgLevel->nLargeCritRate < nRand )
                  {
                    if ( pCfgLevel->nSmallCritRate < nRand )
                    {
                      ++nTimes;
                    }
                    else
                    {
                      nTimes += 2;
                      if ( !nCrit )
                        nCrit = 1;
                    }
                  }
                  else
                  {
                    nTimes += 10;
                    nCrit = 2;
                  }
                }
                nAddExp = nTimes * pCfgLevel->nGetExp;
                CShiZhuang::addShiZhuangExp(this, nType, nAddExp);
                CShiZhuang::sendShiZhuangPeiYangResult(this, nType, nAddExp, nCrit);
                v2 = 0;
                goto LABEL_56;
              }
              v2 = 2;
            }
            else
            {
              v2 = 2;
            }
          }
          else
          {
            v2 = 2;
          }
        }
      }
      else
      {
        v2 = 2;
      }
    }
    else
    {
      v2 = 2;
    }
LABEL_56:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


#####################################
int32_t __cdecl CShiZhuang::onWear(CShiZhuang *const this, Answer::NetPacket *inPacket)
{
  int8_t nType; // [rsp+1Bh] [rbp-5h]
  int nId; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned __int8)nType > 2u )
    return 2;
  if ( nId < 0 )
    return 2;
  if ( nId )
  {
    if ( !ShiZhuangInfo::IsActive(&this->m_vShiZhuang[nType], nId) )
      return 2;
  }
  else if ( !this->m_vShiZhuang[nType].m_nWear )
  {
    return 2;
  }
  CShiZhuang::wear(this, nType, nId);
  if ( nType == 1 )
    CShiZhuang::CheckSuitEffect(this);
  CShiZhuang::sendShiZhuangInfo(this, nType);
  return 0;
}


#####################################
int32_t __cdecl CShiZhuang::onLevelUp(CShiZhuang *const this, Answer::NetPacket *inPacket)
{
  int32_t NewShiZhuangLevel; // r12d
  CfgData *v4; // rax
  int32_t v5; // r12d
  CfgData *v6; // rax
  CExtCharBag *Bag; // rax
  int *v8; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  int32_t nId; // [rsp+18h] [rbp-38h] BYREF
  int8_t nType; // [rsp+1Fh] [rbp-31h]
  const ShiZhuLevelUp *pShiZhuangLevelUp; // [rsp+20h] [rbp-30h]
  const ShiZhuLevelUp *pShiZhuangNextLevelUp; // [rsp+28h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( !CShiZhuang::IsForever(this, nType, nId) )
    return 2;
  NewShiZhuangLevel = CShiZhuang::GetNewShiZhuangLevel(this, nId);
  v4 = Answer::Singleton<CfgData>::instance();
  pShiZhuangLevelUp = CfgData::GetShiZhuLevelUp(v4, nId, NewShiZhuangLevel);
  v5 = CShiZhuang::GetNewShiZhuangLevel(this, nId) + 1;
  v6 = Answer::Singleton<CfgData>::instance();
  pShiZhuangNextLevelUp = CfgData::GetShiZhuLevelUp(v6, nId, v5);
  if ( !pShiZhuangLevelUp || !pShiZhuangNextLevelUp )
    return 2;
  if ( std::list<ItemData>::empty(&pShiZhuangLevelUp->lCostItem) )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::RemoveItem(Bag, &pShiZhuangLevelUp->lCostItem, ITEM_CHANGE_REASON::IDCR_SHI_ZHUANG_LEVEL_UP) )
    return 2;
  v8 = std::map<int,int>::operator[](&this->m_ShiZhuangLevel, &nId);
  ++*v8;
  CShiZhuang::CheckSuitInfo(this);
  CShiZhuang::sendShiZhuangInfo(this, nType);
  CShiZhuang::CheckSuitEffect(this);
  Player::RecalcAttr(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v12 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v12, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CShiZhuang::sendShiZhuangPeiYangResult(CShiZhuang *const this, int8_t nType, int32_t nExp, int8_t nCrit)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer && (unsigned __int8)nType <= 2u )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F1Du);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nType);
      Answer::NetPacket::writeInt32(packet, nExp);
      Answer::NetPacket::writeInt8(packet, nCrit);
      Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[nType].m_nLevel);
      Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[nType].m_nExp);
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
void __cdecl CShiZhuang::PackShiZhuangInfo(CShiZhuang *const this, Answer::NetPacket *packet)
{
  int32_t WearId; // edx
  int32_t v3; // edx
  int32_t EffectId; // edx
  int32_t v5; // edx

  if ( packet )
  {
    WearId = CShiZhuang::GetWearId(this, 0);
    Answer::NetPacket::writeInt32(packet, WearId);
    v3 = CShiZhuang::GetWearId(this, 1);
    Answer::NetPacket::writeInt32(packet, v3);
    EffectId = CShiZhuang::GetEffectId(this);
    Answer::NetPacket::writeInt32(packet, EffectId);
    v5 = CShiZhuang::GetWearId(this, 2);
    Answer::NetPacket::writeInt32(packet, v5);
  }
}


#####################################
void __cdecl CShiZhuang::appendShiZhuangInfo(CShiZhuang *const this, int8_t nType, Answer::NetPacket *packet)
{
  int32_t WearId; // edx
  int32_t second; // ebx
  int first; // edx
  int32_t v7; // edx
  std::pair<const int,int> *v8; // rax
  int32_t v9; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > itShiZhuang; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v13; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+64h] [rbp-1Ch]
  uint32_t nOldOffset; // [rsp+68h] [rbp-18h]
  uint32_t nOffset; // [rsp+6Ch] [rbp-14h]

  if ( this->m_pPlayer && packet && (unsigned __int8)nType <= 2u )
  {
    Answer::NetPacket::writeInt8(packet, nType);
    WearId = CShiZhuang::GetWearId(this, nType);
    Answer::NetPacket::writeInt32(packet, WearId);
    Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[nType].m_nLevel);
    Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[nType].m_nExp);
    nCount = 0;
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    for ( iter._M_node = std::map<int,int>::begin(&this->m_vShiZhuang[nType].m_lActive)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter) )
    {
      v13._M_node = std::map<int,int>::end(&this->m_vShiZhuang[nType].m_lActive)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v13) )
        break;
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second )
      {
        second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
        if ( second < Unit::getNow(this->m_pPlayer) )
          continue;
      }
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
      Answer::NetPacket::writeInt32(packet, first);
      v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      Answer::NetPacket::writeInt32(packet, v7);
      v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter);
      itShiZhuang._M_node = std::map<int,int>::find(&this->m_ShiZhuangLevel, (const int *const)v8)._M_node;
      __x._M_node = std::map<int,int>::end(&this->m_ShiZhuangLevel)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itShiZhuang, &__x) )
      {
        v9 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itShiZhuang)->second;
        Answer::NetPacket::writeInt32(packet, v9);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 0);
      }
      ++nCount;
    }
    nOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt32(packet, nCount);
    Answer::NetPacket::setWOffset(packet, nOffset);
  }
}


#####################################
void __cdecl CShiZhuang::sendShiZhuangInfo(CShiZhuang *const this, int8_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && (unsigned __int8)nType <= 2u )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F1Cu);
    if ( packet )
    {
      CShiZhuang::appendShiZhuangInfo(this, nType, packet);
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
void __cdecl CShiZhuang::SendShiZhuangInfo(CShiZhuang *const this)
{
  char i; // [rsp+1Fh] [rbp-1h]

  for ( i = 0; i <= 2; ++i )
    CShiZhuang::sendShiZhuangInfo(this, i);
}


#####################################
int32_t __cdecl CShiZhuang::GetWearId(CShiZhuang *const this, int8_t nType)
{
  if ( (unsigned __int8)nType > 2u )
    return 0;
  if ( ShiZhuangInfo::IsActive(&this->m_vShiZhuang[nType], this->m_vShiZhuang[nType].m_nWear) )
    return this->m_vShiZhuang[nType].m_nWear;
  return 0;
}


#####################################
void __cdecl CShiZhuang::AddPlayerAttr(CShiZhuang *const this)
{
  int32_t m_nLevel; // r12d
  int8_t v2; // bl
  CfgData *v3; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v6; // rax
  int32_t second; // ebx
  int first; // ebx
  CfgData *v10; // rax
  const CfgShiZhuangTable *v11; // rax
  int32_t v12; // ebx
  const AddAttribute *v13; // rax
  int32_t v14; // r12d
  int v15; // ebx
  CfgData *v16; // rax
  int32_t v18; // ebx
  const AddAttribute *v19; // rax
  int32_t nLevel; // r13d
  int v21; // r12d
  CfgData *v22; // rax
  int32_t v23; // eax
  int32_t v24; // ebx
  const AddAttribute *v25; // rax
  std::_List_const_iterator<AddAttribute> AttrIt; // [rsp+10h] [rbp-130h] BYREF
  AddAttrList Stu; // [rsp+20h] [rbp-120h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > it_3; // [rsp+30h] [rbp-110h] BYREF
  std::_List_const_iterator<AddAttribute> it_2; // [rsp+40h] [rbp-100h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it_1; // [rsp+50h] [rbp-F0h] BYREF
  std::_List_const_iterator<AddAttribute> it_0; // [rsp+60h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+70h] [rbp-D0h] BYREF
  std::_List_const_iterator<AddAttribute> it; // [rsp+80h] [rbp-C0h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+90h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v35; // [rsp+A0h] [rbp-A0h] BYREF
  std::_List_const_iterator<AddAttribute> v36; // [rsp+B0h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v37; // [rsp+C0h] [rbp-80h] BYREF
  std::_List_const_iterator<AddAttribute> v38; // [rsp+D0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > v39; // [rsp+E0h] [rbp-60h] BYREF
  std::_List_const_iterator<AddAttribute> v40; // [rsp+F0h] [rbp-50h] BYREF
  int32_t i; // [rsp+104h] [rbp-3Ch]
  const CfgShiZhuangLevel *pCfgLevel; // [rsp+108h] [rbp-38h]
  const CfgShiZhuang *pCfg; // [rsp+110h] [rbp-30h]
  const ShiZhuLevelUp *pShiZhuangLevelUp; // [rsp+118h] [rbp-28h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 2; ++i )
    {
      m_nLevel = this->m_vShiZhuang[i].m_nLevel;
      v2 = i;
      v3 = Answer::Singleton<CfgData>::instance();
      ShiZhuangTable = CfgData::GetShiZhuangTable(v3);
      pCfgLevel = CfgShiZhuangTable::GetShiZhuangLevel(ShiZhuangTable, v2, m_nLevel);
      if ( pCfgLevel )
      {
        for ( it._M_node = std::list<AddAttribute>::begin(&pCfgLevel->vAttr)._M_node;
              ;
              std::_List_const_iterator<AddAttribute>::operator++(&it) )
        {
          __x._M_node = std::list<AddAttribute>::end(&pCfgLevel->vAttr)._M_node;
          if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it, &__x) )
            break;
          m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
          v6 = std::_List_const_iterator<AddAttribute>::operator->(&it);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v6->m_nAddAttrType, m_nAddAttrValue);
        }
      }
      for ( iter._M_node = std::map<int,int>::begin(&this->m_vShiZhuang[i].m_lActive)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter) )
      {
        v35._M_node = std::map<int,int>::end(&this->m_vShiZhuang[i].m_lActive)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v35) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second )
        {
          second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
          if ( second < Unit::getNow(this->m_pPlayer) )
            continue;
        }
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
        v10 = Answer::Singleton<CfgData>::instance();
        v11 = CfgData::GetShiZhuangTable(v10);
        pCfg = CfgShiZhuangTable::GetShiZhuang(v11, first);
        if ( pCfg )
        {
          for ( it_0._M_node = std::list<AddAttribute>::begin(&pCfg->vAttr)._M_node;
                ;
                std::_List_const_iterator<AddAttribute>::operator++(&it_0) )
          {
            v36._M_node = std::list<AddAttribute>::end(&pCfg->vAttr)._M_node;
            if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_0, &v36) )
              break;
            v12 = std::_List_const_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
            v13 = std::_List_const_iterator<AddAttribute>::operator->(&it_0);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v13->m_nAddAttrType, v12);
          }
        }
      }
    }
    for ( it_1._M_node = std::map<int,int>::begin(&this->m_ShiZhuangLevel)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it_1, 0) )
    {
      v37._M_node = std::map<int,int>::end(&this->m_ShiZhuangLevel)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it_1, &v37) )
        break;
      v14 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_1)->second;
      v15 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_1)->first;
      v16 = Answer::Singleton<CfgData>::instance();
      pShiZhuangLevelUp = CfgData::GetShiZhuLevelUp(v16, v15, v14);
      if ( pShiZhuangLevelUp && !std::list<AddAttribute>::empty(&pShiZhuangLevelUp->lAttr) )
      {
        for ( it_2._M_node = std::list<AddAttribute>::begin(&pShiZhuangLevelUp->lAttr)._M_node;
              ;
              std::_List_const_iterator<AddAttribute>::operator++(&it_2) )
        {
          v38._M_node = std::list<AddAttribute>::end(&pShiZhuangLevelUp->lAttr)._M_node;
          if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_2, &v38) )
            break;
          v18 = std::_List_const_iterator<AddAttribute>::operator->(&it_2)->m_nAddAttrValue;
          v19 = std::_List_const_iterator<AddAttribute>::operator->(&it_2);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v19->m_nAddAttrType, v18);
        }
      }
    }
    for ( it_3._M_node = std::map<int,SuitInfo>::begin(&this->m_SuitInfoMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator++(&it_3, 0) )
    {
      v39._M_node = std::map<int,SuitInfo>::end(&this->m_SuitInfoMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator!=(&it_3, &v39) )
        break;
      std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&it_3);
      nLevel = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&it_3)->second.nLevel;
      v21 = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&it_3)->first;
      v22 = Answer::Singleton<CfgData>::instance();
      v23 = (unsigned int)CfgData::GetShiZhuangTable(v22);
      CfgShiZhuangTable::GetShiZhuangSuitAttr((const CfgShiZhuangTable *const)&Stu, v23, v21, nLevel);
      for ( AttrIt._M_node = std::list<AddAttribute>::begin(&Stu)._M_node;
            ;
            std::_List_const_iterator<AddAttribute>::operator++(&AttrIt, 0) )
      {
        v40._M_node = std::list<AddAttribute>::end(&Stu)._M_node;
        if ( !std::_List_const_iterator<AddAttribute>::operator!=(&AttrIt, &v40) )
          break;
        v24 = std::_List_const_iterator<AddAttribute>::operator->(&AttrIt)->m_nAddAttrValue;
        v25 = std::_List_const_iterator<AddAttribute>::operator->(&AttrIt);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v25->m_nAddAttrType, v24);
      }
      std::list<AddAttribute>::~list(&Stu);
    }
  }
}


#####################################
int32_t __cdecl CShiZhuang::GetShiZhuangLevel(CShiZhuang *const this, int8_t nType)
{
  if ( (unsigned __int8)nType <= 2u )
    return this->m_vShiZhuang[nType].m_nLevel;
  else
    return 0;
}


#####################################
void __cdecl CShiZhuang::addShiZhuangExp(CShiZhuang *const this, int8_t nType, int32_t nAddExp)
{
  int32_t m_nLevel; // r12d
  CfgData *v4; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  int32_t v6; // r12d
  CfgData *v7; // rax
  const CfgShiZhuangTable *v8; // rax
  int32_t v9; // r12d
  CfgData *v10; // rax
  const CfgShiZhuangTable *v11; // rax
  const CfgShiZhuangLevel *pCfgLevel; // [rsp+10h] [rbp-20h]
  const CfgShiZhuangLevel *pCfgNextLevel; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( (unsigned __int8)nType <= 2u && nAddExp > 0 )
    {
      m_nLevel = this->m_vShiZhuang[nType].m_nLevel;
      v4 = Answer::Singleton<CfgData>::instance();
      ShiZhuangTable = CfgData::GetShiZhuangTable(v4);
      pCfgLevel = CfgShiZhuangTable::GetShiZhuangLevel(ShiZhuangTable, nType, m_nLevel);
      v6 = this->m_vShiZhuang[nType].m_nLevel + 1;
      v7 = Answer::Singleton<CfgData>::instance();
      v8 = CfgData::GetShiZhuangTable(v7);
      pCfgNextLevel = CfgShiZhuangTable::GetShiZhuangLevel(v8, nType, v6);
      if ( pCfgLevel )
      {
        if ( pCfgNextLevel )
        {
          this->m_vShiZhuang[nType].m_nExp += nAddExp;
          do
          {
            if ( this->m_vShiZhuang[nType].m_nExp < pCfgLevel->nLevelExp )
              break;
            ++this->m_vShiZhuang[nType].m_nLevel;
            this->m_vShiZhuang[nType].m_nExp -= pCfgLevel->nLevelExp;
            Player::recalcAttr(this->m_pPlayer, 0, 0);
            pCfgLevel = pCfgNextLevel;
            v9 = this->m_vShiZhuang[nType].m_nLevel + 1;
            v10 = Answer::Singleton<CfgData>::instance();
            v11 = CfgData::GetShiZhuangTable(v10);
            pCfgNextLevel = CfgShiZhuangTable::GetShiZhuangLevel(v11, nType, v9);
          }
          while ( pCfgNextLevel );
        }
      }
    }
  }
}


#####################################
bool __cdecl CShiZhuang::ActiveWithItem(CShiZhuang *const this, int32_t nId, int32_t nAddTime)
{
  CfgData *v4; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  const CfgShiZhuang *pShiZhuang; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 0;
  v4 = Answer::Singleton<CfgData>::instance();
  ShiZhuangTable = CfgData::GetShiZhuangTable(v4);
  pShiZhuang = CfgShiZhuangTable::GetShiZhuang(ShiZhuangTable, nId);
  if ( !pShiZhuang )
    return 0;
  if ( ShiZhuangInfo::IsActive(&this->m_vShiZhuang[pShiZhuang->nType], nId) )
    ShiZhuangInfo::AddTime(&this->m_vShiZhuang[pShiZhuang->nType], nId, nAddTime);
  if ( !ShiZhuangInfo::IsActive(&this->m_vShiZhuang[pShiZhuang->nType], nId) )
  {
    ShiZhuangInfo::AddTime(&this->m_vShiZhuang[pShiZhuang->nType], nId, nAddTime);
    Player::recalcAttr(this->m_pPlayer, 0, 0);
    CShiZhuang::wear(this, pShiZhuang->nType, nId);
  }
  CShiZhuang::sendShiZhuangInfo(this, pShiZhuang->nType);
  return 1;
}


#####################################
void __cdecl CShiZhuang::wear(CShiZhuang *const this, int8_t nType, int32_t nId)
{
  if ( this->m_pPlayer && (unsigned __int8)nType <= 2u )
  {
    this->m_vShiZhuang[nType].m_nWear = nId;
    Player::SetNeedSyncAround(this->m_pPlayer);
    Player::setSyncToTeamFlag(this->m_pPlayer);
    if ( nType )
    {
      if ( nType == 1 )
        Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_SHI_ZHUANG_CLOTHES, nId);
    }
    else
    {
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_SHI_ZHUANG_WEAPON, nId);
    }
  }
}


#####################################
bool __cdecl CShiZhuang::IsForever(CShiZhuang *const this, int8_t nType, int32_t nId)
{
  return (unsigned __int8)nType <= 2u && ShiZhuangInfo::IsForever(&this->m_vShiZhuang[nType], nId);
}


#####################################
int32_t __cdecl CShiZhuang::GetNewShiZhuangLevel(CShiZhuang *const this, int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CShiZhuang *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,int>::find(&this->m_ShiZhuangLevel, &nIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_ShiZhuangLevel)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl CShiZhuang::CheckSuitInfo(CShiZhuang *const this)
{
  int first; // ebx
  CfgData *v2; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  SuitInfo *v4; // rax
  int32_t second; // ebx
  SuitInfo *v7; // rbx
  int32_t nCount; // r13d
  int32_t nLevel; // r12d
  int v10; // ebx
  CfgData *v11; // rax
  const CfgShiZhuangTable *v12; // rax
  std::pair<const int,SuitInfo> *v13; // rax
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > SuitIt; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > v17; // [rsp+40h] [rbp-40h] BYREF
  const CfgShiZhuang *pShiZhuang; // [rsp+50h] [rbp-30h]
  int32_t SuitLevel; // [rsp+5Ch] [rbp-24h]

  std::map<int,SuitInfo>::clear(&this->m_SuitInfoMap);
  for ( it._M_node = std::map<int,int>::begin(&this->m_ShiZhuangLevel)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end(&this->m_ShiZhuangLevel)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
    v2 = Answer::Singleton<CfgData>::instance();
    ShiZhuangTable = CfgData::GetShiZhuangTable(v2);
    pShiZhuang = CfgShiZhuangTable::GetShiZhuang(ShiZhuangTable, first);
    if ( pShiZhuang && pShiZhuang->nSuitId > 0 )
    {
      v4 = std::map<int,SuitInfo>::operator[](&this->m_SuitInfoMap, &pShiZhuang->nSuitId);
      ++v4->nCount;
      if ( std::map<int,SuitInfo>::operator[](&this->m_SuitInfoMap, &pShiZhuang->nSuitId)->nLevel <= 0
        || (second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second,
            second < std::map<int,SuitInfo>::operator[](&this->m_SuitInfoMap, &pShiZhuang->nSuitId)->nLevel) )
      {
        v7 = std::map<int,SuitInfo>::operator[](&this->m_SuitInfoMap, &pShiZhuang->nSuitId);
        v7->nLevel = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      }
    }
  }
  for ( SuitIt._M_node = std::map<int,SuitInfo>::begin(&this->m_SuitInfoMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator++(&SuitIt, 0) )
  {
    v17._M_node = std::map<int,SuitInfo>::end(&this->m_SuitInfoMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator!=(&SuitIt, &v17) )
      break;
    nCount = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&SuitIt)->second.nCount;
    nLevel = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&SuitIt)->second.nLevel;
    v10 = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&SuitIt)->first;
    v11 = Answer::Singleton<CfgData>::instance();
    v12 = CfgData::GetShiZhuangTable(v11);
    SuitLevel = CfgShiZhuangTable::GetShiZhuangSuitLevel(v12, v10, nLevel, nCount);
    v13 = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&SuitIt);
    v13->second.nEffectLevel = SuitLevel;
  }
}


#####################################
void __cdecl CShiZhuang::CheckSuitEffect(CShiZhuang *const this)
{
  CfgData *v1; // rax
  const CfgShiZhuangTable *ShiZhuangTable; // rax
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SuitInfo> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t OldId; // [rsp+30h] [rbp-10h]
  int32_t WearId; // [rsp+34h] [rbp-Ch]
  const CfgShiZhuang *pShiZhuang; // [rsp+38h] [rbp-8h]

  OldId = this->m_EffectId;
  WearId = CShiZhuang::GetWearId(this, 1);
  v1 = Answer::Singleton<CfgData>::instance();
  ShiZhuangTable = CfgData::GetShiZhuangTable(v1);
  pShiZhuang = CfgShiZhuangTable::GetShiZhuang(ShiZhuangTable, WearId);
  if ( pShiZhuang && pShiZhuang->nSuitId > 0 )
  {
    it._M_node = std::map<int,SuitInfo>::find(&this->m_SuitInfoMap, &pShiZhuang->nSuitId)._M_node;
    __x._M_node = std::map<int,SuitInfo>::end(&this->m_SuitInfoMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator!=(&it, &__x) )
      this->m_EffectId = std::_Rb_tree_iterator<std::pair<int const,SuitInfo>>::operator->(&it)->second.nEffectLevel;
    else
      this->m_EffectId = 0;
    if ( this->m_EffectId != OldId )
    {
      Player::SetNeedSyncAround(this->m_pPlayer);
      Player::setSyncToTeamFlag(this->m_pPlayer);
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_SHI_ZHUANG_EFFECT, this->m_EffectId);
    }
  }
}


