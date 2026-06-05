// Decompiled methods for class: CTrade
// Source: gameserver.cc
// Total methods: 28

#####################################
void __cdecl CTrade::~CTrade(CTrade *const this)
{
  CTrade::~CTrade(this);
  operator delete(this);
}


#####################################
void __cdecl CTrade::GetInterestsProtocol(CTrade *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int16 v3; // [rsp+20h] [rbp-10h] BYREF
  unsigned __int16 v4; // [rsp+22h] [rbp-Eh] BYREF
  unsigned __int16 v5; // [rsp+24h] [rbp-Ch] BYREF
  unsigned __int16 v6; // [rsp+26h] [rbp-Ah] BYREF
  unsigned __int16 v7; // [rsp+28h] [rbp-8h] BYREF
  unsigned __int16 v8; // [rsp+2Ah] [rbp-6h] BYREF
  unsigned __int16 v9; // [rsp+2Ch] [rbp-4h] BYREF
  unsigned __int16 v10; // [rsp+2Eh] [rbp-2h] BYREF

  __x = 419;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 420;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 421;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 422;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 428;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 424;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 425;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 426;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 427;
  std::list<unsigned short>::push_back(procList, &v10);
}


#####################################
int32_t __cdecl CTrade::DispatchNetDatas(CTrade *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  GameService *v4; // rax
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v7; // rax
  CTrade *PlayerTrade; // rax
  Player *pTarget; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( Player::GetFuLiLevel(this->m_pPlayer) == 1 )
    return 2;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 2;
  if ( !Unit::isAlive(this->m_pPlayer) )
    return 2;
  switch ( nProcId )
  {
    case 0x1A3u:
      result = CTrade::OnAskTrade(this, inPacket);
      break;
    case 0x1A4u:
      result = CTrade::OnAgreeTrade(this, inPacket);
      break;
    case 0x1A5u:
      result = CTrade::OnAddItem(this, inPacket);
      break;
    case 0x1A6u:
      result = CTrade::OnRemoveItem(this, inPacket);
      break;
    case 0x1A8u:
      result = CTrade::OnSubMoney(this, inPacket);
      break;
    case 0x1A9u:
      result = CTrade::OnLock(this, inPacket);
      break;
    case 0x1AAu:
      if ( CTrade::OnSured(this, inPacket) )
      {
        RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
        m_TargetId = this->m_TargetId;
        v7 = Answer::Singleton<GameService>::instance();
        pTarget = GameService::getPlayer(v7, m_TargetId, RunnerId, 1);
        if ( pTarget )
        {
          PlayerTrade = Player::GetPlayerTrade(pTarget);
          (*PlayerTrade->_vptr_IExtSystem)(PlayerTrade);
        }
        (*this->_vptr_IExtSystem)(this);
      }
      goto LABEL_23;
    case 0x1ABu:
      result = CTrade::OnCancel(this, inPacket);
      break;
    case 0x1ACu:
      result = CTrade::OnAddMoney(this, inPacket);
      break;
    default:
LABEL_23:
      result = 0;
      break;
  }
  return result;
}


#####################################
void __cdecl CTrade::OnCleanUp(CTrade *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  this->m_TargetId = 0;
  this->m_IsTrading = 0;
  this->m_IsLock = 0;
  this->m_IsSureTrad = 0;
  this->m_TradMoney = 0;
  this->m_TradGold = 0;
  for ( i = 0; i <= 5; ++i )
    TradeData::OnClanup(&this->m_TradeData[i]);
}


#####################################
int32_t __cdecl CTrade::OnAskTrade(CTrade *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  CChrDepot *CharDepot; // rax
  CChrDepot *v6; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  CFunctionOpen *v8; // rax
  int32_t MapId; // ebx
  CTrade *PlayerTrade; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  uint16_t v15; // r13
  int16_t v16; // r12
  int8_t v17; // bl
  GameService *v18; // rax
  Position TarPos; // [rsp+10h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-40h] BYREF
  CharId_t TargetId; // [rsp+28h] [rbp-38h]
  Player *pTarget; // [rsp+30h] [rbp-30h]
  int32_t Distance; // [rsp+3Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( CTrade::IsTrading(this) )
    return 2;
  TargetId = Answer::NetPacket::readInt64(inPacket);
  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v4, TargetId, RunnerId, 1);
  if ( !pTarget )
    return 2;
  if ( Player::GetSysSettingInfo(pTarget, 4) )
  {
    Player::TiShiInfo(this->m_pPlayer, 5, 0);
    return 2;
  }
  else
  {
    CharDepot = Player::GetCharDepot(this->m_pPlayer);
    if ( !CChrDepot::IsEnterSecondPasswordOperate(CharDepot) )
    {
      Player::TiShiInfo(this->m_pPlayer, 29, 0);
      return 2;
    }
    else
    {
      v6 = Player::GetCharDepot(pTarget);
      if ( !CChrDepot::IsEnterSecondPasswordOperate(v6) )
      {
        Player::TiShiInfo(this->m_pPlayer, 30, 0);
        return 2;
      }
      else
      {
        PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
        if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 103) )
        {
          return 2;
        }
        else
        {
          v8 = Player::GetPlayerFunctionOpen(pTarget);
          if ( !CFunctionOpen::IsOpened(v8, 103) )
          {
            Player::TiShiInfo(this->m_pPlayer, 7, 0);
            return 2;
          }
          else
          {
            MapId = StaticObj::getMapId(pTarget);
            if ( MapId == StaticObj::getMapId(this->m_pPlayer) )
            {
              PlayerTrade = Player::GetPlayerTrade(pTarget);
              if ( CTrade::IsTrading(PlayerTrade) )
              {
                Proc = Answer::NetPacket::getProc(inPacket);
                GateIndex = Player::getGateIndex(this->m_pPlayer);
                ConnId = Player::getConnId(this->m_pPlayer);
                v14 = Answer::Singleton<GameService>::instance();
                return GameService::replyfailure(v14, ConnId, GateIndex, Proc, 1, 0);
              }
              else if ( CTrade::IsTrading(this) )
              {
                return 2;
              }
              else
              {
                TarPos = StaticObj::getCurrentTile(pTarget);
                CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
                Distance = Position::tileDistance(&CurrentTile, &TarPos);
                if ( Distance <= 20 )
                {
                  CTrade::SendAskTrade(this, pTarget);
                  v15 = Answer::NetPacket::getProc(inPacket);
                  v16 = Player::getGateIndex(this->m_pPlayer);
                  v17 = Player::getConnId(this->m_pPlayer);
                  v18 = Answer::Singleton<GameService>::instance();
                  GameService::replySuccess(v18, v17, v16, v15, 0);
                  return 0;
                }
                else
                {
                  return 2;
                }
              }
            }
            else
            {
              return 2;
            }
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CTrade::OnAgreeTrade(CTrade *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  int32_t MapId; // ebx
  CTrade *PlayerTrade; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  CharId_t Cid; // rbx
  CTrade *v12; // rax
  CTrade *v13; // rax
  CharId_t v14; // r14
  uint16_t v15; // r13
  int16_t v16; // r12
  GameService *v17; // rax
  Position TarPos; // [rsp+10h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-40h] BYREF
  CharId_t TargetId; // [rsp+28h] [rbp-38h]
  Player *pTarget; // [rsp+30h] [rbp-30h]
  int32_t Distance; // [rsp+3Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( CTrade::IsTrading(this) )
    return 2;
  TargetId = Answer::NetPacket::readInt64(inPacket);
  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v4, TargetId, RunnerId, 1);
  if ( !pTarget )
    return 2;
  MapId = StaticObj::getMapId(pTarget);
  if ( MapId != StaticObj::getMapId(this->m_pPlayer) )
    return 2;
  PlayerTrade = Player::GetPlayerTrade(pTarget);
  if ( CTrade::IsTrading(PlayerTrade) )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v10, ConnId, GateIndex, Proc, 1, 0);
  }
  else
  {
    TarPos = StaticObj::getCurrentTile(pTarget);
    CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
    Distance = Position::tileDistance(&CurrentTile, &TarPos);
    if ( Distance <= 20 )
    {
      CTrade::SetTargetChar(this, TargetId);
      CTrade::SetTrading(this);
      Cid = Player::getCid(this->m_pPlayer);
      v12 = Player::GetPlayerTrade(pTarget);
      CTrade::SetTargetChar(v12, Cid);
      v13 = Player::GetPlayerTrade(pTarget);
      CTrade::SetTrading(v13);
      CTrade::SendOperateToTarget(this, OPERATE_VALUES::OPERATE_AGREE_TRADE);
      v14 = Player::getCid(this->m_pPlayer);
      v15 = Answer::NetPacket::getProc(inPacket);
      v16 = Player::getGateIndex(this->m_pPlayer);
      LOBYTE(Cid) = Player::getConnId(this->m_pPlayer);
      v17 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v17, Cid, v16, v15, v14);
      return 0;
    }
    else
    {
      return 2;
    }
  }
}


#####################################
int32_t __cdecl CTrade::OnAddItem(CTrade *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  TradeData TradItem; // [rsp+10h] [rbp-60h] BYREF
  MemChrBag BagItem; // [rsp+40h] [rbp-30h]
  int32_t BagSlot; // [rsp+68h] [rbp-8h]
  int8_t TradeSlot; // [rsp+6Fh] [rbp-1h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsTrading(this) )
    return 2;
  if ( CTrade::IsLock(this) || CTrade::IsSureTrad(this) )
    return 2;
  BagSlot = Answer::NetPacket::readInt32(inPacket);
  TradeSlot = Answer::NetPacket::readInt8(inPacket);
  if ( BagSlot < 0 )
    return 2;
  if ( (unsigned __int8)TradeSlot > 6u )
    return 2;
  if ( CTrade::HaveSameBagSlot(this, BagSlot) )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  BagItem = *CExtCharBag::GetSlotData(Bag, BagSlot);
  if ( BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
    return 2;
  if ( BagItem.bind == 1 || BagItem.bind == 2 )
    return 2;
  if ( this->m_TradeData[TradeSlot].CharBagData.itemId > 0 || this->m_TradeData[TradeSlot].CharBagData.itemCount > 0 )
    return 2;
  TradeData::TradeData(&TradItem);
  TradItem.BagSlot = BagSlot;
  TradItem.CharBagData = BagItem;
  this->m_TradeData[TradeSlot] = TradItem;
  CTrade::SendItemChange(this, TradeSlot);
  CTrade::SendTargetItemChange(this, TradeSlot);
  return 0;
}


#####################################
int32_t __cdecl CTrade::OnRemoveItem(CTrade *const this, Answer::NetPacket *inPacket)
{
  int8_t TradeSlot; // [rsp+1Fh] [rbp-1h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsTrading(this) )
    return 2;
  if ( CTrade::IsLock(this) || CTrade::IsSureTrad(this) )
    return 2;
  TradeSlot = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)TradeSlot > 6u )
    return 2;
  if ( this->m_TradeData[TradeSlot].CharBagData.itemId <= 0 || this->m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
    return 2;
  CTrade::RemoveItem(this, TradeSlot);
  CTrade::SendItemChange(this, TradeSlot);
  CTrade::SendTargetItemChange(this, TradeSlot);
  return 0;
}


#####################################
int32_t __cdecl CTrade::OnAddMoney(CTrade *const this, Answer::NetPacket *inPacket)
{
  CVip *PlayerVip; // rax
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v7; // rax
  int64_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v11; // rax
  CTrade *PlayerTrade; // rax
  int8_t AddMoneyType; // [rsp+13h] [rbp-2Dh]
  int AddMoneyCount; // [rsp+14h] [rbp-2Ch]
  Player *pTarget; // [rsp+18h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsTrading(this) )
    return 2;
  if ( CTrade::IsLock(this) || CTrade::IsSureTrad(this) )
    return 2;
  AddMoneyType = Answer::NetPacket::readInt8(inPacket);
  AddMoneyCount = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned __int8)AddMoneyType >= 2u )
    return 2;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( !CVip::CanAuction(PlayerVip) )
    return 2;
  if ( AddMoneyType == 1 && Player::GetFuLiLevel(this->m_pPlayer) == 1 )
  {
    RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
    m_TargetId = this->m_TargetId;
    v7 = Answer::Singleton<GameService>::instance();
    pTarget = GameService::getPlayer(v7, m_TargetId, RunnerId, 1);
    if ( pTarget )
    {
      Proc = Answer::NetPacket::getProc(inPacket);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v11, ConnId, GateIndex, 0x1ABu, Proc);
      CTrade::SendOperateToTarget(this, OPERATE_VALUES::OPERATE_CANCEL);
      (*this->_vptr_IExtSystem)(this);
      PlayerTrade = Player::GetPlayerTrade(pTarget);
      (*PlayerTrade->_vptr_IExtSystem)(PlayerTrade);
    }
    return 2;
  }
  else if ( AddMoneyCount > 0 )
  {
    if ( Player::GetCurrency(this->m_pPlayer, (const CURRENCY_TYPE)AddMoneyType) >= AddMoneyCount )
    {
      if ( AddMoneyType )
        this->m_TradGold = AddMoneyCount;
      else
        this->m_TradMoney = AddMoneyCount;
      CTrade::SendTradeMoneyChange(this);
      CTrade::SendTargetTradeMoneychange(this);
      return 0;
    }
    else
    {
      return 2;
    }
  }
  else
  {
    return 2;
  }
}


#####################################
int32_t __cdecl CTrade::OnSubMoney(CTrade *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsTrading(this) )
    return 2;
  if ( !CTrade::IsLock(this) && !CTrade::IsSureTrad(this) )
  {
    Answer::NetPacket::readInt8(inPacket);
    Answer::NetPacket::readInt32(inPacket);
  }
  return 2;
}


#####################################
int32_t __cdecl CTrade::OnLock(CTrade *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  CTrade::SetLock(this);
  CTrade::SendOperateToTarget(this, OPERATE_VALUES::OPERATE_SET_LOCK);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CTrade::OnSured(CTrade *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v5; // rax
  CChrDepot *CharDepot; // rax
  CChrDepot *v7; // rax
  CTrade *PlayerTrade; // rax
  CTrade *v9; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v11; // rax
  int32_t v12; // eax
  uint16_t v13; // r13
  int16_t v14; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  uint16_t v17; // r13
  int16_t v18; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  int32_t v21; // eax
  uint16_t v22; // r13
  int16_t v23; // r12
  int8_t v24; // bl
  GameService *v25; // rax
  uint16_t v26; // r13
  int16_t v27; // r12
  int8_t v28; // bl
  GameService *v29; // rax
  int64_t v30; // rbx
  uint16_t v31; // r13
  int16_t v32; // r12
  int8_t v33; // bl
  GameService *v34; // rax
  uint16_t v35; // r13
  int16_t v36; // r12
  int8_t v37; // bl
  GameService *v38; // rax
  int64_t v39; // rbx
  uint16_t v40; // r13
  int16_t v41; // r12
  int8_t v42; // bl
  GameService *v43; // rax
  uint16_t v44; // r13
  int16_t v45; // r12
  int8_t v46; // bl
  GameService *v47; // rax
  int64_t v48; // rbx
  uint16_t v49; // r13
  int16_t v50; // r12
  int8_t v51; // bl
  GameService *v52; // rax
  uint16_t v53; // r13
  int16_t v54; // r12
  int8_t v55; // bl
  GameService *v56; // rax
  int64_t v57; // rbx
  uint16_t v58; // r13
  int16_t v59; // r12
  int8_t v60; // bl
  GameService *v61; // rax
  uint16_t v62; // r13
  int16_t v63; // r12
  int8_t v64; // bl
  GameService *v65; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v69; // rax
  uint16_t v70; // r13
  int16_t v71; // r12
  int8_t v72; // bl
  GameService *v73; // rax
  CTrade *v74; // rax
  uint16_t v75; // r13
  int16_t v76; // r12
  int8_t v77; // bl
  GameService *v78; // rax
  uint16_t v79; // r13
  int16_t v80; // r12
  int8_t v81; // bl
  GameService *v82; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v84; // rax
  int8_t v85; // bl
  CEquipManager *v86; // rax
  int8_t v87; // bl
  int8_t v88; // bl
  CEquipManager *v89; // rax
  EquipId_t v90; // rbx
  CEquipManager *v91; // rax
  int8_t v92; // bl
  CEquipManager *v93; // rax
  int8_t v94; // bl
  int8_t v95; // bl
  CEquipManager *v96; // rax
  CTrade *v97; // rax
  CTrade *v98; // rax
  CharId_t Cid; // rax
  CVip *PlayerVip; // rax
  double v101; // xmm0_8
  CharId_t v102; // rax
  CharId_t v103; // rax
  CVip *v104; // rax
  double v105; // xmm0_8
  CharId_t v106; // rax
  CharId_t v107; // rax
  CVip *v108; // rax
  double v109; // xmm0_8
  CharId_t v110; // rax
  CharId_t v111; // rax
  CVip *v112; // rax
  double v113; // xmm0_8
  CharId_t v114; // rax
  CTrade *v115; // rax
  CTrade *v116; // rax
  uint16_t v117; // r13
  int16_t v118; // r12
  int8_t v119; // bl
  GameService *v120; // rax
  MemEquip equip; // [rsp+10h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter_0; // [rsp+50h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+60h] [rbp-A0h] BYREF
  MemChrBagVector TargetItemVector; // [rsp+70h] [rbp-90h] BYREF
  int32_t TargetGold; // [rsp+88h] [rbp-78h] BYREF
  int32_t TargetMoney; // [rsp+8Ch] [rbp-74h] BYREF
  MemChrBagVector ItemVector; // [rsp+90h] [rbp-70h] BYREF
  int32_t Gold; // [rsp+A8h] [rbp-58h] BYREF
  int32_t Money; // [rsp+ACh] [rbp-54h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+B0h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v132; // [rsp+C0h] [rbp-40h] BYREF
  Player *pTarget; // [rsp+D0h] [rbp-30h]
  int32_t BagFreeCount; // [rsp+D8h] [rbp-28h]
  int32_t TargetBagFreeCount; // [rsp+DCh] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsLock(this) )
    return 2;
  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  m_TargetId = this->m_TargetId;
  v5 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v5, m_TargetId, RunnerId, 1);
  if ( !pTarget )
    return 2;
  CharDepot = Player::GetCharDepot(this->m_pPlayer);
  if ( !CChrDepot::IsEnterSecondPasswordOperate(CharDepot) )
  {
    Player::TiShiInfo(this->m_pPlayer, 29, 0);
    return 2;
  }
  else
  {
    v7 = Player::GetCharDepot(pTarget);
    if ( !CChrDepot::IsEnterSecondPasswordOperate(v7) )
    {
      Player::TiShiInfo(this->m_pPlayer, 30, 0);
      return 2;
    }
    else
    {
      PlayerTrade = Player::GetPlayerTrade(pTarget);
      if ( CTrade::IsSureTrad(PlayerTrade) )
      {
        Money = 0;
        Gold = 0;
        std::vector<MemChrBag>::vector(&ItemVector);
        TargetMoney = 0;
        TargetGold = 0;
        std::vector<MemChrBag>::vector(&TargetItemVector);
        CTrade::GetTradeItem(this, &Money, &Gold, &ItemVector);
        v9 = Player::GetPlayerTrade(pTarget);
        CTrade::GetTradeItem(v9, &TargetMoney, &TargetGold, &TargetItemVector);
        Bag = Player::GetBag(this->m_pPlayer);
        BagFreeCount = CExtCharBag::GetFreeSlotCount(Bag);
        v11 = Player::GetBag(pTarget);
        TargetBagFreeCount = CExtCharBag::GetFreeSlotCount(v11);
        v12 = std::vector<MemChrBag>::size(&TargetItemVector);
        if ( v12 <= BagFreeCount )
        {
          v21 = std::vector<MemChrBag>::size(&ItemVector);
          if ( v21 <= TargetBagFreeCount )
          {
            v30 = TargetMoney;
            if ( v30 <= Player::GetCurrency(pTarget, CURRENCY_TYPE::CURRENCY_MONEY) )
            {
              v39 = TargetGold;
              if ( v39 <= Player::GetCurrency(pTarget, CURRENCY_TYPE::CURRENCY_GOLD) )
              {
                v48 = Money;
                if ( v48 <= Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_MONEY) )
                {
                  v57 = Gold;
                  if ( v57 <= Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) )
                  {
                    if ( !CTrade::CompareItem(this) )
                    {
                      Proc = Answer::NetPacket::getProc(inPacket);
                      GateIndex = Player::getGateIndex(pTarget);
                      ConnId = Player::getConnId(pTarget);
                      v69 = Answer::Singleton<GameService>::instance();
                      GameService::replyfailure(v69, ConnId, GateIndex, Proc, 9, 0);
                      v70 = Answer::NetPacket::getProc(inPacket);
                      v71 = Player::getGateIndex(this->m_pPlayer);
                      v72 = Player::getConnId(this->m_pPlayer);
                      v73 = Answer::Singleton<GameService>::instance();
                      v2 = GameService::replyfailure(v73, v72, v71, v70, 8, 0);
                    }
                    else
                    {
                      v74 = Player::GetPlayerTrade(pTarget);
                      if ( !CTrade::CompareItem(v74) )
                      {
                        v75 = Answer::NetPacket::getProc(inPacket);
                        v76 = Player::getGateIndex(pTarget);
                        v77 = Player::getConnId(pTarget);
                        v78 = Answer::Singleton<GameService>::instance();
                        GameService::replyfailure(v78, v77, v76, v75, 8, 0);
                        v79 = Answer::NetPacket::getProc(inPacket);
                        v80 = Player::getGateIndex(this->m_pPlayer);
                        v81 = Player::getConnId(this->m_pPlayer);
                        v82 = Answer::Singleton<GameService>::instance();
                        v2 = GameService::replyfailure(v82, v81, v80, v79, 9, 0);
                      }
                      else
                      {
                        for ( iter._M_current = std::vector<MemChrBag>::begin(&TargetItemVector)._M_current;
                              ;
                              __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
                        {
                          __rhs._M_current = std::vector<MemChrBag>::end(&TargetItemVector)._M_current;
                          if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
                            break;
                          if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemClass == 2 )
                          {
                            srcId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->srcId;
                            v84 = Answer::Singleton<CEquipManager>::instance();
                            CEquipManager::GetMemEquip(&equip, v84, srcId);
                            LODWORD(srcId) = equip.base;
                            if ( (_DWORD)srcId == __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemId )
                            {
                              equip.owner = Player::getCid(this->m_pPlayer);
                              v85 = Player::getConnId(this->m_pPlayer);
                              v86 = Answer::Singleton<CEquipManager>::instance();
                              CEquipManager::UpdateMemEquip(v86, v85, &equip, 8);
                              v87 = Player::getConnId(this->m_pPlayer);
                              if ( v87 != Player::getConnId(pTarget) )
                              {
                                v88 = Player::getConnId(pTarget);
                                v89 = Answer::Singleton<CEquipManager>::instance();
                                CEquipManager::UpdateMemEquip(v89, v88, &equip, 8);
                              }
                            }
                            MemEquip::~MemEquip(&equip);
                          }
                        }
                        for ( iter_0._M_current = std::vector<MemChrBag>::begin(&ItemVector)._M_current;
                              ;
                              __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter_0) )
                        {
                          v132._M_current = std::vector<MemChrBag>::end(&ItemVector)._M_current;
                          if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter_0, &v132) )
                            break;
                          if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter_0)->itemClass == 2 )
                          {
                            v90 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter_0)->srcId;
                            v91 = Answer::Singleton<CEquipManager>::instance();
                            CEquipManager::GetMemEquip(&equip, v91, v90);
                            LODWORD(v90) = equip.base;
                            if ( (_DWORD)v90 == __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter_0)->itemId )
                            {
                              equip.owner = Player::getCid(pTarget);
                              v92 = Player::getConnId(this->m_pPlayer);
                              v93 = Answer::Singleton<CEquipManager>::instance();
                              CEquipManager::UpdateMemEquip(v93, v92, &equip, 8);
                              v94 = Player::getConnId(this->m_pPlayer);
                              if ( v94 != Player::getConnId(pTarget) )
                              {
                                v95 = Player::getConnId(pTarget);
                                v96 = Answer::Singleton<CEquipManager>::instance();
                                CEquipManager::UpdateMemEquip(v96, v95, &equip, 8);
                              }
                            }
                            MemEquip::~MemEquip(&equip);
                          }
                        }
                        CTrade::RemoveBagItem(this);
                        v97 = Player::GetPlayerTrade(pTarget);
                        CTrade::RemoveBagItem(v97);
                        CTrade::AddBagItem(this, &TargetItemVector);
                        v98 = Player::GetPlayerTrade(pTarget);
                        CTrade::AddBagItem(v98, &ItemVector);
                        if ( Money > 0 )
                        {
                          Cid = Player::getCid(pTarget);
                          Player::DecCurrency(
                            this->m_pPlayer,
                            CURRENCY_TYPE::CURRENCY_MONEY,
                            Money,
                            CURRENCY_CHANGE_REASON::MCR_TRADE_CONST_MONEY,
                            Cid);
                          PlayerVip = Player::GetPlayerVip(pTarget);
                          if ( CVip::GetVipLevel(PlayerVip) <= 3 )
                            v101 = (double)Money * 0.8;
                          else
                            v101 = (double)Money * 0.98;
                          Money = (int)v101;
                          v102 = Player::getCid(this->m_pPlayer);
                          Player::AddCurrency(
                            pTarget,
                            CURRENCY_TYPE::CURRENCY_MONEY,
                            Money,
                            CURRENCY_CHANGE_REASON::MCR_TRADE_GET_MONEY,
                            v102);
                        }
                        if ( Gold > 0 )
                        {
                          v103 = Player::getCid(pTarget);
                          Player::DecCurrency(
                            this->m_pPlayer,
                            CURRENCY_TYPE::CURRENCY_GOLD,
                            Gold,
                            CURRENCY_CHANGE_REASON::GCR_TRADE_CONST_GOLD,
                            v103);
                          v104 = Player::GetPlayerVip(pTarget);
                          if ( CVip::GetVipLevel(v104) <= 3 )
                            v105 = (double)Gold * 0.8;
                          else
                            v105 = (double)Gold * 0.98;
                          Gold = (int)v105;
                          v106 = Player::getCid(this->m_pPlayer);
                          Player::AddCurrency(
                            pTarget,
                            CURRENCY_TYPE::CURRENCY_GOLD,
                            Gold,
                            CURRENCY_CHANGE_REASON::GCR_TRADE_GET_GOLD,
                            v106);
                        }
                        if ( TargetMoney > 0 )
                        {
                          v107 = Player::getCid(this->m_pPlayer);
                          Player::DecCurrency(
                            pTarget,
                            CURRENCY_TYPE::CURRENCY_MONEY,
                            TargetMoney,
                            CURRENCY_CHANGE_REASON::MCR_TRADE_CONST_MONEY,
                            v107);
                          v108 = Player::GetPlayerVip(this->m_pPlayer);
                          if ( CVip::GetVipLevel(v108) <= 3 )
                            v109 = (double)TargetMoney * 0.8;
                          else
                            v109 = (double)TargetMoney * 0.98;
                          TargetMoney = (int)v109;
                          v110 = Player::getCid(pTarget);
                          Player::AddCurrency(
                            this->m_pPlayer,
                            CURRENCY_TYPE::CURRENCY_MONEY,
                            TargetMoney,
                            CURRENCY_CHANGE_REASON::MCR_TRADE_GET_MONEY,
                            v110);
                        }
                        if ( TargetGold > 0 )
                        {
                          v111 = Player::getCid(this->m_pPlayer);
                          Player::DecCurrency(
                            pTarget,
                            CURRENCY_TYPE::CURRENCY_GOLD,
                            TargetGold,
                            CURRENCY_CHANGE_REASON::GCR_TRADE_CONST_GOLD,
                            v111);
                          v112 = Player::GetPlayerVip(this->m_pPlayer);
                          if ( CVip::GetVipLevel(v112) <= 3 )
                            v113 = (double)TargetGold * 0.8;
                          else
                            v113 = (double)TargetGold * 0.98;
                          TargetGold = (int)v113;
                          v114 = Player::getCid(pTarget);
                          Player::AddCurrency(
                            this->m_pPlayer,
                            CURRENCY_TYPE::CURRENCY_GOLD,
                            TargetGold,
                            CURRENCY_CHANGE_REASON::GCR_TRADE_GET_GOLD,
                            v114);
                        }
                        CTrade::SendTradeSucceed(this, &TargetMoney, &TargetGold, &TargetItemVector);
                        v115 = Player::GetPlayerTrade(pTarget);
                        CTrade::SendTradeSucceed(v115, &Money, &Gold, &ItemVector);
                        (*this->_vptr_IExtSystem)(this);
                        v116 = Player::GetPlayerTrade(pTarget);
                        (*v116->_vptr_IExtSystem)(v116);
                        v2 = 0;
                      }
                    }
                  }
                  else
                  {
                    v58 = Answer::NetPacket::getProc(inPacket);
                    v59 = Player::getGateIndex(pTarget);
                    v60 = Player::getConnId(pTarget);
                    v61 = Answer::Singleton<GameService>::instance();
                    GameService::replyfailure(v61, v60, v59, v58, 7, 0);
                    v62 = Answer::NetPacket::getProc(inPacket);
                    v63 = Player::getGateIndex(this->m_pPlayer);
                    v64 = Player::getConnId(this->m_pPlayer);
                    v65 = Answer::Singleton<GameService>::instance();
                    v2 = GameService::replyfailure(v65, v64, v63, v62, 6, 0);
                  }
                }
                else
                {
                  v49 = Answer::NetPacket::getProc(inPacket);
                  v50 = Player::getGateIndex(pTarget);
                  v51 = Player::getConnId(pTarget);
                  v52 = Answer::Singleton<GameService>::instance();
                  GameService::replyfailure(v52, v51, v50, v49, 5, 0);
                  v53 = Answer::NetPacket::getProc(inPacket);
                  v54 = Player::getGateIndex(this->m_pPlayer);
                  v55 = Player::getConnId(this->m_pPlayer);
                  v56 = Answer::Singleton<GameService>::instance();
                  v2 = GameService::replyfailure(v56, v55, v54, v53, 4, 0);
                }
              }
              else
              {
                v40 = Answer::NetPacket::getProc(inPacket);
                v41 = Player::getGateIndex(pTarget);
                v42 = Player::getConnId(pTarget);
                v43 = Answer::Singleton<GameService>::instance();
                GameService::replyfailure(v43, v42, v41, v40, 6, 0);
                v44 = Answer::NetPacket::getProc(inPacket);
                v45 = Player::getGateIndex(this->m_pPlayer);
                v46 = Player::getConnId(this->m_pPlayer);
                v47 = Answer::Singleton<GameService>::instance();
                v2 = GameService::replyfailure(v47, v46, v45, v44, 7, 0);
              }
            }
            else
            {
              v31 = Answer::NetPacket::getProc(inPacket);
              v32 = Player::getGateIndex(pTarget);
              v33 = Player::getConnId(pTarget);
              v34 = Answer::Singleton<GameService>::instance();
              GameService::replyfailure(v34, v33, v32, v31, 4, 0);
              v35 = Answer::NetPacket::getProc(inPacket);
              v36 = Player::getGateIndex(this->m_pPlayer);
              v37 = Player::getConnId(this->m_pPlayer);
              v38 = Answer::Singleton<GameService>::instance();
              v2 = GameService::replyfailure(v38, v37, v36, v35, 5, 0);
            }
          }
          else
          {
            v22 = Answer::NetPacket::getProc(inPacket);
            v23 = Player::getGateIndex(pTarget);
            v24 = Player::getConnId(pTarget);
            v25 = Answer::Singleton<GameService>::instance();
            GameService::replyfailure(v25, v24, v23, v22, 3, 0);
            v26 = Answer::NetPacket::getProc(inPacket);
            v27 = Player::getGateIndex(this->m_pPlayer);
            v28 = Player::getConnId(this->m_pPlayer);
            v29 = Answer::Singleton<GameService>::instance();
            v2 = GameService::replyfailure(v29, v28, v27, v26, 2, 0);
          }
        }
        else
        {
          v13 = Answer::NetPacket::getProc(inPacket);
          v14 = Player::getGateIndex(pTarget);
          v15 = Player::getConnId(pTarget);
          v16 = Answer::Singleton<GameService>::instance();
          GameService::replyfailure(v16, v15, v14, v13, 2, 0);
          v17 = Answer::NetPacket::getProc(inPacket);
          v18 = Player::getGateIndex(this->m_pPlayer);
          v19 = Player::getConnId(this->m_pPlayer);
          v20 = Answer::Singleton<GameService>::instance();
          v2 = GameService::replyfailure(v20, v19, v18, v17, 3, 0);
        }
        std::vector<MemChrBag>::~vector(&TargetItemVector);
        std::vector<MemChrBag>::~vector(&ItemVector);
      }
      else
      {
        CTrade::SetSureTrad(this);
        CTrade::SendOperateToTarget(this, OPERATE_VALUES::OPERATE_SET_SURED);
        v117 = Answer::NetPacket::getProc(inPacket);
        v118 = Player::getGateIndex(this->m_pPlayer);
        v119 = Player::getConnId(this->m_pPlayer);
        v120 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v120, v119, v118, v117, 0);
        return 0;
      }
    }
  }
  return v2;
}


#####################################
int32_t __cdecl CTrade::OnCancel(CTrade *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v5; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  CTrade *PlayerTrade; // rax
  Player *pTarget; // [rsp+18h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( !CTrade::IsTrading(this) )
    return 2;
  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  m_TargetId = this->m_TargetId;
  v5 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v5, m_TargetId, RunnerId, 1);
  if ( !pTarget )
    return 2;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CTrade::SendOperateToTarget(this, OPERATE_VALUES::OPERATE_CANCEL);
  (*this->_vptr_IExtSystem)(this);
  PlayerTrade = Player::GetPlayerTrade(pTarget);
  (*PlayerTrade->_vptr_IExtSystem)(PlayerTrade);
  return 0;
}


#####################################
void __cdecl CTrade::SendAskTrade(CTrade *const this, Player *pTarget)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  int32_t v5; // eax
  int32_t v6; // eax
  Sex_t Sex; // al
  Job_t Job; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( pTarget && this->m_pPlayer )
  {
    ConnId = Player::getConnId(pTarget);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA3u);
    if ( packet )
    {
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      v5 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, v5);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      v6 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 10))(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, v6);
      Sex = Player::getSex(this->m_pPlayer);
      Answer::NetPacket::writeInt8(packet, Sex);
      Job = Player::getJob(this->m_pPlayer);
      Answer::NetPacket::writeInt8(packet, Job);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pTarget);
      v11 = Player::getConnId(pTarget);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CTrade::SendOperateToTarget(CTrade *const this, OPERATE_VALUES OperateType)
{
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  const Player *pTarget; // [rsp+10h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  m_TargetId = this->m_TargetId;
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v4, m_TargetId, RunnerId, 1);
  if ( pTarget )
  {
    if ( this->m_pPlayer )
    {
      ConnId = Player::getConnId(pTarget);
      v6 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA9u);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, OperateType);
        if ( OperateType == OPERATE_VALUES::OPERATE_AGREE_TRADE )
        {
          Cid = Player::getCid(this->m_pPlayer);
          Answer::NetPacket::writeInt64(packet, Cid);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pTarget);
        v10 = Player::getConnId(pTarget);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v11, v10, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CTrade::SendItemChange(CTrade *const this, int32_t TradeSlot)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( (unsigned int)TradeSlot <= 6 )
  {
    if ( this->m_pPlayer )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA4u);
      if ( packet )
      {
        if ( this->m_TradeData[TradeSlot].CharBagData.itemId < 0
          || this->m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
        {
          this->m_TradeData[0].BagSlot = -1;
        }
        Answer::NetPacket::writeInt8(packet, TradeSlot);
        Answer::NetPacket::writeInt32(packet, this->m_TradeData[TradeSlot].BagSlot);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CTrade::SendTargetItemChange(CTrade *const this, int32_t TradeSlot)
{
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  EquipId_t srcId; // rbx
  CEquipManager *v8; // rax
  CEquipManager *v9; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  MemEquip equip; // [rsp+10h] [rbp-60h] BYREF
  Player *pTarget; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( (unsigned int)TradeSlot <= 6 )
  {
    RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
    m_TargetId = this->m_TargetId;
    v4 = Answer::Singleton<GameService>::instance();
    pTarget = GameService::getPlayer(v4, m_TargetId, RunnerId, 1);
    if ( this->m_pPlayer )
    {
      if ( pTarget )
      {
        ConnId = Player::getConnId(this->m_pPlayer);
        v6 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA5u);
        if ( packet )
        {
          if ( this->m_TradeData[TradeSlot].CharBagData.itemId < 0
            || this->m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
          {
            this->m_TradeData[0].BagSlot = -1;
          }
          if ( this->m_TradeData[TradeSlot].CharBagData.itemClass == 2 )
          {
            srcId = this->m_TradeData[TradeSlot].CharBagData.srcId;
            v8 = Answer::Singleton<CEquipManager>::instance();
            CEquipManager::GetMemEquip(&equip, v8, srcId);
            if ( equip.base == this->m_TradeData[TradeSlot].CharBagData.itemId )
            {
              v9 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::SendPlayerEquipInfo(v9, pTarget, &equip);
            }
            MemEquip::~MemEquip(&equip);
          }
          Answer::NetPacket::writeInt8(packet, TradeSlot);
          Answer::NetPacket::writeInt32(packet, this->m_TradeData[TradeSlot].CharBagData.itemId);
          Answer::NetPacket::writeInt8(packet, this->m_TradeData[TradeSlot].CharBagData.itemClass);
          Answer::NetPacket::writeInt32(packet, this->m_TradeData[TradeSlot].CharBagData.itemCount);
          Answer::NetPacket::writeInt8(packet, this->m_TradeData[TradeSlot].CharBagData.bind);
          Answer::NetPacket::writeInt32(packet, this->m_TradeData[TradeSlot].CharBagData.endTime);
          Answer::NetPacket::writeInt64(packet, this->m_TradeData[TradeSlot].CharBagData.srcId);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(pTarget);
          v12 = Player::getConnId(this->m_pPlayer);
          v13 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v13, v12, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
void __cdecl CTrade::SendTradeMoneyChange(CTrade *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_TradMoney);
      Answer::NetPacket::writeInt32(packet, this->m_TradGold);
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
void __cdecl CTrade::SendTargetTradeMoneychange(CTrade *const this)
{
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  const Player *pTarget; // [rsp+10h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  m_TargetId = this->m_TargetId;
  v3 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v3, m_TargetId, RunnerId, 1);
  if ( this->m_pPlayer && pTarget )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA7u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_TradMoney);
      Answer::NetPacket::writeInt32(packet, this->m_TradGold);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pTarget);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CTrade::SendTradeSucceed(
        CTrade *const this,
        int32_t *const Moeny,
        int32_t *const Gold,
        MemChrBagVector *const ItemVector)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  MemChrBag *v6; // rax
  MemChrBag *v7; // rax
  MemChrBag *v8; // rax
  MemChrBag *v9; // rax
  MemChrBag *v10; // rax
  MemChrBag *v11; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v14; // bl
  GameService *v15; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+20h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-20h]
  int8_t nSize; // [rsp+4Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CA8u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, *Moeny);
      Answer::NetPacket::writeInt32(packet, *Gold);
      nSize = std::vector<MemChrBag>::size(ItemVector);
      Answer::NetPacket::writeInt8(packet, nSize);
      for ( it._M_current = std::vector<MemChrBag>::begin(ItemVector)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(ItemVector)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v6 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->itemId);
        v7 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v7->itemClass);
        v8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v8->itemCount);
        v9 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v9->bind);
        v10 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v10->endTime);
        v11 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        Answer::NetPacket::writeInt64(packet, v11->srcId);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v14 = Player::getConnId(this->m_pPlayer);
      v15 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v15, v14, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CTrade::RemoveItem(CTrade *const this, int32_t TradeSlot)
{
  TradeData TradeItem; // [rsp+10h] [rbp-30h] BYREF

  if ( (unsigned int)TradeSlot <= 6 )
  {
    TradeData::TradeData(&TradeItem);
    this->m_TradeData[TradeSlot] = TradeItem;
  }
}


#####################################
int32_t __cdecl CTrade::GetDistance(CTrade *const this, Position Pos)
{
  Position Posa; // [rsp+0h] [rbp-20h] BYREF
  CTrade *thisa; // [rsp+8h] [rbp-18h]
  Position CurrentTile; // [rsp+10h] [rbp-10h] BYREF
  int32_t Distance; // [rsp+1Ch] [rbp-4h]

  thisa = this;
  Posa = Pos;
  Distance = 0;
  CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
  return Position::tileDistance(&CurrentTile, &Posa);
}


#####################################
void __cdecl CTrade::GetTradeItem(
        CTrade *const this,
        int32_t *const Moeny,
        int32_t *const Gold,
        MemChrBagVector *const ItemVector)
{
  int32_t i; // [rsp+2Ch] [rbp-4h]

  *Moeny = this->m_TradMoney;
  *Gold = this->m_TradGold;
  for ( i = 0; i <= 5; ++i )
  {
    if ( this->m_TradeData[i].BagSlot >= 0
      && this->m_TradeData[i].CharBagData.itemId > 0
      && this->m_TradeData[i].CharBagData.itemCount > 0 )
    {
      std::vector<MemChrBag>::push_back(ItemVector, &this->m_TradeData[i].CharBagData);
    }
  }
}


#####################################
void __cdecl CTrade::CheckDistance(CTrade *const this)
{
  int32_t RunnerId; // r12d
  CharId_t m_TargetId; // rbx
  GameService *v3; // rax
  int32_t MapId; // ebx
  Position CurrentTile; // rsi
  CTrade *PlayerTrade; // rax
  Player *pTarget; // [rsp+18h] [rbp-18h]

  if ( CTrade::IsTrading(this) )
  {
    RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
    m_TargetId = this->m_TargetId;
    v3 = Answer::Singleton<GameService>::instance();
    pTarget = GameService::getPlayer(v3, m_TargetId, RunnerId, 1);
    if ( this->m_pPlayer && pTarget )
    {
      MapId = StaticObj::getMapId(pTarget);
      if ( MapId != StaticObj::getMapId(this->m_pPlayer)
        || (CurrentTile = StaticObj::getCurrentTile(pTarget), CTrade::GetDistance(this, CurrentTile) > 20) )
      {
        (*this->_vptr_IExtSystem)(this);
        PlayerTrade = Player::GetPlayerTrade(pTarget);
        (*PlayerTrade->_vptr_IExtSystem)(PlayerTrade);
      }
    }
    else
    {
      (*this->_vptr_IExtSystem)(this);
    }
  }
}


#####################################
bool __cdecl CTrade::CompareItem(CTrade *const this)
{
  int32_t BagSlot; // ebx
  CExtCharBag *Bag; // rax
  const MemChrBag *SlotData; // rax
  __int64 BagItem; // [rsp+10h] [rbp-40h]
  __int64 BagItem_8; // [rsp+18h] [rbp-38h]
  int32_t i; // [rsp+3Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  for ( i = 0; i <= 5; ++i )
  {
    if ( this->m_TradeData[i].CharBagData.itemId > 0 && this->m_TradeData[i].CharBagData.itemCount > 0 )
    {
      BagSlot = this->m_TradeData[i].BagSlot;
      Bag = Player::GetBag(this->m_pPlayer);
      SlotData = CExtCharBag::GetSlotData(Bag, BagSlot);
      BagItem = *(_QWORD *)&SlotData->itemId;
      BagItem_8 = *(_QWORD *)&SlotData->itemCount;
      if ( BYTE4(BagItem_8) != this->m_TradeData[i].CharBagData.bind
        || (unsigned int)*(_QWORD *)&SlotData->endTime != this->m_TradeData[i].CharBagData.endTime
        || BYTE4(BagItem) != this->m_TradeData[i].CharBagData.itemClass
        || __PAIR64__(BagItem_8, BagItem) != __PAIR64__(
                                               this->m_TradeData[i].CharBagData.itemCount,
                                               this->m_TradeData[i].CharBagData.itemId)
        || SlotData->srcId != this->m_TradeData[i].CharBagData.srcId )
      {
        return 0;
      }
    }
  }
  return 1;
}


#####################################
bool __cdecl CTrade::RemoveBagItem(CTrade *const this)
{
  bool v1; // bl
  std::_Ios_Openmode v2; // eax
  std::_Ios_Openmode v3; // eax
  unsigned int itemId; // ebx
  __int64 v5; // rax
  int32_t BagSlot; // ebx
  CExtCharBag *Bag; // rax
  _BYTE v9[16]; // [rsp+10h] [rbp-360h] BYREF
  _BYTE v10[352]; // [rsp+20h] [rbp-350h] BYREF
  _BYTE v11[16]; // [rsp+180h] [rbp-1F0h] BYREF
  _BYTE v12[352]; // [rsp+190h] [rbp-1E0h] BYREF
  MemChrBag slotData; // [rsp+2F0h] [rbp-80h] BYREF
  ItemData item; // [rsp+310h] [rbp-60h] BYREF
  ItemDataList lst; // [rsp+320h] [rbp-50h] BYREF
  Int32Vector vSlot; // [rsp+330h] [rbp-40h] BYREF
  int8_t ItemType[12]; // [rsp+350h] [rbp-20h] BYREF
  int32_t i; // [rsp+35Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v11, (unsigned int)v2);
  v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v9, (unsigned int)v3);
  std::vector<int>::vector(&vSlot);
  std::list<ItemData>::list(&lst);
  for ( i = 0; i <= 5; ++i )
  {
    if ( this->m_TradeData[i].BagSlot >= 0
      && this->m_TradeData[i].CharBagData.itemId > 0
      && this->m_TradeData[i].CharBagData.itemCount > 0 )
    {
      if ( !std::list<ItemData>::empty(&lst) )
      {
        std::operator<<<std::char_traits<char>>(v12, &unk_8F33E8);
        std::operator<<<std::char_traits<char>>(v10, &unk_8F33E8);
      }
      itemId = this->m_TradeData[i].CharBagData.itemId;
      GetLogItemFront((int8_t)ItemType);
      v5 = std::operator<<<char>(v12, ItemType);
      std::ostream::operator<<(v5, itemId);
      std::string::~string(ItemType);
      std::ostream::operator<<(v10, (unsigned int)-this->m_TradeData[i].CharBagData.itemCount);
      *(_QWORD *)&item.m_nId = 0;
      item.m_nCount = 0;
      item.m_nClass = this->m_TradeData[i].CharBagData.itemClass;
      item.m_nCount = this->m_TradeData[i].CharBagData.itemCount;
      item.m_nId = this->m_TradeData[i].CharBagData.itemId;
      std::list<ItemData>::push_back(&lst, &item);
      memset(&slotData, 0, sizeof(slotData));
      BagSlot = this->m_TradeData[i].BagSlot;
      Bag = Player::GetBag(this->m_pPlayer);
      CExtCharBag::SetSlotData(Bag, BagSlot, &slotData, ITEM_CHANGE_REASON::ICR_TRADE, 0);
    }
  }
  v1 = 1;
  std::list<ItemData>::~list(&lst);
  std::vector<int>::~vector(&vSlot);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v9);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v11);
  return v1;
}


#####################################
void __cdecl CTrade::AddBagItem(CTrade *const this, MemChrBagVector *const ItemVector)
{
  CExtCharBag *Bag; // rax
  std::_Ios_Openmode v4; // eax
  std::_Ios_Openmode v5; // eax
  unsigned int itemId; // ebx
  __int64 v7; // rax
  const MemChrBag *v8; // rax
  _BYTE v9[16]; // [rsp+10h] [rbp-340h] BYREF
  _BYTE v10[352]; // [rsp+20h] [rbp-330h] BYREF
  _BYTE v11[16]; // [rsp+180h] [rbp-1D0h] BYREF
  _BYTE v12[352]; // [rsp+190h] [rbp-1C0h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+2F0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __i; // [rsp+300h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v15; // [rsp+310h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+320h] [rbp-30h] BYREF
  int8_t ItemType[32]; // [rsp+330h] [rbp-20h] BYREF

  if ( this->m_pPlayer && !std::vector<MemChrBag>::empty(ItemVector) )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    CExtCharBag::AddItem(Bag, ItemVector, ITEM_CHANGE_REASON::ICR_TRADE);
    v4 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v11, (unsigned int)v4);
    v5 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v9, (unsigned int)v5);
    __i._M_current = std::vector<MemChrBag>::begin(ItemVector)._M_current;
    __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::__normal_iterator<MemChrBag*>(&iter, &__i);
    while ( 1 )
    {
      v15._M_current = std::vector<MemChrBag>::end(ItemVector)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag const*,MemChrBag*,std::vector<MemChrBag>>(&iter, &v15) )
        break;
      __rhs._M_current = std::vector<MemChrBag>::begin(ItemVector)._M_current;
      if ( __gnu_cxx::operator!=<MemChrBag const*,MemChrBag*,std::vector<MemChrBag>>(&iter, &__rhs) )
      {
        std::operator<<<std::char_traits<char>>(v12, &unk_8F33E8);
        std::operator<<<std::char_traits<char>>(v10, &unk_8F33E8);
      }
      itemId = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter)->itemId;
      __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
      GetLogItemFront((int8_t)ItemType);
      v7 = std::operator<<<char>(v12, ItemType);
      std::ostream::operator<<(v7, itemId);
      std::string::~string(ItemType);
      v8 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
      std::ostream::operator<<(v10, (unsigned int)v8->itemCount);
      __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter);
    }
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v9);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v11);
  }
}


#####################################
bool __cdecl CTrade::HaveSameBagSlot(CTrade *const this, int32_t BagSlot)
{
  int32_t i; // [rsp+18h] [rbp-4h]

  for ( i = 0; i <= 5; ++i )
  {
    if ( this->m_TradeData[i].BagSlot >= 0 && this->m_TradeData[i].BagSlot == BagSlot )
      return 1;
  }
  return 0;
}


