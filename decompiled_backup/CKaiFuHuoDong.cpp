// Decompiled methods for class: CKaiFuHuoDong
// Source: gameserver.cc
// Total methods: 27

#####################################
void __cdecl CKaiFuHuoDong::Init(CKaiFuHuoDong *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  std::pair<const int,BossFirstKilled> *v4; // rbx
  const char *StringValue; // rbx
  std::pair<const int,BossFirstKilled> *v6; // rax
  std::pair<const int,BossFirstKilled> *v7; // rbx
  char szSQL[4096]; // [rsp+10h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > it; // [rsp+1040h] [rbp-50h] BYREF
  int32_t BossId; // [rsp+104Ch] [rbp-44h] BYREF
  Answer::MySqlQuery result; // [rsp+1050h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > __x; // [rsp+1070h] [rbp-20h] BYREF

  v2 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
  strcpy(szSQL, "select * from mem_boss_first_killed");
  memset(&szSQL[36], 0, 4060);
  v3 = Answer::MySqlDBGuard::query(&db, szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v3);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    BossId = Answer::MySqlQuery::getIntValue(&result, "boss_id", 0);
    it._M_node = std::map<int,BossFirstKilled>::find(&this->m_BossFirstKilledMap, &BossId)._M_node;
    __x._M_node = std::map<int,BossFirstKilled>::end(&this->m_BossFirstKilledMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator!=(&it, &__x) )
    {
      v4 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
      v4->second.Killer = Answer::MySqlQuery::getInt64Value(&result, "killer", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "killer_name", &byte_8E3B03);
      v6 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
      std::string::operator=(&v6->second.KillerName, StringValue);
      v7 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
      v7->second.KillTime = Answer::MySqlQuery::getIntValue(&result, "kill_time", 0);
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
bool __cdecl CKaiFuHuoDong::InTime(CKaiFuHuoDong *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  return CfgData::getServerType(v1) != 1 && CKaiFuHuoDong::GetDaysFromServerStart(this) <= this->m_nHDLastDay;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::KaiFuHuoDongOperator(
        CKaiFuHuoDong *const this,
        Player *pPlayer,
        Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  uint16_t Proc; // ax
  CExtFlopDraw *v6; // rax
  CExtFlopDraw *CExtFlopDraw; // rax
  uint16_t v8; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v11; // rax
  int32_t nIndex; // [rsp+2Ch] [rbp-24h]

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  if ( !inPacket || !pPlayer )
    return 2;
  Proc = Answer::NetPacket::getProc(inPacket);
  if ( Proc == 496 )
    return CKaiFuHuoDong::OnGetReward(this, pPlayer, inPacket);
  if ( Proc > 0x1F0u )
  {
    if ( Proc == 497 )
    {
      CKaiFuHuoDong::SendBossFirstKillInfo(this, pPlayer);
      return 0;
    }
    if ( Proc == 498 )
    {
      nIndex = Answer::NetPacket::readInt32(inPacket);
      CExtFlopDraw = Player::GetCExtFlopDraw(pPlayer);
      if ( CExtFlopDraw::OnFlopDraw(CExtFlopDraw, 2, nIndex) )
      {
        CKaiFuHuoDong::SendKaiFuHuoDongIcon(this, pPlayer);
        v8 = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(pPlayer);
        ConnId = Player::getConnId(pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v11, ConnId, GateIndex, v8, nIndex);
      }
    }
  }
  else if ( Proc == 495 )
  {
    CKaiFuHuoDong::AskInfo(this, pPlayer, inPacket);
    v6 = Player::GetCExtFlopDraw(pPlayer);
    CExtFlopDraw::SendFlopRecord(v6, pPlayer, 2);
    return 0;
  }
  return 2;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::OnGetReward(CKaiFuHuoDong *const this, Player *pPlayer, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  GameService *v4; // rax
  int32_t DaysFromServerStart; // r12d
  int32_t v6; // r12d
  int first; // edx
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // r12d
  std::pair<const int,CfgKaiFuHuoDongData> *v11; // rax
  int64_t Conditions; // rdx
  int64_t v13; // rdx
  std::pair<const int,CfgKaiFuHuoDongData> *v14; // rax
  std::pair<const int,CfgKaiFuHuoDongData> *v15; // rax
  int32_t PetEffect; // edx
  int v17; // edx
  CfgData *v18; // rax
  int32_t ServerStartDayZeroTime; // r12d
  int v20; // edx
  int32_t LimitCount; // r12d
  int32_t v22; // r12d
  int v23; // edx
  int32_t v24; // r12d
  CExtCharWing *CharWing; // rax
  int32_t Level; // r12d
  int v27; // edx
  int32_t v28; // r12d
  int32_t Record; // r12d
  int v30; // edx
  int32_t v31; // r12d
  CExtCharJueWei *CharJueWei; // rax
  int32_t JueWei; // r12d
  int v34; // edx
  int32_t v35; // r12d
  CExtEquip *Equip; // rax
  int32_t IsAllPosLevel; // r12d
  int v38; // edx
  int32_t v39; // r12d
  CFaBao *PlayerFaBao; // rax
  int32_t FaBaoLevel; // r12d
  int64_t v42; // rdx
  int32_t TodayPayGold; // r12d
  int64_t v44; // rdx
  int32_t v45; // edx
  std::pair<const int,CfgKaiFuHuoDongData> *v46; // rax
  std::pair<const int,CfgKaiFuHuoDongData> *v47; // rax
  MemChrBag *v48; // r12
  Time_t v49; // r13d
  CfgData *v50; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  CExtCharBag *v52; // rax
  int v53; // r12d
  int v54; // r12d
  int32_t GongGaoId; // edx
  int v56; // ecx
  int v57; // edx
  int32_t v58; // ebx
  GameService *v59; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > itemIt; // [rsp+20h] [rbp-90h] BYREF
  MemChrBagVector Items; // [rsp+30h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+50h] [rbp-60h] BYREF
  int32_t Index; // [rsp+5Ch] [rbp-54h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+60h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-40h] BYREF
  int32_t nIndex; // [rsp+78h] [rbp-38h]
  int32_t Gold; // [rsp+7Ch] [rbp-34h]
  int32_t DiffGold; // [rsp+80h] [rbp-30h]
  int32_t EndTime; // [rsp+84h] [rbp-2Ch]
  CfgKaiFuHuoDongData *pCfg; // [rsp+88h] [rbp-28h]

  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( !inPacket || !pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,CfgKaiFuHuoDongData>::find(&this->m_KaiFuHuoDongCfg, &Index)._M_node;
  __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator==(&it, &__x) )
    return 2;
  DaysFromServerStart = CKaiFuHuoDong::GetDaysFromServerStart(this);
  if ( DaysFromServerStart < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.StartDay )
    return 2;
  v6 = CKaiFuHuoDong::GetDaysFromServerStart(this);
  if ( v6 > std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.EndDay )
    return 2;
  first = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
  if ( CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, first) )
    return 2;
  Bag = Player::GetBag(pPlayer);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  v11 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
  if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&v11->second.ItemVector) )
    return 2;
  switch ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type )
  {
    case 1:
      if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions <= 0 )
        return 2;
      Conditions = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions;
      if ( Player::DecCurrency(
             pPlayer,
             CURRENCY_TYPE::CURRENCY_GOLD,
             Conditions,
             CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_1,
             0) )
      {
        goto LABEL_72;
      }
      return 2;
    case 2:
      nIndex = Player::getRecord(pPlayer, 1031);
      Gold = 0;
      if ( nIndex <= 0 )
        goto LABEL_31;
      pCfg = CKaiFuHuoDong::GetKaiFuHuoDongData(this, nIndex);
      if ( pCfg )
      {
        Gold = pCfg->Conditions;
LABEL_31:
        v14 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
        if ( v14->second.Conditions > Gold )
        {
          v15 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
          DiffGold = v15->second.Conditions - Gold;
          if ( Player::DecCurrency(
                 pPlayer,
                 CURRENCY_TYPE::CURRENCY_GOLD,
                 DiffGold,
                 CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_3,
                 0) )
          {
            PetEffect = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.PetEffect;
            Player::updateRecord(pPlayer, 1029, PetEffect);
            v17 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            Player::updateRecord(pPlayer, 1031, v17);
            v18 = Answer::Singleton<CfgData>::instance();
            ServerStartDayZeroTime = CfgData::getServerStartDayZeroTime(v18, SERVER_TYPE::SVT_NORMAL);
            EndTime = ServerStartDayZeroTime + 86400 * CKaiFuHuoDong::GetKaiFuPetEndDay(this);
            Player::updateRecord(pPlayer, 1030, EndTime);
            Player::RecalcAttr(pPlayer);
            goto LABEL_72;
          }
          v3 = 2;
        }
        else
        {
          v3 = 2;
        }
      }
      else
      {
        v3 = 2;
      }
      break;
    case 3:
      if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions <= 0 )
        return 2;
      v13 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions;
      if ( Player::DecCurrency(
             pPlayer,
             CURRENCY_TYPE::CURRENCY_GOLD,
             v13,
             CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_2,
             0) )
      {
        goto LABEL_72;
      }
      return 2;
    case 4:
      v20 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      LimitCount = CKaiFuHuoDong::GetLimitCount(this, v20);
      if ( LimitCount >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      v22 = (*((__int64 (__fastcall **)(Player *))pPlayer->_vptr_Entity + 9))(pPlayer);
      if ( v22 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 5:
      v23 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      v24 = CKaiFuHuoDong::GetLimitCount(this, v23);
      if ( v24 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      CharWing = Player::GetCharWing(pPlayer);
      Level = CExtCharWing::GetLevel(CharWing);
      if ( Level >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 0xA:
      v27 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      v28 = CKaiFuHuoDong::GetLimitCount(this, v27);
      if ( v28 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      Record = Player::getRecord(pPlayer, 1150);
      if ( Record >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 0xB:
      v30 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      v31 = CKaiFuHuoDong::GetLimitCount(this, v30);
      if ( v31 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      CharJueWei = Player::GetCharJueWei(pPlayer);
      JueWei = CExtCharJueWei::GetJueWei(CharJueWei);
      if ( JueWei >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 0xC:
      v34 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      v35 = CKaiFuHuoDong::GetLimitCount(this, v34);
      if ( v35 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      Equip = Player::GetEquip(pPlayer);
      IsAllPosLevel = CExtEquip::IsAllPosLevel(Equip);
      if ( IsAllPosLevel >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 0xD:
      v38 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      v39 = CKaiFuHuoDong::GetLimitCount(this, v38);
      if ( v39 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
        return 2;
      PlayerFaBao = Player::GetPlayerFaBao(pPlayer);
      FaBaoLevel = CFaBao::GetFaBaoLevel(PlayerFaBao, 3);
      if ( FaBaoLevel >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
        goto LABEL_72;
      return 2;
    case 0xF:
      if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions <= 0 )
        return 2;
      v42 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions;
      if ( Player::DecCurrency(
             pPlayer,
             CURRENCY_TYPE::CURRENCY_GOLD,
             v42,
             CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_1,
             0) )
      {
        goto LABEL_72;
      }
      return 2;
    case 0x10:
      if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions <= 0 )
        return 2;
      TodayPayGold = Player::GetTodayPayGold(pPlayer);
      if ( TodayPayGold < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions1 )
        return 2;
      v44 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions;
      if ( !Player::DecCurrency(
              pPlayer,
              CURRENCY_TYPE::CURRENCY_GOLD,
              v44,
              CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_FREE_GIFT,
              0) )
        return 2;
      v45 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions;
      Player::updateRecord(pPlayer, 1905, v45);
LABEL_72:
      v46 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
      if ( !std::vector<MemChrBag>::size(&v46->second.ItemVector) )
        goto LABEL_82;
      v47 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
      std::vector<MemChrBag>::vector(&Items, &v47->second.ItemVector);
      for ( itemIt._M_current = std::vector<MemChrBag>::begin(&Items)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&itemIt, 0) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&Items)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&itemIt, &__rhs) )
          break;
        if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&itemIt)->endTime > 0 )
        {
          v48 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&itemIt);
          v49 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&itemIt)->endTime;
          v50 = Answer::Singleton<CfgData>::instance();
          LimitTimeTable = CfgData::GetLimitTimeTable(v50);
          v48->endTime = CfgLimitTimeTable::GetLimitTime(LimitTimeTable, v49);
        }
      }
      v52 = Player::GetBag(pPlayer);
      if ( !CExtCharBag::AddItem(v52, &Items, ITEM_CHANGE_REASON::ICR_KAI_FU_HUO_DONG) )
      {
        v3 = 2;
        v53 = 0;
      }
      else
      {
        v53 = 1;
      }
      std::vector<MemChrBag>::~vector(&Items);
      if ( v53 )
      {
LABEL_82:
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.GongGaoId > 0 )
        {
          v54 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
          GongGaoId = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.GongGaoId;
          CKaiFuHuoDong::GongGao(this, pPlayer, GongGaoId, v54);
        }
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit > 0 )
        {
          v56 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
          CKaiFuHuoDong::AddLimitCount(this, v56, 1);
          v57 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
          v58 = CKaiFuHuoDong::GetLimitCount(this, v57);
          if ( v58 == std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
          {
            v59 = Answer::Singleton<GameService>::instance();
            GameService::broadCastKiaFuHuoDongIcon(v59);
          }
        }
        CKaiFuHuoDong::AddRewardRecord(this, pPlayer, Index);
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 2 )
          CKaiFuHuoDong::SendKaiFuPetIcon(this, pPlayer);
        else
          CKaiFuHuoDong::SendKaiFuHuoDongIcon(this, pPlayer);
        CKaiFuHuoDong::SendHuoDongInfo(this, pPlayer);
        return 0;
      }
      return v3;
    default:
      return 2;
  }
  return v3;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetLimitCount(CKaiFuHuoDong *const this, int32_t index)
{
  std::_Ios_Openmode v2; // eax
  __int64 v3; // rax
  Answer::DBPool *v4; // rax
  const char *v5; // rax
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  int32_t v8; // ebx
  char mySql[1024]; // [rsp+10h] [rbp-5E0h] BYREF
  _BYTE v11[16]; // [rsp+410h] [rbp-1E0h] BYREF
  __int64 v12; // [rsp+420h] [rbp-1D0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+580h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+5B0h] [rbp-40h] BYREF
  std::string v15; // [rsp+5D0h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v11, (unsigned int)v2);
  v3 = std::operator<<<std::char_traits<char>>(&v12, "KAI_FU_LIMIT_");
  std::ostream::operator<<(v3, (unsigned int)index);
  v4 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v4);
  memset(mySql, 0, sizeof(mySql));
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v15, v11);
  v5 = (const char *)std::string::c_str(&v15);
  snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='%s'", v5);
  std::string::~string(&v15);
  v6 = Answer::MySqlDBGuard::query(&db, mySql);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, 0, &byte_8E3B03);
    v8 = atoi(StringValue);
  }
  else
  {
    v8 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v11);
  return v8;
}


#####################################
void __cdecl CKaiFuHuoDong::AddLimitCount(CKaiFuHuoDong *const this, int32_t index, int32_t Values)
{
  std::_Ios_Openmode v3; // eax
  __int64 v4; // rax
  Answer::DBPool *v5; // rax
  const char *v6; // rax
  Answer::MySqlQuery *v7; // rax
  const char *v8; // rax
  const char *v9; // rax
  char mySql_0[1024]; // [rsp+10h] [rbp-A00h] BYREF
  char mySql[1024]; // [rsp+410h] [rbp-600h] BYREF
  _BYTE v13[16]; // [rsp+810h] [rbp-200h] BYREF
  __int64 v14; // [rsp+820h] [rbp-1F0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+980h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+9B0h] [rbp-60h] BYREF
  std::string v17; // [rsp+9D0h] [rbp-40h] BYREF
  std::string v18; // [rsp+9E0h] [rbp-30h] BYREF
  std::string v19; // [rsp+9F0h] [rbp-20h] BYREF

  v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v13, (unsigned int)v3);
  v4 = std::operator<<<std::char_traits<char>>(&v14, "KAI_FU_LIMIT_");
  std::ostream::operator<<(v4, (unsigned int)index);
  v5 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v5);
  memset(mySql, 0, sizeof(mySql));
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v17, v13);
  v6 = (const char *)std::string::c_str(&v17);
  snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='%s'", v6);
  std::string::~string(&v17);
  v7 = Answer::MySqlDBGuard::query(&db, mySql);
  Answer::MySqlQuery::MySqlQuery(&result, v7);
  memset(mySql_0, 0, sizeof(mySql_0));
  if ( Answer::MySqlQuery::eof(&result) )
  {
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v18, v13);
    v8 = (const char *)std::string::c_str(&v18);
    snprintf(mySql_0, 0x3FFu, "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('%s','%d')", v8, Values);
    std::string::~string(&v18);
  }
  else
  {
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v19, v13);
    v9 = (const char *)std::string::c_str(&v19);
    snprintf(mySql_0, 0x3FFu, "UPDATE `sys_server_config` SET `value`= value + %d WHERE `name`='%s'", Values, v9);
    std::string::~string(&v19);
  }
  Answer::MySqlDBGuard::excute(&db, mySql_0);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v13);
}


#####################################
void __cdecl CKaiFuHuoDong::GongGao(CKaiFuHuoDong *const this, Player *pPlayer, int32_t GongGaoId, int32_t Index)
{
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v7; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, GongGaoId);
    Cid = Player::getCid(pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, Index);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v7, packet);
  }
}


#####################################
void __cdecl CKaiFuHuoDong::AddRewardRecord(CKaiFuHuoDong *const this, Player *pPlayer, int32_t Index)
{
  int32_t v3; // edx
  int32_t v4; // edx

  if ( pPlayer )
  {
    if ( Index > 32 )
    {
      v4 = Player::getRecord(pPlayer, 1081) | (1 << (Index - 33));
      Player::updateRecord(pPlayer, 1081, v4);
    }
    else
    {
      v3 = Player::getRecord(pPlayer, 1032) | (1 << (Index - 1));
      Player::updateRecord(pPlayer, 1032, v3);
    }
  }
}


#####################################
bool __cdecl CKaiFuHuoDong::IsAlreadyGet(CKaiFuHuoDong *const this, Player *pPlayer, int32_t Index)
{
  if ( !pPlayer )
    return 1;
  if ( Index > 32 )
  {
    if ( ((Player::getRecord(pPlayer, 1081) >> (Index - 33)) & 1) != 1 )
      return 0;
  }
  else if ( ((Player::getRecord(pPlayer, 1032) >> (Index - 1)) & 1) != 1 )
  {
    return 0;
  }
  return 1;
}


#####################################
void __cdecl CKaiFuHuoDong::SendHuoDongInfo(CKaiFuHuoDong *const this, Player *pPlayer)
{
  int first; // edx
  std::pair<const int,CfgKaiFuHuoDongData> *v3; // rax
  std::pair<const int,CfgKaiFuHuoDongData> *v4; // rax
  int *v5; // rbx
  int32_t Limit; // r12d
  int v7; // edx
  int8_t ConnId; // bl
  GameService *v9; // rax
  int32_t v10; // eax
  int *v11; // rax
  int32_t v12; // eax
  std::pair<const int,int> *v13; // rax
  std::pair<const int,int> *v14; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v17; // bl
  GameService *v18; // rax
  Int32Int32Map LimitInfo; // [rsp+10h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > biter; // [rsp+40h] [rbp-80h] BYREF
  std::_List_iterator<int> iter; // [rsp+50h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+60h] [rbp-60h] BYREF
  Int32List AlreadyGetIndexList; // [rsp+70h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+80h] [rbp-40h] BYREF
  std::_List_iterator<int> v25; // [rsp+90h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v26; // [rsp+A0h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+A8h] [rbp-18h]

  if ( pPlayer )
  {
    std::list<int>::list(&AlreadyGetIndexList);
    it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
    std::map<int,int>::map(&LimitInfo);
    while ( 1 )
    {
      __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      if ( CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, first) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
        std::list<int>::push_back(&AlreadyGetIndexList, &v3->first);
      }
      if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit > 0 )
      {
        v4 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it);
        v5 = std::map<int,int>::operator[](&LimitInfo, &v4->first);
        Limit = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit;
        v7 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
        *v5 = Limit - CKaiFuHuoDong::GetLimitCount(this, v7);
      }
      std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it);
    }
    ConnId = Player::getConnId(pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v9, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CECu);
    if ( packet )
    {
      v10 = std::list<int>::size(&AlreadyGetIndexList);
      Answer::NetPacket::writeInt32(packet, v10);
      for ( iter._M_node = std::list<int>::begin(&AlreadyGetIndexList)._M_node;
            ;
            std::_List_iterator<int>::operator++(&iter, 0) )
      {
        v25._M_node = std::list<int>::end(&AlreadyGetIndexList)._M_node;
        if ( !std::_List_iterator<int>::operator!=(&iter, &v25) )
          break;
        v11 = std::_List_iterator<int>::operator*(&iter);
        Answer::NetPacket::writeInt32(packet, *v11);
      }
      v12 = std::map<int,int>::size(&LimitInfo);
      Answer::NetPacket::writeInt32(packet, v12);
      for ( biter._M_node = std::map<int,int>::begin(&LimitInfo)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&biter, 0) )
      {
        v26._M_node = std::map<int,int>::end(&LimitInfo)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&biter, &v26) )
          break;
        v13 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&biter);
        Answer::NetPacket::writeInt32(packet, v13->first);
        v14 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&biter);
        Answer::NetPacket::writeInt32(packet, v14->second);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v17 = Player::getConnId(pPlayer);
      v18 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v18, v17, GateIndex, packet);
    }
    std::map<int,int>::~map(&LimitInfo);
    std::list<int>::~list(&AlreadyGetIndexList);
  }
}


#####################################
int32_t __cdecl CKaiFuHuoDong::AskInfo(CKaiFuHuoDong *const this, Player *pPlayer, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  if ( !pPlayer || !inPacket )
    return 2;
  CKaiFuHuoDong::SendHuoDongInfo(this, pPlayer);
  return 0;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetDaysFromServerStart(CKaiFuHuoDong *const this)
{
  CfgData *v1; // rax
  CfgData *v3; // rax
  int DiffDay; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
    return 99999;
  v3 = Answer::Singleton<CfgData>::instance();
  DiffDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1;
  if ( DiffDay > 0 )
    return DiffDay;
  else
    return 99999;
}


#####################################
void __cdecl CKaiFuHuoDong::GetKaiFuHuoDongIcon(
        CKaiFuHuoDong *const this,
        Player *pPlayer,
        IconStateList *const IconList)
{
  CfgData *v3; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nDayFromServerStart; // [rsp+3Ch] [rbp-4h]

  if ( pPlayer )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::isUniteServer(v3) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 66) )
      {
        nDayFromServerStart = CKaiFuHuoDong::GetDaysFromServerStart(this);
        if ( this->m_nHDLastDay >= nDayFromServerStart || CKaiFuHuoDong::HaveTeHuiGift(this, pPlayer) )
        {
          CKaiFuHuoDong::GetKaiFuHuoDongIconStu(&__x, this, pPlayer);
          std::list<ShowIcon>::push_back(IconList, &__x);
        }
      }
    }
  }
}


#####################################
void __cdecl CKaiFuHuoDong::SendKaiFuHuoDongIcon(CKaiFuHuoDong *const this, Player *pPlayer)
{
  CfgData *v2; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::isUniteServer(v2) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 66) )
      {
        CKaiFuHuoDong::GetKaiFuHuoDongIconStu(&stu, this, pPlayer);
        Player::SendIconState(pPlayer, &stu);
      }
    }
  }
}


#####################################
int32_t __cdecl CKaiFuHuoDong::HaveRewardCount(CKaiFuHuoDong *const this, Player *pPlayer)
{
  int32_t DaysFromServerStart; // ebx
  int32_t v4; // ebx
  int32_t v6; // ebx
  int first; // edx
  int v9; // edx
  int32_t LimitCount; // ebx
  CExtCharWing *CharWing; // rax
  int32_t Level; // ebx
  int v13; // edx
  int v15; // edx
  int32_t v16; // ebx
  int32_t Record; // ebx
  int v18; // edx
  int v20; // edx
  int32_t v21; // ebx
  CExtCharJueWei *CharJueWei; // rax
  int32_t JueWei; // ebx
  int v24; // edx
  int v26; // edx
  int32_t v27; // ebx
  CExtEquip *Equip; // rax
  int32_t IsAllPosLevel; // ebx
  int v30; // edx
  int v32; // edx
  int32_t v33; // ebx
  CFaBao *PlayerFaBao; // rax
  int32_t FaBaoLevel; // ebx
  int v36; // edx
  int v38; // edx
  int32_t v39; // ebx
  int32_t MaxFlopTimes; // ebx
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t Count; // [rsp+28h] [rbp-18h]
  int32_t FlopCount; // [rsp+2Ch] [rbp-14h]

  if ( !pPlayer )
    return 0;
  Count = 0;
  for ( it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
      break;
    DaysFromServerStart = CKaiFuHuoDong::GetDaysFromServerStart(this);
    if ( DaysFromServerStart >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.StartDay )
    {
      v4 = CKaiFuHuoDong::GetDaysFromServerStart(this);
      if ( v4 <= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.EndDay )
      {
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 4 )
        {
          v6 = (*((__int64 (__fastcall **)(Player *))pPlayer->_vptr_Entity + 9))(pPlayer);
          if ( v6 >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            first = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, first) )
            {
              v9 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              LimitCount = CKaiFuHuoDong::GetLimitCount(this, v9);
              if ( LimitCount < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 5 )
        {
          CharWing = Player::GetCharWing(pPlayer);
          Level = CExtCharWing::GetLevel(CharWing);
          if ( Level >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            v13 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, v13) )
            {
              v15 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              v16 = CKaiFuHuoDong::GetLimitCount(this, v15);
              if ( v16 < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 10 )
        {
          Record = Player::getRecord(pPlayer, 1150);
          if ( Record >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            v18 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, v18) )
            {
              v20 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              v21 = CKaiFuHuoDong::GetLimitCount(this, v20);
              if ( v21 < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 11 )
        {
          CharJueWei = Player::GetCharJueWei(pPlayer);
          JueWei = CExtCharJueWei::GetJueWei(CharJueWei);
          if ( JueWei >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            v24 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, v24) )
            {
              v26 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              v27 = CKaiFuHuoDong::GetLimitCount(this, v26);
              if ( v27 < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 12 )
        {
          Equip = Player::GetEquip(pPlayer);
          IsAllPosLevel = CExtEquip::IsAllPosLevel(Equip);
          if ( IsAllPosLevel >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            v30 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, v30) )
            {
              v32 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              v33 = CKaiFuHuoDong::GetLimitCount(this, v32);
              if ( v33 < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 13 )
        {
          PlayerFaBao = Player::GetPlayerFaBao(pPlayer);
          FaBaoLevel = CFaBao::GetFaBaoLevel(PlayerFaBao, 3);
          if ( FaBaoLevel >= std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Conditions )
          {
            v36 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
            if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, v36) )
            {
              v38 = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
              v39 = CKaiFuHuoDong::GetLimitCount(this, v38);
              if ( v39 < std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Limit )
                ++Count;
            }
          }
        }
        else if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 17 )
        {
          MaxFlopTimes = CKaiFuHuoDong::GetMaxFlopTimes(this, pPlayer);
          FlopCount = MaxFlopTimes - Player::getRecord(pPlayer, 2130);
          if ( FlopCount > 0 )
            Count += FlopCount;
        }
      }
    }
  }
  return Count;
}


#####################################
void __cdecl CKaiFuHuoDong::OnKilledMonster(CKaiFuHuoDong *const this, Player *pPlayer, int32_t Mid)
{
  int32_t DaysFromServerStart; // ebx
  int32_t v5; // ebx
  std::pair<const int,BossFirstKilled> *v6; // rbx
  std::pair<const int,BossFirstKilled> *v7; // rax
  std::pair<const int,BossFirstKilled> *v8; // rbx
  std::pair<const int,BossFirstKilled> *v10; // rax
  std::_Ios_Openmode v11; // eax
  std::pair<const int,BossFirstKilled> *v12; // rax
  int32_t EmailId; // r12d
  CharId_t Cid; // rbx
  DBService *v15; // rax
  int32_t KillTime; // r13d
  std::pair<const int,BossFirstKilled> *v17; // rax
  CharId_t Killer; // r12
  DBService *v19; // rax
  GameService *v20; // rax
  std::pair<const int,BossFirstKilled> *v21; // rax
  CharId_t v22; // rax
  std::pair<const int,BossFirstKilled> *v23; // rax
  std::pair<const int,BossFirstKilled> *v24; // rax
  uint32_t WOffset; // eax
  GameService *v26; // rax
  int32_t Mida; // [rsp+1Ch] [rbp-234h] BYREF
  Player *pPlayera; // [rsp+20h] [rbp-230h]
  CKaiFuHuoDong *thisa; // [rsp+28h] [rbp-228h]
  _BYTE v30[16]; // [rsp+30h] [rbp-220h] BYREF
  __int64 v31; // [rsp+40h] [rbp-210h] BYREF
  MemChrBag item; // [rsp+1A0h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > it; // [rsp+1C0h] [rbp-90h] BYREF
  Answer::MutexGuard lock; // [rsp+1D0h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > __x; // [rsp+1E0h] [rbp-70h] BYREF
  _BYTE v36[16]; // [rsp+1F0h] [rbp-60h] BYREF
  std::string Param; // [rsp+200h] [rbp-50h] BYREF
  std::string p_Name; // [rsp+210h] [rbp-40h] BYREF
  std::string val; // [rsp+220h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+228h] [rbp-28h]

  thisa = this;
  pPlayera = pPlayer;
  Mida = Mid;
  if ( CKaiFuHuoDong::InTime(this) && pPlayera )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_Lock);
    it._M_node = std::map<int,BossFirstKilled>::find(&thisa->m_BossFirstKilledMap, &Mida)._M_node;
    __x._M_node = std::map<int,BossFirstKilled>::end(&thisa->m_BossFirstKilledMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator!=(&it, &__x) )
    {
      DaysFromServerStart = CKaiFuHuoDong::GetDaysFromServerStart(thisa);
      if ( DaysFromServerStart <= std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.EndDay )
      {
        v5 = CKaiFuHuoDong::GetDaysFromServerStart(thisa);
        if ( v5 >= std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.StartDay
          && std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.Killer <= 0 )
        {
          v6 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
          v6->second.Killer = Player::getCid(pPlayera);
          Player::getName((const Player *const)v36);
          v7 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
          std::string::operator=(&v7->second.KillerName, v36);
          std::string::~string(v36);
          v8 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
          v8->second.KillTime = Unit::getNow(pPlayera);
          if ( std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.RewardType >= 0
            && std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.RewardValue > 0 )
          {
            *(_QWORD *)&item.itemId = 0x400000000LL;
            memset(&item.itemCount, 0, 24);
            v10 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
            item.itemId = TranseCurrencyItem((CURRENCY_TYPE)v10->second.RewardType);
            item.itemCount = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.RewardValue;
            v11 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
            std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
              v30,
              (unsigned int)v11);
            v12 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
            std::ostream::operator<<(&v31, (unsigned int)v12->second.BossId);
            std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, v30);
            EmailId = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.EmailId;
            Cid = Player::getCid(pPlayera);
            v15 = Answer::Singleton<DBService>::instance();
            DBService::OnSendSysMail(v15, 0, Cid, EmailId, &item, ITEM_CHANGE_REASON::ICR_KAI_HUO_EQUIP_BACK, &Param, 0);
            std::string::~string(&Param);
            KillTime = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.KillTime;
            v17 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
            std::string::string(&p_Name, &v17->second.KillerName);
            Killer = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.Killer;
            LODWORD(Cid) = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.BossId;
            v19 = Answer::Singleton<DBService>::instance();
            DBService::SaveBossFirstKilled(v19, Cid, Killer, &p_Name, KillTime);
            std::string::~string(&p_Name);
            v20 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v20, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( packet )
            {
              v21 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
              Answer::NetPacket::writeInt32(packet, v21->second.GongGaoId);
              v22 = Player::getCid(pPlayera);
              Answer::NetPacket::writeInt64(packet, v22);
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              Answer::NetPacket::writeInt32(packet, Mida);
              v23 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
              Answer::NetPacket::writeInt8(packet, v23->second.RewardType);
              v24 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
              Answer::NetPacket::writeInt32(packet, v24->second.RewardValue);
              WOffset = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, WOffset);
              v26 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v26, packet);
            }
            std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v30);
          }
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CKaiFuHuoDong::OnUpdateKilledMonster(
        CKaiFuHuoDong *const this,
        int32_t Mid,
        CharId_t cid,
        std::string *p_Name,
        int32_t KillTime)
{
  std::string *p_KillerName; // rdx
  int32_t Mida; // [rsp+24h] [rbp-4Ch] BYREF
  CKaiFuHuoDong *thisa; // [rsp+28h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > it; // [rsp+30h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > __x; // [rsp+50h] [rbp-20h] BYREF

  thisa = this;
  Mida = Mid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  it._M_node = std::map<int,BossFirstKilled>::find(&this->m_BossFirstKilledMap, &Mida)._M_node;
  __x._M_node = std::map<int,BossFirstKilled>::end(&thisa->m_BossFirstKilledMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator!=(&it, &__x) )
  {
    std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.Killer = cid;
    p_KillerName = &std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.KillerName;
    std::string::operator=(p_KillerName, p_Name);
    std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.KillTime = KillTime;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CKaiFuHuoDong::SendBossFirstKillInfo(CKaiFuHuoDong *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,BossFirstKilled> *v4; // rax
  std::pair<const int,BossFirstKilled> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossFirstKilled> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  int32_t Oldoffset; // [rsp+38h] [rbp-18h]
  int32_t NewWoffset; // [rsp+3Ch] [rbp-14h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CEDu);
    if ( packet )
    {
      Count = 0;
      Oldoffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( it._M_node = std::map<int,BossFirstKilled>::begin(&this->m_BossFirstKilledMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator++(&it) )
      {
        __x._M_node = std::map<int,BossFirstKilled>::end(&this->m_BossFirstKilledMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it)->second.Killer > 0 )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->second.BossId);
          v5 = std::_Rb_tree_iterator<std::pair<int const,BossFirstKilled>>::operator->(&it);
          Answer::NetPacket::writeUTF8(packet, &v5->second.KillerName);
          ++Count;
        }
      }
      NewWoffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, Oldoffset);
      Answer::NetPacket::writeInt32(packet, Count);
      Answer::NetPacket::setWOffset(packet, NewWoffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v8 = Player::getConnId(pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CKaiFuHuoDong::HaveTeHuiGift(CKaiFuHuoDong *const this, Player *pPlayer)
{
  int first; // edx
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( !pPlayer )
    return 0;
  for ( it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 1 )
    {
      first = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      if ( !CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, first) )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CKaiFuHuoDong::HaveBuyPetItem(CKaiFuHuoDong *const this, Player *pPlayer)
{
  int first; // edx
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( !pPlayer )
    return 0;
  for ( it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 2 )
    {
      first = std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->first;
      if ( CKaiFuHuoDong::IsAlreadyGet(this, pPlayer, first) )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CKaiFuHuoDong::GetKaiFuPetIcon(CKaiFuHuoDong *const this, Player *pPlayer, IconStateList *const IconList)
{
  CfgData *v3; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nDayFromServerStart; // [rsp+3Ch] [rbp-4h]

  if ( pPlayer )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::isUniteServer(v3) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 66) )
      {
        nDayFromServerStart = CKaiFuHuoDong::GetDaysFromServerStart(this);
        if ( CKaiFuHuoDong::GetKaiFuPetEndDay(this) >= nDayFromServerStart
          && CKaiFuHuoDong::GetKaiFuPetStartDay(this) <= nDayFromServerStart )
        {
          CKaiFuHuoDong::GetKaiFuPetIcon(&__x, this, pPlayer);
          std::list<ShowIcon>::push_back(IconList, &__x);
        }
      }
    }
  }
}


#####################################
void __cdecl CKaiFuHuoDong::SendKaiFuPetIcon(CKaiFuHuoDong *const this, Player *pPlayer)
{
  CfgData *v2; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::isUniteServer(v2) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 66) )
      {
        CKaiFuHuoDong::GetKaiFuPetIcon(&stu, this, pPlayer);
        Player::SendIconState(pPlayer, &stu);
      }
    }
  }
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetKaiFuPetStartDay(CKaiFuHuoDong *const this)
{
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 2 )
      return std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.StartDay;
  }
  return 0;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetKaiFuPetEndDay(CKaiFuHuoDong *const this)
{
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgKaiFuHuoDongData> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::map<int,CfgKaiFuHuoDongData>::begin(&this->m_KaiFuHuoDongCfg)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgKaiFuHuoDongData>::end(&this->m_KaiFuHuoDongCfg)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.Type == 2 )
      return std::_Rb_tree_iterator<std::pair<int const,CfgKaiFuHuoDongData>>::operator->(&it)->second.EndDay;
  }
  return 0;
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetFlopType(CKaiFuHuoDong *const this, int32_t nFlopId)
{
  GameService *v2; // rax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( nFlopId >= 0 && this->m_FlopSize > nFlopId )
    return *std::vector<int>::operator[](&this->m_FlopType, nFlopId);
  return 0;
}


#####################################
bool __cdecl CKaiFuHuoDong::CanFlopDraw(CKaiFuHuoDong *const this, Player *pPlayer, int32_t FlopId)
{
  GameService *v3; // rax
  ItemData *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v10; // rax
  int32_t FlopTimes; // [rsp+20h] [rbp-20h]
  int32_t BuyTimes; // [rsp+28h] [rbp-18h]
  int32_t NeedCost; // [rsp+2Ch] [rbp-14h]

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 0;
  if ( CKaiFuHuoDong::GetDaysFromServerStart(this) < this->m_FlopStartTime
    || CKaiFuHuoDong::GetDaysFromServerStart(this) > this->m_FlopEndTime )
  {
    return 0;
  }
  if ( !pPlayer || FlopId < 0 || this->m_FlopSize <= FlopId )
    return 0;
  if ( std::vector<ItemData>::operator[](&this->m_FlopCost, FlopId)->m_nId > 0 )
  {
    v6 = std::vector<ItemData>::operator[](&this->m_FlopCost, FlopId);
    Bag = Player::GetBag(pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, v6, ITEM_CHANGE_REASON::IDCR_FLOP) )
      return 0;
  }
  if ( *std::vector<int>::operator[](&this->m_FlopType, FlopId) == 4 )
    return 1;
  FlopTimes = Player::getRecord(pPlayer, 2130);
  if ( FlopTimes >= CKaiFuHuoDong::GetMaxFlopTimes(this, pPlayer) )
  {
    BuyTimes = Player::getRecord(pPlayer, 2129);
    if ( CKaiFuHuoDong::GetDaysFromServerStart(this) == this->m_FlopEndTime || this->m_FlopBuyTimes > BuyTimes )
    {
      NeedCost = 500 * (BuyTimes + 1);
      if ( NeedCost > 0 )
      {
        if ( !Player::DecCurrency(pPlayer, CURRENCY_TYPE::CURRENCY_GOLD, NeedCost, CURRENCY_CHANGE_REASON::GCR_FLOP, 0) )
        {
          return 0;
        }
        else
        {
          OperateLimit = Player::GetOperateLimit(pPlayer);
          CExtOperateLimit::AddLimitCount(OperateLimit, 2129, 1);
          v10 = Player::GetOperateLimit(pPlayer);
          CExtOperateLimit::AddLimitCount(v10, 2130, 1);
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
      return 0;
    }
  }
  else
  {
    v8 = Player::GetOperateLimit(pPlayer);
    CExtOperateLimit::AddLimitCount(v8, 2130, 1);
    return 1;
  }
}


#####################################
int32_t __cdecl CKaiFuHuoDong::GetMaxFlopTimes(CKaiFuHuoDong *const this, Player *pPlayer)
{
  GameService *v3; // rax
  int32_t Times; // [rsp+18h] [rbp-8h]

  if ( !pPlayer )
    return 0;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 0;
  Times = this->m_FlopFreeTimes;
  if ( Player::GetTodayPayGold(pPlayer) > 0 )
    ++Times;
  return Player::getRecord(pPlayer, 2129) + Times;
}


