// Decompiled methods for class: CExtCurrency
// Source: gameserver.cc
// Total methods: 18

#####################################
void __cdecl CExtCurrency::~CExtCurrency(CExtCurrency *const this)
{
  CExtCurrency::~CExtCurrency(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCurrency::OnCleanUp(CExtCurrency *const this)
{
  this->m_bNeedSync = 0;
  bzero(this->m_aCurrency, 0x60u);
  bzero(this->m_aUpdateSign, 0xCu);
}


#####################################
void __cdecl CExtCurrency::SynCurrency(CExtCurrency *const this)
{
  if ( this->m_bNeedSync )
  {
    this->m_bNeedSync = 0;
    CExtCurrency::SendCurrencyInfo(this, 0);
  }
}


#####################################
void __cdecl CExtCurrency::OnLoadFromDB(CExtCurrency *const this, const PlayerDBData *const dbData)
{
  memcpy(this->m_aCurrency, dbData->m_CurrencyData.vCurrency, sizeof(this->m_aCurrency));
}


#####################################
void __cdecl CExtCurrency::OnSaveToDB(CExtCurrency *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->m_CurrencyData.vCurrency, this->m_aCurrency, sizeof(dbData->m_CurrencyData.vCurrency));
}


#####################################
void __cdecl CExtCurrency::GetInterestsProtocol(CExtCurrency *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 20074;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 660;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 20190;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CExtCurrency::DispatchNetDatas(CExtCurrency *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x4E6Au:
      return CExtCurrency::onSocialAddCurrency(this, inPacket);
    case 0x4EDEu:
      return CExtCurrency::syncGold(this, inPacket);
    case 0x294u:
      return CExtCurrency::OnCurrencyDuiHuan(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCurrency::onSocialAddCurrency(CExtCurrency *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int8_t nCurrency; // [rsp+17h] [rbp-19h]
  int nCount; // [rsp+18h] [rbp-18h]
  CURRENCY_CHANGE_REASON nReason; // [rsp+1Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nCurrency = Answer::NetPacket::readInt8(inPacket);
  nCount = Answer::NetPacket::readInt32(inPacket);
  nReason = Answer::NetPacket::readInt32(inPacket);
  if ( nCount < 0 )
  {
    CExtCurrency::DecCurrency(this, (const CURRENCY_TYPE)nCurrency, -nCount, nReason, 0);
  }
  else
  {
    CExtCurrency::AddCurrency(this, (const CURRENCY_TYPE)nCurrency, nCount, nReason, 0);
    if ( nReason == CURRENCY_CHANGE_REASON::GCR_FAMILY_OPEN_RED_PACKET )
    {
      if ( nCurrency == 1 )
      {
        OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1064, nCount);
      }
      else if ( nCurrency == 2 )
      {
        v4 = Player::GetOperateLimit(this->m_pPlayer);
        CExtOperateLimit::AddLimitCount(v4, 1128, nCount);
      }
    }
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCurrency::OnCurrencyDuiHuan(CExtCurrency *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  int32_t Record; // eax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int Double; // [rsp+1Ch] [rbp-34h]
  DuiHuanLimit *pCfg; // [rsp+20h] [rbp-30h]
  int32_t Rate; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Double = Answer::NetPacket::readInt32(inPacket);
  v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetDuiHuanLimitCount(v4, v3);
  if ( !pCfg )
    return 10002;
  if ( pCfg->ConstCurrency <= 0 || pCfg->ConstGold <= 0 || pCfg->ShengYaoBi <= 0 || pCfg->Limit <= 0 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 2102) >= pCfg->Limit )
    return 10002;
  Rate = 1;
  if ( Double > 0 )
  {
    if ( CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD) < pCfg->ConstGold )
      return 10002;
    Rate = 2;
  }
  if ( !CExtCurrency::DecMoneyAndNoBind(this, pCfg->ConstCurrency, CURRENCY_CHANGE_REASON::MCR_CURRENCY_DUI_HUAN, 0) )
    return 10002;
  if ( Double > 0
    && !CExtCurrency::DecCurrency(
          this,
          CURRENCY_TYPE::CURRENCY_GOLD,
          pCfg->ConstGold,
          CURRENCY_CHANGE_REASON::MCR_CURRENCY_DUI_HUAN,
          0) )
  {
    return 10002;
  }
  CExtCurrency::AddCurrency(
    this,
    CURRENCY_TYPE::CURRENCY_VIGOUR,
    Rate * pCfg->ShengYaoBi,
    CURRENCY_CHANGE_REASON::VCR_CURRENCY_DUI_HUAN,
    0);
  Record = Player::getRecord(this->m_pPlayer, 2102);
  Player::updateRecord(this->m_pPlayer, 2102, Record + 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCurrency::syncGold(CExtCurrency *const this, Answer::NetPacket *inPacket)
{
  int32_t Gold; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 2;
  Gold = Answer::NetPacket::readInt32(inPacket);
  Player::syncGold(this->m_pPlayer, Gold);
  return 0;
}


#####################################
int64_t __cdecl CExtCurrency::GetMoneyBindAndNoBind(CExtCurrency *const this)
{
  int64_t Money; // [rsp+10h] [rbp-10h]

  Money = CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY);
  return Money + CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY);
}


#####################################
bool __cdecl CExtCurrency::DecMoneyAndNoBind(
        CExtCurrency *const this,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  __int64 BindMoney; // [rsp+20h] [rbp-20h]

  BindMoney = CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY);
  if ( BindMoney + CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY) < nVal )
    return 0;
  if ( BindMoney >= nVal )
    return CExtCurrency::DecCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY, nVal, opWay, nParam);
  if ( BindMoney <= 0 )
    return CExtCurrency::DecCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY, nVal, opWay, nParam);
  if ( !CExtCurrency::DecCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY, nVal - BindMoney, opWay, nParam) )
    return 0;
  return CExtCurrency::DecCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY, BindMoney, opWay, nParam);
}


#####################################
int64_t __cdecl CExtCurrency::GetCurrency(const CExtCurrency *const this, const CURRENCY_TYPE nType)
{
  if ( !CExtCurrency::checkCurrencyType(this, nType) )
    return 0;
  else
    return this->m_aCurrency[nType];
}


#####################################
bool __cdecl CExtCurrency::AddCurrency(
        CExtCurrency *const this,
        const CURRENCY_TYPE nType,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  bool result; // al
  int64_t MaxVal; // rbx
  BenefitType v7; // eax
  BenefitType v8; // eax
  BenefitType v9; // eax
  BenefitType v10; // eax
  BenefitType v11; // eax
  BenefitType v12; // eax
  CShenWei *ShenWei; // rax
  int64_t v14; // rbx
  CfgData *v15; // rax
  CfgData *v16; // rax
  int8_t ConnId; // bl
  GameService *v18; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v21; // bl
  GameService *v22; // rax
  BenefitType v23; // eax
  int64_t Currency; // rax
  BenefitType v25; // eax
  BenefitType v26; // eax
  BenefitType v27; // eax
  BenefitType v28; // eax
  BenefitType v29; // eax
  __int64 nVala; // [rsp+28h] [rbp-58h]
  std::string val; // [rsp+40h] [rbp-40h] BYREF
  int64_t nMaxAddVal; // [rsp+50h] [rbp-30h]
  int32_t OldLevel; // [rsp+58h] [rbp-28h]
  int32_t NewLevel; // [rsp+5Ch] [rbp-24h]
  CfgCachet *pCfg; // [rsp+60h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+68h] [rbp-18h]

  nVala = nVal;
  if ( nVal > 0 )
  {
    MaxVal = CExtCurrency::getMaxVal(this, nType);
    nMaxAddVal = MaxVal - CExtCurrency::GetCurrency(this, nType);
    if ( nVala > nMaxAddVal )
      nVala = nMaxAddVal;
    if ( nVala > 0 )
    {
      switch ( nType )
      {
        case CURRENCY_TYPE::CURRENCY_MONEY:
          if ( opWay != CURRENCY_CHANGE_REASON::GCR_DEPOT_GET
            && opWay != CURRENCY_CHANGE_REASON::MCR_MAIL_CURRENCY_ITEM
            && opWay != CURRENCY_CHANGE_REASON::MCR_TRADE_GET_MONEY
            && opWay != CURRENCY_CHANGE_REASON::GCR_AUCTION_SELL
            && opWay != CURRENCY_CHANGE_REASON::MCR_MONEY_GAIN_ITEM )
          {
            nVala = (int)(Player::benefitRatio(this->m_pPlayer) * (double)(int)nVala);
          }
          if ( nVala > 0 )
          {
            v7 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 2, nVala, v7);
            goto LABEL_42;
          }
          return 1;
        case CURRENCY_TYPE::CURRENCY_GOLD:
          v8 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 3, nVala, v8);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_CASH:
          v9 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 4, nVala, v9);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_VIGOUR:
          v28 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 16, nVala, v28);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_DRAW_SCORE:
          v10 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 8, nVala, v10);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_BOSS_SCORE:
          v11 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 9, nVala, v11);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_BIND_MONEY:
          if ( opWay != CURRENCY_CHANGE_REASON::GCR_DEPOT_GET
            && opWay != CURRENCY_CHANGE_REASON::MCR_MAIL_CURRENCY_ITEM
            && opWay != CURRENCY_CHANGE_REASON::MCR_TRADE_GET_MONEY
            && opWay != CURRENCY_CHANGE_REASON::GCR_AUCTION_SELL
            && opWay != CURRENCY_CHANGE_REASON::MCR_MONEY_GAIN_ITEM )
          {
            nVala = (int)(Player::benefitRatio(this->m_pPlayer) * (double)(int)nVala);
          }
          if ( nVala > 0 )
          {
            v12 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 10, nVala, v12);
LABEL_42:
            result = CExtCurrency::changeCurrency(this, nType, nVala, opWay, nParam);
          }
          else
          {
            result = 1;
          }
          break;
        case CURRENCY_TYPE::CURRENCY_HONOR:
          ShenWei = Player::GetShenWei(this->m_pPlayer);
          OldLevel = CShenWei::GetShenWeiLevel(ShenWei);
          v14 = nVala + CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_HONOR);
          v15 = Answer::Singleton<CfgData>::instance();
          NewLevel = CfgData::GetCachetLevel(v15, v14);
          if ( OldLevel != NewLevel )
          {
            v16 = Answer::Singleton<CfgData>::instance();
            pCfg = CfgData::GetCfgCachet(v16, NewLevel);
            if ( pCfg )
            {
              if ( pCfg->nGongGaoId > 0 )
              {
                ConnId = Player::getConnId(this->m_pPlayer);
                v18 = Answer::Singleton<GameService>::instance();
                packet = GameService::popNetpacket(v18, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
                if ( packet )
                {
                  Answer::NetPacket::writeInt32(packet, pCfg->nGongGaoId);
                  Player::getName((const Player *const)&val);
                  Answer::NetPacket::writeUTF8(packet, &val);
                  std::string::~string(&val);
                  Cid = Player::getCid(this->m_pPlayer);
                  Answer::NetPacket::writeInt64(packet, Cid);
                  Answer::NetPacket::writeInt32(packet, OldLevel);
                  Answer::NetPacket::writeInt32(packet, NewLevel);
                  WOffset = Answer::NetPacket::getWOffset(packet);
                  Answer::NetPacket::setSize(packet, WOffset);
                  v21 = Player::getConnId(this->m_pPlayer);
                  v22 = Answer::Singleton<GameService>::instance();
                  GameService::worldBroadcast(v22, v21, packet);
                }
              }
            }
            Player::RecalcAttr(this->m_pPlayer);
          }
          v23 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 11, nVala, v23);
          Currency = CExtCurrency::GetCurrency(this, CURRENCY_TYPE::CURRENCY_HONOR);
          Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_SHEN_WEI, nVala + Currency);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_AC_SOCRE:
          v25 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 12, nVala, v25);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_CONTRIBUTION:
          v26 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 13, nVala, v26);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_BLOOD:
          v29 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 17, nVala, v29);
          goto LABEL_42;
        case CURRENCY_TYPE::CURRENCY_DUST:
          v27 = Player::benefitType(this->m_pPlayer);
          Player::sendGainInfo(this->m_pPlayer, 15, nVala, v27);
          goto LABEL_42;
        default:
          goto LABEL_42;
      }
    }
    else
    {
      return 1;
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "CExtCurrency::AddCurrency() wrong value!!! nType=%d, nVal=%d, opWay=%d, nParam=%lld\n",
      nType,
      nVal,
      opWay,
      nParam);
    return 0;
  }
  return result;
}


#####################################
bool __cdecl CExtCurrency::DecCurrency(
        CExtCurrency *const this,
        const CURRENCY_TYPE nType,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  BenefitType v6; // eax
  BenefitType v7; // eax
  BenefitType v8; // eax
  BenefitType v9; // eax
  BenefitType v10; // eax
  BenefitType v11; // eax
  BenefitType v12; // eax
  BenefitType v13; // eax
  BenefitType v14; // eax
  BenefitType v15; // eax
  BenefitType v16; // eax
  BenefitType v17; // eax
  CExtOperateLimit *OperateLimit; // rax
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v20; // rax
  Player *v21; // rbx
  CFestivalDoubleEleven *v22; // rax
  Player *v23; // rbx
  COpenBeta *v24; // rax
  Player *v25; // rbx
  CUniteServer *v26; // rax
  Player *v27; // rbx
  CKiaFuRecharge *v28; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  DBService *v30; // rax
  log_abnormal stu; // [rsp+30h] [rbp-80h] BYREF
  _BYTE v35[16]; // [rsp+50h] [rbp-60h] BYREF
  log_abnormal p_stu; // [rsp+60h] [rbp-50h] BYREF
  int64_t nRealValue; // [rsp+88h] [rbp-28h]
  int32_t nUsedGold; // [rsp+94h] [rbp-1Ch]
  int32_t oldRecord; // [rsp+98h] [rbp-18h]
  int32_t NewRecord; // [rsp+9Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  if ( nVal > 0 )
  {
    if ( CExtCurrency::GetCurrency(this, nType) >= nVal )
    {
      nRealValue = -nVal;
      if ( !CExtCurrency::changeCurrency(this, nType, -nVal, opWay, nParam) )
      {
        return 0;
      }
      else
      {
        switch ( nType )
        {
          case CURRENCY_TYPE::CURRENCY_MONEY:
            if ( opWay != CURRENCY_CHANGE_REASON::MCR_PK_DROP )
            {
              v6 = Player::benefitType(this->m_pPlayer);
              Player::sendGainInfo(this->m_pPlayer, 2, nRealValue, v6);
            }
            break;
          case CURRENCY_TYPE::CURRENCY_GOLD:
            v7 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 3, nRealValue, v7);
            break;
          case CURRENCY_TYPE::CURRENCY_CASH:
            v8 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 4, nRealValue, v8);
            break;
          case CURRENCY_TYPE::CURRENCY_VIGOUR:
            v16 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 16, nRealValue, v16);
            break;
          case CURRENCY_TYPE::CURRENCY_DRAW_SCORE:
            v9 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 8, nRealValue, v9);
            break;
          case CURRENCY_TYPE::CURRENCY_BOSS_SCORE:
            v10 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 9, nRealValue, v10);
            break;
          case CURRENCY_TYPE::CURRENCY_BIND_MONEY:
            v11 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 10, nRealValue, v11);
            break;
          case CURRENCY_TYPE::CURRENCY_HONOR:
            v12 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 11, nRealValue, v12);
            break;
          case CURRENCY_TYPE::CURRENCY_AC_SOCRE:
            v13 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 12, nRealValue, v13);
            break;
          case CURRENCY_TYPE::CURRENCY_CONTRIBUTION:
            v14 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 13, nRealValue, v14);
            break;
          case CURRENCY_TYPE::CURRENCY_BLOOD:
            v17 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 17, nRealValue, v17);
            break;
          case CURRENCY_TYPE::CURRENCY_DUST:
            v15 = Player::benefitType(this->m_pPlayer);
            Player::sendGainInfo(this->m_pPlayer, 15, nRealValue, v15);
            break;
          default:
            break;
        }
        if ( nType == CURRENCY_TYPE::CURRENCY_GOLD
          && opWay != CURRENCY_CHANGE_REASON::GCR_TRADE_CONST_GOLD
          && opWay != CURRENCY_CHANGE_REASON::GCR_AUCTION_BUY
          && opWay != CURRENCY_CHANGE_REASON::GCR_AUCTION_SELL
          && opWay != CURRENCY_CHANGE_REASON::GCR_FAMILY_SEND_RED_PACKET
          && opWay != CURRENCY_CHANGE_REASON::GCR_RANSOM_ITEM
          && opWay != CURRENCY_CHANGE_REASON::GCR_DEPOT_GET
          && (opWay != CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM
           || nParam != 3062 && nParam != 3063 && nParam != 3064) )
        {
          nUsedGold = nVal;
          OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::AddLimitCount(OperateLimit, 2031, nVal);
          m_pPlayer = this->m_pPlayer;
          v20 = Answer::Singleton<CFestivalDoubleEleven>::instance();
          CFestivalDoubleEleven::AddXiaoFeiRecord(v20, m_pPlayer, nVal);
          v21 = this->m_pPlayer;
          v22 = Answer::Singleton<CFestivalDoubleEleven>::instance();
          CFestivalDoubleEleven::UpdateXiaoFeiRank(v22, v21);
          v23 = this->m_pPlayer;
          v24 = Answer::Singleton<COpenBeta>::instance();
          COpenBeta::updateXiaoFeiSumRank(v24, v23, nVal);
          v25 = this->m_pPlayer;
          v26 = Answer::Singleton<CUniteServer>::instance();
          CUniteServer::AddXiaoFeiValue(v26, v25, nVal);
          v27 = this->m_pPlayer;
          v28 = Answer::Singleton<CKiaFuRecharge>::instance();
          CKiaFuRecharge::OnXiaoFeiSum(v28, v27, nVal);
          PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
          CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 17, nVal, 0);
        }
        if ( nType == CURRENCY_TYPE::CURRENCY_GOLD )
        {
          oldRecord = Player::getRecord(this->m_pPlayer, 2117);
          Player::updateRecord(this->m_pPlayer, 2117, nVal + oldRecord);
          NewRecord = Player::getRecord(this->m_pPlayer, 2117);
          if ( oldRecord <= (int)&unk_98967F && NewRecord > (int)&unk_98967F )
          {
            memset(&stu, 0, 28);
            std::string::string(&stu.sName);
            stu.nCid = Player::getCid(this->m_pPlayer);
            Player::getName((const Player *const)v35);
            std::string::operator=(&stu.sName, v35);
            std::string::~string(v35);
            stu.nType = 3;
            stu.nValue = NewRecord;
            log_abnormal::log_abnormal(&p_stu, &stu);
            v30 = Answer::Singleton<DBService>::instance();
            DBService::logAbnormal(v30, &p_stu);
            log_abnormal::~log_abnormal(&p_stu);
            log_abnormal::~log_abnormal(&stu);
          }
        }
        return 1;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "CExtCurrency::AddCurrency() wrong value!!! nType=%d, nVal=%d, opWay=%d, nParam=%lld\n",
      nType,
      nVal,
      opWay,
      nParam);
    return 0;
  }
}


#####################################
bool __cdecl CExtCurrency::changeCurrency(
        CExtCurrency *const this,
        const CURRENCY_TYPE nType,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  int32_t FuLiLevel; // r12d
  int32_t nTime; // ebx
  CharId_t Cid; // r14
  int8_t ConnId; // r13
  DBService *v10; // rax
  int v11; // ebx
  int64_t Currency; // rax
  DBService *v13; // rax
  int v14; // ebx
  int64_t v15; // rax
  DBService *v16; // rax
  int32_t MapId; // r12d
  int v18; // ebx
  int v19; // eax
  DBService *v20; // rax
  int v21; // ebx
  int32_t v22; // eax
  DBService *v23; // rax
  int8_t v24; // bl
  DBService *v25; // rax
  DBService *v26; // rax
  DBService *v27; // rax
  int64_t LeftVal; // [rsp+38h] [rbp-11A8h]
  char LogString[4096]; // [rsp+70h] [rbp-1170h] BYREF
  currency_log stu; // [rsp+1070h] [rbp-170h] BYREF
  std::string name; // [rsp+10D0h] [rbp-110h] BYREF
  _BYTE v35[16]; // [rsp+10E0h] [rbp-100h] BYREF
  _BYTE v36[16]; // [rsp+10F0h] [rbp-F0h] BYREF
  _BYTE v37[16]; // [rsp+1100h] [rbp-E0h] BYREF
  _BYTE v38[16]; // [rsp+1110h] [rbp-D0h] BYREF
  _BYTE v39[16]; // [rsp+1120h] [rbp-C0h] BYREF
  _BYTE v40[16]; // [rsp+1130h] [rbp-B0h] BYREF
  _BYTE v41[16]; // [rsp+1140h] [rbp-A0h] BYREF
  log_abnormal p_stu; // [rsp+1150h] [rbp-90h] BYREF
  _BYTE v43[16]; // [rsp+1170h] [rbp-70h] BYREF
  log_abnormal v44; // [rsp+1180h] [rbp-60h] BYREF
  PLATFORM_LOG_DATA_TYPE nLogType; // [rsp+11A0h] [rbp-40h]
  int32_t Type; // [rsp+11A4h] [rbp-3Ch]
  int32_t oldRecord; // [rsp+11A8h] [rbp-38h]
  int32_t NewRecord; // [rsp+11ACh] [rbp-34h]

  if ( !this->m_pPlayer || !nVal )
    return 0;
  if ( !CExtCurrency::checkCurrencyType(this, nType) )
    return 0;
  this->m_aCurrency[nType] += nVal;
  this->m_aUpdateSign[nType] = 1;
  this->m_bNeedSync = 1;
  FuLiLevel = Player::GetFuLiLevel(this->m_pPlayer);
  LeftVal = this->m_aCurrency[nType];
  nTime = Unit::getNow(this->m_pPlayer);
  Player::getName((const Player *const)&name);
  Cid = Player::getCid(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<DBService>::instance();
  DBService::logCurrency(v10, ConnId, Cid, &name, nType, opWay, nVal, nParam, nTime, LeftVal, FuLiLevel);
  std::string::~string(&name);
  if ( nVal > 0
    && nType == CURRENCY_TYPE::CURRENCY_GOLD
    && opWay != CURRENCY_CHANGE_REASON::GCR_RECHARGE
    && opWay != CURRENCY_CHANGE_REASON::GCR_GM_PAY )
  {
    memset(&stu, 0, 40);
    std::string::string((std::string *)&stu);
    std::string::string(&stu.passport);
    std::string::string((std::string *)&stu.cid);
    std::string::operator=(&stu, "yb_income");
    stu.log_time = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v35);
    std::string::operator=(&stu.passport, v35);
    std::string::~string(v35);
    stu.name._M_dataplus._M_p = (char *)Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    v11 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH);
    snprintf(LogString, 0xFFFu, "amount=%d&balance=%lld&level=%d&reason=%d", nVal, Currency, v11, opWay);
    std::string::operator=(&stu.cid, LogString);
    LOBYTE(v11) = Player::getConnId(this->m_pPlayer);
    v13 = Answer::Singleton<DBService>::instance();
    DBService::log360(v13, v11, (Log360 *const)&stu);
    Log360::~Log360((Log360 *const)&stu);
  }
  if ( nVal < 0 && nType == CURRENCY_TYPE::CURRENCY_GOLD && opWay != CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM )
  {
    memset(&stu, 0, 40);
    std::string::string((std::string *)&stu);
    std::string::string(&stu.passport);
    std::string::string((std::string *)&stu.cid);
    std::string::operator=(&stu, "yb_expend");
    stu.log_time = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v36);
    std::string::operator=(&stu.passport, v36);
    std::string::~string(v36);
    stu.name._M_dataplus._M_p = (char *)Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    v14 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v15 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
    snprintf(LogString, 0xFFFu, "amount=%d&balance=%lld&level=%d&reason=%d&type=0", -(int)nVal, v15, v14, opWay);
    std::string::operator=(&stu.cid, LogString);
    LOBYTE(v14) = Player::getConnId(this->m_pPlayer);
    v16 = Answer::Singleton<DBService>::instance();
    DBService::log360(v16, v14, (Log360 *const)&stu);
    Log360::~Log360((Log360 *const)&stu);
  }
  if ( nVal > 0 && nType == CURRENCY_TYPE::CURRENCY_CASH && opWay != CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM )
  {
    memset(&stu, 0, 40);
    std::string::string((std::string *)&stu);
    std::string::string(&stu.passport);
    std::string::string((std::string *)&stu.cid);
    std::string::operator=(&stu, "giftmoney_income");
    stu.log_time = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v37);
    std::string::operator=(&stu.passport, v37);
    std::string::~string(v37);
    stu.name._M_dataplus._M_p = (char *)Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    MapId = StaticObj::getMapId(this->m_pPlayer);
    v18 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v19 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH);
    snprintf(LogString, 0xFFFu, "money=%d&balance=%d&reason=%d&level=%d&map_id=%d", nVal, v19, opWay, v18, MapId);
    std::string::operator=(&stu.cid, LogString);
    LOBYTE(v18) = Player::getConnId(this->m_pPlayer);
    v20 = Answer::Singleton<DBService>::instance();
    DBService::log360(v20, v18, (Log360 *const)&stu);
    Log360::~Log360((Log360 *const)&stu);
  }
  if ( nVal != 100000 && (nType == CURRENCY_TYPE::CURRENCY_MONEY || nType == CURRENCY_TYPE::CURRENCY_BIND_MONEY) )
  {
    memset(&stu, 0, 40);
    std::string::string((std::string *)&stu);
    std::string::string(&stu.passport);
    std::string::string((std::string *)&stu.cid);
    std::string::operator=(&stu, "gold");
    stu.log_time = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v38);
    std::string::operator=(&stu.passport, v38);
    std::string::~string(v38);
    stu.name._M_dataplus._M_p = (char *)Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    Type = nType != CURRENCY_TYPE::CURRENCY_MONEY;
    v21 = Player::GetCurrency(this->m_pPlayer, nType);
    v22 = StaticObj::getMapId(this->m_pPlayer);
    snprintf(LogString, 0xFFFu, "num=%d&status=%d&map_id=%d&balance=%d&type=%d", nVal, opWay, v22, v21, Type);
    std::string::operator=(&stu.cid, LogString);
    LOBYTE(v21) = Player::getConnId(this->m_pPlayer);
    v23 = Answer::Singleton<DBService>::instance();
    DBService::log360(v23, v21, (Log360 *const)&stu);
    Log360::~Log360((Log360 *const)&stu);
  }
  nLogType = get_currency_log_type(nType);
  if ( nLogType != PLATFORM_LOG_DATA_TYPE::PLDT_INVALID )
  {
    currency_log::currency_log(&stu);
    stu.log_Sid = Player::getSid(this->m_pPlayer);
    stu.log_time = Unit::getNow(this->m_pPlayer);
    Player::GetPassport((Player *const)v39);
    std::string::operator=(&stu.passport, v39);
    std::string::~string(v39);
    stu.cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)v40);
    std::string::operator=(&stu.name, v40);
    std::string::~string(v40);
    stu.time = Unit::getNow(this->m_pPlayer);
    stu.type = nVal <= 0;
    stu.opway = opWay;
    stu.value = abs64(nVal);
    stu.level = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v24 = Player::getConnId(this->m_pPlayer);
    v25 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v25, v24, nLogType, &stu);
    currency_log::~currency_log(&stu);
  }
  if ( nVal > 0 && nType == CURRENCY_TYPE::CURRENCY_GOLD )
  {
    oldRecord = Player::getRecord(this->m_pPlayer, 2116);
    Player::updateRecord(this->m_pPlayer, 2116, nVal + oldRecord);
    NewRecord = Player::getRecord(this->m_pPlayer, 2116);
    if ( oldRecord <= (int)&unk_98967F && NewRecord > (int)&unk_98967F )
    {
      memset(&stu, 0, 28);
      std::string::string((std::string *)&stu.log_time);
      stu._vptr_platform_log_base = (int (**)(...))Player::getCid(this->m_pPlayer);
      Player::getName((const Player *const)v41);
      std::string::operator=(&stu.log_time, v41);
      std::string::~string(v41);
      LOBYTE(stu.passport._M_dataplus._M_p) = 2;
      HIDWORD(stu.passport._M_dataplus._M_p) = NewRecord;
      log_abnormal::log_abnormal(&p_stu, (const log_abnormal *const)&stu);
      v26 = Answer::Singleton<DBService>::instance();
      DBService::logAbnormal(v26, &p_stu);
      log_abnormal::~log_abnormal(&p_stu);
      log_abnormal::~log_abnormal((log_abnormal *const)&stu);
    }
    if ( nVal > (__int64)&loc_4C4B3F )
    {
      memset(&stu, 0, 28);
      std::string::string((std::string *)&stu.log_time);
      stu._vptr_platform_log_base = (int (**)(...))Player::getCid(this->m_pPlayer);
      Player::getName((const Player *const)v43);
      std::string::operator=(&stu.log_time, v43);
      std::string::~string(v43);
      LOBYTE(stu.passport._M_dataplus._M_p) = 1;
      HIDWORD(stu.passport._M_dataplus._M_p) = nVal;
      LODWORD(stu.cid) = opWay;
      log_abnormal::log_abnormal(&v44, (const log_abnormal *const)&stu);
      v27 = Answer::Singleton<DBService>::instance();
      DBService::logAbnormal(v27, &v44);
      log_abnormal::~log_abnormal(&v44);
      log_abnormal::~log_abnormal((log_abnormal *const)&stu);
    }
  }
  return 1;
}


#####################################
void __cdecl CExtCurrency::SendCurrencyInfo(CExtCurrency *const this, bool bAll)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  uint32_t oldOffset; // [rsp+20h] [rbp-20h]
  int8_t nCount; // [rsp+27h] [rbp-19h]
  uint32_t newOffset; // [rsp+28h] [rbp-18h]
  char i; // [rsp+2Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DC8u);
    if ( packet )
    {
      oldOffset = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt8(packet, 0);
      for ( i = 0; i <= 11; ++i )
      {
        if ( bAll || this->m_aUpdateSign[i] )
        {
          this->m_aUpdateSign[i] = 0;
          Answer::NetPacket::writeInt8(packet, i);
          Answer::NetPacket::writeInt64(packet, this->m_aCurrency[i]);
          ++nCount;
        }
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt8(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
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
bool __cdecl CExtCurrency::checkCurrencyType(const CExtCurrency *const this, const CURRENCY_TYPE nType)
{
  return (unsigned int)nType < CURRENCY_TYPE::CURRENCY_TYPE_COUNT;
}


