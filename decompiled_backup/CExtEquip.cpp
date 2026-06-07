// Decompiled methods for class: CExtEquip
// Source: gameserver.cc
// Total methods: 95

#####################################
void __cdecl CExtEquip::~CExtEquip(CExtEquip *const this)
{
  CExtEquip::~CExtEquip(this);
  operator delete(this);
}


#####################################
void __cdecl CExtEquip::OnCleanUp(CExtEquip *const this)
{
  bzero(this->m_vMemEquip, 0xBA0u);
  bzero(this->m_vMemPosLevel, 0x28u);
  bzero(this->m_vMemStrengthen, 0x28u);
  bzero(this->m_vShenYaoEquipPos, 0x28u);
  CExtEquip::clearGemInfo(this);
  std::list<int>::clear(&this->m_lstDirty);
  this->m_nEquipStar = 0;
  this->m_nEquipGem = 0;
  this->m_nGongMingSuitId = 0;
  this->m_nGongMingSuitBuff = 0;
}


#####################################
void __cdecl CExtEquip::OnLoadFromDB(CExtEquip *const this, const PlayerDBData *const dbData)
{
  CfgData *v2; // rax
  int32_t nSkillLevel; // r12d
  int32_t v4; // ebx
  CExtCharSkill *v5; // rax
  int32_t nSkillTalent; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t nLevel; // [rsp+14h] [rbp-1Ch]
  MoFuSkillCfg *pMoFuSkillCfg; // [rsp+18h] [rbp-18h]

  memcpy(this->m_vMemEquip, dbData->equipData.vEquip, sizeof(this->m_vMemEquip));
  CExtEquip::loadGemString(this, &dbData->gemData.gemInfo);
  CExtEquip::loadPosLevelString(this, &dbData->gemData.posLevel);
  CExtEquip::LoadStrengthenString(this, &dbData->gemData.Strengthen);
  CExtEquip::LoadShenYaoString(this, &dbData->gemData.ShenYaoEquipPos);
  CExtEquip::checkEquipSuit(this, 0);
  CExtEquip::updateEquipStar(this);
  CExtEquip::updateEquipGem(this);
  nLevel = CExtEquip::GetMoFuSuitLevel(this);
  v2 = Answer::Singleton<CfgData>::instance();
  pMoFuSkillCfg = CfgData::GetMoFuSkillCfg(v2, nLevel);
  if ( pMoFuSkillCfg )
  {
    if ( pMoFuSkillCfg->nActivation <= 0 )
    {
      nSkillTalent = pMoFuSkillCfg->nSkillTalent;
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(CharSkill, nSkillTalent, 0);
    }
    else
    {
      nSkillLevel = pMoFuSkillCfg->nSkillLevel;
      v4 = pMoFuSkillCfg->nSkillTalent;
      v5 = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(v5, v4, nSkillLevel);
    }
  }
}


#####################################
void __cdecl CExtEquip::OnSaveToDB(CExtEquip *const this, PlayerDBData *const dbData)
{
  _BYTE v2[16]; // [rsp+10h] [rbp-50h] BYREF
  _BYTE v3[16]; // [rsp+20h] [rbp-40h] BYREF
  _BYTE v4[16]; // [rsp+30h] [rbp-30h] BYREF
  _BYTE v5[32]; // [rsp+40h] [rbp-20h] BYREF

  memcpy(dbData->equipData.vEquip, this->m_vMemEquip, sizeof(dbData->equipData.vEquip));
  CExtEquip::saveGemString((CExtEquip *const)v2);
  std::string::operator=(&dbData->gemData.gemInfo, v2);
  std::string::~string(v2);
  CExtEquip::savePosLevelString((CExtEquip *const)v3);
  std::string::operator=(&dbData->gemData.posLevel, v3);
  std::string::~string(v3);
  CExtEquip::saveStrengthenString((CExtEquip *const)v4);
  std::string::operator=(&dbData->gemData.Strengthen, v4);
  std::string::~string(v4);
  CExtEquip::saveShenYaoString((CExtEquip *const)v5);
  std::string::operator=(&dbData->gemData.ShenYaoEquipPos, v5);
  std::string::~string(v5);
  dbData->chr.weapon = this->m_vMemEquip[0].itemId;
  dbData->chr.cloth = this->m_vMemEquip[2].itemId;
  dbData->chr.equipStar = this->m_nEquipStar;
  dbData->chr.equipGem = this->m_nEquipGem;
}


#####################################
void __cdecl CExtEquip::GetInterestsProtocol(CExtEquip *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-22h] BYREF
  unsigned __int16 v3; // [rsp+20h] [rbp-20h] BYREF
  unsigned __int16 v4; // [rsp+22h] [rbp-1Eh] BYREF
  unsigned __int16 v5; // [rsp+24h] [rbp-1Ch] BYREF
  unsigned __int16 v6; // [rsp+26h] [rbp-1Ah] BYREF
  unsigned __int16 v7; // [rsp+28h] [rbp-18h] BYREF
  unsigned __int16 v8; // [rsp+2Ah] [rbp-16h] BYREF
  unsigned __int16 v9; // [rsp+2Ch] [rbp-14h] BYREF
  unsigned __int16 v10; // [rsp+2Eh] [rbp-12h] BYREF
  unsigned __int16 v11; // [rsp+30h] [rbp-10h] BYREF
  unsigned __int16 v12; // [rsp+32h] [rbp-Eh] BYREF
  unsigned __int16 v13; // [rsp+34h] [rbp-Ch] BYREF
  unsigned __int16 v14; // [rsp+36h] [rbp-Ah] BYREF
  unsigned __int16 v15; // [rsp+38h] [rbp-8h] BYREF
  unsigned __int16 v16; // [rsp+3Ah] [rbp-6h] BYREF
  unsigned __int16 v17; // [rsp+3Ch] [rbp-4h] BYREF
  unsigned __int16 v18; // [rsp+3Eh] [rbp-2h] BYREF

  __x = 711;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 712;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 714;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 716;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 717;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 702;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 521;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 701;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 718;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 854;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 775;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 703;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 704;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 705;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 706;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 707;
  std::list<unsigned short>::push_back(procList, &v17);
  v18 = 305;
  std::list<unsigned short>::push_back(procList, &v18);
}


#####################################
int32_t __cdecl CExtEquip::DispatchNetDatas(CExtEquip *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 707 )
    return CExtEquip::onShenYaoPosLevelUp(this, inPacket);
  if ( nProcId > 0x2C3u )
  {
    if ( nProcId == 716 )
      return CExtEquip::onGemAdd(this, inPacket);
    if ( nProcId > 0x2CCu )
    {
      if ( nProcId == 718 )
        return CExtEquip::onEquipUpPhase(this, inPacket);
      if ( nProcId < 0x2CEu )
        return CExtEquip::onGemRemove(this, inPacket);
      if ( nProcId == 775 )
        return CExtEquip::onGemLevelUp(this, inPacket);
      if ( nProcId == 854 )
        return CExtEquip::onBackEquip(this, inPacket);
    }
    else
    {
      switch ( nProcId )
      {
        case 0x2C8u:
          return CExtEquip::onEquipUnDress(this, inPacket);
        case 0x2CAu:
          return CExtEquip::onEquipUpStar(this, inPacket);
        case 0x2C7u:
          return CExtEquip::onEquipDress(this, inPacket);
      }
    }
  }
  else
  {
    if ( nProcId == 702 )
      return CExtEquip::onGemOpenHole(this, inPacket);
    if ( nProcId > 0x2BEu )
    {
      if ( nProcId == 704 )
        return CExtEquip::onEquipExchangeStar(this, inPacket);
      if ( nProcId < 0x2C0u )
        return CExtEquip::onEquipStrenGthen(this, inPacket);
      if ( nProcId == 705 )
        return CExtEquip::onMoFuHuiShou(this, inPacket);
      if ( nProcId == 706 )
        return CExtEquip::onMoFuDuiHuan(this, inPacket);
    }
    else
    {
      switch ( nProcId )
      {
        case 0x209u:
          return CExtEquip::onRelieveBind(this, inPacket);
        case 0x2BDu:
          return CExtEquip::onEquipUpPos(this, inPacket);
        case 0x131u:
          return CExtEquip::OnXinMoEquipHuiShou(this, inPacket);
      }
    }
  }
  return 0;
}


#####################################
int32_t __cdecl CExtEquip::onEquipDress(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  int8_t Int8; // dl
  int32_t nBagSlot; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 2;
  nBagSlot = Answer::NetPacket::readInt32(inPacket);
  Int8 = Answer::NetPacket::readInt8(inPacket);
  if ( !CExtEquip::onEquipExchange(this, nBagSlot, Int8) )
    return 2;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtEquip::onEquipUnDress(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  int8_t nEquipSlot; // [rsp+1Bh] [rbp-5h]
  int nBagSlot; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 2;
  nEquipSlot = Answer::NetPacket::readInt8(inPacket);
  nBagSlot = Player::getFirstFreeSlot(this->m_pPlayer);
  if ( nBagSlot < 0 )
    return 2;
  if ( !CExtEquip::onEquipExchange(this, nBagSlot, nEquipSlot) )
    return 2;
  return 0;
}


#####################################
int32_t __cdecl CExtEquip::onEquipExchangeStar(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  CEquipManager *v5; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v7; // rax
  int32_t itemId; // ebx
  CfgData *v9; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v11; // ebx
  CfgData *v12; // rax
  const CfgEquipTable *v13; // rax
  int8_t star; // bl
  CfgData *v15; // rax
  ItemData *p_CostItem; // rbx
  CExtCharBag *v17; // rax
  int8_t ConnId; // bl
  DBService *v19; // rax
  int8_t v20; // bl
  DBService *v21; // rax
  int8_t v22; // bl
  CEquipManager *v23; // rax
  int8_t v24; // bl
  CEquipManager *v25; // rax
  CExtCharBag *v26; // rax
  CExtCharBag *v27; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v30; // bl
  GameService *v31; // rax
  MemEquip desEquip; // [rsp+10h] [rbp-180h] BYREF
  MemEquip srcEquip; // [rsp+50h] [rbp-140h] BYREF
  UpStartLog SrcEQuipLog; // [rsp+90h] [rbp-100h] BYREF
  UpStartLog DesEQuipLog; // [rsp+C0h] [rbp-D0h] BYREF
  MemChrBag desSlot; // [rsp+F0h] [rbp-A0h] BYREF
  MemChrBag srcSlot; // [rsp+110h] [rbp-80h] BYREF
  _BYTE v39[16]; // [rsp+130h] [rbp-60h] BYREF
  _BYTE v40[11]; // [rsp+140h] [rbp-50h] BYREF
  int8_t nSrcBagType; // [rsp+14Bh] [rbp-45h]
  int32_t nSrcSlot; // [rsp+14Ch] [rbp-44h]
  int8_t nDesBagType; // [rsp+153h] [rbp-3Dh]
  int32_t nDesSlot; // [rsp+154h] [rbp-3Ch]
  const CfgEquip *pSrcEquip; // [rsp+158h] [rbp-38h]
  const CfgEquip *pDesEquip; // [rsp+160h] [rbp-30h]
  CfgEquipExchange *pCfg; // [rsp+168h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nSrcBagType = Answer::NetPacket::readInt8(inPacket);
    nSrcSlot = Answer::NetPacket::readInt32(inPacket);
    nDesBagType = Answer::NetPacket::readInt8(inPacket);
    nDesSlot = Answer::NetPacket::readInt32(inPacket);
    memset(&srcSlot, 0, sizeof(srcSlot));
    if ( nSrcBagType )
    {
      if ( nSrcBagType != 1 )
        return 2;
      Bag = Player::GetBag(this->m_pPlayer);
      srcSlot = *CExtCharBag::GetSlotData(Bag, nSrcSlot);
    }
    else
    {
      if ( (unsigned int)nSrcSlot > 0x5C )
        return 2;
      srcSlot = *CExtEquip::GetEquipSlot(this, nSrcSlot);
    }
    if ( srcSlot.itemId <= 0 || srcSlot.itemClass != 2 || srcSlot.srcId <= 0 )
      return 2;
    memset(&desSlot, 0, sizeof(desSlot));
    if ( nDesBagType )
    {
      if ( nDesBagType != 1 )
        return 2;
      v4 = Player::GetBag(this->m_pPlayer);
      desSlot = *CExtCharBag::GetSlotData(v4, nDesSlot);
    }
    else
    {
      if ( (unsigned int)nDesSlot > 0x5C )
        return 2;
      desSlot = *CExtEquip::GetEquipSlot(this, nDesSlot);
    }
    if ( desSlot.itemId <= 0 || desSlot.itemClass != 2 || desSlot.srcId <= 0 )
      return 2;
    v5 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&srcEquip, v5, srcSlot.srcId);
    if ( srcEquip.base != srcSlot.itemId )
    {
      v2 = 2;
LABEL_56:
      MemEquip::~MemEquip(&srcEquip);
      return v2;
    }
    srcId = desSlot.srcId;
    v7 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&desEquip, v7, srcId);
    if ( desEquip.base == desSlot.itemId )
    {
      if ( srcEquip.star > desEquip.star )
      {
        itemId = srcSlot.itemId;
        v9 = Answer::Singleton<CfgData>::instance();
        EquipTable = CfgData::GetEquipTable(v9);
        pSrcEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
        v11 = desSlot.itemId;
        v12 = Answer::Singleton<CfgData>::instance();
        v13 = CfgData::GetEquipTable(v12);
        pDesEquip = CfgEquipTable::GetEquip(v13, v11);
        if ( pSrcEquip && pDesEquip )
        {
          if ( pSrcEquip->m_nType == pDesEquip->m_nType )
          {
            if ( srcEquip.star <= pDesEquip->m_nLimitStar )
            {
              star = srcEquip.star;
              v15 = Answer::Singleton<CfgData>::instance();
              pCfg = CfgData::GetEquipExchange(v15, star);
              if ( pCfg )
              {
                if ( pCfg->Money <= 0 )
                {
                  if ( ItemData::IsEmpty(&pCfg->CostItem) )
                  {
                    v2 = 2;
                    goto LABEL_55;
                  }
                  p_CostItem = &pCfg->CostItem;
                  v17 = Player::GetBag(this->m_pPlayer);
                  if ( !CExtCharBag::RemoveItem(v17, p_CostItem, ITEM_CHANGE_REASON::IDCR_EQUIP_STAR_CHANGE) )
                  {
                    v2 = 2;
                    goto LABEL_55;
                  }
                }
                else if ( !Player::DecCurrency(
                             this->m_pPlayer,
                             CURRENCY_TYPE::CURRENCY_GOLD,
                             pCfg->Money,
                             CURRENCY_CHANGE_REASON::GCR_EQUIP_EXCHANGE_STAR,
                             srcEquip.star) )
                {
                  v2 = 2;
                  goto LABEL_55;
                }
                desEquip.star = srcEquip.star;
                srcEquip.star = 0;
                memset(&DesEQuipLog, 0, 36);
                std::string::string(&DesEQuipLog.nName);
                DesEQuipLog.nCid = Player::getCid(this->m_pPlayer);
                Player::getName((const Player *const)v39);
                std::string::operator=(&DesEQuipLog.nName, v39);
                std::string::~string(v39);
                DesEQuipLog.nNewStar = desEquip.star;
                DesEQuipLog.nEquipId = desEquip.base;
                DesEQuipLog.nSrcId = desEquip.id;
                DesEQuipLog.nOpway = 2;
                ConnId = Player::getConnId(this->m_pPlayer);
                v19 = Answer::Singleton<DBService>::instance();
                DBService::LogUpEquipStar(v19, ConnId, &DesEQuipLog);
                memset(&SrcEQuipLog, 0, 36);
                std::string::string(&SrcEQuipLog.nName);
                SrcEQuipLog.nCid = Player::getCid(this->m_pPlayer);
                Player::getName((const Player *const)v40);
                std::string::operator=(&SrcEQuipLog.nName, v40);
                std::string::~string(v40);
                SrcEQuipLog.nNewStar = srcEquip.star;
                SrcEQuipLog.nEquipId = srcEquip.base;
                SrcEQuipLog.nSrcId = srcEquip.id;
                SrcEQuipLog.nOpway = 2;
                v20 = Player::getConnId(this->m_pPlayer);
                v21 = Answer::Singleton<DBService>::instance();
                DBService::LogUpEquipStar(v21, v20, &SrcEQuipLog);
                v22 = Player::getConnId(this->m_pPlayer);
                v23 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::UpdateMemEquip(v23, v22, &srcEquip, 215);
                v24 = Player::getConnId(this->m_pPlayer);
                v25 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::UpdateMemEquip(v25, v24, &desEquip, 215);
                if ( nDesBagType )
                {
                  v26 = Player::GetBag(this->m_pPlayer);
                  CExtCharBag::SetSlotData(v26, nDesSlot, &desSlot, ITEM_CHANGE_REASON::ICR_NONE, 0);
                  v27 = Player::GetBag(this->m_pPlayer);
                  CExtCharBag::ForceSendDirty(v27);
                }
                else
                {
                  CExtEquip::addDirty(this, nDesSlot);
                  CExtEquip::checkDirty(this);
                }
                if ( !nSrcBagType || !nDesBagType )
                {
                  Player::recalcAttr(this->m_pPlayer, 0, 0);
                  CExtEquip::updateEquipStar(this);
                }
                Proc = Answer::NetPacket::getProc(inPacket);
                GateIndex = Player::getGateIndex(this->m_pPlayer);
                v30 = Player::getConnId(this->m_pPlayer);
                v31 = Answer::Singleton<GameService>::instance();
                GameService::replySuccess(v31, v30, GateIndex, Proc, 0);
                v2 = 0;
                UpStartLog::~UpStartLog(&SrcEQuipLog);
                UpStartLog::~UpStartLog(&DesEQuipLog);
                goto LABEL_55;
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
    else
    {
      v2 = 2;
    }
LABEL_55:
    MemEquip::~MemEquip(&desEquip);
    goto LABEL_56;
  }
  return 2;
}


#####################################
int32_t __cdecl CExtEquip::onMoFuHuiShou(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int *v3; // rax
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int *v7; // rax
  int32_t v8; // ebx
  CExtCharBag *Bag; // rax
  MemChrBag EquipBag; // [rsp+10h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > itV; // [rsp+30h] [rbp-A0h] BYREF
  Int32Vector vRemoveSlot; // [rsp+40h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+60h] [rbp-70h] BYREF
  Int32Vector vSlot; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v17; // [rsp+A0h] [rbp-30h] BYREF
  int32_t Values; // [rsp+B0h] [rbp-20h]
  int32_t BackCount; // [rsp+B4h] [rbp-1Ch]
  const CfgEquip *pCfgEquip; // [rsp+B8h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  it._M_current = std::vector<int>::begin(&vSlot)._M_current;
  std::vector<int>::vector(&vRemoveSlot);
  Values = 0;
  while ( 1 )
  {
    __rhs._M_current = std::vector<int>::end(&vSlot)._M_current;
    if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &__rhs) )
      break;
    v3 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
    Player::getBagSlotData(&EquipBag, this->m_pPlayer, *v3);
    if ( EquipBag.itemClass == 2 )
    {
      itemId = EquipBag.itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_MoFuHuiShou >= 0 )
        {
          Values += pCfgEquip->m_MoFuHuiShou;
          v7 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
          std::vector<int>::push_back(&vRemoveSlot, v7);
        }
      }
    }
    __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it, 0);
  }
  BackCount = std::vector<int>::size(&vRemoveSlot);
  if ( BackCount > 0 && Values > 0 )
  {
    for ( itV._M_current = std::vector<int>::begin(&vRemoveSlot)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&itV, 0) )
    {
      v17._M_current = std::vector<int>::end(&vRemoveSlot)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&itV, &v17) )
        break;
      v8 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&itV);
      Bag = Player::GetBag(this->m_pPlayer);
      CExtCharBag::CleanSlot(Bag, v8, ITEM_CHANGE_REASON::ICR_EQUIP_BACK);
    }
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_AC_SOCRE,
      Values,
      CURRENCY_CHANGE_REASON::GCR_MO_FU_HUI_SHOU,
      0);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vRemoveSlot);
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtEquip::OnXinMoEquipHuiShou(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int *v3; // rax
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int *v7; // rax
  int32_t v8; // ebx
  CExtCharBag *Bag; // rax
  CXinMo *CXinMo; // rax
  MemChrBag EquipBag; // [rsp+10h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > itV; // [rsp+30h] [rbp-A0h] BYREF
  Int32Vector vRemoveSlot; // [rsp+40h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+60h] [rbp-70h] BYREF
  Int32Vector vSlot; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+90h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v18; // [rsp+A0h] [rbp-30h] BYREF
  int32_t Values; // [rsp+B0h] [rbp-20h]
  int32_t BackCount; // [rsp+B4h] [rbp-1Ch]
  const CfgEquip *pCfgEquip; // [rsp+B8h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  it._M_current = std::vector<int>::begin(&vSlot)._M_current;
  std::vector<int>::vector(&vRemoveSlot);
  Values = 0;
  while ( 1 )
  {
    __rhs._M_current = std::vector<int>::end(&vSlot)._M_current;
    if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &__rhs) )
      break;
    v3 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
    Player::getBagSlotData(&EquipBag, this->m_pPlayer, *v3);
    if ( EquipBag.itemClass == 2 )
    {
      itemId = EquipBag.itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_XinMoExp >= 0 )
        {
          Values += pCfgEquip->m_XinMoExp;
          v7 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
          std::vector<int>::push_back(&vRemoveSlot, v7);
        }
      }
    }
    __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it, 0);
  }
  BackCount = std::vector<int>::size(&vRemoveSlot);
  if ( BackCount > 0 && Values > 0 )
  {
    for ( itV._M_current = std::vector<int>::begin(&vRemoveSlot)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&itV, 0) )
    {
      v18._M_current = std::vector<int>::end(&vRemoveSlot)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&itV, &v18) )
        break;
      v8 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&itV);
      Bag = Player::GetBag(this->m_pPlayer);
      CExtCharBag::CleanSlot(Bag, v8, ITEM_CHANGE_REASON::ICR_EQUIP_BACK);
    }
    CXinMo = Player::GetCXinMo(this->m_pPlayer);
    CXinMo::AddExp(CXinMo, Values);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vRemoveSlot);
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtEquip::onMoFuDuiHuan(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v5; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-24h]
  MoFuDuiHuan *pCfg; // [rsp+20h] [rbp-20h]
  int32_t AlreadyDuiHuanCount; // [rsp+2Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetMoFuDuiHuanlCfg(v3, nId);
  if ( !pCfg )
    return 2;
  if ( pCfg->WeekLimit <= 0 )
    goto LABEL_14;
  if ( nId == 1 )
  {
    AlreadyDuiHuanCount = Player::getRecord(this->m_pPlayer, 37212);
  }
  else
  {
    if ( nId != 2 )
      return 10002;
    AlreadyDuiHuanCount = Player::getRecord(this->m_pPlayer, 37213);
  }
  if ( pCfg->WeekLimit <= AlreadyDuiHuanCount )
    return 10002;
LABEL_14:
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_AC_SOCRE,
          pCfg->ConstScore,
          CURRENCY_CHANGE_REASON::GCR_MO_FU_DUI_HUAN,
          0) )
    return 10002;
  v5 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::AddItem(v5, &pCfg->Item, ITEM_CHANGE_REASON::IDCR_MO_FU_DUI_HUAN);
  if ( pCfg->WeekLimit > 0 )
  {
    if ( nId == 1 )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 37212, 1);
    }
    else if ( nId == 2 )
    {
      v7 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(v7, 37213, 1);
    }
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtEquip::onEquipUpStar(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v5; // rax
  ItemId_t base; // ebx
  CfgData *v7; // rax
  const CfgEquipTable *EquipTable; // rax
  CfgData *v9; // rax
  int32_t MapId; // eax
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t v13; // eax
  int32_t star; // r12d
  int8_t m_nType; // bl
  CfgData *v16; // rax
  const CfgEquipTable *v17; // rax
  CExtCurrency *v18; // rax
  int64_t MoneyBindAndNoBind; // rax
  int64_t v21; // rax
  ItemDataList *p_m_lCosItem; // rbx
  CExtCharBag *Bag; // rax
  CExtCharBag *v25; // rax
  int64_t m_nCostMoney; // rbx
  CExtCurrency *Currency; // rax
  CExtCharBag *v28; // rax
  Answer::Random *v29; // rax
  ChrTask *Task; // rax
  int8_t ConnId; // bl
  CEquipManager *v32; // rax
  ChrTask *v33; // rax
  int8_t v34; // bl
  DBService *v35; // rax
  int32_t v36; // r12d
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v38; // rax
  EquipId_t v39; // r14
  uint16_t v40; // r13
  GameService *v41; // rax
  GameService *v42; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v45; // rax
  EquipId_t id; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v49; // bl
  GameService *v50; // rax
  MemChrBag v52; // [rsp+0h] [rbp-160h] BYREF
  Answer::NetPacket *inPacketa; // [rsp+20h] [rbp-140h]
  CExtEquip *thisa; // [rsp+28h] [rbp-138h]
  MemEquip equip; // [rsp+30h] [rbp-130h] BYREF
  UpStartLog EquipLog; // [rsp+70h] [rbp-F0h] BYREF
  MemChrBag bagItem; // [rsp+A0h] [rbp-C0h] BYREF
  int32_t nUnBindCount; // [rsp+C8h] [rbp-98h] BYREF
  int32_t nBindCount; // [rsp+CCh] [rbp-94h] BYREF
  Int32Vector vSlot; // [rsp+D0h] [rbp-90h] BYREF
  _BYTE v61[16]; // [rsp+F0h] [rbp-70h] BYREF
  std::string val; // [rsp+100h] [rbp-60h] BYREF
  int8_t nBagType; // [rsp+113h] [rbp-4Dh]
  int32_t nPos; // [rsp+114h] [rbp-4Ch]
  const CfgEquip *pCfgEquip; // [rsp+118h] [rbp-48h]
  const CfgEquipUpStar *pCfgUpStar; // [rsp+120h] [rbp-40h]
  int32_t nAddStar; // [rsp+128h] [rbp-38h]
  int32_t nRand; // [rsp+12Ch] [rbp-34h]
  CfgNpc *cfgNpc; // [rsp+130h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+138h] [rbp-28h]

  thisa = this;
  inPacketa = inPacket;
  if ( this->m_pPlayer && inPacketa )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(thisa->m_pPlayer);
    if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 215) )
      return 2;
    nBagType = Answer::NetPacket::readInt8(inPacketa);
    nPos = Answer::NetPacket::readInt32(inPacketa);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(thisa->m_pPlayer, inPacketa, &vSlot);
    memset(&bagItem, 0, sizeof(bagItem));
    if ( nBagType )
    {
      if ( nBagType != 1 )
      {
        v2 = 2;
        goto LABEL_73;
      }
      Player::getBagSlotData(&v52, thisa->m_pPlayer, nPos);
      bagItem = v52;
    }
    else
    {
      if ( (unsigned int)nPos > 0x5C )
      {
        v2 = 2;
LABEL_73:
        std::vector<int>::~vector(&vSlot);
        return v2;
      }
      bagItem = thisa->m_vMemEquip[nPos];
    }
    if ( bagItem.itemClass != 2 || bagItem.itemId <= 0 || bagItem.itemCount <= 0 )
    {
      v2 = 2;
      goto LABEL_73;
    }
    srcId = bagItem.srcId;
    v5 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v5, srcId);
    if ( equip.base == bagItem.itemId )
    {
      base = equip.base;
      v7 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v7);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, base);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_nType < 8u )
        {
          v9 = Answer::Singleton<CfgData>::instance();
          cfgNpc = CfgData::getNpc(v9, 3017);
          if ( !cfgNpc )
          {
            v2 = 2;
            goto LABEL_72;
          }
          MapId = StaticObj::getMapId(thisa->m_pPlayer);
          if ( !CfgNpc::findMapId(cfgNpc, MapId) )
          {
            v2 = 2;
            goto LABEL_72;
          }
          PosY = StaticObj::GetPosY(thisa->m_pPlayer);
          PosX = StaticObj::GetPosX(thisa->m_pPlayer);
          v13 = StaticObj::getMapId(thisa->m_pPlayer);
          if ( !CfgNpc::NearNpc(cfgNpc, v13, PosX, PosY, 10) )
          {
            v2 = 2;
            goto LABEL_72;
          }
        }
        if ( equip.star < pCfgEquip->m_nLimitStar )
        {
          star = equip.star;
          m_nType = pCfgEquip->m_nType;
          v16 = Answer::Singleton<CfgData>::instance();
          v17 = CfgData::GetEquipTable(v16);
          pCfgUpStar = CfgEquipTable::GetEquipUpStar(v17, m_nType, star);
          if ( pCfgUpStar )
          {
            if ( pCfgUpStar->m_nRate >= 0 )
            {
              if ( pCfgUpStar->m_nCostMoney > 0
                && (v18 = Player::GetCurrency(thisa->m_pPlayer),
                    MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v18),
                    MoneyBindAndNoBind < pCfgUpStar->m_nCostMoney) )
              {
                v2 = 2;
              }
              else
              {
                if ( pCfgUpStar->m_nCostXingMai <= 0
                  || (v21 = Player::GetCurrency(thisa->m_pPlayer, CURRENCY_TYPE::CURRENCY_BOSS_SCORE),
                      v21 >= pCfgUpStar->m_nCostXingMai) )
                {
                  if ( !std::list<ItemData>::empty(&pCfgUpStar->m_lCosItem) )
                  {
                    nBindCount = 0;
                    nUnBindCount = 0;
                    p_m_lCosItem = &pCfgUpStar->m_lCosItem;
                    Bag = Player::GetBag(thisa->m_pPlayer);
                    if ( !CExtCharBag::RemoveItem(
                            Bag,
                            p_m_lCosItem,
                            ITEM_CHANGE_REASON::ICR_EQUIP_UPSTAR,
                            &nBindCount,
                            &nUnBindCount) )
                    {
                      v2 = 2;
                      goto LABEL_72;
                    }
                    v25 = Player::GetBag(thisa->m_pPlayer);
                    CExtCharBag::ForceSendDirty(v25);
                  }
                  if ( pCfgUpStar->m_nCostMoney > 0 )
                  {
                    m_nCostMoney = pCfgUpStar->m_nCostMoney;
                    Currency = Player::GetCurrency(thisa->m_pPlayer);
                    CExtCurrency::DecMoneyAndNoBind(Currency, m_nCostMoney, CURRENCY_CHANGE_REASON::MCR_EQUIP_UPSTAR, 0);
                  }
                  if ( pCfgUpStar->m_nCostXingMai > 0 )
                    Player::DecCurrency(
                      thisa->m_pPlayer,
                      CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
                      pCfgUpStar->m_nCostXingMai,
                      CURRENCY_CHANGE_REASON::SCR_EQUIP_UPSTAR,
                      0);
                  if ( nBagType )
                  {
                    v28 = Player::GetBag(thisa->m_pPlayer);
                    CExtCharBag::SetSlotData(v28, nPos, &bagItem, ITEM_CHANGE_REASON::ICR_NONE, 0);
                  }
                  else
                  {
                    CExtEquip::addDirty(thisa, nPos);
                  }
                  nAddStar = 0;
                  v29 = Answer::Singleton<Answer::Random>::instance();
                  nRand = Answer::Random::generate(v29, 1, 10000);
                  if ( pCfgUpStar->m_nRate < nRand )
                    nAddStar = -pCfgUpStar->m_nFailLostStar;
                  else
                    nAddStar = pCfgUpStar->m_nSuccessAddStar;
                  Task = Player::GetTask(thisa->m_pPlayer);
                  ChrTask::updateTaskCount(Task, 8, 0);
                  if ( nAddStar )
                  {
                    equip.star += nAddStar;
                    ConnId = Player::getConnId(thisa->m_pPlayer);
                    v32 = Answer::Singleton<CEquipManager>::instance();
                    CEquipManager::UpdateMemEquip(v32, ConnId, &equip, 215);
                    if ( !nBagType )
                    {
                      Player::recalcAttr(thisa->m_pPlayer, 0, 0);
                      v33 = Player::GetTask(thisa->m_pPlayer);
                      ChrTask::updateTaskCount(v33, 19, 0);
                      CExtEquip::updateEquipStar(thisa);
                    }
                    if ( pCfgEquip->m_nType < 8u )
                    {
                      memset(&EquipLog, 0, 36);
                      std::string::string(&EquipLog.nName);
                      EquipLog.nCid = Player::getCid(thisa->m_pPlayer);
                      Player::getName((const Player *const)v61);
                      std::string::operator=(&EquipLog.nName, v61);
                      std::string::~string(v61);
                      EquipLog.nNewStar = equip.star;
                      EquipLog.nEquipId = equip.base;
                      EquipLog.nSrcId = equip.id;
                      EquipLog.nOpway = 1;
                      v34 = Player::getConnId(thisa->m_pPlayer);
                      v35 = Answer::Singleton<DBService>::instance();
                      DBService::LogUpEquipStar(v35, v34, &EquipLog);
                      UpStartLog::~UpStartLog(&EquipLog);
                    }
                  }
                  if ( nAddStar <= 0 )
                  {
                    id = equip.id;
                    Proc = Answer::NetPacket::getProc(inPacketa);
                    GateIndex = Player::getGateIndex(thisa->m_pPlayer);
                    v49 = Player::getConnId(thisa->m_pPlayer);
                    v50 = Answer::Singleton<GameService>::instance();
                    GameService::replyfailure(v50, v49, GateIndex, Proc, 1, id);
                  }
                  else
                  {
                    v36 = equip.star;
                    m_pPlayer = thisa->m_pPlayer;
                    v38 = Answer::Singleton<CFestivalDoubleEleven>::instance();
                    CFestivalDoubleEleven::AddEquipUpStarBack(v38, m_pPlayer, v36);
                    v39 = equip.id;
                    v40 = Answer::NetPacket::getProc(inPacketa);
                    LOWORD(v36) = Player::getGateIndex(thisa->m_pPlayer);
                    LOBYTE(m_pPlayer) = Player::getConnId(thisa->m_pPlayer);
                    v41 = Answer::Singleton<GameService>::instance();
                    GameService::replySuccess(v41, (int8_t)m_pPlayer, v36, v40, v39);
                    if ( pCfgEquip->m_nType < 8u && equip.star == 5 * (equip.star / 5) )
                    {
                      v42 = Answer::Singleton<GameService>::instance();
                      packet = GameService::popNetpacket(v42, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
                      if ( packet )
                      {
                        Answer::NetPacket::writeInt32(packet, 524);
                        Player::getName((const Player *const)&val);
                        Answer::NetPacket::writeUTF8(packet, &val);
                        std::string::~string(&val);
                        Cid = Player::getCid(thisa->m_pPlayer);
                        Answer::NetPacket::writeInt64(packet, Cid);
                        Answer::NetPacket::writeInt32(packet, equip.base);
                        Answer::NetPacket::writeInt64(packet, equip.id);
                        Answer::NetPacket::writeInt32(packet, equip.star);
                        WOffset = Answer::NetPacket::getWOffset(packet);
                        Answer::NetPacket::setSize(packet, WOffset);
                        v45 = Answer::Singleton<GameService>::instance();
                        GameService::worldBroadcast(v45, 0, packet);
                      }
                    }
                  }
                  v2 = 0;
                  goto LABEL_72;
                }
                v2 = 2;
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
    else
    {
      v2 = 2;
    }
LABEL_72:
    MemEquip::~MemEquip(&equip);
    goto LABEL_73;
  }
  return 2;
}


#####################################
int32_t __cdecl CExtEquip::onBackEquip(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CVip *PlayerVip; // rax
  CVip *v4; // rax
  int *v6; // rax
  int32_t itemId; // ebx
  CfgData *v8; // rax
  const CfgEquipTable *EquipTable; // rax
  int *v10; // rax
  int *v11; // rax
  int32_t v12; // ebx
  CExtCharBag *Bag; // rax
  CVip *v14; // rax
  std::pair<const int,int> *v15; // rax
  int64_t v16; // r12
  std::pair<const int,int> *v17; // rax
  ChrTask *Task; // rax
  Int32Int32Map CurrMap; // [rsp+10h] [rbp-110h] BYREF
  MemChrBag EquipBag; // [rsp+40h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > itV; // [rsp+60h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itMap; // [rsp+70h] [rbp-B0h] BYREF
  Int32Vector vRemoveSlot; // [rsp+80h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+A0h] [rbp-80h] BYREF
  Int32Vector vSlot; // [rsp+B0h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+D0h] [rbp-50h] BYREF
  int __k; // [rsp+DCh] [rbp-44h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v29; // [rsp+E0h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+F0h] [rbp-30h] BYREF
  int32_t BackCount; // [rsp+100h] [rbp-20h]
  int32_t Rate; // [rsp+104h] [rbp-1Ch]
  const CfgEquip *pCfgEquip; // [rsp+108h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  if ( StaticObj::getMapId(this->m_pPlayer) != 50001 )
  {
    PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
    if ( !CVip::GetVipFlg(PlayerVip, 1) )
    {
      v4 = Player::GetPlayerVip(this->m_pPlayer);
      if ( !CVip::GetVipFlg(v4, 2) )
        return 10002;
    }
  }
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  it._M_current = std::vector<int>::begin(&vSlot)._M_current;
  std::map<int,int>::map(&CurrMap);
  std::vector<int>::vector(&vRemoveSlot);
  while ( 1 )
  {
    __rhs._M_current = std::vector<int>::end(&vSlot)._M_current;
    if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &__rhs) )
      break;
    v6 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
    Player::getBagSlotData(&EquipBag, this->m_pPlayer, *v6);
    if ( EquipBag.itemClass == 2 )
    {
      itemId = EquipBag.itemId;
      v8 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v8);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_BackType >= 0 && pCfgEquip->m_BackValue > 0 )
        {
          __k = pCfgEquip->m_BackType;
          v10 = std::map<int,int>::operator[](&CurrMap, &__k);
          *v10 += pCfgEquip->m_BackValue;
          v11 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
          std::vector<int>::push_back(&vRemoveSlot, v11);
        }
      }
    }
    __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it, 0);
  }
  BackCount = std::vector<int>::size(&vRemoveSlot);
  if ( BackCount > 0 )
  {
    for ( itV._M_current = std::vector<int>::begin(&vRemoveSlot)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&itV, 0) )
    {
      v29._M_current = std::vector<int>::end(&vRemoveSlot)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&itV, &v29) )
        break;
      v12 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&itV);
      Bag = Player::GetBag(this->m_pPlayer);
      CExtCharBag::CleanSlot(Bag, v12, ITEM_CHANGE_REASON::ICR_EQUIP_BACK);
    }
    v14 = Player::GetPlayerVip(this->m_pPlayer);
    Rate = CVip::GetVipEquipBackRate(v14);
    for ( itMap._M_node = std::map<int,int>::begin(&CurrMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itMap, 0) )
    {
      __x._M_node = std::map<int,int>::end(&CurrMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itMap, &__x) )
        break;
      v15 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      v16 = Rate * v15->second / 10;
      v17 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
      Player::AddCurrency(
        this->m_pPlayer,
        (const CURRENCY_TYPE)v17->first,
        v16,
        CURRENCY_CHANGE_REASON::GCR_EQUIP_BACK,
        0);
    }
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskCount(Task, 40, BackCount);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vRemoveSlot);
  std::map<int,int>::~map(&CurrMap);
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtEquip::onEquipUpPhase(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const cfgEquipUpPhaseTable *EquipUpPhaseTable; // rax
  EquipId_t srcId; // r12
  CEquipManager *v6; // rax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *Bag; // rax
  int v12; // r12d
  int *M_current; // r12
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v14; // rax
  int v15; // r12d
  CExtCharBag *v16; // rax
  CExtCharBag *v17; // rax
  int64_t m_CostMoney; // rbx
  CExtCurrency *v19; // rax
  int8_t ConnId; // bl
  GameService *v21; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v24; // bl
  GameService *v25; // rax
  int8_t v26; // bl
  CEquipManager *v27; // rax
  CExtCharBag *v28; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v30; // rax
  EquipId_t id; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  GameService *v34; // rax
  MemChrBag v36; // [rsp+0h] [rbp-170h] BYREF
  Answer::NetPacket *inPacketa; // [rsp+20h] [rbp-150h]
  CExtEquip *thisa; // [rsp+28h] [rbp-148h]
  MemEquip NowEquip; // [rsp+30h] [rbp-140h] BYREF
  MemChrBag EquipBag; // [rsp+70h] [rbp-100h] BYREF
  Int32Vector Slot; // [rsp+90h] [rbp-E0h] BYREF
  std::_List_iterator<ItemData> it; // [rsp+B0h] [rbp-C0h] BYREF
  Int32Vector SlotList; // [rsp+C0h] [rbp-B0h] BYREF
  ItemDataList CostItem; // [rsp+E0h] [rbp-90h] BYREF
  std::_List_iterator<ItemData> v45; // [rsp+F0h] [rbp-80h] BYREF
  Int32Vector __x; // [rsp+100h] [rbp-70h] BYREF
  std::string val; // [rsp+120h] [rbp-50h] BYREF
  int8_t nBagType; // [rsp+137h] [rbp-39h]
  int32_t EquipId; // [rsp+138h] [rbp-38h]
  int32_t nPos; // [rsp+13Ch] [rbp-34h]
  const cfgEquipUpPhase *EquipUpPhase; // [rsp+140h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+148h] [rbp-28h]

  thisa = this;
  inPacketa = inPacket;
  if ( inPacket && thisa->m_pPlayer )
  {
    nBagType = Answer::NetPacket::readInt8(inPacketa);
    EquipId = Answer::NetPacket::readInt32(inPacketa);
    nPos = Answer::NetPacket::readInt32(inPacketa);
    memset(&EquipBag, 0, sizeof(EquipBag));
    if ( nBagType )
    {
      if ( nBagType != 1 )
        return 2;
      Player::getBagSlotData(&v36, thisa->m_pPlayer, nPos);
      EquipBag = v36;
    }
    else
    {
      if ( (unsigned int)nPos > 0x5C )
        return 2;
      EquipBag = thisa->m_vMemEquip[nPos];
    }
    if ( EquipBag.itemId <= 0 || EquipBag.itemCount <= 0 )
      return 2;
    if ( EquipBag.itemClass != 2 )
      return 10002;
    v3 = Answer::Singleton<CfgData>::instance();
    EquipUpPhaseTable = CfgData::GetEquipUpPhaseTable(v3);
    EquipUpPhase = cfgEquipUpPhaseTable::GetData(EquipUpPhaseTable, EquipId);
    if ( !EquipId )
      return 10002;
    srcId = EquipBag.srcId;
    v6 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&NowEquip, v6, srcId);
    if ( NowEquip.base != EquipBag.itemId )
    {
      v2 = 10002;
LABEL_53:
      MemEquip::~MemEquip(&NowEquip);
      return v2;
    }
    if ( EquipUpPhase->m_CostMoney > 0 )
    {
      Currency = Player::GetCurrency(thisa->m_pPlayer);
      MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
      if ( MoneyBindAndNoBind < EquipUpPhase->m_CostMoney )
      {
        v2 = 2;
        goto LABEL_53;
      }
    }
    std::list<ItemData>::list(&CostItem, &EquipUpPhase->m_CostItems);
    if ( nBagType == 1 )
    {
      std::vector<int>::vector(&SlotList);
      for ( it._M_node = std::list<ItemData>::begin(&CostItem)._M_node; ; std::_List_iterator<ItemData>::operator++(
                                                                            &it,
                                                                            0) )
      {
        v45._M_node = std::list<ItemData>::end(&CostItem)._M_node;
        if ( !std::_List_iterator<ItemData>::operator!=(&it, &v45) )
          break;
        std::vector<int>::vector(&Slot);
        m_nId = std::_List_iterator<ItemData>::operator->(&it)->m_nId;
        m_nClass = std::_List_iterator<ItemData>::operator->(&it)->m_nClass;
        Bag = Player::GetBag(thisa->m_pPlayer);
        CExtCharBag::GetItemSlot(&__x, Bag, m_nClass, m_nId, nPos);
        std::vector<int>::operator=(&Slot, &__x);
        std::vector<int>::~vector(&__x);
        if ( std::vector<int>::size(&Slot) )
        {
          M_current = std::vector<int>::end(&Slot)._M_current;
          v14._M_current = std::vector<int>::begin(&Slot)._M_current;
          std::vector<int>::assign<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
            &SlotList,
            v14,
            (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
          v12 = 1;
        }
        else
        {
          v2 = 2;
          v12 = 0;
        }
        std::vector<int>::~vector(&Slot);
        if ( !v12 )
        {
          v15 = 0;
          goto LABEL_37;
        }
      }
      if ( std::vector<int>::size(&SlotList) )
      {
        v16 = Player::GetBag(thisa->m_pPlayer);
        if ( !CExtCharBag::RemoveItem(v16, &SlotList, &CostItem, ITEM_CHANGE_REASON::ICR_EQUIP_UP_STAGE) )
        {
          v2 = 10002;
          v15 = 0;
        }
        else
        {
          v15 = 1;
        }
      }
      else
      {
        v2 = 2;
        v15 = 0;
      }
LABEL_37:
      std::vector<int>::~vector(&SlotList);
      if ( !v15 )
        goto LABEL_52;
    }
    else
    {
      v17 = Player::GetBag(thisa->m_pPlayer);
      if ( !CExtCharBag::RemoveItem(v17, &CostItem, ITEM_CHANGE_REASON::ICR_EQUIP_UP_STAGE) )
      {
        v2 = 10002;
        goto LABEL_52;
      }
    }
    if ( EquipUpPhase->m_CostMoney <= 0
      || (m_CostMoney = EquipUpPhase->m_CostMoney,
          v19 = Player::GetCurrency(thisa->m_pPlayer),
          CExtCurrency::DecMoneyAndNoBind(v19, m_CostMoney, CURRENCY_CHANGE_REASON::MCR_EQUIP_UP_LEVEL, 0)) )
    {
      NowEquip.base = EquipUpPhase->m_GiveEquip;
      if ( EquipUpPhase->m_GongGaoId > 0 )
      {
        ConnId = Player::getConnId(thisa->m_pPlayer);
        v21 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v21, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet )
        {
          v2 = 10002;
          goto LABEL_52;
        }
        Answer::NetPacket::writeInt32(packet, EquipUpPhase->m_GongGaoId);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Cid = Player::getCid(thisa->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, Cid);
        Answer::NetPacket::writeInt64(packet, EquipBag.srcId);
        Answer::NetPacket::writeInt32(packet, EquipUpPhase->m_CostEquip);
        Answer::NetPacket::writeInt32(packet, EquipUpPhase->m_GiveEquip);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v24 = Player::getConnId(thisa->m_pPlayer);
        v25 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v25, v24, packet);
      }
      v26 = Player::getConnId(thisa->m_pPlayer);
      v27 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::UpdateMemEquip(v27, v26, &NowEquip, 220);
      if ( nBagType )
      {
        EquipBag.itemId = EquipUpPhase->m_GiveEquip;
        v28 = Player::GetBag(thisa->m_pPlayer);
        CExtCharBag::SetSlotData(v28, nPos, &EquipBag, ITEM_CHANGE_REASON::ICR_NONE, 0);
      }
      else
      {
        thisa->m_vMemEquip[nPos].itemId = EquipUpPhase->m_GiveEquip;
        CExtEquip::addDirty(thisa, nPos);
        CExtEquip::checkEquipSuit(thisa, 0);
        Player::recalcAttr(thisa->m_pPlayer, 0, 0);
      }
      m_pPlayer = thisa->m_pPlayer;
      v30 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v30, m_pPlayer, &NowEquip);
      id = NowEquip.id;
      Proc = Answer::NetPacket::getProc(inPacketa);
      GateIndex = Player::getGateIndex(thisa->m_pPlayer);
      LOBYTE(m_pPlayer) = Player::getConnId(thisa->m_pPlayer);
      v34 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v34, (int8_t)m_pPlayer, GateIndex, Proc, id);
      v2 = 0;
      goto LABEL_52;
    }
    v2 = 10002;
LABEL_52:
    std::list<ItemData>::~list(&CostItem);
    goto LABEL_53;
  }
  return 2;
}


#####################################
int32_t __cdecl CExtEquip::onRelieveBind(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  CExtCharBag *v5; // rax
  MemChrBag v7; // [rsp+0h] [rbp-A0h] BYREF
  Answer::NetPacket *inPacketa; // [rsp+20h] [rbp-80h]
  CExtEquip *thisa; // [rsp+28h] [rbp-78h]
  MemChrBag Equip; // [rsp+30h] [rbp-70h] BYREF
  ItemData data; // [rsp+50h] [rbp-50h] BYREF
  Int32Vector vSlot; // [rsp+60h] [rbp-40h] BYREF
  int32_t nItemPos; // [rsp+84h] [rbp-1Ch] BYREF
  int8_t nBagType; // [rsp+8Bh] [rbp-15h]
  int32_t nPos; // [rsp+8Ch] [rbp-14h]

  thisa = this;
  inPacketa = inPacket;
  if ( !inPacket || !thisa->m_pPlayer )
    return 10002;
  nBagType = Answer::NetPacket::readInt8(inPacketa);
  nPos = Answer::NetPacket::readInt32(inPacketa);
  nItemPos = Answer::NetPacket::readInt32(inPacketa);
  memset(&Equip, 0, sizeof(Equip));
  if ( nBagType )
  {
    if ( nBagType != 1 )
      return 2;
    Player::getBagSlotData(&v7, thisa->m_pPlayer, nPos);
    Equip = v7;
  }
  else
  {
    if ( (unsigned int)nPos > 0x5C )
      return 2;
    Equip = thisa->m_vMemEquip[nPos];
  }
  if ( !Equip.bind )
    return 2;
  if ( Equip.itemId <= 0 || Equip.itemCount <= 0 )
    return 2;
  if ( Equip.itemClass != 2 )
    return 10002;
  std::vector<int>::vector(&vSlot);
  *(_QWORD *)&data.m_nId = 0;
  data.m_nCount = 0;
  std::vector<int>::push_back(&vSlot, &nItemPos);
  data.m_nId = 7321;
  data.m_nClass = 1;
  data.m_nCount = 1;
  Bag = Player::GetBag(thisa->m_pPlayer);
  if ( !CExtCharBag::RemoveItem(Bag, &vSlot, &data, ITEM_CHANGE_REASON::ICR_EQUIP_RELIEVE_BIND) )
  {
    v2 = 2;
  }
  else
  {
    if ( nBagType )
    {
      Equip.bind = 0;
      v4 = Player::GetBag(thisa->m_pPlayer);
      CExtCharBag::SetSlotData(v4, nPos, &Equip, ITEM_CHANGE_REASON::ICR_NONE, 0);
      v5 = Player::GetBag(thisa->m_pPlayer);
      CExtCharBag::ForceSendDirty(v5);
    }
    else
    {
      thisa->m_vMemEquip[nPos].bind = 0;
      CExtEquip::addDirty(thisa, nPos);
    }
    v2 = 0;
  }
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtEquip::onEquipStrenGthen(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  ItemData *p_ConstItem; // r12
  CExtCharBag *Bag; // rax
  int64_t v8; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  int32_t v13; // r12d
  int32_t v14; // ebx
  CfgData *v15; // rax
  const CfgEquipTable *v16; // rax
  GameService *v17; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v20; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-70h] BYREF
  std::string val; // [rsp+30h] [rbp-50h] BYREF
  int8_t nPos; // [rsp+43h] [rbp-3Dh]
  int32_t nLevel; // [rsp+44h] [rbp-3Ch]
  const EquipStrengthenCfg *pStrengthen; // [rsp+48h] [rbp-38h]
  const EquipStrengthenCfg *pNewStrengthen; // [rsp+50h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nPos = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( (unsigned __int8)nPos < 0xAu )
    {
      nLevel = this->m_vMemStrengthen[nPos];
      v3 = nPos;
      v4 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v4);
      pStrengthen = CfgEquipTable::GetEquipStrengthenCfg(EquipTable, v3, nLevel);
      if ( pStrengthen )
      {
        if ( ItemData::IsEmpty(&pStrengthen->ConstItem) )
        {
          v2 = 10002;
        }
        else
        {
          p_ConstItem = &pStrengthen->ConstItem;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::RemoveItem(Bag, &vSlot, p_ConstItem, ITEM_CHANGE_REASON::IDCR_EQUIP_STREN_GTHEN) )
          {
            v2 = 10002;
          }
          else
          {
            ++this->m_vMemStrengthen[nPos];
            Player::recalcAttr(this->m_pPlayer, 0, 0);
            v8 = nPos;
            Proc = Answer::NetPacket::getProc(inPacket);
            GateIndex = Player::getGateIndex(this->m_pPlayer);
            ConnId = Player::getConnId(this->m_pPlayer);
            v12 = Answer::Singleton<GameService>::instance();
            GameService::replySuccess(v12, ConnId, GateIndex, Proc, v8);
            v13 = this->m_vMemStrengthen[nPos];
            v14 = nPos;
            v15 = Answer::Singleton<CfgData>::instance();
            v16 = CfgData::GetEquipTable(v15);
            pNewStrengthen = CfgEquipTable::GetEquipStrengthenCfg(v16, v14, v13);
            if ( pNewStrengthen )
            {
              if ( pNewStrengthen->GongGaoId > 0 )
              {
                v17 = Answer::Singleton<GameService>::instance();
                packet = GameService::popNetpacket(v17, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
                if ( !packet )
                {
                  v2 = 10002;
                  goto LABEL_19;
                }
                Answer::NetPacket::writeInt32(packet, pNewStrengthen->GongGaoId);
                Player::getName((const Player *const)&val);
                Answer::NetPacket::writeUTF8(packet, &val);
                std::string::~string(&val);
                Cid = Player::getCid(this->m_pPlayer);
                Answer::NetPacket::writeInt64(packet, Cid);
                Answer::NetPacket::writeInt8(packet, nPos);
                Answer::NetPacket::writeInt32(packet, this->m_vMemStrengthen[nPos]);
                WOffset = Answer::NetPacket::getWOffset(packet);
                Answer::NetPacket::setSize(packet, WOffset);
                v20 = Answer::Singleton<GameService>::instance();
                GameService::worldBroadcast(v20, 0, packet);
              }
              v2 = 0;
              goto LABEL_19;
            }
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
LABEL_19:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 2;
}


#####################################
void __cdecl CExtEquip::SendStrenGthenInfo(CExtEquip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  char i; // [rsp+1Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DC2u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 10);
      for ( i = 0; i <= 9; ++i )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_vMemStrengthen[i]);
      }
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
int32_t __cdecl CExtEquip::onEquipUpPos(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // r13d
  int8_t v4; // r12
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v7; // eax
  CExtCurrency *v8; // rax
  int64_t MoneyBindAndNoBind; // rax
  bool v10; // al
  ItemData *v11; // r12
  CExtCharBag *v12; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *Bag; // rax
  ItemData *v16; // rax
  ItemData *v17; // rax
  ItemData *v18; // rax
  int32_t v19; // r13d
  int8_t v20; // r12
  CfgData *v21; // rax
  int v22; // r12d
  std::_List_iterator<ItemData> v23; // rax
  int64_t Currency; // rax
  CExtCharBag *v26; // rax
  ItemDataList *p_m_nConstItem; // rbx
  CExtCharBag *v30; // rax
  int64_t m_nCostMoney; // rbx
  CExtCurrency *v32; // rax
  bool v33; // al
  ItemData *p_m_BaoHuConst; // rbx
  CExtCharBag *v35; // rax
  Answer::Random *v36; // rax
  int32_t v37; // eax
  int64_t v39; // r15
  int32_t v40; // r14d
  uint16_t v41; // r13
  int16_t v42; // r12
  int8_t v43; // bl
  GameService *v44; // rax
  int64_t v45; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v49; // rax
  GameService *v50; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v53; // rax
  ChrTask *Task; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  Player *m_pPlayer; // rbx
  CKaiFuHuoDong *v57; // rax
  CSevenDayTask *CSevenDayTask; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-C0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-B0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-A0h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-80h] BYREF
  std::string val; // [rsp+60h] [rbp-70h] BYREF
  int8_t nPos; // [rsp+71h] [rbp-5Fh]
  int8_t AutoBuy; // [rsp+72h] [rbp-5Eh]
  int8_t BaoHu; // [rsp+73h] [rbp-5Dh]
  int32_t nLevel; // [rsp+74h] [rbp-5Ch]
  const CfgEquipUpPos *pCfgEquipUpPos; // [rsp+78h] [rbp-58h]
  int32_t nCostGold; // [rsp+84h] [rbp-4Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-48h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-44h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-40h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-38h]

  if ( inPacket && this->m_pPlayer )
  {
    nPos = Answer::NetPacket::readInt8(inPacket);
    AutoBuy = Answer::NetPacket::readInt8(inPacket);
    BaoHu = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    if ( (unsigned __int8)nPos < 0xAu )
    {
      nLevel = this->m_vMemPosLevel[nPos];
      v3 = nLevel + 1;
      v4 = nPos;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquipUpPos = CfgEquipTable::GetEquipUpPos(EquipTable, v4, v3);
      if ( pCfgEquipUpPos )
      {
        v7 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
        if ( v7 >= pCfgEquipUpPos->m_nNeedLevel )
        {
          if ( pCfgEquipUpPos->m_nCostMoney <= 0
            || (v8 = Player::GetCurrency(this->m_pPlayer),
                MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v8),
                MoneyBindAndNoBind >= pCfgEquipUpPos->m_nCostMoney) )
          {
            v10 = !ItemData::IsEmpty(&pCfgEquipUpPos->m_BaoHuConst) && BaoHu == 1;
            if ( v10
              && (v11 = &pCfgEquipUpPos->m_BaoHuConst,
                  v12 = Player::GetBag(this->m_pPlayer),
                  !CExtCharBag::HasItem(v12, v11)) )
            {
              v2 = 10002;
            }
            else
            {
              if ( AutoBuy )
              {
                nCostGold = 0;
                std::list<ItemData>::list(&costItemList, &pCfgEquipUpPos->m_nConstItem);
                iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
                while ( 1 )
                {
                  __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
                  if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
                    break;
                  nBuyCount = 0;
                  m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
                  m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
                  Bag = Player::GetBag(this->m_pPlayer);
                  nItemCount = CExtCharBag::GetItemCount(Bag, &vSlot, m_nClass, m_nId);
                  v16 = std::_List_iterator<ItemData>::operator->(&iter);
                  if ( v16->m_nCount > nItemCount )
                  {
                    v17 = std::_List_iterator<ItemData>::operator->(&iter);
                    nBuyCount = v17->m_nCount - nItemCount;
                    v18 = std::_List_iterator<ItemData>::operator->(&iter);
                    v18->m_nCount = nItemCount;
                  }
                  if ( nBuyCount > 0 )
                  {
                    v19 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
                    v20 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
                    v21 = Answer::Singleton<CfgData>::instance();
                    pCfgGameShop = CfgData::GetGameShopItem(v21, v20, v19);
                    if ( !pCfgGameShop )
                    {
                      v2 = 2;
                      v22 = 0;
                      goto LABEL_51;
                    }
                    nCostGold += nBuyCount * pCfgGameShop->Price;
                  }
                  if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
                  {
                    std::_List_iterator<ItemData>::operator++(&iter);
                  }
                  else
                  {
                    v23._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
                    std::list<ItemData>::erase(&costItemList, v23);
                  }
                }
                if ( nCostGold > 0
                  && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
                {
                  v2 = 10002;
                  v22 = 0;
                }
                else if ( !std::list<ItemData>::empty(&costItemList)
                       && (v26 = Player::GetBag(this->m_pPlayer),
                           !CExtCharBag::RemoveItem(v26, &vSlot, &costItemList, ITEM_CHANGE_REASON::ICR_UP_EQUIP_POS)) )
                {
                  v2 = 10002;
                  v22 = 0;
                }
                else if ( nCostGold > 0
                       && !Player::DecCurrency(
                             this->m_pPlayer,
                             CURRENCY_TYPE::CURRENCY_GOLD,
                             nCostGold,
                             CURRENCY_CHANGE_REASON::MCR_EQUIP_UPPOS,
                             0) )
                {
                  v2 = 10002;
                  v22 = 0;
                }
                else
                {
                  v22 = 1;
                }
LABEL_51:
                std::list<ItemData>::~list(&costItemList);
                if ( !v22 )
                  goto LABEL_81;
              }
              else
              {
                p_m_nConstItem = &pCfgEquipUpPos->m_nConstItem;
                v30 = Player::GetBag(this->m_pPlayer);
                if ( !CExtCharBag::RemoveItem(v30, p_m_nConstItem, ITEM_CHANGE_REASON::ICR_UP_EQUIP_POS) )
                {
                  v2 = 10002;
                  goto LABEL_81;
                }
              }
              if ( pCfgEquipUpPos->m_nCostMoney > 0
                && (m_nCostMoney = pCfgEquipUpPos->m_nCostMoney,
                    v32 = Player::GetCurrency(this->m_pPlayer),
                    !CExtCurrency::DecMoneyAndNoBind(v32, m_nCostMoney, CURRENCY_CHANGE_REASON::MCR_EQUIP_UPPOS, 0)) )
              {
                v2 = 10002;
              }
              else
              {
                v33 = !ItemData::IsEmpty(&pCfgEquipUpPos->m_BaoHuConst) && BaoHu == 1;
                if ( !v33
                  || (p_m_BaoHuConst = &pCfgEquipUpPos->m_BaoHuConst,
                      v35 = Player::GetBag(this->m_pPlayer),
                      CExtCharBag::RemoveItem(v35, p_m_BaoHuConst, ITEM_CHANGE_REASON::ICR_UP_EQUIP_POS)) )
                {
                  v36 = Answer::Singleton<Answer::Random>::instance();
                  v37 = Answer::Random::generate(v36, 1, 10000);
                  if ( v37 <= pCfgEquipUpPos->m_nRate )
                  {
                    this->m_vMemPosLevel[nPos] = nLevel + 1;
                    Player::recalcAttr(this->m_pPlayer, 0, 0);
                    v45 = nPos;
                    Proc = Answer::NetPacket::getProc(inPacket);
                    GateIndex = Player::getGateIndex(this->m_pPlayer);
                    ConnId = Player::getConnId(this->m_pPlayer);
                    v49 = Answer::Singleton<GameService>::instance();
                    GameService::replySuccess(v49, ConnId, GateIndex, Proc, v45);
                    if ( pCfgEquipUpPos->m_GongGaoId > 0 )
                    {
                      v50 = Answer::Singleton<GameService>::instance();
                      packet = GameService::popNetpacket(v50, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
                      if ( !packet )
                      {
                        v2 = 10002;
                        goto LABEL_81;
                      }
                      Answer::NetPacket::writeInt32(packet, pCfgEquipUpPos->m_GongGaoId);
                      Cid = Player::getCid(this->m_pPlayer);
                      Answer::NetPacket::writeInt64(packet, Cid);
                      Player::getName((const Player *const)&val);
                      Answer::NetPacket::writeUTF8(packet, &val);
                      std::string::~string(&val);
                      Answer::NetPacket::writeInt8(packet, nPos);
                      Answer::NetPacket::writeInt32(packet, this->m_vMemPosLevel[nPos]);
                      WOffset = Answer::NetPacket::getWOffset(packet);
                      Answer::NetPacket::setSize(packet, WOffset);
                      v53 = Answer::Singleton<GameService>::instance();
                      GameService::worldBroadcast(v53, 0, packet);
                    }
                  }
                  else
                  {
                    if ( !ItemData::IsEmpty(&pCfgEquipUpPos->m_BaoHuConst) && BaoHu == 1 )
                      this->m_vMemPosLevel[nPos] = nLevel;
                    else
                      this->m_vMemPosLevel[nPos] = nLevel - 1;
                    if ( this->m_vMemPosLevel[nPos] < 0 )
                      this->m_vMemPosLevel[nPos] = 0;
                    Player::recalcAttr(this->m_pPlayer, 0, 0);
                    v39 = this->m_vMemPosLevel[nPos];
                    v40 = nPos;
                    v41 = Answer::NetPacket::getProc(inPacket);
                    v42 = Player::getGateIndex(this->m_pPlayer);
                    v43 = Player::getConnId(this->m_pPlayer);
                    v44 = Answer::Singleton<GameService>::instance();
                    GameService::replyfailure(v44, v43, v42, v41, v40, v39);
                  }
                  Task = Player::GetTask(this->m_pPlayer);
                  ChrTask::updateTaskCount(Task, 24, 0);
                  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
                  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 10, 0, 0);
                  m_pPlayer = this->m_pPlayer;
                  v57 = Answer::Singleton<CKaiFuHuoDong>::instance();
                  CKaiFuHuoDong::SendKaiFuHuoDongIcon(v57, m_pPlayer);
                  LODWORD(m_pPlayer) = CExtEquip::GetEquipAllUpPosLevel(this);
                  CSevenDayTask = Player::GetCSevenDayTask(this->m_pPlayer);
                  CSevenDayTask::UpdateTaskState(CSevenDayTask, 6, (int32_t)m_pPlayer, 1);
                  v2 = 0;
                  goto LABEL_81;
                }
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
    }
    else
    {
      v2 = 10002;
    }
LABEL_81:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtEquip::onShenYaoPosLevelUp(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v6; // r12d
  int32_t v7; // ebx
  CfgData *v8; // rax
  const CfgEquipTable *v9; // rax
  ItemDataList *p_nCost; // rbx
  CExtCharBag *Bag; // rax
  int8_t ConnId; // bl
  GameService *v13; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v16; // bl
  GameService *v17; // rax
  CExtCharBag *v18; // rax
  int64_t v19; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v22; // bl
  GameService *v23; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-70h] BYREF
  std::string val; // [rsp+30h] [rbp-50h] BYREF
  int8_t nPos; // [rsp+43h] [rbp-3Dh]
  int32_t nLevel; // [rsp+44h] [rbp-3Ch]
  const ShenYaoPos *pCfgEquipUpPos; // [rsp+48h] [rbp-38h]
  const ShenYaoPos *pCfgEquipNextUpPos; // [rsp+50h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nPos = Answer::NetPacket::readInt8(inPacket);
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  if ( nPos > 10 && nPos <= 20 )
  {
    nLevel = this->m_vMemPosLevel[nPos + 9];
    v3 = nPos;
    v4 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v4);
    pCfgEquipUpPos = CfgEquipTable::GetShenYaoPosCfg(EquipTable, v3, nLevel);
    v6 = nLevel + 1;
    v7 = nPos;
    v8 = Answer::Singleton<CfgData>::instance();
    v9 = CfgData::GetEquipTable(v8);
    pCfgEquipNextUpPos = CfgEquipTable::GetShenYaoPosCfg(v9, v7, v6);
    if ( pCfgEquipUpPos && pCfgEquipNextUpPos )
    {
      if ( std::list<ItemData>::empty(&pCfgEquipUpPos->nCost) )
      {
        v2 = 10002;
      }
      else
      {
        p_nCost = &pCfgEquipUpPos->nCost;
        Bag = Player::GetBag(this->m_pPlayer);
        if ( !CExtCharBag::RemoveItem(Bag, p_nCost, ITEM_CHANGE_REASON::IDCR_SHEN_YAO_POS_LEVEL_UP) )
        {
          v2 = 10002;
        }
        else
        {
          this->m_vMemPosLevel[nPos + 9] = nLevel + 1;
          Player::RecalcAttr(this->m_pPlayer);
          if ( pCfgEquipNextUpPos->nGongGaoId > 0 )
          {
            ConnId = Player::getConnId(this->m_pPlayer);
            v13 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v13, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( packet )
            {
              Answer::NetPacket::writeInt32(packet, pCfgEquipNextUpPos->nGongGaoId);
              Cid = Player::getCid(this->m_pPlayer);
              Answer::NetPacket::writeInt64(packet, Cid);
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              Answer::NetPacket::writeInt32(packet, nPos);
              Answer::NetPacket::writeInt32(packet, nLevel + 1);
              WOffset = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, WOffset);
              v16 = Player::getConnId(this->m_pPlayer);
              v17 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v17, v16, packet);
            }
          }
          v18 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::ForceSendDirty(v18);
          v19 = nPos;
          Proc = Answer::NetPacket::getProc(inPacket);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          v22 = Player::getConnId(this->m_pPlayer);
          v23 = Answer::Singleton<GameService>::instance();
          GameService::replySuccess(v23, v22, GateIndex, Proc, v19);
          v2 = 0;
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
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtEquip::onGemOpenHole(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v4; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  CExtCurrency *Currency; // rax
  CExtCharBag *Bag; // rax
  int64_t m_nCostMoney; // rbx
  CExtCurrency *v11; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v15; // rax
  int8_t nPos; // [rsp+1Eh] [rbp-32h]
  char nSlot; // [rsp+1Fh] [rbp-31h]
  int OpenLevel; // [rsp+20h] [rbp-30h]
  const CfgGemOpenHole *pCfgGemOpenHole; // [rsp+28h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nPos = Answer::NetPacket::readInt8(inPacket);
  nSlot = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)nPos > 9u || (unsigned __int8)nSlot >= 4u )
    return 10002;
  OpenLevel = CExtEquip::GetGemOpenLevel(this, nPos);
  if ( OpenLevel <= 0
    || (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < OpenLevel )
  {
    return 10002;
  }
  if ( this->m_vMemGem[nPos][nSlot] >= 0 )
    return 10002;
  if ( nSlot > 0 && *((int *)&this->m_vMemEquip[92].srcId + 4 * nPos + nSlot + 1) < 0 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  ItemGemTable = CfgData::GetItemGemTable(v4);
  pCfgGemOpenHole = CfgItemGemTable::GetGemOpenHole(ItemGemTable, nSlot);
  if ( !pCfgGemOpenHole )
    return 10002;
  if ( pCfgGemOpenHole->m_nCostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < pCfgGemOpenHole->m_nCostMoney )
      return 10002;
  }
  if ( !std::list<ItemData>::empty(&pCfgGemOpenHole->m_lCostItem) )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, &pCfgGemOpenHole->m_lCostItem, ITEM_CHANGE_REASON::ICR_GEM_OPEN_HOLE) )
      return 10002;
  }
  if ( pCfgGemOpenHole->m_nCostMoney > 0 )
  {
    m_nCostMoney = pCfgGemOpenHole->m_nCostMoney;
    v11 = Player::GetCurrency(this->m_pPlayer);
    CExtCurrency::DecMoneyAndNoBind(v11, m_nCostMoney, CURRENCY_CHANGE_REASON::MCR_GEM_OPEN_HOLE, 0);
  }
  this->m_vMemGem[nPos][nSlot] = 0;
  CExtEquip::SendGemInfo(this, nPos, nSlot);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v15 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v15, ConnId, GateIndex, Proc, nPos);
  return 0;
}


#####################################
int32_t __cdecl CExtEquip::GetGemOpenLevel(CExtEquip *const this, int32_t EquipSlot)
{
  int32_t result; // eax

  switch ( EquipSlot )
  {
    case 0:
      result = 300;
      break;
    case 1:
      result = 320;
      break;
    case 2:
      result = 310;
      break;
    case 3:
      result = 340;
      break;
    case 4:
      result = 410;
      break;
    case 5:
      result = 430;
      break;
    case 6:
      result = 330;
      break;
    case 7:
      result = 370;
      break;
    case 8:
      result = 350;
      break;
    case 9:
      result = 390;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtEquip::GetMoFuSuitLevel(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int v3; // ebx
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t m_nGrade; // eax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  int32_t SuitId; // [rsp+48h] [rbp-28h]
  int8_t i; // [rsp+4Fh] [rbp-21h]
  const MemChrBag *curEquip; // [rsp+50h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+58h] [rbp-18h]

  SuitId = 0;
  for ( i = 50; i <= 58; ++i )
  {
    curEquip = &this->m_vMemEquip[i];
    if ( curEquip->srcId <= 0 || curEquip->itemClass != 2 )
      return 0;
    srcId = curEquip->srcId;
    v2 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v2, srcId);
    if ( equip.base == curEquip->itemId )
    {
      itemId = this->m_vMemEquip[i].itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( SuitId )
        {
          if ( pCfgEquip->m_nGrade >= SuitId )
            m_nGrade = SuitId;
          else
            m_nGrade = pCfgEquip->m_nGrade;
          SuitId = m_nGrade;
        }
        else
        {
          SuitId = pCfgEquip->m_nGrade;
        }
        v3 = 1;
      }
      else
      {
        SuitId = 0;
        v3 = 0;
      }
    }
    else
    {
      SuitId = 0;
      v3 = 0;
    }
    MemEquip::~MemEquip(&equip);
    if ( !v3 )
      return SuitId;
  }
  return SuitId;
}


#####################################
int32_t __cdecl CExtEquip::onGemAdd(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CfgData *v4; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  CfgData *v6; // rax
  const CfgItemGemTable *v7; // rax
  CExtCharBag *v8; // rax
  CExtCharBag *v9; // rax
  int64_t v10; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  MemChrBag addGem; // [rsp+10h] [rbp-90h] BYREF
  MemChrBag bagItem; // [rsp+30h] [rbp-70h] BYREF
  int8_t nPos; // [rsp+5Ah] [rbp-46h]
  int8_t nSlot; // [rsp+5Bh] [rbp-45h]
  int32_t nBagSlot; // [rsp+5Ch] [rbp-44h]
  int32_t nId; // [rsp+60h] [rbp-40h]
  int32_t nGemId; // [rsp+64h] [rbp-3Ch]
  const CfgItemGem *pCfgGem; // [rsp+68h] [rbp-38h]
  int32_t i; // [rsp+70h] [rbp-30h]
  int32_t GemId; // [rsp+74h] [rbp-2Ch]
  const CfgItemGem *pCfgCheckGem; // [rsp+78h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nPos = Answer::NetPacket::readInt8(inPacket);
  nSlot = Answer::NetPacket::readInt8(inPacket);
  nBagSlot = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned __int8)nPos > 9u || (unsigned __int8)nSlot >= 4u )
    return 10002;
  nId = this->m_vMemGem[nPos][nSlot];
  if ( nId < 0 )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  bagItem = *CExtCharBag::GetSlotData(Bag, nBagSlot);
  if ( bagItem.itemClass != 3 )
    return 10002;
  nGemId = bagItem.itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  ItemGemTable = CfgData::GetItemGemTable(v4);
  pCfgGem = CfgItemGemTable::GetItemGem(ItemGemTable, bagItem.itemId);
  if ( !pCfgGem )
    return 10002;
  if ( !CfgItemGem::CheckPos(pCfgGem, nPos) )
    return 10002;
  for ( i = 0; i <= 3; ++i )
  {
    GemId = this->m_vMemGem[nPos][i];
    if ( GemId > 0 )
    {
      v6 = Answer::Singleton<CfgData>::instance();
      v7 = CfgData::GetItemGemTable(v6);
      pCfgCheckGem = CfgItemGemTable::GetItemGem(v7, GemId);
      if ( pCfgCheckGem )
      {
        if ( pCfgCheckGem->m_nType == pCfgGem->m_nType )
          return 10002;
      }
    }
  }
  if ( nId > 0 )
  {
    *(_DWORD *)&addGem.itemClass = 3;
    *(_QWORD *)&addGem.itemCount = 0x100000001LL;
    *(_QWORD *)&addGem.endTime = 0;
    addGem.srcId = 0;
    addGem.itemId = nId;
    v8 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(v8, &addGem, ITEM_CHANGE_REASON::ICR_GEM_TO_BAG) )
      return 10002;
  }
  --bagItem.itemCount;
  v9 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(v9, nBagSlot, &bagItem, ITEM_CHANGE_REASON::ICR_ADD_GEM, 0);
  this->m_vMemGem[nPos][nSlot] = nGemId;
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  CExtEquip::updateEquipGem(this);
  CExtEquip::SendGemInfo(this, nPos, nSlot);
  v10 = nPos;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v14, ConnId, GateIndex, Proc, v10);
  return 0;
}


#####################################
int32_t __cdecl CExtEquip::onGemRemove(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  int64_t v4; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  MemChrBag addGem; // [rsp+10h] [rbp-50h] BYREF
  int8_t nPos; // [rsp+3Ah] [rbp-26h]
  int8_t nSlot; // [rsp+3Bh] [rbp-25h]
  int32_t nId; // [rsp+3Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nPos = Answer::NetPacket::readInt8(inPacket);
  nSlot = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)nPos > 9u || (unsigned __int8)nSlot >= 4u )
    return 10002;
  nId = this->m_vMemGem[nPos][nSlot];
  if ( nId <= 0 )
    return 10002;
  *(_DWORD *)&addGem.itemClass = 3;
  *(_QWORD *)&addGem.itemCount = 0x100000001LL;
  *(_QWORD *)&addGem.endTime = 0;
  addGem.srcId = 0;
  addGem.itemId = nId;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addGem, ITEM_CHANGE_REASON::ICR_GEM_TO_BAG) )
    return 10002;
  this->m_vMemGem[nPos][nSlot] = 0;
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  CExtEquip::SendGemInfo(this, nPos, nSlot);
  v4 = nPos;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, v4);
  return 0;
}


#####################################
int32_t __cdecl CExtEquip::onGemLevelUp(CExtEquip *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  CExtCurrency *v5; // rax
  int64_t MoneyBindAndNoBind; // rax
  ItemData *v8; // rbx
  CExtCharBag *Bag; // rax
  ItemData *v10; // rbx
  CExtCharBag *v11; // rax
  ItemData *v12; // rax
  ItemData *v13; // rax
  int32_t m_nId; // r12d
  int8_t m_nClass; // bl
  CfgData *v16; // rax
  CExtCharBag *v17; // rax
  int64_t nCostMoney; // rbx
  CExtCurrency *Currency; // rax
  int32_t nNextId; // r13d
  CharId_t Cid; // r12
  int64_t v23; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v27; // rax
  ItemData stu_0; // [rsp+10h] [rbp-F0h] BYREF
  ItemData stu; // [rsp+20h] [rbp-E0h] BYREF
  ItemDataList SubItem; // [rsp+30h] [rbp-D0h] BYREF
  std::_List_iterator<ItemData> it; // [rsp+40h] [rbp-C0h] BYREF
  ItemDataList NeedItemList; // [rsp+50h] [rbp-B0h] BYREF
  Int32Vector vSlot; // [rsp+60h] [rbp-A0h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+80h] [rbp-80h] BYREF
  std::string strName; // [rsp+90h] [rbp-70h] BYREF
  int32_t nEquipPos; // [rsp+A4h] [rbp-5Ch]
  int8_t nGemSlot; // [rsp+AAh] [rbp-56h]
  int8_t bAutoBuy; // [rsp+ABh] [rbp-55h]
  int32_t nGemId; // [rsp+ACh] [rbp-54h]
  const CfgGemLevelUp *pCfgGemLevelUp; // [rsp+B0h] [rbp-50h]
  int32_t NeedGold; // [rsp+BCh] [rbp-44h]
  int64_t HaveGold; // [rsp+C0h] [rbp-40h]
  int32_t HaveBindCount; // [rsp+CCh] [rbp-34h]
  int32_t HaveUnBindCount; // [rsp+D0h] [rbp-30h]
  int32_t DiffCount; // [rsp+D4h] [rbp-2Ch]
  CfgGameShop *pShop; // [rsp+D8h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nEquipPos = Answer::NetPacket::readInt32(inPacket);
  nGemSlot = Answer::NetPacket::readInt8(inPacket);
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  bAutoBuy = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)nGemSlot < 4u )
  {
    if ( (unsigned int)nEquipPos < 0xA )
    {
      nGemId = this->m_vMemGem[nEquipPos][nGemSlot];
      if ( nGemId > 0 )
      {
        v3 = Answer::Singleton<CfgData>::instance();
        ItemGemTable = CfgData::GetItemGemTable(v3);
        pCfgGemLevelUp = CfgItemGemTable::GetGemLevelUp(ItemGemTable, nGemId);
        if ( pCfgGemLevelUp )
        {
          if ( pCfgGemLevelUp->nCostMoney > 0
            && (v5 = Player::GetCurrency(this->m_pPlayer),
                MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v5),
                MoneyBindAndNoBind < pCfgGemLevelUp->nCostMoney) )
          {
            v2 = 2;
          }
          else
          {
            std::list<ItemData>::list(&NeedItemList, &pCfgGemLevelUp->lCostItems);
            it._M_node = std::list<ItemData>::begin(&NeedItemList)._M_node;
            NeedGold = 0;
            std::list<ItemData>::list(&SubItem);
            while ( 1 )
            {
              __x._M_node = std::list<ItemData>::end(&NeedItemList)._M_node;
              if ( !std::_List_iterator<ItemData>::operator!=(&it, &__x) )
                break;
              v8 = std::_List_iterator<ItemData>::operator*(&it);
              Bag = Player::GetBag(this->m_pPlayer);
              HaveBindCount = CExtCharBag::HaveItemCount(Bag, v8, 1, 0);
              v10 = std::_List_iterator<ItemData>::operator*(&it);
              v11 = Player::GetBag(this->m_pPlayer);
              HaveUnBindCount = CExtCharBag::HaveItemCount(v11, v10, 0, 0);
              v12 = std::_List_iterator<ItemData>::operator*(&it);
              if ( v12->m_nCount <= HaveBindCount + HaveUnBindCount )
              {
                stu_0 = *std::_List_iterator<ItemData>::operator*(&it);
                std::list<ItemData>::push_back(&SubItem, &stu_0);
              }
              else
              {
                if ( bAutoBuy != 1 )
                {
                  v2 = 2;
                  goto LABEL_46;
                }
                v13 = std::_List_iterator<ItemData>::operator*(&it);
                DiffCount = v13->m_nCount - (HaveBindCount + HaveUnBindCount);
                m_nId = std::_List_iterator<ItemData>::operator*(&it)->m_nId;
                m_nClass = std::_List_iterator<ItemData>::operator*(&it)->m_nClass;
                v16 = Answer::Singleton<CfgData>::instance();
                pShop = CfgData::GetGameShopItem(v16, m_nClass, m_nId);
                if ( !pShop )
                {
                  v2 = 2;
                  goto LABEL_46;
                }
                NeedGold += DiffCount * pShop->Price;
                *(_QWORD *)&stu.m_nId = *(_QWORD *)&std::_List_iterator<ItemData>::operator*(&it)->m_nId;
                stu.m_nCount = HaveBindCount + HaveUnBindCount;
                if ( HaveBindCount + HaveUnBindCount > 0 )
                  std::list<ItemData>::push_back(&SubItem, &stu);
              }
              std::_List_iterator<ItemData>::operator++(&it);
            }
            HaveGold = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
            if ( NeedGold <= HaveGold )
            {
              if ( !std::list<ItemData>::empty(&SubItem)
                && (v17 = Player::GetBag(this->m_pPlayer),
                    !CExtCharBag::RemoveItem(v17, &vSlot, &SubItem, ITEM_CHANGE_REASON::IDCR_GEM_LEVEL_UP)) )
              {
                v2 = 2;
              }
              else if ( NeedGold > 0
                     && !Player::DecCurrency(
                           this->m_pPlayer,
                           CURRENCY_TYPE::CURRENCY_GOLD,
                           NeedGold,
                           CURRENCY_CHANGE_REASON::GCR_GEM_LEVEL_UP_AUTO_BUY,
                           nGemId) )
              {
                v2 = 2;
              }
              else if ( pCfgGemLevelUp->nCostMoney > 0
                     && (nCostMoney = pCfgGemLevelUp->nCostMoney,
                         Currency = Player::GetCurrency(this->m_pPlayer),
                         !CExtCurrency::DecMoneyAndNoBind(
                            Currency,
                            nCostMoney,
                            CURRENCY_CHANGE_REASON::GCR_GEM_LEVEL_UP,
                            0)) )
              {
                v2 = 2;
              }
              else
              {
                if ( pCfgGemLevelUp->nBroadId > 0 )
                {
                  nNextId = pCfgGemLevelUp->nNextId;
                  Cid = Player::getCid(this->m_pPlayer);
                  Player::getName((const Player *const)&strName);
                  CExtEquip::broadcastGemLevelUp(this, pCfgGemLevelUp->nBroadId, &strName, Cid, nNextId);
                  std::string::~string(&strName);
                }
                this->m_vMemGem[nEquipPos][nGemSlot] = pCfgGemLevelUp->nNextId;
                Player::recalcAttr(this->m_pPlayer, 0, 0);
                CExtEquip::updateEquipGem(this);
                CExtEquip::SendGemInfo(this, nEquipPos, nGemSlot);
                v23 = pCfgGemLevelUp->nNextId;
                Proc = Answer::NetPacket::getProc(inPacket);
                GateIndex = Player::getGateIndex(this->m_pPlayer);
                ConnId = Player::getConnId(this->m_pPlayer);
                v27 = Answer::Singleton<GameService>::instance();
                GameService::replySuccess(v27, ConnId, GateIndex, Proc, v23);
                v2 = 0;
              }
            }
            else
            {
              v2 = 2;
            }
LABEL_46:
            std::list<ItemData>::~list(&SubItem);
            std::list<ItemData>::~list(&NeedItemList);
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
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
void __cdecl CExtEquip::broadcastGemLevelUp(
        CExtEquip *const this,
        int32_t nBroadId,
        const std::string *const strName,
        CharId_t nCharId,
        int32_t nGemId)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nBroadId);
    Answer::NetPacket::writeInt64(packet, nCharId);
    Answer::NetPacket::writeUTF8(packet, strName);
    Answer::NetPacket::writeInt32(packet, nGemId);
    Answer::NetPacket::writeInt8(packet, 3);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, v8, packet);
  }
}


#####################################
int8_t __cdecl CExtEquip::GetEquipStar(const CExtEquip *const this, int8_t nSlot)
{
  int8_t star; // bl
  EquipId_t srcId; // rbx
  CEquipManager *v4; // rax
  MemEquip Equip; // [rsp+10h] [rbp-50h] BYREF

  if ( this->m_vMemEquip[nSlot].itemId <= 0 || this->m_vMemEquip[nSlot].srcId <= 0 )
    return 0;
  srcId = this->m_vMemEquip[nSlot].srcId;
  v4 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::GetMemEquip(&Equip, v4, srcId);
  if ( Equip.base == this->m_vMemEquip[nSlot].itemId )
    star = Equip.star;
  else
    star = 0;
  MemEquip::~MemEquip(&Equip);
  return star;
}


#####################################
void __cdecl CExtEquip::PackageEquipInfo(const CExtEquip *const this, Answer::NetPacket *packet)
{
  EquipId_t srcId; // rbx
  CEquipManager *v3; // rax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  int32_t nEquipCount; // [rsp+48h] [rbp-28h]
  uint32_t nOldOffset; // [rsp+4Ch] [rbp-24h]
  uint32_t nNewOffset; // [rsp+50h] [rbp-20h]
  int32_t i; // [rsp+54h] [rbp-1Ch]
  const MemChrBag *curEquip; // [rsp+58h] [rbp-18h]

  if ( packet && this->m_pPlayer )
  {
    nEquipCount = 0;
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    for ( i = 0; i <= 92; ++i )
    {
      curEquip = &this->m_vMemEquip[i];
      if ( curEquip->srcId > 0 && curEquip->itemClass == 2 )
      {
        srcId = curEquip->srcId;
        v3 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::GetMemEquip(&equip, v3, srcId);
        if ( equip.base == curEquip->itemId )
        {
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt8(packet, curEquip->bind);
          Answer::NetPacket::writeInt64(packet, equip.id);
          Answer::NetPacket::writeInt32(packet, equip.base);
          Answer::NetPacket::writeInt8(packet, equip.star);
          Answer::NetPacket::writeInt32(packet, equip.MapId);
          Answer::NetPacket::writeInt32(packet, equip.Mid);
          Answer::NetPacket::writeInt32(packet, equip.time);
          Answer::NetPacket::writeUTF8(packet, &equip.name);
          Answer::NetPacket::writeInt32(packet, equip.Lucky);
          ++nEquipCount;
        }
        MemEquip::~MemEquip(&equip);
      }
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt8(packet, nEquipCount);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
void __cdecl CExtEquip::PackageGemInfo(const CExtEquip *const this, Answer::NetPacket *packet)
{
  int8_t gemCount; // [rsp+10h] [rbp-10h]
  int32_t oldBengin; // [rsp+14h] [rbp-Ch]
  int oldwoffset; // [rsp+18h] [rbp-8h]
  char i; // [rsp+1Eh] [rbp-2h]
  char j; // [rsp+1Fh] [rbp-1h]

  if ( packet && this->m_pPlayer )
  {
    gemCount = 0;
    oldBengin = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt8(packet, 0);
    for ( i = 0; i <= 9; ++i )
    {
      for ( j = 0; j <= 3; ++j )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt8(packet, j);
        Answer::NetPacket::writeInt32(packet, this->m_vMemGem[i][j]);
        ++gemCount;
      }
    }
    oldwoffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, oldBengin);
    Answer::NetPacket::writeInt8(packet, gemCount);
    Answer::NetPacket::setWOffset(packet, oldwoffset);
  }
}


#####################################
void __cdecl CExtEquip::SendEquipInfo(CExtEquip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-30h]
  int8_t equipCount; // [rsp+18h] [rbp-28h]
  int32_t oldBengin; // [rsp+1Ch] [rbp-24h]
  int oldwoffset; // [rsp+20h] [rbp-20h]
  char i; // [rsp+27h] [rbp-19h]
  const MemChrBag *tSlot; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DBEu);
    if ( packet )
    {
      equipCount = 0;
      oldBengin = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt8(packet, 0);
      for ( i = 0; i <= 92; ++i )
      {
        tSlot = &this->m_vMemEquip[i];
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, tSlot->itemId);
        Answer::NetPacket::writeInt8(packet, tSlot->bind);
        Answer::NetPacket::writeInt32(packet, tSlot->endTime);
        Answer::NetPacket::writeInt64(packet, tSlot->srcId);
        ++equipCount;
      }
      oldwoffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldBengin);
      Answer::NetPacket::writeInt8(packet, equipCount);
      Answer::NetPacket::setWOffset(packet, oldwoffset);
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
void __cdecl CExtEquip::PackageShenYaoPosLevelUp(const CExtEquip *const this, Answer::NetPacket *packet)
{
  int8_t i; // [rsp+1Fh] [rbp-1h]

  if ( packet && this->m_pPlayer )
  {
    Answer::NetPacket::writeInt32(packet, 10);
    for ( i = 0; i <= 9; ++i )
      Answer::NetPacket::writeInt32(packet, this->m_vShenYaoEquipPos[i]);
  }
}


#####################################
void __cdecl CExtEquip::SendShenYaoPosLevelInfo(CExtEquip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DC3u);
  if ( packet )
  {
    CExtEquip::PackageShenYaoPosLevelUp(this, packet);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v5 = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v6, v5, GateIndex, packet);
  }
}


#####################################
void __cdecl CExtEquip::SendGemInfo(CExtEquip *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DBFu);
    if ( packet )
    {
      CExtEquip::PackageGemInfo(this, packet);
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
void __cdecl CExtEquip::SendPosLevelInfo(CExtEquip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  char i; // [rsp+1Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DC1u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 10);
      for ( i = 0; i <= 9; ++i )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_vMemPosLevel[i]);
      }
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
int32_t __cdecl CExtEquip::GetPosLevel(CExtEquip *const this, int8_t Pos)
{
  if ( (unsigned __int8)Pos < 0xAu )
    return this->m_vMemPosLevel[Pos];
  else
    return 0;
}


#####################################
int32_t __cdecl CExtEquip::getStrenGthenLevel(CExtEquip *const this, int8_t Pos)
{
  if ( (unsigned __int8)Pos < 0xAu )
    return this->m_vMemStrengthen[Pos];
  else
    return 0;
}


#####################################
bool __cdecl CExtEquip::IsAllPosTop(CExtEquip *const this)
{
  int32_t v1; // r12d
  CfgData *v2; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t nPos; // [rsp+10h] [rbp-20h]

  for ( nPos = 0; nPos <= 9; ++nPos )
  {
    v1 = this->m_vMemPosLevel[nPos] + 1;
    v2 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v2);
    if ( CfgEquipTable::GetEquipUpPos(EquipTable, nPos, v1) )
      return 0;
  }
  return 1;
}


#####################################
int32_t __cdecl CExtEquip::IsAllPosLevel(CExtEquip *const this)
{
  int32_t Level; // [rsp+10h] [rbp-8h]
  int32_t nPos; // [rsp+14h] [rbp-4h]

  Level = 0;
  for ( nPos = 0; nPos <= 9; ++nPos )
  {
    if ( this->m_vMemPosLevel[nPos] > 0 )
      Level += this->m_vMemPosLevel[nPos];
  }
  return Level;
}


#####################################
void __cdecl CExtEquip::SendGemInfo(CExtEquip *const this, int8_t nPos, int8_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && (unsigned __int8)nPos <= 9u && (unsigned __int8)nSlot < 4u )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DBFu);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 1);
      Answer::NetPacket::writeInt8(packet, nPos);
      Answer::NetPacket::writeInt8(packet, nSlot);
      Answer::NetPacket::writeInt32(packet, this->m_vMemGem[nPos][nSlot]);
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
void __cdecl CExtEquip::AddCharAttr(CExtEquip *const this)
{
  CExtEquip::addEquipAttr(this);
  CExtEquip::addGemAttr(this);
  CExtEquip::addSuitAttr(this);
  CExtEquip::addPosLevelAttr(this);
  CExtEquip::AddStrengthenAttr(this);
  CExtEquip::addShenYaoPosAttr(this);
}


#####################################
void __cdecl CExtEquip::addEquipAttr(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  ItemId_t base; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  CGoblin *CGoblin; // rax
  int32_t v7; // ebx
  CGoblin *v8; // rax
  int32_t v9; // ebx
  CGoblin *v10; // rax
  const AttrAddon *v11; // rax
  int32_t v12; // ebx
  const AttrAddon *v13; // rax
  const AttrAddon *v14; // rax
  const AttrAddon *v15; // rax
  int32_t star; // r12d
  int8_t m_nType; // bl
  CfgData *v18; // rax
  const CfgEquipTable *v19; // rax
  bool v20; // al
  const AttrAddon *v21; // rax
  int32_t v22; // ebx
  const AttrAddon *v23; // rax
  int32_t addon; // ebx
  const AttrAddon *v25; // rax
  int32_t v26; // ebx
  CfgData *v27; // rax
  const CfgEquipTable *v28; // rax
  const AttrAddon *v29; // rax
  int32_t v30; // ebx
  const AttrAddon *v31; // rax
  int32_t CRongHe; // eax
  int32_t v33; // ebx
  AttrAddon *v34; // rax
  MemEquip equip; // [rsp+10h] [rbp-170h] BYREF
  std::_List_iterator<AttrAddon> it; // [rsp+50h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_3; // [rsp+60h] [rbp-120h] BYREF
  AttrAddonList lAttr; // [rsp+70h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_2; // [rsp+80h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_1; // [rsp+90h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_0; // [rsp+A0h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+B0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+C0h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v44; // [rsp+D0h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v45; // [rsp+E0h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v46; // [rsp+F0h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v47; // [rsp+100h] [rbp-80h] BYREF
  std::_List_iterator<AttrAddon> __x; // [rsp+110h] [rbp-70h] BYREF
  int8_t i; // [rsp+127h] [rbp-59h]
  MemChrBag *curEquip; // [rsp+128h] [rbp-58h]
  const CfgEquip *pCfgEquip; // [rsp+130h] [rbp-50h]
  float AttrRate; // [rsp+138h] [rbp-48h]
  int32_t nType; // [rsp+13Ch] [rbp-44h]
  int32_t nRate; // [rsp+140h] [rbp-40h]
  int32_t nRate_0; // [rsp+144h] [rbp-3Ch]
  int32_t nRate_1; // [rsp+148h] [rbp-38h]
  int32_t nAddon; // [rsp+14Ch] [rbp-34h]
  const CfgEquipUpStar *pCfgStar; // [rsp+150h] [rbp-30h]
  float AttrRate_0; // [rsp+158h] [rbp-28h]
  int32_t StrenGthenLevel; // [rsp+15Ch] [rbp-24h]
  const EquipStrengthenCfg *pStrengthen; // [rsp+160h] [rbp-20h]
  float AttrRate_1; // [rsp+16Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 92; ++i )
    {
      curEquip = &this->m_vMemEquip[i];
      if ( curEquip->srcId > 0 && curEquip->itemClass == 2 )
      {
        srcId = curEquip->srcId;
        v2 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::GetMemEquip(&equip, v2, srcId);
        if ( equip.base == curEquip->itemId )
        {
          base = equip.base;
          v4 = Answer::Singleton<CfgData>::instance();
          EquipTable = CfgData::GetEquipTable(v4);
          pCfgEquip = CfgEquipTable::GetEquip(EquipTable, base);
          if ( pCfgEquip )
          {
            for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->m_vAttrAddon)._M_current;
                  ;
                  __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
            {
              __rhs._M_current = std::vector<AttrAddon>::end(&pCfgEquip->m_vAttrAddon)._M_current;
              if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
                break;
              AttrRate = 1.0;
              if ( i > 32 && i <= 38 )
              {
                nType = CExtEquip::GetEquipType(this, i);
                if ( nType != -1 )
                {
                  CGoblin = Player::GetCGoblin(this->m_pPlayer);
                  nRate = CGoblin::GetAddAttrRate(CGoblin, nType);
                  if ( nRate )
                    AttrRate = (float)((float)nRate / 1000.0) + AttrRate;
                }
              }
              if ( i > 49 && i <= 58 )
              {
                v7 = i;
                v8 = Player::GetCGoblin(this->m_pPlayer);
                nRate_0 = CGoblin::GetMoFuChrAttr(v8, v7);
                if ( nRate_0 )
                  AttrRate = (float)((float)nRate_0 / 1000.0) + AttrRate;
              }
              if ( i > 43 && i <= 49 )
              {
                v9 = i;
                v10 = Player::GetCGoblin(this->m_pPlayer);
                nRate_1 = CGoblin::GetWingEquipRefiningAttr(v10, v9);
                if ( nRate_1 )
                  AttrRate = (float)((float)nRate_1 / 1000.0) + AttrRate;
              }
              if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
              {
                v11 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
                v12 = (int)(float)((float)v11->addon * AttrRate);
                v13 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
                Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v13->index, v12);
                if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index == 45 )
                {
                  v14 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
                  Player::AddBeiGongAttr(this->m_pPlayer, 2, v14->addon);
                }
              }
            }
            for ( iter_0._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->m_vElement)._M_current;
                  ;
                  __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_0) )
            {
              v44._M_current = std::vector<AttrAddon>::end(&pCfgEquip->m_vElement)._M_current;
              if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_0, &v44) )
                break;
              if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon > 0 )
              {
                nAddon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon;
                v15 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0);
                Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v15->index, nAddon);
              }
            }
            if ( equip.star > 0 )
            {
              star = equip.star;
              m_nType = pCfgEquip->m_nType;
              v18 = Answer::Singleton<CfgData>::instance();
              v19 = CfgData::GetEquipTable(v18);
              pCfgStar = CfgEquipTable::GetEquipUpStar(v19, m_nType, star);
              if ( pCfgStar )
              {
                if ( (unsigned __int8)i > 9u )
                {
                  for ( iter_2._M_current = std::vector<AttrAddon>::begin(&pCfgStar->m_vAttrAddon)._M_current;
                        ;
                        __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_2) )
                  {
                    v46._M_current = std::vector<AttrAddon>::end(&pCfgStar->m_vAttrAddon)._M_current;
                    if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_2, &v46) )
                      break;
                    if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_2)->addon > 0 )
                    {
                      addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_2)->addon;
                      v25 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_2);
                      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v25->index, addon);
                    }
                  }
                }
                else
                {
                  for ( iter_1._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->m_BaseAttr)._M_current;
                        ;
                        __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_1) )
                  {
                    v45._M_current = std::vector<AttrAddon>::end(&pCfgEquip->m_BaseAttr)._M_current;
                    if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_1, &v45) )
                      break;
                    AttrRate_0 = (float)pCfgStar->m_RongLianAttr / 1000.0;
                    v20 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_1)->index == 45
                       || __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_1)->index == 11;
                    if ( !v20
                      && __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_1)->addon > 0 )
                    {
                      v21 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_1);
                      v22 = (int)(float)((float)v21->addon * AttrRate_0);
                      v23 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_1);
                      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v23->index, v22);
                    }
                  }
                }
              }
            }
            if ( (unsigned __int8)i <= 9u )
            {
              StrenGthenLevel = CExtEquip::getStrenGthenLevel(this, i);
              v26 = i;
              v27 = Answer::Singleton<CfgData>::instance();
              v28 = CfgData::GetEquipTable(v27);
              pStrengthen = CfgEquipTable::GetEquipStrengthenCfg(v28, v26, StrenGthenLevel);
              if ( pStrengthen && pStrengthen->AttrRate > 0 )
              {
                for ( iter_3._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->m_BaseAttr)._M_current;
                      ;
                      __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_3) )
                {
                  v47._M_current = std::vector<AttrAddon>::end(&pCfgEquip->m_BaseAttr)._M_current;
                  if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_3, &v47) )
                    break;
                  AttrRate_1 = (float)pStrengthen->AttrRate / 1000.0;
                  if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_3)->addon > 0 )
                  {
                    v29 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_3);
                    v30 = (int)(float)((float)v29->addon * AttrRate_1);
                    v31 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_3);
                    Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v31->index, v30);
                  }
                }
              }
              CRongHe = (unsigned int)Player::GetCRongHe(this->m_pPlayer);
              CRongHe::GetAttrList((CRongHe *const)&lAttr, CRongHe);
              for ( it._M_node = std::list<AttrAddon>::begin(&lAttr)._M_node;
                    ;
                    std::_List_iterator<AttrAddon>::operator++(&it, 0) )
              {
                __x._M_node = std::list<AttrAddon>::end(&lAttr)._M_node;
                if ( !std::_List_iterator<AttrAddon>::operator!=(&it, &__x) )
                  break;
                if ( std::_List_iterator<AttrAddon>::operator->(&it)->addon > 0 )
                {
                  v33 = std::_List_iterator<AttrAddon>::operator->(&it)->addon;
                  v34 = std::_List_iterator<AttrAddon>::operator->(&it);
                  Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v34->index, v33);
                }
              }
              std::list<AttrAddon>::~list(&lAttr);
            }
          }
        }
        MemEquip::~MemEquip(&equip);
      }
    }
  }
}


#####################################
void __cdecl CExtEquip::addGemAttr(CExtEquip *const this)
{
  CfgData *v1; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v4; // rax
  CfgData *v5; // rax
  const CfgItemGemTable *v6; // rax
  int32_t v7; // ebx
  const AttrAddon *v8; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_0; // [rsp+10h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+20h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+30h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v12; // [rsp+40h] [rbp-40h] BYREF
  int32_t nGemLevel; // [rsp+54h] [rbp-2Ch]
  int8_t i; // [rsp+5Ah] [rbp-26h]
  int8_t j; // [rsp+5Bh] [rbp-25h]
  int32_t nGemId; // [rsp+5Ch] [rbp-24h]
  const CfgItemGem *pCfgGem; // [rsp+60h] [rbp-20h]
  const CfgGemSuit *pCfgGemSuit; // [rsp+68h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nGemLevel = 0;
    for ( i = 0; i <= 9; ++i )
    {
      if ( this->m_vMemEquip[i].itemId > 0 )
      {
        for ( j = 0; j <= 3; ++j )
        {
          nGemId = this->m_vMemGem[i][j];
          if ( nGemId > 0 )
          {
            v1 = Answer::Singleton<CfgData>::instance();
            ItemGemTable = CfgData::GetItemGemTable(v1);
            pCfgGem = CfgItemGemTable::GetItemGem(ItemGemTable, nGemId);
            if ( pCfgGem )
            {
              nGemLevel += pCfgGem->m_nLevel;
              for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgGem->m_vAttrAddon)._M_current;
                    ;
                    __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
              {
                __rhs._M_current = std::vector<AttrAddon>::end(&pCfgGem->m_vAttrAddon)._M_current;
                if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
                  break;
                if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
                {
                  addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
                  v4 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
                  Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v4->index, addon);
                }
              }
            }
          }
        }
      }
    }
    if ( nGemLevel > 0 )
    {
      v5 = Answer::Singleton<CfgData>::instance();
      v6 = CfgData::GetItemGemTable(v5);
      pCfgGemSuit = CfgItemGemTable::GetGemSuit(v6, nGemLevel);
      if ( pCfgGemSuit )
      {
        for ( iter_0._M_current = std::vector<AttrAddon>::begin(&pCfgGemSuit->m_vAttrAddon)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_0) )
        {
          v12._M_current = std::vector<AttrAddon>::end(&pCfgGemSuit->m_vAttrAddon)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_0, &v12) )
            break;
          if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon > 0 )
          {
            v7 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon;
            v8 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v8->index, v7);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtEquip::AddStrengthenAttr(CExtEquip *const this)
{
  CfgData *v1; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v3; // eax
  CfgData *v4; // rax
  const CfgEquipTable *v5; // rax
  int32_t addon; // ebx
  const AttrAddon *v7; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-40h] BYREF
  int32_t i; // [rsp+30h] [rbp-30h]
  int32_t StrenGthenLevel; // [rsp+34h] [rbp-2Ch]
  const EquipStrengthenCfg *pStrengthen; // [rsp+38h] [rbp-28h]
  int32_t StrenNeedLevel; // [rsp+40h] [rbp-20h]
  int32_t AddLevel; // [rsp+44h] [rbp-1Ch]
  const EquipStrengthenCfg *AddSTrengthen; // [rsp+48h] [rbp-18h]

  for ( i = 0; i <= 9; ++i )
  {
    if ( this->m_vMemEquip[i].itemId > 0 )
    {
      StrenGthenLevel = CExtEquip::getStrenGthenLevel(this, i);
      v1 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v1);
      pStrengthen = CfgEquipTable::GetEquipStrengthenCfg(EquipTable, i, StrenGthenLevel);
      if ( pStrengthen )
      {
        if ( pStrengthen->NeedPos <= 9u && this->m_vMemEquip[pStrengthen->NeedPos].itemId > 0 )
        {
          StrenNeedLevel = CExtEquip::getStrenGthenLevel(this, pStrengthen->NeedPos);
          v3 = StrenGthenLevel <= StrenNeedLevel ? StrenGthenLevel : StrenNeedLevel;
          AddLevel = v3;
          if ( v3 > 0 )
          {
            v4 = Answer::Singleton<CfgData>::instance();
            v5 = CfgData::GetEquipTable(v4);
            AddSTrengthen = CfgEquipTable::GetEquipStrengthenCfg(v5, i, AddLevel);
            if ( AddSTrengthen )
            {
              for ( iter._M_current = std::vector<AttrAddon>::begin(&AddSTrengthen->vAttrAddon)._M_current;
                    ;
                    __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
              {
                __rhs._M_current = std::vector<AttrAddon>::end(&AddSTrengthen->vAttrAddon)._M_current;
                if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
                  break;
                if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
                {
                  addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
                  v7 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
                  Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v7->index, addon);
                }
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtEquip::addSuitAttr(CExtEquip *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t addon; // ebx
  AttrAddon *v5; // rax
  AttrAddon *v6; // rax
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > addIter; // [rsp+10h] [rbp-70h] BYREF
  AttrAddonVector addList; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<int> it; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+50h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+60h] [rbp-20h] BYREF
  const CfgEquipSuit *pSuit; // [rsp+68h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( it._M_node = std::list<int>::begin(&this->m_EquipSuit)._M_node; ; std::_List_iterator<int>::operator++(&it) )
    {
      __x._M_node = std::list<int>::end(&this->m_EquipSuit)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
        break;
      v1 = *std::_List_iterator<int>::operator*(&it);
      v2 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v2);
      pSuit = CfgEquipTable::GetEquipSuit(EquipTable, v1);
      if ( pSuit )
      {
        CfgEquipSuit::GetAttrAddon(&addList, pSuit);
        for ( addIter._M_current = std::vector<AttrAddon>::begin(&addList)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator++(&addIter) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&addList)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon *,std::vector<AttrAddon>>(&addIter, &__rhs) )
            break;
          if ( __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&addIter)->addon > 0 )
          {
            addon = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&addIter)->addon;
            v5 = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&addIter);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
            if ( __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&addIter)->index == 45 )
            {
              v6 = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&addIter);
              Player::AddBeiGongAttr(this->m_pPlayer, 3, v6->addon);
            }
          }
        }
        std::vector<AttrAddon>::~vector(&addList);
      }
    }
  }
}


#####################################
void __cdecl CExtEquip::addPosLevelAttr(CExtEquip *const this)
{
  int8_t v1; // bl
  CfgData *v2; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  CfgData *v6; // rax
  const CfgEquipTable *v7; // rax
  int32_t v8; // ebx
  const AttrAddon *v9; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_0; // [rsp+10h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+20h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+30h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v13; // [rsp+40h] [rbp-40h] BYREF
  int32_t nSuitLevel; // [rsp+54h] [rbp-2Ch]
  int8_t i; // [rsp+5Bh] [rbp-25h]
  int32_t nLevel; // [rsp+5Ch] [rbp-24h]
  const CfgEquipUpPos *pCfgEquipUpPos; // [rsp+60h] [rbp-20h]
  const CfgEquipPosSuit *pCfgEquipPosSuit; // [rsp+68h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nSuitLevel = -1;
    for ( i = 0; i <= 9; ++i )
    {
      nLevel = this->m_vMemPosLevel[i];
      if ( nSuitLevel >= 0 )
      {
        if ( nLevel < nSuitLevel )
          nSuitLevel = nLevel;
      }
      else
      {
        nSuitLevel = nLevel;
      }
      if ( nLevel > 0 )
      {
        v1 = i;
        v2 = Answer::Singleton<CfgData>::instance();
        EquipTable = CfgData::GetEquipTable(v2);
        pCfgEquipUpPos = CfgEquipTable::GetEquipUpPos(EquipTable, v1, nLevel);
        if ( pCfgEquipUpPos )
        {
          for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgEquipUpPos->m_vAttrAddon)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<AttrAddon>::end(&pCfgEquipUpPos->m_vAttrAddon)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
            {
              addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
              v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
            }
          }
        }
      }
    }
    if ( nSuitLevel > 0 )
    {
      v6 = Answer::Singleton<CfgData>::instance();
      v7 = CfgData::GetEquipTable(v6);
      pCfgEquipPosSuit = CfgEquipTable::GetEquipPosSuit(v7, nSuitLevel);
      if ( pCfgEquipPosSuit )
      {
        for ( iter_0._M_current = std::vector<AttrAddon>::begin(&pCfgEquipPosSuit->m_vAttrAddon)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_0) )
        {
          v13._M_current = std::vector<AttrAddon>::end(&pCfgEquipPosSuit->m_vAttrAddon)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_0, &v13) )
            break;
          if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon > 0 )
          {
            v8 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon;
            v9 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v9->index, v8);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CExtEquip::GetEquipAllGemLevel(CExtEquip *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  int32_t sum; // [rsp+1Ch] [rbp-24h]
  int32_t i; // [rsp+20h] [rbp-20h]
  int32_t j; // [rsp+24h] [rbp-1Ch]
  const CfgItemGem *pGem; // [rsp+28h] [rbp-18h]

  sum = 0;
  for ( i = 0; i <= 9; ++i )
  {
    for ( j = 0; j <= 3; ++j )
    {
      if ( this->m_vMemGem[i][j] > 0 )
      {
        v1 = this->m_vMemGem[i][j];
        v2 = Answer::Singleton<CfgData>::instance();
        ItemGemTable = CfgData::GetItemGemTable(v2);
        pGem = CfgItemGemTable::GetItemGem(ItemGemTable, v1);
        if ( pGem )
          sum += pGem->m_nLevel;
      }
    }
  }
  return sum;
}


#####################################
void __cdecl CExtEquip::addShenYaoPosAttr(CExtEquip *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  CfgData *v6; // rax
  const CfgEquipTable *v7; // rax
  int32_t v8; // ebx
  const AttrAddon *v9; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_0; // [rsp+10h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+20h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+30h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > v13; // [rsp+40h] [rbp-40h] BYREF
  int32_t nSuitLevel; // [rsp+54h] [rbp-2Ch]
  int8_t i; // [rsp+5Bh] [rbp-25h]
  int32_t nLevel; // [rsp+5Ch] [rbp-24h]
  const ShenYaoPos *pCfgEquipUpPos; // [rsp+60h] [rbp-20h]
  const ShenYaoPosSuit *pCfgEquipPosSuit; // [rsp+68h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nSuitLevel = -1;
    for ( i = 0; i <= 9; ++i )
    {
      nLevel = this->m_vShenYaoEquipPos[i];
      if ( nSuitLevel >= 0 )
      {
        if ( nLevel < nSuitLevel )
          nSuitLevel = nLevel;
      }
      else
      {
        nSuitLevel = nLevel;
      }
      if ( nLevel > 0 )
      {
        v1 = i + 11;
        v2 = Answer::Singleton<CfgData>::instance();
        EquipTable = CfgData::GetEquipTable(v2);
        pCfgEquipUpPos = CfgEquipTable::GetShenYaoPosCfg(EquipTable, v1, nLevel);
        if ( pCfgEquipUpPos )
        {
          for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgEquipUpPos->vAttrAddon)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<AttrAddon>::end(&pCfgEquipUpPos->vAttrAddon)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
            {
              addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
              v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
            }
          }
        }
      }
    }
    if ( nSuitLevel > 0 )
    {
      v6 = Answer::Singleton<CfgData>::instance();
      v7 = CfgData::GetEquipTable(v6);
      pCfgEquipPosSuit = CfgEquipTable::GetShenYaoPosSuit(v7, nSuitLevel);
      if ( pCfgEquipPosSuit )
      {
        for ( iter_0._M_current = std::vector<AttrAddon>::begin(&pCfgEquipPosSuit->vAttrAddon)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_0) )
        {
          v13._M_current = std::vector<AttrAddon>::end(&pCfgEquipPosSuit->vAttrAddon)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_0, &v13) )
            break;
          if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon > 0 )
          {
            v8 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon;
            v9 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v9->index, v8);
          }
        }
      }
    }
  }
}


#####################################
bool __cdecl CExtEquip::onEquipExchange(CExtEquip *const this, int32_t nBagSlot, int8_t nEquipSlot)
{
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  int32_t nSkillLevel; // r12d
  int32_t v7; // ebx
  CExtCharSkill *v8; // rax
  int32_t nSkillTalent; // ebx
  CExtCharSkill *CharSkill; // rax
  ChrTask *Task; // rax
  ChrTask *v12; // rax
  MemChrBag bagItem; // [rsp+10h] [rbp-40h] BYREF
  bool IsGongGao; // [rsp+33h] [rbp-1Dh]
  int32_t nLevel; // [rsp+34h] [rbp-1Ch]
  MoFuSkillCfg *pMoFuSkillCfg; // [rsp+38h] [rbp-18h]

  if ( (unsigned __int8)nEquipSlot > 0x5Cu )
    return 0;
  if ( !CExtCharBag::IsSlotValid(&this->m_pPlayer->m_extCharBag, nBagSlot) )
    return 0;
  Player::getBagSlotData(&bagItem, this->m_pPlayer, nBagSlot);
  if ( bagItem.itemId > 0 && !CExtEquip::checkDressEquip(this, nBagSlot, nEquipSlot) )
    return 0;
  Bag = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(Bag, nBagSlot, &this->m_vMemEquip[nEquipSlot], ITEM_CHANGE_REASON::ICR_NONE, 0);
  this->m_vMemEquip[nEquipSlot] = bagItem;
  if ( !nEquipSlot || nEquipSlot == 2 )
  {
    Player::SetNeedSyncAround(this->m_pPlayer);
    Player::setSyncToTeamFlag(this->m_pPlayer);
    if ( nEquipSlot )
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_CLOTH, bagItem.itemId);
    else
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_MAIN_WEAPON, bagItem.itemId);
  }
  CExtEquip::addDirty(this, nEquipSlot);
  IsGongGao = 0;
  if ( nEquipSlot > 10 )
    IsGongGao = nEquipSlot <= 20;
  CExtEquip::checkEquipSuit(this, IsGongGao);
  CExtEquip::updateEquipStar(this);
  CExtEquip::updateEquipGem(this);
  if ( nEquipSlot > 49 && nEquipSlot <= 58 )
  {
    nLevel = CExtEquip::GetMoFuSuitLevel(this);
    v5 = Answer::Singleton<CfgData>::instance();
    pMoFuSkillCfg = CfgData::GetMoFuSkillCfg(v5, nLevel);
    if ( pMoFuSkillCfg )
    {
      if ( pMoFuSkillCfg->nActivation <= 0 )
      {
        nSkillTalent = pMoFuSkillCfg->nSkillTalent;
        CharSkill = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(CharSkill, nSkillTalent, 0);
      }
      else
      {
        nSkillLevel = pMoFuSkillCfg->nSkillLevel;
        v7 = pMoFuSkillCfg->nSkillTalent;
        v8 = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(v8, v7, nSkillLevel);
      }
    }
  }
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(Task, 18, 0);
  v12 = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(v12, 19, 0);
  Player::SetNeedSyncAround(this->m_pPlayer);
  return 1;
}


#####################################
bool __cdecl CExtEquip::checkDressEquip(const CExtEquip *const this, int32_t nBagSlot, int8_t nEquipSlot)
{
  bool v3; // bl
  CExtCharBag *Bag; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v6; // rax
  int32_t itemId; // ebx
  CfgData *v8; // rax
  int8_t m_nJob; // bl
  CExtCharWing *CharWing; // rax
  int32_t Level; // eax
  CXinMo *CXinMo; // rax
  int32_t ActiveXinMoLevel; // eax
  int32_t m_nLevel; // ebx
  CXingMai *XingMai; // rax
  bool v17; // al
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  const MemChrBag *bagItem; // [rsp+48h] [rbp-28h]
  const CfgEquip *pCfgEquip; // [rsp+50h] [rbp-20h]
  int32_t CurLevel; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    bagItem = CExtCharBag::GetSlotData(Bag, nBagSlot);
    if ( bagItem->srcId <= 0 || bagItem->itemClass != 2 )
      return 0;
    srcId = bagItem->srcId;
    v6 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v6, srcId);
    if ( bagItem->itemId == equip.base )
    {
      itemId = bagItem->itemId;
      v8 = Answer::Singleton<CfgData>::instance();
      pCfgEquip = CfgData::getEquip(v8, itemId);
      if ( pCfgEquip )
      {
        if ( !pCfgEquip->m_nJob || (m_nJob = pCfgEquip->m_nJob, m_nJob == Player::getJob(this->m_pPlayer)) )
        {
          if ( pCfgEquip->m_nType <= 39 || pCfgEquip->m_nType > 45 )
          {
            if ( pCfgEquip->m_nType <= 60 || pCfgEquip->m_nType > 68 )
            {
              m_nLevel = pCfgEquip->m_nLevel;
              if ( m_nLevel > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
              {
                v3 = 0;
                goto LABEL_39;
              }
            }
            else
            {
              if ( pCfgEquip->m_nGrade <= 0 )
              {
                v3 = 0;
                goto LABEL_39;
              }
              CXinMo = Player::GetCXinMo(this->m_pPlayer);
              ActiveXinMoLevel = CXinMo::GetActiveXinMoLevel(CXinMo);
              if ( ActiveXinMoLevel < pCfgEquip->m_nLevel )
              {
                v3 = 0;
                goto LABEL_39;
              }
            }
          }
          else
          {
            CharWing = Player::GetCharWing(this->m_pPlayer);
            Level = CExtCharWing::GetLevel(CharWing);
            if ( Level < pCfgEquip->m_nLevel )
            {
              v3 = 0;
              goto LABEL_39;
            }
          }
          if ( pCfgEquip->m_nType <= 54
            || pCfgEquip->m_nType > 60
            || (CurLevel = Player::getRecord(this->m_pPlayer, 1161), pCfgEquip->m_GongMingLevel <= CurLevel) )
          {
            if ( !CExtEquip::checkEquipPlace(this, pCfgEquip->m_nType, nEquipSlot) )
            {
              v3 = 0;
            }
            else
            {
              v17 = 0;
              if ( isXingMaiSlot(nEquipSlot) )
              {
                XingMai = Player::GetXingMai(this->m_pPlayer);
                if ( !CXingMai::IsXingMaiSlotActived(XingMai, nEquipSlot) )
                  v17 = 1;
              }
              v3 = !v17;
            }
          }
          else
          {
            v3 = 0;
          }
          goto LABEL_39;
        }
        v3 = 0;
      }
      else
      {
        v3 = 0;
      }
    }
    else
    {
      v3 = 0;
    }
LABEL_39:
    MemEquip::~MemEquip(&equip);
    return v3;
  }
  return 0;
}


#####################################
bool __cdecl CExtEquip::checkEquipPlace(const CExtEquip *const this, int8_t nEquipType, int8_t nEquipSlot)
{
  bool result; // al

  switch ( nEquipType )
  {
    case 0:
      result = nEquipSlot == 0;
      break;
    case 1:
      result = nEquipSlot == 1;
      break;
    case 2:
      result = nEquipSlot == 2;
      break;
    case 3:
      result = nEquipSlot == 3 || nEquipSlot == 8;
      break;
    case 4:
      result = nEquipSlot == 4;
      break;
    case 5:
      result = nEquipSlot == 5;
      break;
    case 6:
      result = nEquipSlot == 6;
      break;
    case 7:
      result = nEquipSlot == 7 || nEquipSlot == 9;
      break;
    case 8:
      result = nEquipSlot == 10;
      break;
    case 9:
      result = nEquipSlot == 11;
      break;
    case 10:
      result = nEquipSlot == 12;
      break;
    case 11:
      result = nEquipSlot == 13;
      break;
    case 12:
      result = nEquipSlot == 14 || nEquipSlot == 19;
      break;
    case 13:
      result = nEquipSlot == 15;
      break;
    case 14:
      result = nEquipSlot == 16;
      break;
    case 15:
      result = nEquipSlot == 17;
      break;
    case 16:
      result = nEquipSlot == 18 || nEquipSlot == 20;
      break;
    case 17:
      result = nEquipSlot == 21;
      break;
    case 18:
      result = nEquipSlot == 22;
      break;
    case 19:
      result = nEquipSlot == 23;
      break;
    case 20:
      result = nEquipSlot == 24;
      break;
    case 21:
      result = nEquipSlot == 25;
      break;
    case 22:
      result = nEquipSlot == 26;
      break;
    case 23:
      result = nEquipSlot == 27;
      break;
    case 24:
      result = nEquipSlot == 28;
      break;
    case 25:
      result = nEquipSlot == 29;
      break;
    case 26:
      result = nEquipSlot == 30;
      break;
    case 27:
      result = nEquipSlot == 31;
      break;
    case 28:
      result = nEquipSlot == 32;
      break;
    case 29:
      result = nEquipSlot == 33;
      break;
    case 30:
      result = nEquipSlot == 34;
      break;
    case 31:
      result = nEquipSlot == 35;
      break;
    case 32:
      result = nEquipSlot == 36;
      break;
    case 33:
      result = nEquipSlot == 37;
      break;
    case 34:
      result = nEquipSlot == 38;
      break;
    case 35:
      result = nEquipSlot == 39;
      break;
    case 36:
      result = nEquipSlot == 40;
      break;
    case 37:
      result = nEquipSlot == 41;
      break;
    case 38:
      result = nEquipSlot == 42;
      break;
    case 39:
      result = nEquipSlot == 43;
      break;
    case 40:
      result = nEquipSlot == 44;
      break;
    case 41:
      result = nEquipSlot == 45;
      break;
    case 42:
      result = nEquipSlot == 46;
      break;
    case 43:
      result = nEquipSlot == 47;
      break;
    case 44:
      result = nEquipSlot == 48;
      break;
    case 45:
      result = nEquipSlot == 49;
      break;
    case 46:
      result = nEquipSlot == 50;
      break;
    case 47:
      result = nEquipSlot == 51;
      break;
    case 48:
      result = nEquipSlot == 52;
      break;
    case 49:
      result = nEquipSlot == 53;
      break;
    case 50:
      result = nEquipSlot == 54;
      break;
    case 51:
      result = nEquipSlot == 55;
      break;
    case 52:
      result = nEquipSlot == 56;
      break;
    case 53:
      result = nEquipSlot == 57;
      break;
    case 54:
      result = nEquipSlot == 58;
      break;
    case 55:
      result = nEquipSlot == 59;
      break;
    case 56:
      result = nEquipSlot == 60;
      break;
    case 57:
      result = nEquipSlot == 61;
      break;
    case 58:
      result = nEquipSlot == 62;
      break;
    case 59:
      result = nEquipSlot == 63;
      break;
    case 60:
      result = nEquipSlot == 64;
      break;
    case 61:
      result = nEquipSlot == 65;
      break;
    case 62:
      result = nEquipSlot == 66;
      break;
    case 63:
      result = nEquipSlot == 67;
      break;
    case 64:
      result = nEquipSlot == 68 || nEquipSlot == 73;
      break;
    case 65:
      result = nEquipSlot == 69;
      break;
    case 66:
      result = nEquipSlot == 70;
      break;
    case 67:
      result = nEquipSlot == 71;
      break;
    case 68:
      result = nEquipSlot == 72 || nEquipSlot == 74;
      break;
    case 75:
      result = nEquipSlot == 81;
      break;
    case 76:
      result = nEquipSlot == 82;
      break;
    case 77:
      result = nEquipSlot == 83;
      break;
    case 78:
      result = nEquipSlot == 84;
      break;
    case 79:
      result = nEquipSlot == 85;
      break;
    case 80:
      result = nEquipSlot == 86;
      break;
    case 81:
      result = nEquipSlot == 87;
      break;
    case 82:
      result = nEquipSlot == 88;
      break;
    case 83:
      result = nEquipSlot == 89;
      break;
    case 84:
      result = nEquipSlot == 90;
      break;
    case 85:
      result = nEquipSlot == 91;
      break;
    case 86:
      result = nEquipSlot == 92;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtEquip::GetTeJieValue(CExtEquip *const this, int32_t nSlot)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquip *pCfgEquip; // [rsp+38h] [rbp-18h]

  if ( nSlot <= 86 || nSlot > 92 )
    return 0;
  v3 = *(_QWORD *)&CExtEquip::GetEquipSlot(this, nSlot)->itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgEquip = CfgData::getEquip(v4, v3);
  if ( pCfgEquip )
    return pCfgEquip->m_TeJieParam;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipType(CExtEquip *const this, int32_t Slot)
{
  int32_t result; // eax

  switch ( Slot )
  {
    case '!':
      result = 29;
      break;
    case '"':
      result = 30;
      break;
    case '#':
      result = 31;
      break;
    case '$':
      result = 32;
      break;
    case '%':
      result = 33;
      break;
    case '&':
      result = 34;
      break;
    case '\'':
      result = 35;
      break;
    case '(':
      result = 36;
      break;
    case ')':
      result = 37;
      break;
    case '*':
      result = 38;
      break;
    case '+':
      result = 39;
      break;
    case '2':
      result = 46;
      break;
    case '3':
      result = 47;
      break;
    case '4':
      result = 48;
      break;
    case '5':
      result = 49;
      break;
    case '6':
      result = 50;
      break;
    case '7':
      result = 51;
      break;
    case '8':
      result = 52;
      break;
    case '9':
      result = 53;
      break;
    case ':':
      result = 54;
      break;
    case ';':
      result = 55;
      break;
    case '<':
      result = 56;
      break;
    case '=':
      result = 57;
      break;
    case '>':
      result = 58;
      break;
    case '?':
      result = 59;
      break;
    case '@':
      result = 60;
      break;
    default:
      result = -1;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipSlotPlace(CExtEquip *const this, int32_t nType)
{
  int32_t result; // eax

  switch ( nType )
  {
    case 17:
      result = 21;
      break;
    case 18:
      result = 22;
      break;
    case 19:
      result = 23;
      break;
    case 20:
      result = 24;
      break;
    case 21:
      result = 25;
      break;
    case 22:
      result = 26;
      break;
    case 23:
      result = 27;
      break;
    case 24:
      result = 28;
      break;
    case 25:
      result = 29;
      break;
    case 26:
      result = 30;
      break;
    case 27:
      result = 31;
      break;
    case 28:
      result = 32;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtEquip::GetMaxPolishLevel(CExtEquip *const this, int32_t Slot)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquip *pCfgEquip; // [rsp+38h] [rbp-18h]

  if ( (unsigned int)Slot > 0x5C )
    return 0;
  v3 = *(_QWORD *)&CExtEquip::GetEquipSlot(this, Slot)->itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgEquip = CfgData::getEquip(v4, v3);
  if ( pCfgEquip )
    return pCfgEquip->m_PolishLevel;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtEquip::GetMaxRefiningLevel(CExtEquip *const this, int32_t Slot)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquip *pCfgEquip; // [rsp+38h] [rbp-18h]

  if ( (unsigned int)Slot > 0x5C )
    return 0;
  v3 = *(_QWORD *)&CExtEquip::GetEquipSlot(this, Slot)->itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgEquip = CfgData::getEquip(v4, v3);
  if ( pCfgEquip )
    return pCfgEquip->m_WingEquipRefiningLevel;
  else
    return 0;
}


#####################################
void __cdecl CExtEquip::addDirty(CExtEquip *const this, int32_t nSlot)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<int> v3; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CExtEquip *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<int> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nSlota = nSlot;
  M_node = std::list<int>::end(&this->m_lstDirty)._M_node;
  v3._M_node = std::list<int>::begin(&this->m_lstDirty)._M_node;
  iter._M_node = std::find<std::_List_iterator<int>,int>(v3, (std::_List_iterator<int>)M_node, &nSlota)._M_node;
  __x._M_node = std::list<int>::end(&thisa->m_lstDirty)._M_node;
  if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
    std::list<int>::push_back(&thisa->m_lstDirty, &nSlota);
}


#####################################
void __cdecl CExtEquip::checkDirty(CExtEquip *const this)
{
  if ( CExtEquip::sendDirty(this) )
    CExtEquip::clearDirty(this);
}


#####################################
bool __cdecl CExtEquip::sendDirty(CExtEquip *const this)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_List_iterator<int> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<int> iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-30h]
  uint32_t nOffSet; // [rsp+38h] [rbp-28h]
  int32_t nCount; // [rsp+3Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+40h] [rbp-20h]
  int32_t nSlot; // [rsp+44h] [rbp-1Ch]
  const MemChrBag *tSlot; // [rsp+48h] [rbp-18h]

  if ( !this->m_pPlayer || std::list<int>::empty(&this->m_lstDirty) )
    return 0;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DB7u);
  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt8(packet, 0);
  nOffSet = Answer::NetPacket::getWOffset(packet);
  nCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  iter._M_node = std::list<int>::begin(&this->m_lstDirty)._M_node;
  eiter._M_node = std::list<int>::end(&this->m_lstDirty)._M_node;
  while ( std::_List_iterator<int>::operator!=(&iter, &eiter) )
  {
    nSlot = *std::_List_iterator<int>::operator*(&iter);
    if ( (unsigned int)nSlot <= 0x5C )
    {
      tSlot = CExtEquip::GetEquipSlot(this, nSlot);
      Answer::NetPacket::writeInt32(packet, nSlot);
      Answer::NetPacket::writeInt32(packet, tSlot->itemId);
      Answer::NetPacket::writeInt8(packet, tSlot->itemClass);
      Answer::NetPacket::writeInt32(packet, tSlot->itemCount);
      Answer::NetPacket::writeInt8(packet, tSlot->bind);
      Answer::NetPacket::writeInt32(packet, tSlot->endTime);
      Answer::NetPacket::writeInt64(packet, tSlot->srcId);
      ++nCount;
    }
    std::_List_iterator<int>::operator++(&iter);
  }
  endOffSet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, nOffSet);
  Answer::NetPacket::writeInt32(packet, nCount);
  Answer::NetPacket::setWOffset(packet, endOffSet);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v7 = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v8, v7, GateIndex, packet);
  return 1;
}


#####################################
void __cdecl CExtEquip::getDropEquip(
        CExtEquip *const this,
        Player *pKiller,
        int32_t nDropRate,
        MemChrBagVector *const DropItems,
        int32_t Mid)
{
  Answer::Random *v5; // rax
  int v6; // ebx
  Answer::Random *v7; // rax
  CfgData *v8; // rax
  const CfgEquipTable *EquipTable; // rax
  Answer::Random *v10; // rax
  int8_t ConnId; // bl
  DBService *v12; // rax
  __int64 v13; // rdx
  DropLog stu; // [rsp+30h] [rbp-D0h] BYREF
  MemChrBag ItemTmp; // [rsp+70h] [rbp-90h] BYREF
  Int32Vector vSlot; // [rsp+90h] [rbp-70h] BYREF
  _BYTE v19[16]; // [rsp+B0h] [rbp-50h] BYREF
  _BYTE v20[12]; // [rsp+C0h] [rbp-40h] BYREF
  int32_t nRand; // [rsp+CCh] [rbp-34h]
  int32_t nSize; // [rsp+D0h] [rbp-30h]
  int32_t RandSlot; // [rsp+D4h] [rbp-2Ch]
  int32_t nEquipSlot; // [rsp+D8h] [rbp-28h]
  int32_t StrenGthenLevel; // [rsp+DCh] [rbp-24h]
  const EquipStrengthenCfg *pStrengthen; // [rsp+E0h] [rbp-20h]
  int32_t StrenGthenRand; // [rsp+ECh] [rbp-14h]

  if ( this->m_pPlayer )
  {
    CExtEquip::getCanDropEquipSlots(&vSlot, this);
    if ( !std::vector<int>::empty(&vSlot) )
    {
      v5 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v5, 1, 1000);
      if ( nRand < nDropRate )
      {
        nSize = std::vector<int>::size(&vSlot);
        v6 = nSize - 1;
        v7 = Answer::Singleton<Answer::Random>::instance();
        RandSlot = Answer::Random::generate(v7, 0, v6);
        nEquipSlot = *std::vector<int>::operator[](&vSlot, RandSlot);
        StrenGthenLevel = CExtEquip::getStrenGthenLevel(this, RandSlot);
        if ( StrenGthenLevel <= 0
          || (v8 = Answer::Singleton<CfgData>::instance(),
              EquipTable = CfgData::GetEquipTable(v8),
              (pStrengthen = CfgEquipTable::GetEquipStrengthenCfg(EquipTable, RandSlot, StrenGthenLevel)) != 0)
          && pStrengthen->DropRate > 0
          && (v10 = Answer::Singleton<Answer::Random>::instance(),
              StrenGthenRand = Answer::Random::generate(v10, 1, 1000),
              pStrengthen->DropRate < StrenGthenRand) )
        {
          std::vector<MemChrBag>::push_back(DropItems, &this->m_vMemEquip[nEquipSlot]);
          if ( pKiller )
          {
            memset(&stu, 0, sizeof(stu));
            std::string::string(&stu.sName);
            std::string::string(&stu.sKillerName);
            stu.nCid = Player::getCid(this->m_pPlayer);
            Player::getName((const Player *const)v19);
            std::string::operator=(&stu.sName, v19);
            std::string::~string(v19);
            stu.nEquipId = this->m_vMemEquip[nEquipSlot].itemId;
            stu.nSrcId = this->m_vMemEquip[nEquipSlot].srcId;
            stu.nMapId = StaticObj::getMapId(this->m_pPlayer);
            stu.nKiller = Player::getCid(pKiller);
            Player::getName((const Player *const)v20);
            std::string::operator=(&stu.sKillerName, v20);
            std::string::~string(v20);
            ConnId = Player::getConnId(this->m_pPlayer);
            v12 = Answer::Singleton<DBService>::instance();
            DBService::LogEquipDrop(v12, ConnId, &stu);
            DropLog::~DropLog(&stu);
          }
          memset(&ItemTmp, 0, sizeof(ItemTmp));
          v13 = 16 * (2LL * nEquipSlot + 1);
          *(int (***)(...))((char *)&this->_vptr_IExtSystem + v13) = 0;
          *(Player **)((char *)&this->m_pPlayer + v13) = *(Player **)&ItemTmp.itemCount;
          *(_QWORD *)((char *)&this->m_vMemEquip[0].itemId + v13) = *(_QWORD *)&ItemTmp.endTime;
          *(_QWORD *)((char *)&this->m_vMemEquip[0].itemCount + v13) = ItemTmp.srcId;
          CExtEquip::addDirty(this, nEquipSlot);
          if ( !nEquipSlot || nEquipSlot == 2 )
          {
            Player::SetNeedSyncAround(this->m_pPlayer);
            Player::setSyncToTeamFlag(this->m_pPlayer);
            if ( nEquipSlot )
            {
              if ( nEquipSlot == 2 )
                Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_CLOTH, 0);
            }
            else
            {
              Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_MAIN_WEAPON, 0);
            }
          }
        }
      }
    }
    std::vector<int>::~vector(&vSlot);
  }
}


#####################################
void __cdecl CExtEquip::GetDropEquip(
        CExtEquip *const this,
        Player *pKiller,
        int32_t DropCount,
        int32_t DropRate,
        MemChrBagVector *const DropItems,
        int32_t Mid)
{
  std::_Ios_Openmode v7; // eax
  unsigned int MapId; // ebx
  unsigned int Now; // eax
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  unsigned int bind; // ebx
  unsigned int itemClass; // r12d
  MemChrBag *v20; // rax
  __int64 v21; // rax
  __int64 v22; // rax
  __int64 v23; // rax
  __int64 v24; // rax
  __int64 v25; // rax
  int64_t srcId; // rbx
  CEquipManager *v27; // rax
  CfgData *v28; // rax
  const CfgEquipTable *EquipTable; // rax
  int8_t v30; // r12
  int32_t itemId; // ebx
  CfgData *v32; // rax
  GameService *v33; // rax
  CharId_t Cid; // rax
  int32_t v35; // eax
  MemChrBag *v36; // rax
  MemChrBag *v37; // rax
  MemChrBag *v38; // rax
  uint32_t WOffset; // eax
  GameService *v40; // rax
  MemChrBag *v42; // r13
  CharId_t v43; // r12
  int8_t ConnId; // bl
  DBService *v45; // rax
  int8_t v46; // bl
  CEquipManager *v47; // rax
  CharId_t v48; // r12
  int8_t v49; // bl
  DBService *v50; // rax
  _BYTE v55[16]; // [rsp+40h] [rbp-260h] BYREF
  _BYTE v56[352]; // [rsp+50h] [rbp-250h] BYREF
  MemEquip equip; // [rsp+1B0h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+1F0h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+200h] [rbp-A0h] BYREF
  _BYTE v60[16]; // [rsp+210h] [rbp-90h] BYREF
  std::string val; // [rsp+220h] [rbp-80h] BYREF
  std::string v62; // [rsp+230h] [rbp-70h] BYREF
  char v63; // [rsp+23Fh] [rbp-61h] BYREF
  std::string v64; // [rsp+240h] [rbp-60h] BYREF
  std::string Param; // [rsp+250h] [rbp-50h] BYREF
  std::string v66; // [rsp+260h] [rbp-40h] BYREF
  int32_t i; // [rsp+26Ch] [rbp-34h]
  const CfgEquip *pCfgEquip; // [rsp+270h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+278h] [rbp-28h]

  for ( i = 0; i < DropCount; ++i )
    CExtEquip::getDropEquip(this, pKiller, DropRate, DropItems, Mid);
  if ( this->m_pPlayer && std::vector<MemChrBag>::size(DropItems) )
  {
    it._M_current = std::vector<MemChrBag>::begin(DropItems)._M_current;
    while ( 1 )
    {
      __rhs._M_current = std::vector<MemChrBag>::end(DropItems)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
        break;
      v7 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
      std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
        v55,
        (unsigned int)v7);
      MapId = StaticObj::getMapId(this->m_pPlayer);
      Now = Unit::getNow(this->m_pPlayer);
      v10 = std::ostream::operator<<(v56, Now);
      v11 = std::operator<<<std::char_traits<char>>(v10, L"|1");
      v12 = std::ostream::operator<<(v11, MapId);
      std::operator<<<std::char_traits<char>>(v12, L"|1");
      if ( pKiller )
      {
        Player::getName((const Player *const)v60);
        v13 = std::operator<<<char>(v56, v60);
        std::operator<<<std::char_traits<char>>(v13, L"|1");
        std::string::~string(v60);
      }
      else
      {
        v14 = std::operator<<<std::char_traits<char>>(v56, 9269978);
        std::operator<<<std::char_traits<char>>(v14, L"|1");
      }
      v15 = std::ostream::operator<<(v56, (unsigned int)Mid);
      v16 = std::operator<<<std::char_traits<char>>(v15, L"|1");
      v17 = std::ostream::operator<<(v16, 1);
      std::operator<<<std::char_traits<char>>(v17, L"|1");
      bind = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind;
      itemClass = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemClass;
      v20 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
      v21 = std::ostream::operator<<(v56, (unsigned int)v20->itemId);
      v22 = std::operator<<<std::char_traits<char>>(v21, L"|1");
      v23 = std::ostream::operator<<(v22, itemClass);
      v24 = std::operator<<<std::char_traits<char>>(v23, L"|1");
      v25 = std::ostream::operator<<(v24, bind);
      std::operator<<<std::char_traits<char>>(v25, L"|1");
      srcId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->srcId;
      v27 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v27, srcId);
      LODWORD(srcId) = equip.base;
      v28 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v28);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, srcId);
      if ( pCfgEquip )
      {
        if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind == 1 )
        {
          v30 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemClass;
          itemId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemId;
          v32 = Answer::Singleton<CfgData>::instance();
          if ( CfgData::dropBroadcast(v32, itemId, v30) )
          {
            v33 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v33, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            Answer::NetPacket::writeInt32(packet, 537);
            Answer::NetPacket::writeInt32(packet, 0);
            if ( pKiller )
            {
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              Cid = Player::getCid(pKiller);
              Answer::NetPacket::writeInt64(packet, Cid);
            }
            else
            {
              std::allocator<char>::allocator(&v63);
              std::string::string(&v62, 9269980, &v63);
              Answer::NetPacket::writeUTF8(packet, &v62);
              std::string::~string(&v62);
              std::allocator<char>::~allocator(&v63);
              Answer::NetPacket::writeInt64(packet, 0);
            }
            v35 = StaticObj::getMapId(this->m_pPlayer);
            Answer::NetPacket::writeInt32(packet, v35);
            Answer::NetPacket::writeInt32(packet, Mid);
            Player::getName((const Player *const)&v64);
            Answer::NetPacket::writeUTF8(packet, &v64);
            std::string::~string(&v64);
            v36 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
            Answer::NetPacket::writeInt8(packet, v36->itemClass);
            v37 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
            Answer::NetPacket::writeInt32(packet, v37->itemId);
            v38 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
            Answer::NetPacket::writeInt32(packet, v38->itemCount);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v40 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v40, packet);
          }
        }
        if ( pCfgEquip->m_BackGold > 0
          && __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind == 1 )
        {
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, v55);
          v42 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
          v43 = Player::getCid(this->m_pPlayer);
          ConnId = Player::getConnId(this->m_pPlayer);
          v45 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v45, ConnId, v43, 2000, v42, ITEM_CHANGE_REASON::IDCR_MAIL_SHU_HUI, &Param, 0);
          std::string::~string(&Param);
        }
        else
        {
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v66, v55);
          v48 = Player::getCid(this->m_pPlayer);
          v49 = Player::getConnId(this->m_pPlayer);
          v50 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v50, v49, v48, 2000, &v66, 0);
          std::string::~string(&v66);
          equip.owner = 0;
        }
        v46 = Player::getConnId(this->m_pPlayer);
        v47 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::UpdateMemEquip(v47, v46, &equip, 614);
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0);
      }
      else
      {
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0);
      }
      MemEquip::~MemEquip(&equip);
      std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v55);
    }
  }
  CExtEquip::checkEquipSuit(this, 0);
  CExtEquip::updateEquipStar(this);
  CExtEquip::updateEquipGem(this);
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Player::SetNeedSyncAround(this->m_pPlayer);
}


#####################################
void __cdecl CExtEquip::broadcastItemCombi(CExtEquip *const this, int32_t ItemId, int8_t ItemClass)
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
void __cdecl CExtEquip::EquipUpStarGongGao(CExtEquip *const this, MemEquip *const Equip)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 115);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt64(packet, Equip->id);
      Answer::NetPacket::writeInt32(packet, Equip->base);
      Answer::NetPacket::writeInt8(packet, Equip->star);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v7, v6, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtEquip::GetLowestStar(CExtEquip *const this)
{
  int32_t v1; // ebx
  EquipId_t srcId; // r12
  CEquipManager *v3; // rax
  int v4; // r12d
  MemEquip Equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t LowesetStar; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  LowesetStar = 99999;
  for ( i = 0; i <= 92; ++i )
  {
    srcId = this->m_vMemEquip[i].srcId;
    v3 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&Equip, v3, srcId);
    if ( Equip.base == this->m_vMemEquip[i].itemId )
    {
      if ( Equip.star < LowesetStar )
        LowesetStar = Equip.star;
      v4 = 1;
    }
    else
    {
      v1 = 0;
      v4 = 0;
    }
    MemEquip::~MemEquip(&Equip);
    if ( v4 != 1 )
      return v1;
  }
  return LowesetStar;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipAllCount(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  MemEquip Equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t Count; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  Count = 0;
  for ( i = 0; i <= 92; ++i )
  {
    if ( this->m_vMemEquip[i].itemId > 0 && this->m_vMemEquip[i].srcId > 0 )
    {
      srcId = this->m_vMemEquip[i].srcId;
      v2 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&Equip, v2, srcId);
      if ( Equip.base == this->m_vMemEquip[i].itemId )
        ++Count;
      MemEquip::~MemEquip(&Equip);
    }
  }
  return Count;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipAllStar(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  MemEquip Equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t AllStar; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  AllStar = 0;
  for ( i = 0; i <= 92; ++i )
  {
    if ( this->m_vMemEquip[i].itemId > 0 && this->m_vMemEquip[i].srcId > 0 )
    {
      srcId = this->m_vMemEquip[i].srcId;
      v2 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&Equip, v2, srcId);
      if ( Equip.base == this->m_vMemEquip[i].itemId )
        AllStar += Equip.star;
      MemEquip::~MemEquip(&Equip);
    }
  }
  return AllStar;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipAllUpPosLevel(CExtEquip *const this)
{
  int32_t v2; // eax
  int32_t Level; // [rsp+10h] [rbp-8h]
  int32_t nPos; // [rsp+14h] [rbp-4h]

  Level = 0;
  for ( nPos = 0; nPos <= 9; ++nPos )
  {
    if ( this->m_vMemPosLevel[nPos] <= 0 )
      return 0;
    if ( Level )
    {
      if ( this->m_vMemPosLevel[nPos] >= Level )
        v2 = Level;
      else
        v2 = this->m_vMemPosLevel[nPos];
      Level = v2;
    }
    else
    {
      Level = this->m_vMemPosLevel[nPos];
    }
  }
  return Level;
}


#####################################
int32_t __cdecl CExtEquip::HaveLevelEquipCount(CExtEquip *const this, int32_t Level)
{
  int32_t itemId; // ebx
  CfgData *v3; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t Count; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+14h] [rbp-1Ch]
  const CfgEquip *pCfgEquip; // [rsp+18h] [rbp-18h]

  Count = 0;
  for ( i = 0; i <= 92; ++i )
  {
    itemId = this->m_vMemEquip[i].itemId;
    v3 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v3);
    pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( pCfgEquip && pCfgEquip->m_nLevel >= Level )
      ++Count;
  }
  return Count;
}


#####################################
int32_t __cdecl CExtEquip::HaveStarEquipCount(CExtEquip *const this, int32_t Star)
{
  int32_t v2; // ebx
  EquipId_t srcId; // r12
  CEquipManager *v4; // rax
  int v5; // r12d
  MemEquip Equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t Count; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  Count = 0;
  for ( i = 0; i <= 92; ++i )
  {
    srcId = this->m_vMemEquip[i].srcId;
    v4 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&Equip, v4, srcId);
    if ( Equip.base == this->m_vMemEquip[i].itemId )
    {
      if ( Equip.star >= Star )
        ++Count;
      v5 = 1;
    }
    else
    {
      v2 = 0;
      v5 = 0;
    }
    MemEquip::~MemEquip(&Equip);
    if ( v5 != 1 )
      return v2;
  }
  return Count;
}


#####################################
int32_t __cdecl CExtEquip::HaveQualityGradeEquipCount(CExtEquip *const this, int8_t nQuality, int8_t nGrade)
{
  int32_t itemId; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t Count; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+14h] [rbp-1Ch]
  const CfgEquip *pCfgEquip; // [rsp+18h] [rbp-18h]

  Count = 0;
  for ( i = 0; i <= 92; ++i )
  {
    itemId = this->m_vMemEquip[i].itemId;
    v4 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v4);
    pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( pCfgEquip && pCfgEquip->m_nQuality >= nQuality && pCfgEquip->m_nGrade >= nGrade )
      ++Count;
  }
  return Count;
}


#####################################
int32_t __cdecl CExtEquip::GetWingEquipCount3SuitId(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int32_t itemId; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v6; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v8; // rax
  MemEquip equip; // [rsp+10h] [rbp-80h] BYREF
  Int32Vector Suit; // [rsp+50h] [rbp-40h] BYREF
  int32_t j; // [rsp+6Ch] [rbp-24h]
  const MemChrBag *curEquip; // [rsp+70h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+78h] [rbp-18h]

  std::vector<int>::vector(&Suit);
  for ( j = 44; j <= 49; ++j )
  {
    curEquip = &this->m_vMemEquip[j];
    if ( curEquip->srcId > 0 && curEquip->itemClass == 2 )
    {
      srcId = curEquip->srcId;
      v2 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v2, srcId);
      if ( equip.base == curEquip->itemId )
      {
        itemId = this->m_vMemEquip[j].itemId;
        v4 = Answer::Singleton<CfgData>::instance();
        EquipTable = CfgData::GetEquipTable(v4);
        pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
        if ( pCfgEquip )
        {
          if ( pCfgEquip->m_nSuitId > 0 )
            std::vector<int>::push_back(&Suit, &pCfgEquip->m_nSuitId);
        }
      }
      MemEquip::~MemEquip(&equip);
    }
  }
  if ( std::vector<int>::size(&Suit) > 2 )
  {
    M_current = std::vector<int>::end(&Suit)._M_current;
    v8._M_current = std::vector<int>::begin(&Suit)._M_current;
    std::sort<__gnu_cxx::__normal_iterator<int *,std::vector<int>>,bool (*)(int const&,int const&)>(
      v8,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current,
      (bool (*)(const int32_t *, const int32_t *))comp);
    v6 = *std::vector<int>::operator[](&Suit, 2u);
  }
  else
  {
    v6 = 0;
  }
  std::vector<int>::~vector(&Suit);
  return v6;
}


#####################################
int32_t __cdecl CExtEquip::GetWingEquipCount6SuitId(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int v3; // ebx
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  int32_t SuitId; // [rsp+48h] [rbp-28h]
  int32_t j; // [rsp+4Ch] [rbp-24h]
  const MemChrBag *curEquip; // [rsp+50h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+58h] [rbp-18h]

  SuitId = 0;
  for ( j = 44; j <= 49; ++j )
  {
    curEquip = &this->m_vMemEquip[j];
    if ( curEquip->srcId <= 0 || curEquip->itemClass != 2 )
      return 0;
    srcId = curEquip->srcId;
    v2 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v2, srcId);
    if ( equip.base == curEquip->itemId )
    {
      itemId = this->m_vMemEquip[j].itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_nSuitId2 > 0 )
        {
          if ( SuitId )
          {
            if ( pCfgEquip->m_nSuitId2 < SuitId )
              SuitId = pCfgEquip->m_nSuitId2;
          }
          else
          {
            SuitId = pCfgEquip->m_nSuitId2;
          }
          v3 = 1;
        }
        else
        {
          SuitId = 0;
          v3 = 0;
        }
      }
      else
      {
        SuitId = 0;
        v3 = 0;
      }
    }
    else
    {
      SuitId = 0;
      v3 = 0;
    }
    MemEquip::~MemEquip(&equip);
    if ( !v3 )
      return SuitId;
  }
  return SuitId;
}


#####################################
int32_t __cdecl CExtEquip::GetCount6SuitId(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int32_t itemId; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v6; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v8; // rax
  MemEquip equip; // [rsp+10h] [rbp-80h] BYREF
  Int32Vector Suit; // [rsp+50h] [rbp-40h] BYREF
  int32_t j; // [rsp+6Ch] [rbp-24h]
  const MemChrBag *curEquip; // [rsp+70h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+78h] [rbp-18h]

  std::vector<int>::vector(&Suit);
  for ( j = 21; j <= 32; ++j )
  {
    curEquip = &this->m_vMemEquip[j];
    if ( curEquip->srcId > 0 && curEquip->itemClass == 2 )
    {
      srcId = curEquip->srcId;
      v2 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v2, srcId);
      if ( equip.base == curEquip->itemId )
      {
        itemId = this->m_vMemEquip[j].itemId;
        v4 = Answer::Singleton<CfgData>::instance();
        EquipTable = CfgData::GetEquipTable(v4);
        pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
        if ( pCfgEquip )
        {
          if ( pCfgEquip->m_nSuitId > 0 )
            std::vector<int>::push_back(&Suit, &pCfgEquip->m_nSuitId);
        }
      }
      MemEquip::~MemEquip(&equip);
    }
  }
  if ( std::vector<int>::size(&Suit) > 5 )
  {
    M_current = std::vector<int>::end(&Suit)._M_current;
    v8._M_current = std::vector<int>::begin(&Suit)._M_current;
    std::sort<__gnu_cxx::__normal_iterator<int *,std::vector<int>>,bool (*)(int const&,int const&)>(
      v8,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current,
      (bool (*)(const int32_t *, const int32_t *))comp);
    v6 = *std::vector<int>::operator[](&Suit, 5u);
  }
  else
  {
    v6 = 0;
  }
  std::vector<int>::~vector(&Suit);
  return v6;
}


#####################################
int32_t __cdecl CExtEquip::GetCount12SuitId(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int v3; // ebx
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  int32_t SuitId; // [rsp+48h] [rbp-28h]
  int32_t j; // [rsp+4Ch] [rbp-24h]
  const MemChrBag *curEquip; // [rsp+50h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+58h] [rbp-18h]

  SuitId = 0;
  for ( j = 21; j <= 32; ++j )
  {
    curEquip = &this->m_vMemEquip[j];
    if ( curEquip->srcId <= 0 || curEquip->itemClass != 2 )
      return 0;
    srcId = curEquip->srcId;
    v2 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v2, srcId);
    if ( equip.base == curEquip->itemId )
    {
      itemId = this->m_vMemEquip[j].itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( pCfgEquip->m_nSuitId2 > 0 )
        {
          if ( SuitId )
          {
            if ( pCfgEquip->m_nSuitId2 < SuitId )
              SuitId = pCfgEquip->m_nSuitId2;
          }
          else
          {
            SuitId = pCfgEquip->m_nSuitId2;
          }
          v3 = 1;
        }
        else
        {
          SuitId = 0;
          v3 = 0;
        }
      }
      else
      {
        SuitId = 0;
        v3 = 0;
      }
    }
    else
    {
      SuitId = 0;
      v3 = 0;
    }
    MemEquip::~MemEquip(&equip);
    if ( !v3 )
      return SuitId;
  }
  return SuitId;
}


#####################################
int32_t __cdecl CExtEquip::GetWeaponBless(CExtEquip *const this)
{
  int32_t Lucky; // ebx
  EquipId_t srcId; // r12
  CEquipManager *v3; // rax
  int v4; // r12d
  MemEquip equip; // [rsp+10h] [rbp-50h] BYREF
  MemChrBag *weapon; // [rsp+48h] [rbp-18h]

  weapon = this->m_vMemEquip;
  if ( this->m_vMemEquip[0].srcId <= 0 || weapon->itemId <= 0 )
    return 0;
  srcId = this->m_vMemEquip[0].srcId;
  v3 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::GetMemEquip(&equip, v3, srcId);
  if ( equip.base == weapon->itemId )
  {
    Lucky = equip.Lucky;
    v4 = 0;
  }
  else
  {
    v4 = 1;
  }
  MemEquip::~MemEquip(&equip);
  if ( v4 == 1 )
    return 0;
  return Lucky;
}


#####################################
void __cdecl CExtEquip::SetWeaponBless(CExtEquip *const this, int32_t nBless)
{
  EquipId_t srcId; // rbx
  CEquipManager *v3; // rax
  int64_t v4; // rbx
  int32_t Lucky; // r12d
  int32_t MapId; // eax
  DBService *v7; // rax
  CEquipManager *v8; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v10; // rax
  char LogString[4096]; // [rsp+20h] [rbp-1070h] BYREF
  MemEquip equip; // [rsp+1020h] [rbp-70h] BYREF
  Generallog stuLog; // [rsp+1060h] [rbp-30h] BYREF
  MemChrBag *weapon; // [rsp+1078h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    weapon = this->m_vMemEquip;
    if ( this->m_vMemEquip[0].srcId > 0 && weapon->itemId > 0 )
    {
      srcId = this->m_vMemEquip[0].srcId;
      v3 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v3, srcId);
      if ( equip.base == weapon->itemId && equip.Lucky != nBless )
      {
        memset(&stuLog, 0, sizeof(stuLog));
        std::string::string(&stuLog.sString);
        stuLog.nCid = Player::getCid(this->m_pPlayer);
        stuLog.Time = Unit::getNow(this->m_pPlayer);
        memset(LogString, 0, sizeof(LogString));
        v4 = this->m_vMemEquip[0].srcId;
        Lucky = equip.Lucky;
        MapId = StaticObj::getMapId(this->m_pPlayer);
        snprintf(LogString, 0xFFFu, "Bless mapId =%d,old=%d,new=%d,srcid=%lld\n", MapId, Lucky, nBless, v4);
        std::string::operator=(&stuLog.sString, LogString);
        LOBYTE(v4) = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<DBService>::instance();
        DBService::logGeneral(v7, v4, &stuLog);
        equip.Lucky = nBless;
        LOBYTE(v4) = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::UpdateMemEquip(v8, v4, &equip, 1404);
        m_pPlayer = this->m_pPlayer;
        v10 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::SendPlayerEquipInfo(v10, m_pPlayer, &equip);
        Generallog::~Generallog(&stuLog);
      }
      MemEquip::~MemEquip(&equip);
    }
  }
}


#####################################
void __cdecl CExtEquip::checkEquipSuit(CExtEquip *const this, bool IsGongGao)
{
  int32_t v2; // eax
  int32_t v3; // eax
  int32_t v4; // eax
  int32_t v5; // eax
  int v6; // eax
  int v7; // eax
  EquipId_t srcId; // rbx
  CEquipManager *v9; // rax
  int v10; // ebx
  int32_t itemId; // ebx
  CfgData *v12; // rax
  const CfgEquipTable *EquipTable; // rax
  int8_t ConnId; // bl
  GameService *v15; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v18; // bl
  GameService *v19; // rax
  int32_t v20; // eax
  MemEquip equip; // [rsp+10h] [rbp-E0h] BYREF
  int32_t MaxSuitId2; // [rsp+50h] [rbp-A0h] BYREF
  int32_t MaxSuitId; // [rsp+54h] [rbp-9Ch] BYREF
  int32_t MinRingSuit; // [rsp+58h] [rbp-98h] BYREF
  int32_t MaxRingSuit; // [rsp+5Ch] [rbp-94h] BYREF
  int32_t SuitId_1; // [rsp+60h] [rbp-90h] BYREF
  int32_t SuitId_0; // [rsp+64h] [rbp-8Ch] BYREF
  int32_t nGongMingSuit; // [rsp+68h] [rbp-88h] BYREF
  int32_t WingSuit6; // [rsp+6Ch] [rbp-84h] BYREF
  int32_t WingSuit3; // [rsp+70h] [rbp-80h] BYREF
  int32_t Suit6; // [rsp+74h] [rbp-7Ch] BYREF
  int32_t Suit12; // [rsp+78h] [rbp-78h] BYREF
  int32_t SuitId; // [rsp+7Ch] [rbp-74h] BYREF
  std::string val; // [rsp+80h] [rbp-70h] BYREF
  int32_t Count; // [rsp+90h] [rbp-60h]
  int32_t SuitBaseId; // [rsp+94h] [rbp-5Ch]
  int32_t LeftGlove; // [rsp+98h] [rbp-58h]
  int32_t RightGlove; // [rsp+9Ch] [rbp-54h]
  int32_t MaxGloveSlot; // [rsp+A0h] [rbp-50h]
  int32_t MinGloveSlot; // [rsp+A4h] [rbp-4Ch]
  int32_t LeftRingSuit; // [rsp+A8h] [rbp-48h]
  int32_t RightRingSuit; // [rsp+ACh] [rbp-44h]
  int32_t MinRingSlot; // [rsp+B0h] [rbp-40h]
  int32_t SuitId1; // [rsp+B4h] [rbp-3Ch]
  int32_t SuitId2; // [rsp+B8h] [rbp-38h]
  int32_t SuitId3; // [rsp+BCh] [rbp-34h]
  int32_t SuitId4; // [rsp+C0h] [rbp-30h]
  int32_t j; // [rsp+C4h] [rbp-2Ch]
  const MemChrBag *curEquip; // [rsp+C8h] [rbp-28h]
  const CfgEquip *pCfgEquip; // [rsp+D0h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+D8h] [rbp-18h]

  std::list<int>::clear(&this->m_EquipSuit);
  SuitId_0 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[1].itemId, this->m_vMemEquip[6].itemId);
  if ( SuitId_0 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &SuitId_0);
  SuitId_1 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[4].itemId, this->m_vMemEquip[5].itemId);
  if ( SuitId_1 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &SuitId_1);
  SuitBaseId = CExtEquip::CheckSuitId(this, this->m_vMemEquip[3].itemId, this->m_vMemEquip[8].itemId);
  if ( SuitBaseId <= 0 )
  {
    SuitId1 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[3].itemId, this->m_vMemEquip[7].itemId);
    SuitId2 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[3].itemId, this->m_vMemEquip[9].itemId);
    if ( SuitId1 <= SuitId2 )
      v6 = SuitId2;
    else
      v6 = SuitId1;
    MaxSuitId = v6;
    if ( v6 > 0 )
      std::list<int>::push_back(&this->m_EquipSuit, &MaxSuitId);
    SuitId3 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[8].itemId, this->m_vMemEquip[7].itemId);
    SuitId4 = CExtEquip::CheckSuitId(this, this->m_vMemEquip[8].itemId, this->m_vMemEquip[9].itemId);
    if ( SuitId3 <= SuitId4 )
      v7 = SuitId4;
    else
      v7 = SuitId3;
    MaxSuitId2 = v7;
    if ( v7 > 0 )
      std::list<int>::push_back(&this->m_EquipSuit, &MaxSuitId2);
  }
  else
  {
    LeftGlove = CExtEquip::GetEquipSuitId(this, this->m_vMemEquip[3].itemId);
    RightGlove = CExtEquip::GetEquipSuitId(this, this->m_vMemEquip[8].itemId);
    if ( LeftGlove <= RightGlove )
      v2 = 8;
    else
      v2 = 3;
    MaxGloveSlot = v2;
    if ( LeftGlove <= RightGlove )
      v3 = 3;
    else
      v3 = 8;
    MinGloveSlot = v3;
    LeftRingSuit = CExtEquip::CheckSuitId(this, this->m_vMemEquip[MaxGloveSlot].itemId, this->m_vMemEquip[7].itemId);
    RightRingSuit = CExtEquip::CheckSuitId(this, this->m_vMemEquip[MaxGloveSlot].itemId, this->m_vMemEquip[9].itemId);
    if ( LeftRingSuit <= RightRingSuit )
      v4 = RightRingSuit;
    else
      v4 = LeftRingSuit;
    MaxRingSuit = v4;
    if ( LeftRingSuit <= RightRingSuit )
      v5 = 7;
    else
      v5 = 9;
    MinRingSlot = v5;
    if ( MaxRingSuit > 0 )
      std::list<int>::push_back(&this->m_EquipSuit, &MaxRingSuit);
    MinRingSuit = CExtEquip::CheckSuitId(
                    this,
                    this->m_vMemEquip[MinGloveSlot].itemId,
                    this->m_vMemEquip[MinRingSlot].itemId);
    if ( MinRingSuit > 0 )
      std::list<int>::push_back(&this->m_EquipSuit, &MinRingSuit);
  }
  SuitId = 0;
  Count = 0;
  for ( j = 11; j <= 20; ++j )
  {
    curEquip = &this->m_vMemEquip[j];
    if ( curEquip->srcId <= 0 || curEquip->itemClass != 2 )
    {
      SuitId = 0;
      Count = 0;
      break;
    }
    srcId = curEquip->srcId;
    v9 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v9, srcId);
    if ( equip.base != curEquip->itemId )
    {
      SuitId = 0;
      Count = 0;
      v10 = 0;
      goto LABEL_56;
    }
    itemId = this->m_vMemEquip[j].itemId;
    v12 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v12);
    pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( !pCfgEquip )
    {
      SuitId = 0;
      Count = 0;
      v10 = 0;
      goto LABEL_56;
    }
    if ( pCfgEquip->m_nSuitId <= 0 || SuitId )
    {
      if ( pCfgEquip->m_nSuitId > 0 && pCfgEquip->m_nSuitId < SuitId )
        SuitId = pCfgEquip->m_nSuitId;
    }
    else
    {
      SuitId = pCfgEquip->m_nSuitId;
    }
    if ( pCfgEquip->m_nSuitId > 0 && SuitId > 0 )
      ++Count;
    if ( SuitId > 0 && Count == 10 )
    {
      std::list<int>::push_back(&this->m_EquipSuit, &SuitId);
      if ( IsGongGao )
      {
        ConnId = Player::getConnId(this->m_pPlayer);
        v15 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v15, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet )
        {
          v10 = 1;
          goto LABEL_56;
        }
        Answer::NetPacket::writeInt32(packet, 410);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Cid = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, Cid);
        Answer::NetPacket::writeInt32(packet, SuitId);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v18 = Player::getConnId(this->m_pPlayer);
        v19 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v19, v18, packet);
      }
    }
    v10 = 2;
LABEL_56:
    MemEquip::~MemEquip(&equip);
    if ( !v10 )
      break;
    if ( v10 == 1 )
      return;
  }
  Suit12 = CExtEquip::GetCount12SuitId(this);
  if ( Suit12 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &Suit12);
  Suit6 = CExtEquip::GetCount6SuitId(this);
  if ( Suit6 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &Suit6);
  WingSuit3 = CExtEquip::GetWingEquipCount3SuitId(this);
  if ( WingSuit3 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &WingSuit3);
  WingSuit6 = CExtEquip::GetWingEquipCount6SuitId(this);
  if ( WingSuit6 > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &WingSuit6);
  nGongMingSuit = CExtEquip::checkGongMingSuit(this);
  if ( nGongMingSuit > 0 )
    std::list<int>::push_back(&this->m_EquipSuit, &nGongMingSuit);
  v20 = std::list<int>::size(&this->m_EquipSuit);
  Player::updateRecord(this->m_pPlayer, 4, v20);
}


#####################################
int32_t __cdecl CExtEquip::GetAddGemCount(CExtEquip *const this, int32_t nLevel)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  int32_t nCount; // [rsp+1Ch] [rbp-24h]
  int32_t i; // [rsp+20h] [rbp-20h]
  int32_t j; // [rsp+24h] [rbp-1Ch]
  const CfgItemGem *pGem; // [rsp+28h] [rbp-18h]

  nCount = 0;
  for ( i = 0; i <= 9; ++i )
  {
    for ( j = 0; j <= 3; ++j )
    {
      if ( this->m_vMemGem[i][j] > 0 )
      {
        v2 = this->m_vMemGem[i][j];
        v3 = Answer::Singleton<CfgData>::instance();
        ItemGemTable = CfgData::GetItemGemTable(v3);
        pGem = CfgItemGemTable::GetItemGem(ItemGemTable, v2);
        if ( pGem )
        {
          if ( pGem->m_nLevel >= nLevel )
            ++nCount;
        }
      }
    }
  }
  return nCount;
}


#####################################
int32_t __cdecl CExtEquip::GetQualityCount(CExtEquip *const this, int32_t nQuality)
{
  int32_t itemId; // ebx
  CfgData *v3; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t nCount; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+14h] [rbp-1Ch]
  const CfgEquip *pEquip; // [rsp+18h] [rbp-18h]

  nCount = 0;
  for ( i = 0; i <= 92; ++i )
  {
    itemId = this->m_vMemEquip[i].itemId;
    v3 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v3);
    pEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( pEquip && pEquip->m_nQuality >= nQuality )
      ++nCount;
  }
  return nCount;
}


#####################################
void __cdecl CExtEquip::clearGemInfo(CExtEquip *const this)
{
  int8_t i; // [rsp+16h] [rbp-2h]
  int8_t j; // [rsp+17h] [rbp-1h]

  for ( i = 0; i <= 9; ++i )
  {
    for ( j = 0; j <= 3; ++j )
      this->m_vMemGem[i][j] = -1;
  }
}


#####################################
std::string __cdecl CExtEquip::saveGemString(CExtEquip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[366]; // [rsp+20h] [rbp-180h] BYREF
  int8_t i; // [rsp+18Eh] [rbp-12h]
  int8_t j; // [rsp+18Fh] [rbp-11h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 9; ++i )
  {
    if ( i )
      std::operator<<<std::char_traits<char>>(v5, L"|1");
    for ( j = 0; j <= 3; ++j )
    {
      if ( j )
        std::operator<<<std::char_traits<char>>(v5, ":");
      std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (4LL * i + j + 748)));
    }
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CExtEquip::loadGemString(CExtEquip *const this, const std::string *const str)
{
  std::string *v2; // rax
  int v3; // ebx
  int v4; // ebx
  int v5; // r12d
  std::string *v6; // rax
  const char *v7; // rax
  StringVector vGem; // [rsp+10h] [rbp-70h] BYREF
  StringVector vStr; // [rsp+30h] [rbp-50h] BYREF
  std::string delims; // [rsp+50h] [rbp-30h] BYREF
  char v11; // [rsp+5Fh] [rbp-21h] BYREF
  std::string v12; // [rsp+60h] [rbp-20h] BYREF
  char v13; // [rsp+6Dh] [rbp-13h] BYREF
  int8_t i; // [rsp+6Eh] [rbp-12h]
  int8_t j; // [rsp+6Fh] [rbp-11h]

  if ( !(unsigned __int8)std::string::empty((std::string *)str) )
  {
    std::allocator<char>::allocator(&v11);
    std::string::string(&delims, L"|1", &v11);
    Answer::StringUtility::split(&vStr, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v11);
    if ( std::vector<std::string>::size(&vStr) == 10 )
    {
      for ( i = 0; i <= 9; ++i )
      {
        std::allocator<char>::allocator(&v13);
        std::string::string(&v12, ":", &v13);
        v2 = std::vector<std::string>::operator[](&vStr, i);
        Answer::StringUtility::split(&vGem, v2, &v12, 0);
        std::string::~string(&v12);
        std::allocator<char>::~allocator(&v13);
        if ( std::vector<std::string>::size(&vGem) == 4 )
        {
          for ( j = 0; j <= 3; ++j )
          {
            v4 = i;
            v5 = j;
            v6 = std::vector<std::string>::operator[](&vGem, j);
            v7 = (const char *)std::string::c_str(v6);
            this->m_vMemGem[v4][v5] = atoi(v7);
          }
          v3 = 1;
        }
        else
        {
          v3 = 0;
        }
        std::vector<std::string>::~vector(&vGem);
        if ( !v3 )
          break;
      }
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CExtEquip::savePosLevelString(CExtEquip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[367]; // [rsp+20h] [rbp-180h] BYREF
  int8_t i; // [rsp+18Fh] [rbp-11h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 9; ++i )
  {
    if ( i )
      std::operator<<<std::char_traits<char>>(v5, L"|1");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (i + 788LL)));
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CExtEquip::loadPosLevelString(CExtEquip *const this, const std::string *const str)
{
  int v2; // ebx
  std::string *v3; // rax
  const char *v4; // rax
  StringVector vStr; // [rsp+10h] [rbp-40h] BYREF
  std::string delims; // [rsp+30h] [rbp-20h] BYREF
  char v7; // [rsp+3Eh] [rbp-12h] BYREF
  int8_t i; // [rsp+3Fh] [rbp-11h]

  if ( !(unsigned __int8)std::string::empty((std::string *)str) )
  {
    std::allocator<char>::allocator(&v7);
    std::string::string(&delims, L"|1", &v7);
    Answer::StringUtility::split(&vStr, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v7);
    if ( std::vector<std::string>::size(&vStr) == 10 )
    {
      for ( i = 0; i <= 9; ++i )
      {
        v2 = i;
        v3 = std::vector<std::string>::operator[](&vStr, i);
        v4 = (const char *)std::string::c_str(v3);
        this->m_vMemPosLevel[v2] = atoi(v4);
      }
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CExtEquip::saveStrengthenString(CExtEquip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[367]; // [rsp+20h] [rbp-180h] BYREF
  int8_t i; // [rsp+18Fh] [rbp-11h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 9; ++i )
  {
    if ( i )
      std::operator<<<std::char_traits<char>>(v5, L"|1");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (i + 796LL) + 8));
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CExtEquip::LoadStrengthenString(CExtEquip *const this, const std::string *const str)
{
  int v2; // ebx
  std::string *v3; // rax
  const char *v4; // rax
  StringVector vStr; // [rsp+10h] [rbp-40h] BYREF
  std::string delims; // [rsp+30h] [rbp-20h] BYREF
  char v7; // [rsp+3Eh] [rbp-12h] BYREF
  int8_t i; // [rsp+3Fh] [rbp-11h]

  if ( !(unsigned __int8)std::string::empty((std::string *)str) )
  {
    std::allocator<char>::allocator(&v7);
    std::string::string(&delims, L"|1", &v7);
    Answer::StringUtility::split(&vStr, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v7);
    if ( std::vector<std::string>::size(&vStr) == 10 )
    {
      for ( i = 0; i <= 9; ++i )
      {
        v2 = i;
        v3 = std::vector<std::string>::operator[](&vStr, i);
        v4 = (const char *)std::string::c_str(v3);
        this->m_vMemStrengthen[v2] = atoi(v4);
      }
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CExtEquip::saveShenYaoString(CExtEquip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[367]; // [rsp+20h] [rbp-180h] BYREF
  int8_t i; // [rsp+18Fh] [rbp-11h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 9; ++i )
  {
    if ( i )
      std::operator<<<std::char_traits<char>>(v5, L"|1");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (i + 808LL)));
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CExtEquip::LoadShenYaoString(CExtEquip *const this, const std::string *const str)
{
  int v2; // ebx
  std::string *v3; // rax
  const char *v4; // rax
  StringVector vStr; // [rsp+10h] [rbp-40h] BYREF
  std::string delims; // [rsp+30h] [rbp-20h] BYREF
  char v7; // [rsp+3Eh] [rbp-12h] BYREF
  int8_t i; // [rsp+3Fh] [rbp-11h]

  if ( !(unsigned __int8)std::string::empty((std::string *)str) )
  {
    std::allocator<char>::allocator(&v7);
    std::string::string(&delims, L"|1", &v7);
    Answer::StringUtility::split(&vStr, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v7);
    if ( std::vector<std::string>::size(&vStr) == 10 )
    {
      for ( i = 0; i <= 9; ++i )
      {
        v2 = i;
        v3 = std::vector<std::string>::operator[](&vStr, i);
        v4 = (const char *)std::string::c_str(v3);
        this->m_vShenYaoEquipPos[v2] = atoi(v4);
      }
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
void __cdecl CExtEquip::updateEquipGem(CExtEquip *const this)
{
  int32_t m_nEquipGem; // ebx
  CSevenDayTask *CSevenDayTask; // rax
  int32_t nSumValue; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nSumValue = CExtEquip::GetEquipAllGemLevel(this);
    if ( this->m_nEquipGem != nSumValue )
    {
      this->m_nEquipGem = nSumValue;
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_EQUIP_GEM, this->m_nEquipGem);
      m_nEquipGem = this->m_nEquipGem;
      CSevenDayTask = Player::GetCSevenDayTask(this->m_pPlayer);
      CSevenDayTask::UpdateTaskState(CSevenDayTask, 5, m_nEquipGem, 1);
    }
  }
}


#####################################
void __cdecl CExtEquip::updateEquipStar(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  MemEquip equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t nSumValue; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  nSumValue = 0;
  for ( i = 0; i <= 92; ++i )
  {
    if ( this->m_vMemEquip[i].srcId > 0 )
    {
      srcId = this->m_vMemEquip[i].srcId;
      v2 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v2, srcId);
      if ( equip.base == this->m_vMemEquip[i].itemId )
        nSumValue += equip.star;
      MemEquip::~MemEquip(&equip);
    }
  }
  if ( this->m_nEquipStar != nSumValue )
  {
    this->m_nEquipStar = nSumValue;
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_EQUIP_STAR, this->m_nEquipStar);
  }
}


#####################################
int32_t __cdecl CExtEquip::CheckSuitId(CExtEquip *const this, int32_t nSrcId, int32_t DesId)
{
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t m_nSuitId; // ebx
  CfgData *v7; // rax
  const CfgEquipTable *v8; // rax
  CfgData *v9; // rax
  const CfgEquipTable *v10; // rax
  const CfgEquip *pCfgSrcEquip; // [rsp+18h] [rbp-28h]
  const CfgEquipSuit *pSuitCFG; // [rsp+20h] [rbp-20h]
  const CfgEquip *pDesCfgEquip; // [rsp+28h] [rbp-18h]

  if ( nSrcId <= 0 || DesId <= 0 )
    return 0;
  v4 = Answer::Singleton<CfgData>::instance();
  EquipTable = CfgData::GetEquipTable(v4);
  pCfgSrcEquip = CfgEquipTable::GetEquip(EquipTable, nSrcId);
  if ( !pCfgSrcEquip )
    return 0;
  m_nSuitId = pCfgSrcEquip->m_nSuitId;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetEquipTable(v7);
  pSuitCFG = CfgEquipTable::GetEquipSuit(v8, m_nSuitId);
  if ( !pSuitCFG )
    return 0;
  v9 = Answer::Singleton<CfgData>::instance();
  v10 = CfgData::GetEquipTable(v9);
  pDesCfgEquip = CfgEquipTable::GetEquip(v10, DesId);
  if ( !pDesCfgEquip )
    return 0;
  if ( !CfgEquipSuit::IsInIdList(pSuitCFG, pDesCfgEquip->m_nSuitId) )
    return 0;
  if ( pCfgSrcEquip->m_nSuitId > pDesCfgEquip->m_nSuitId )
    return pDesCfgEquip->m_nSuitId;
  return pCfgSrcEquip->m_nSuitId;
}


#####################################
int32_t __cdecl CExtEquip::GetEquipSuitId(CExtEquip *const this, int32_t nId)
{
  CfgData *v2; // rax
  const CfgEquipTable *EquipTable; // rax
  const CfgEquip *pCfgEquip; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<CfgData>::instance();
  EquipTable = CfgData::GetEquipTable(v2);
  pCfgEquip = CfgEquipTable::GetEquip(EquipTable, nId);
  if ( pCfgEquip )
    return pCfgEquip->m_nSuitId;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtEquip::checkGongMingSuit(CExtEquip *const this)
{
  EquipId_t srcId; // rbx
  CEquipManager *v2; // rax
  int v3; // ebx
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t m_nSuitId; // eax
  CExtCharPet *CharPet; // rax
  CExtCharPet *v10; // rax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  int32_t nSuitId; // [rsp+48h] [rbp-28h]
  int8_t i; // [rsp+4Fh] [rbp-21h]
  const MemChrBag *item; // [rsp+50h] [rbp-20h]
  const CfgEquip *pCfgEquip; // [rsp+58h] [rbp-18h]

  nSuitId = 0;
  for ( i = 59; i <= 64; ++i )
  {
    item = &this->m_vMemEquip[i];
    if ( item->srcId <= 0 || item->itemClass != 2 )
    {
      nSuitId = 0;
      break;
    }
    srcId = item->srcId;
    v2 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::GetMemEquip(&equip, v2, srcId);
    if ( equip.base == item->itemId )
    {
      itemId = item->itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      EquipTable = CfgData::GetEquipTable(v5);
      pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
      if ( pCfgEquip )
      {
        if ( nSuitId )
        {
          if ( pCfgEquip->m_nSuitId >= nSuitId )
            m_nSuitId = nSuitId;
          else
            m_nSuitId = pCfgEquip->m_nSuitId;
          nSuitId = m_nSuitId;
        }
        else
        {
          nSuitId = pCfgEquip->m_nSuitId;
        }
        v3 = 1;
      }
      else
      {
        nSuitId = 0;
        v3 = 0;
      }
    }
    else
    {
      nSuitId = 0;
      v3 = 0;
    }
    MemEquip::~MemEquip(&equip);
    if ( !v3 )
      break;
  }
  if ( this->m_nGongMingSuitId != nSuitId )
  {
    this->m_nGongMingSuitId = nSuitId;
    CExtEquip::CheckGongMingSuitBuff(this);
    if ( nSuitId <= 0 )
    {
      CharPet = Player::GetCharPet(this->m_pPlayer);
      if ( CExtCharPet::IsFitting(CharPet) )
      {
        v10 = Player::GetCharPet(this->m_pPlayer);
        CExtCharPet::onRestPet(v10);
      }
    }
  }
  return nSuitId;
}


#####################################
void __cdecl CExtEquip::CheckGongMingSuitBuff(CExtEquip *const this)
{
  CExtCharPet *CharPet; // rax
  int32_t m_nGongMingSuitId; // ebx
  CfgData *v3; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t m_nGongMingSuitBuff; // ebx
  CfgData *v6; // rax
  int32_t v7; // edx
  Buff *v8; // rbx
  AttrAddon attr; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<const BuffAttr*,std::vector<BuffAttr> > iter; // [rsp+30h] [rbp-80h] BYREF
  AttrAddonList lstAttr; // [rsp+40h] [rbp-70h] BYREF
  UnitHandle launcher; // [rsp+50h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<BuffAttr*,std::vector<BuffAttr> > __i; // [rsp+60h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<BuffAttr*,std::vector<BuffAttr> > __rhs; // [rsp+70h] [rbp-40h] BYREF
  const CfgEquipSuit *pSuit; // [rsp+78h] [rbp-38h]
  CfgBuff *pCfgBuff; // [rsp+80h] [rbp-30h]
  Buff *pBuff; // [rsp+88h] [rbp-28h]

  if ( this->m_nGongMingSuitBuff > 0 )
  {
    Unit::removeBuff(this->m_pPlayer, this->m_nGongMingSuitBuff);
    this->m_nGongMingSuitBuff = 0;
    Player::recalcAttr(this->m_pPlayer, 0, 0);
  }
  CharPet = Player::GetCharPet(this->m_pPlayer);
  if ( CExtCharPet::IsFitting(CharPet) )
  {
    m_nGongMingSuitId = this->m_nGongMingSuitId;
    v3 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v3);
    pSuit = CfgEquipTable::GetEquipSuit(EquipTable, m_nGongMingSuitId);
    if ( pSuit )
    {
      if ( pSuit->m_nBuffId > 0 )
      {
        this->m_nGongMingSuitBuff = pSuit->m_nBuffId;
        m_nGongMingSuitBuff = this->m_nGongMingSuitBuff;
        v6 = Answer::Singleton<CfgData>::instance();
        pCfgBuff = CfgData::getBuff(v6, m_nGongMingSuitBuff);
        if ( pCfgBuff )
        {
          launcher.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
          launcher.type = v7;
          v8 = (Buff *)operator new(0x60u);
          Buff::Buff(v8, this->m_pPlayer, pCfgBuff, &launcher, 4, 1);
          pBuff = v8;
          if ( v8 )
          {
            Unit::addBuff(this->m_pPlayer, pBuff);
            std::list<AttrAddon>::list(&lstAttr);
            __i._M_current = std::vector<BuffAttr>::begin(&pCfgBuff->buffAttr)._M_current;
            __gnu_cxx::__normal_iterator<BuffAttr const*,std::vector<BuffAttr>>::__normal_iterator<BuffAttr*>(
              &iter,
              &__i);
            while ( 1 )
            {
              __rhs._M_current = std::vector<BuffAttr>::end(&pCfgBuff->buffAttr)._M_current;
              if ( !__gnu_cxx::operator!=<BuffAttr const*,BuffAttr*,std::vector<BuffAttr>>(&iter, &__rhs) )
                break;
              attr = 0;
              attr.index = __gnu_cxx::__normal_iterator<BuffAttr const*,std::vector<BuffAttr>>::operator->(&iter)->attr;
              attr.addon = __gnu_cxx::__normal_iterator<BuffAttr const*,std::vector<BuffAttr>>::operator->(&iter)->addon;
              std::list<AttrAddon>::push_back(&lstAttr, &attr);
              __gnu_cxx::__normal_iterator<BuffAttr const*,std::vector<BuffAttr>>::operator++(&iter);
            }
            Player::sendAttrAddon(this->m_pPlayer, &lstAttr);
            std::list<AttrAddon>::~list(&lstAttr);
          }
        }
        Player::recalcAttr(this->m_pPlayer, 0, 0);
      }
    }
  }
}


#####################################
int32_t __cdecl CExtEquip::GetGongMingBuffBattle(const CExtEquip *const this)
{
  int32_t m_nGongMingSuitBuff; // ebx
  CfgData *v2; // rax
  CfgBuff *pCfgBuff; // [rsp+18h] [rbp-18h]

  if ( this->m_nGongMingSuitBuff > 0
    && (m_nGongMingSuitBuff = this->m_nGongMingSuitBuff,
        v2 = Answer::Singleton<CfgData>::instance(),
        (pCfgBuff = CfgData::getBuff(v2, m_nGongMingSuitBuff)) != 0) )
  {
    return pCfgBuff->battle;
  }
  else
  {
    return 0;
  }
}


