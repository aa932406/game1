// Decompiled methods for class: CHuoYueDu
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl CHuoYueDu::~CHuoYueDu(CHuoYueDu *const this)
{
  CHuoYueDu::~CHuoYueDu(this);
  operator delete(this);
}


#####################################
void __cdecl CHuoYueDu::GetInterestsProtocol(CHuoYueDu *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 500;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 501;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 502;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CHuoYueDu::DispatchNetDatas(CHuoYueDu *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x1F5u:
      return CHuoYueDu::OnGetHuoYueDuReward(this, inPacket);
    case 0x1F6u:
      return CHuoYueDu::OnSec(this, inPacket);
    case 0x1F4u:
      return CHuoYueDu::OnAskHuoYueDuInfo(this, inPacket);
  }
  return 0;
}


#####################################
void __cdecl CHuoYueDu::OnLoadFromDB(CHuoYueDu *const this, const PlayerDBData *const dbData)
{
  std::map<int,HuoYueDuRecord>::operator=(&this->m_HuoYueDuRecord, &dbData->m_HuoYueDuData.m_HuoYueDuRecord);
}


#####################################
void __cdecl CHuoYueDu::OnSaveToDB(CHuoYueDu *const this, PlayerDBData *const dbData)
{
  std::map<int,HuoYueDuRecord>::operator=(&dbData->m_HuoYueDuData.m_HuoYueDuRecord, &this->m_HuoYueDuRecord);
}


#####################################
void __cdecl CHuoYueDu::OnDaySwitch(CHuoYueDu *const this, int32_t nDiffDays)
{
  int32_t v2; // ebx
  CExtEquip *Equip; // rax

  std::map<int,HuoYueDuRecord>::clear(&this->m_HuoYueDuRecord);
  if ( this->m_pPlayer )
  {
    v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    if ( v2 >= Player::GetMaxLevel(this->m_pPlayer) )
      CHuoYueDu::AddHuoYueDuRecord(this, 6, 0, 1);
    Equip = Player::GetEquip(this->m_pPlayer);
    if ( CExtEquip::IsAllPosTop(Equip) )
      CHuoYueDu::AddHuoYueDuRecord(this, 10, 0, 1);
    if ( Player::IsMiniClient(this->m_pPlayer) )
      CHuoYueDu::AddHuoYueDuRecord(this, 7, 0, 0);
  }
}


#####################################
int32_t __cdecl CHuoYueDu::OnAskHuoYueDuInfo(CHuoYueDu *const this, Answer::NetPacket *inPacket)
{
  CHuoYueDu::SendHuoYueDuInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CHuoYueDu::OnGetHuoYueDuReward(CHuoYueDu *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t NeedHuoYueDu; // ebx
  CExtCharBag *Bag; // rax
  int32_t Index; // [rsp+1Ch] [rbp-24h]
  CfgHuoYueDuReward *pReward; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::GetHuoYueDuReward(v3, Index);
  if ( !pReward )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 2012);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  NeedHuoYueDu = pReward->NeedHuoYueDu;
  if ( NeedHuoYueDu > CHuoYueDu::CalculateHuoYueDu(this) )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pReward->Items, ITEM_CHANGE_REASON::ICR_HUO_YUE_DU) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 2012, NewRecord);
  CHuoYueDu::SendtHuoYueDuIcon(this);
  CHuoYueDu::SendHuoYueDuInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CHuoYueDu::OnSec(CHuoYueDu *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  HuoYueDuRecord *v4; // rax
  int32_t AddHuoYueDu; // r12d
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v7; // rax
  HuoYueDuRecord *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > it; // [rsp+10h] [rbp-30h] BYREF
  int32_t Index; // [rsp+1Ch] [rbp-24h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > __x; // [rsp+20h] [rbp-20h] BYREF
  CfgHuoYueDu *pHuoYueDu; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pHuoYueDu = CfgData::GetHuoYueDuCfg(v3, Index);
  if ( !pHuoYueDu )
    return 2;
  if ( !pHuoYueDu->IsCanSec )
    return 2;
  it._M_node = std::map<int,HuoYueDuRecord>::find(&this->m_HuoYueDuRecord, &Index)._M_node;
  __x._M_node = std::map<int,HuoYueDuRecord>::end(&this->m_HuoYueDuRecord)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator!=(&it, &__x)
    && std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->second.IsSec == 1 )
  {
    return 2;
  }
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          pHuoYueDu->Gold,
          CURRENCY_CHANGE_REASON::GCR_HUO_YUE_DU,
          pHuoYueDu->Index) )
    return 2;
  v4 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &Index);
  if ( v4->FinishTimes < pHuoYueDu->Count )
  {
    CHuoYueDu::AddKiaFuHuoYueDu(this, pHuoYueDu->AddHuoYueDu);
    AddHuoYueDu = pHuoYueDu->AddHuoYueDu;
    m_pPlayer = this->m_pPlayer;
    v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    CFestivalDoubleEleven::AddHuoYueDu(v7, m_pPlayer, AddHuoYueDu);
  }
  std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &Index)->IsSec = 1;
  v8 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &Index);
  v8->FinishTimes = pHuoYueDu->Count;
  CHuoYueDu::SendtHuoYueDuIcon(this);
  CHuoYueDu::SendHuoYueDuInfo(this);
  return 0;
}


#####################################
void __cdecl CHuoYueDu::AddKiaFuHuoYueDu(CHuoYueDu *const this, int32_t Value)
{
  CfgData *v2; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_NORMAL) <= 9 )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1926, Value);
    }
  }
}


#####################################
void __cdecl CHuoYueDu::AddHuoYueDuRecord(CHuoYueDu *const this, int8_t Type, int32_t Effect, bool Complete)
{
  CfgData *v4; // rax
  HuoYueDuTable *HuoYueDuTable; // rax
  std::pair<const int,CfgHuoYueDu> *v6; // rax
  int32_t FinishTimes; // ebx
  std::pair<const int,CfgHuoYueDu> *v8; // rax
  HuoYueDuRecord *v9; // rbx
  std::pair<const int,CfgHuoYueDu> *v10; // rax
  int32_t AddHuoYueDu; // edx
  int32_t v12; // r12d
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v14; // rax
  int32_t v15; // r12d
  Player *v16; // rbx
  CUniteServer *v17; // rax
  CfgData *v18; // rax
  HuoYueDuTable *v19; // rax
  std::pair<const int,CfgHuoYueDu> *v21; // rax
  int32_t v22; // ebx
  std::pair<const int,CfgHuoYueDu> *v23; // rax
  HuoYueDuRecord *v24; // rax
  std::pair<const int,CfgHuoYueDu> *v25; // rax
  int32_t v26; // ebx
  int32_t v27; // edx
  int32_t v28; // r12d
  Player *v29; // rbx
  CFestivalDoubleEleven *v30; // rax
  int32_t v31; // r12d
  Player *v32; // rbx
  CUniteServer *v33; // rax
  CfgData *v34; // rax
  HuoYueDuTable *v35; // rax
  std::pair<const int,CfgHuoYueDu> *v37; // rax
  std::pair<const int,CfgHuoYueDu> *v38; // rax
  int32_t v39; // ebx
  int32_t v40; // edx
  int32_t v41; // r12d
  Player *v42; // rbx
  CFestivalDoubleEleven *v43; // rax
  int32_t v44; // r12d
  Player *v45; // rbx
  CUniteServer *v46; // rax
  std::pair<const int,CfgHuoYueDu> *v47; // rax
  HuoYueDuRecord *v48; // rbx
  std::pair<const int,CfgHuoYueDu> *v49; // rax
  HuoYueDuRecord *v50; // rax
  CfgData *v51; // rax
  HuoYueDuTable *v52; // rax
  std::pair<const int,CfgHuoYueDu> *v53; // rax
  int32_t v54; // ebx
  std::pair<const int,CfgHuoYueDu> *v55; // rax
  HuoYueDuRecord *v56; // rax
  std::pair<const int,CfgHuoYueDu> *v57; // rax
  int32_t v58; // ebx
  int32_t v59; // edx
  int32_t v60; // r12d
  Player *v61; // rbx
  CFestivalDoubleEleven *v62; // rax
  int32_t v63; // r12d
  Player *v64; // rbx
  CUniteServer *v65; // rax
  CfgData *v66; // rax
  HuoYueDuTable *v67; // rax
  std::pair<const int,CfgHuoYueDu> *v68; // rax
  int32_t v69; // ebx
  std::pair<const int,CfgHuoYueDu> *v70; // rax
  int32_t v71; // ebx
  int32_t v72; // edx
  int32_t v73; // r12d
  Player *v74; // rbx
  CFestivalDoubleEleven *v75; // rax
  int32_t v76; // r12d
  Player *v77; // rbx
  CUniteServer *v78; // rax
  std::pair<const int,CfgHuoYueDu> *v79; // rax
  HuoYueDuRecord *v80; // rax
  std::pair<const int,CfgHuoYueDu> *v81; // rax
  int32_t v82; // ebx
  std::pair<const int,CfgHuoYueDu> *v83; // rax
  HuoYueDuRecord *v84; // rbx
  HuoYueDuTable CfgTable; // [rsp+20h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > it_3; // [rsp+50h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > it_2; // [rsp+60h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > it_1; // [rsp+70h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > it_0; // [rsp+80h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > it; // [rsp+90h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > __x; // [rsp+A0h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > v93; // [rsp+B0h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > v94; // [rsp+C0h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > v95; // [rsp+D0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgHuoYueDu> > v96; // [rsp+E0h] [rbp-20h] BYREF
  bool NeedSys; // [rsp+EBh] [rbp-15h]
  int32_t JoinCount; // [rsp+ECh] [rbp-14h]

  if ( this->m_pPlayer )
  {
    if ( Complete )
    {
      v4 = Answer::Singleton<CfgData>::instance();
      HuoYueDuTable = CfgData::GetHuoYueDuTable(v4);
      std::map<int,CfgHuoYueDu>::map(&CfgTable, HuoYueDuTable);
      for ( it._M_node = std::map<int,CfgHuoYueDu>::begin(&CfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator++(&it) )
      {
        __x._M_node = std::map<int,CfgHuoYueDu>::end(&CfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.Type == Type )
        {
          v6 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it);
          FinishTimes = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v6->first)->FinishTimes;
          if ( FinishTimes < std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.Count )
          {
            v8 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it);
            v9 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v8->first);
            v9->FinishTimes = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.Count;
            v10 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it);
            LODWORD(v9) = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v10->first)->FinishTimes;
            if ( (int)v9 >= std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.Count )
            {
              AddHuoYueDu = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.AddHuoYueDu;
              CHuoYueDu::AddKiaFuHuoYueDu(this, AddHuoYueDu);
              v12 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.AddHuoYueDu;
              m_pPlayer = this->m_pPlayer;
              v14 = Answer::Singleton<CFestivalDoubleEleven>::instance();
              CFestivalDoubleEleven::AddHuoYueDu(v14, m_pPlayer, v12);
              v15 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it)->second.AddHuoYueDu;
              v16 = this->m_pPlayer;
              v17 = Answer::Singleton<CUniteServer>::instance();
              CUniteServer::AddHuoYueDu(v17, v16, v15);
            }
            CHuoYueDu::SendHuoYueDuInfo(this);
            CHuoYueDu::SendtHuoYueDuIcon(this);
          }
          break;
        }
      }
      std::map<int,CfgHuoYueDu>::~map(&CfgTable);
    }
    else
    {
      NeedSys = 0;
      switch ( Type )
      {
        case 1:
          v18 = Answer::Singleton<CfgData>::instance();
          v19 = CfgData::GetHuoYueDuTable(v18);
          std::map<int,CfgHuoYueDu>::map(&CfgTable, v19);
          for ( it_0._M_node = std::map<int,CfgHuoYueDu>::begin(&CfgTable)._M_node;
                ;
                std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator++(&it_0) )
          {
            v93._M_node = std::map<int,CfgHuoYueDu>::end(&CfgTable)._M_node;
            if ( !std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator!=(&it_0, &v93) )
              goto LABEL_57;
            if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.Type == Type
              && std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.Effect == Effect )
            {
              break;
            }
          }
          v21 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0);
          v22 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v21->first)->FinishTimes;
          if ( v22 < std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.Count )
          {
            v23 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0);
            v24 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v23->first);
            ++v24->FinishTimes;
            v25 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0);
            v26 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v25->first)->FinishTimes;
            if ( v26 >= std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.Count )
            {
              v27 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.AddHuoYueDu;
              CHuoYueDu::AddKiaFuHuoYueDu(this, v27);
              v28 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.AddHuoYueDu;
              v29 = this->m_pPlayer;
              v30 = Answer::Singleton<CFestivalDoubleEleven>::instance();
              CFestivalDoubleEleven::AddHuoYueDu(v30, v29, v28);
              v31 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_0)->second.AddHuoYueDu;
              v32 = this->m_pPlayer;
              v33 = Answer::Singleton<CUniteServer>::instance();
              CUniteServer::AddHuoYueDu(v33, v32, v31);
            }
            NeedSys = 1;
          }
          goto LABEL_57;
        case 2:
          v34 = Answer::Singleton<CfgData>::instance();
          v35 = CfgData::GetHuoYueDuTable(v34);
          std::map<int,CfgHuoYueDu>::map(&CfgTable, v35);
          it_1._M_node = std::map<int,CfgHuoYueDu>::begin(&CfgTable)._M_node;
          while ( 2 )
          {
            v94._M_node = std::map<int,CfgHuoYueDu>::end(&CfgTable)._M_node;
            if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator!=(&it_1, &v94) )
            {
              if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.Type != Type
                || std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.Effect != Effect )
              {
                std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator++(&it_1);
                continue;
              }
              JoinCount = Player::getRecord(this->m_pPlayer, Effect);
              v37 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1);
              if ( v37->second.Count > JoinCount )
              {
                v49 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1);
                v50 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v49->first);
                v50->FinishTimes = JoinCount;
                NeedSys = 1;
              }
              else
              {
                v38 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1);
                v39 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v38->first)->FinishTimes;
                if ( v39 < std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.Count )
                {
                  v40 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.AddHuoYueDu;
                  CHuoYueDu::AddKiaFuHuoYueDu(this, v40);
                  v41 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.AddHuoYueDu;
                  v42 = this->m_pPlayer;
                  v43 = Answer::Singleton<CFestivalDoubleEleven>::instance();
                  CFestivalDoubleEleven::AddHuoYueDu(v43, v42, v41);
                  v44 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.AddHuoYueDu;
                  v45 = this->m_pPlayer;
                  v46 = Answer::Singleton<CUniteServer>::instance();
                  CUniteServer::AddHuoYueDu(v46, v45, v44);
                }
                v47 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1);
                v48 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v47->first);
                v48->FinishTimes = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_1)->second.Count;
                NeedSys = 1;
              }
            }
            break;
          }
          goto LABEL_57;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
          v51 = Answer::Singleton<CfgData>::instance();
          v52 = CfgData::GetHuoYueDuTable(v51);
          std::map<int,CfgHuoYueDu>::map(&CfgTable, v52);
          it_2._M_node = std::map<int,CfgHuoYueDu>::begin(&CfgTable)._M_node;
          while ( 2 )
          {
            v95._M_node = std::map<int,CfgHuoYueDu>::end(&CfgTable)._M_node;
            if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator!=(&it_2, &v95) )
            {
              if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.Type != Type )
              {
                std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator++(&it_2);
                continue;
              }
              v53 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2);
              v54 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v53->first)->FinishTimes;
              if ( v54 < std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.Count )
              {
                v55 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2);
                v56 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v55->first);
                ++v56->FinishTimes;
                NeedSys = 1;
                v57 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2);
                v58 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v57->first)->FinishTimes;
                if ( v58 == std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.Count )
                {
                  v59 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.AddHuoYueDu;
                  CHuoYueDu::AddKiaFuHuoYueDu(this, v59);
                  v60 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.AddHuoYueDu;
                  v61 = this->m_pPlayer;
                  v62 = Answer::Singleton<CFestivalDoubleEleven>::instance();
                  CFestivalDoubleEleven::AddHuoYueDu(v62, v61, v60);
                  v63 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_2)->second.AddHuoYueDu;
                  v64 = this->m_pPlayer;
                  v65 = Answer::Singleton<CUniteServer>::instance();
                  CUniteServer::AddHuoYueDu(v65, v64, v63);
                }
              }
            }
            break;
          }
          goto LABEL_57;
        case 8:
        case 17:
          v66 = Answer::Singleton<CfgData>::instance();
          v67 = CfgData::GetHuoYueDuTable(v66);
          std::map<int,CfgHuoYueDu>::map(&CfgTable, v67);
          it_3._M_node = std::map<int,CfgHuoYueDu>::begin(&CfgTable)._M_node;
          break;
        default:
          goto LABEL_58;
      }
      while ( 1 )
      {
        v96._M_node = std::map<int,CfgHuoYueDu>::end(&CfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator!=(&it_3, &v96) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.Type == Type )
        {
          v68 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3);
          v69 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v68->first)->FinishTimes;
          if ( v69 < std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.Count )
          {
            v70 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3);
            v71 = Effect + std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v70->first)->FinishTimes;
            if ( v71 >= std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.Count )
            {
              v72 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.AddHuoYueDu;
              CHuoYueDu::AddKiaFuHuoYueDu(this, v72);
              v73 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.AddHuoYueDu;
              v74 = this->m_pPlayer;
              v75 = Answer::Singleton<CFestivalDoubleEleven>::instance();
              CFestivalDoubleEleven::AddHuoYueDu(v75, v74, v73);
              v76 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.AddHuoYueDu;
              v77 = this->m_pPlayer;
              v78 = Answer::Singleton<CUniteServer>::instance();
              CUniteServer::AddHuoYueDu(v78, v77, v76);
            }
            NeedSys = 1;
            v79 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3);
            v80 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v79->first);
            v80->FinishTimes += Effect;
            v81 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3);
            v82 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v81->first)->FinishTimes;
            if ( v82 > std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.Count )
            {
              v83 = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3);
              v84 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &v83->first);
              v84->FinishTimes = std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator->(&it_3)->second.Count;
            }
          }
          break;
        }
        std::_Rb_tree_iterator<std::pair<int const,CfgHuoYueDu>>::operator++(&it_3);
      }
LABEL_57:
      std::map<int,CfgHuoYueDu>::~map(&CfgTable);
LABEL_58:
      if ( NeedSys )
      {
        CHuoYueDu::SendHuoYueDuInfo(this);
        CHuoYueDu::SendtHuoYueDuIcon(this);
      }
    }
  }
}


#####################################
void __cdecl CHuoYueDu::SendHuoYueDuInfo(CHuoYueDu *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  int32_t Record; // eax
  std::pair<const int,HuoYueDuRecord> *v5; // rax
  std::pair<const int,HuoYueDuRecord> *v6; // rax
  std::pair<const int,HuoYueDuRecord> *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CEEu);
    if ( packet )
    {
      nSize = std::map<int,HuoYueDuRecord>::size(&this->m_HuoYueDuRecord);
      v3 = CHuoYueDu::CalculateHuoYueDu(this);
      Answer::NetPacket::writeInt32(packet, v3);
      Record = Player::getRecord(this->m_pPlayer, 2012);
      Answer::NetPacket::writeInt32(packet, Record);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,HuoYueDuRecord>::begin(&this->m_HuoYueDuRecord)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator++(&it) )
      {
        __x._M_node = std::map<int,HuoYueDuRecord>::end(&this->m_HuoYueDuRecord)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator!=(&it, &__x) )
          break;
        v5 = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->first);
        v6 = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->second.FinishTimes);
        v7 = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v7->second.IsSec);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CHuoYueDu::CalculateHuoYueDu(CHuoYueDu *const this)
{
  int first; // ebx
  CfgData *v2; // rax
  std::pair<const int,HuoYueDuRecord> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  CfgHuoYueDu *pHuoYueDu; // [rsp+38h] [rbp-18h]

  Count = 0;
  for ( it._M_node = std::map<int,HuoYueDuRecord>::begin(&this->m_HuoYueDuRecord)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator++(&it) )
  {
    __x._M_node = std::map<int,HuoYueDuRecord>::end(&this->m_HuoYueDuRecord)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->first;
    v2 = Answer::Singleton<CfgData>::instance();
    pHuoYueDu = CfgData::GetHuoYueDuCfg(v2, first);
    if ( pHuoYueDu )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it);
      if ( v3->second.FinishTimes >= pHuoYueDu->Count )
        Count += pHuoYueDu->AddHuoYueDu;
    }
  }
  return Count;
}


#####################################
int32_t __cdecl CHuoYueDu::RewardCount(CHuoYueDu *const this)
{
  CfgData *v1; // rax
  HuoYueDuRewardTable *HuoYueDuRewardTable; // rax
  std::pair<const signed char,CfgHuoYueDuReward> *v3; // rax
  std::pair<const signed char,CfgHuoYueDuReward> *v4; // rax
  int32_t v5; // ebx
  HuoYueDuRewardTable RewardTable; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgHuoYueDuReward> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgHuoYueDuReward> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t Count; // [rsp+64h] [rbp-1Ch]
  int32_t HuoYueDu; // [rsp+68h] [rbp-18h]
  int32_t Record; // [rsp+6Ch] [rbp-14h]

  Count = 0;
  HuoYueDu = CHuoYueDu::CalculateHuoYueDu(this);
  v1 = Answer::Singleton<CfgData>::instance();
  HuoYueDuRewardTable = CfgData::GetHuoYueDuRewardTable(v1);
  std::map<signed char,CfgHuoYueDuReward>::map(&RewardTable, HuoYueDuRewardTable);
  for ( it._M_node = std::map<signed char,CfgHuoYueDuReward>::begin(&RewardTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,CfgHuoYueDuReward>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,CfgHuoYueDuReward>::end(&RewardTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,CfgHuoYueDuReward>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,CfgHuoYueDuReward>>::operator->(&it);
    if ( v3->second.NeedHuoYueDu <= HuoYueDu )
    {
      Record = Player::getRecord(this->m_pPlayer, 2012);
      v4 = std::_Rb_tree_iterator<std::pair<signed char const,CfgHuoYueDuReward>>::operator->(&it);
      if ( (Record & (1 << (LOBYTE(v4->second.Id) - 1))) <= 0 )
        ++Count;
    }
  }
  v5 = Count;
  std::map<signed char,CfgHuoYueDuReward>::~map(&RewardTable);
  return v5;
}


#####################################
void __cdecl CHuoYueDu::GetHuoYueDuIcon(CHuoYueDu *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 197) )
    {
      CHuoYueDu::GettHuoYueDuIcon(&icon, this);
      std::list<ShowIcon>::push_back(IconList, &icon);
    }
  }
}


#####################################
void __cdecl CHuoYueDu::SendtHuoYueDuIcon(CHuoYueDu *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 197) )
    {
      CHuoYueDu::GettHuoYueDuIcon(&icon, this);
      Player::SendIconState(this->m_pPlayer, &icon);
    }
  }
}


