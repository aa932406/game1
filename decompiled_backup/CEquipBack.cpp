// Decompiled methods for class: CEquipBack
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl CEquipBack::Init(CEquipBack *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery *v5; // rax
  BackDepot *v6; // rax
  const char *v7; // rax
  BackLimitInfo *v8; // rax
  char szSQL_1[4096]; // [rsp+10h] [rbp-20C0h] BYREF
  char szSQL[4096]; // [rsp+1010h] [rbp-10C0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+2010h] [rbp-C0h] BYREF
  BackLimitInfo stu_1; // [rsp+2040h] [rbp-90h] BYREF
  BackDepot stu_0; // [rsp+2050h] [rbp-80h] BYREF
  BackRecord stu; // [rsp+2060h] [rbp-70h] BYREF
  Answer::MySqlQuery result_1; // [rsp+2080h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+20A0h] [rbp-30h] BYREF
  int8_t Type; // [rsp+20BFh] [rbp-11h]

  if ( line != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `mem_equip_back_record` order by nTime desc Limit 0, %d", 50);
    v3 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      memset(&stu, 0, sizeof(stu));
      std::string::string(&stu.name);
      stu.nId = Answer::MySqlQuery::getIntValue(&result, "nId", 0);
      stu.nType = Answer::MySqlQuery::getIntValue(&result, "nType", 0);
      stu.nTime = Answer::MySqlQuery::getIntValue(&result, "nTime", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D6C66);
      std::string::operator=(&stu.name, StringValue);
      std::list<BackRecord>::push_back(&this->m_BackRecord, &stu);
      Answer::MySqlQuery::nextRow(&result);
      BackRecord::~BackRecord(&stu);
    }
    memset(szSQL_1, 0, sizeof(szSQL_1));
    snprintf(szSQL_1, 0xFFFu, "SELECT * FROM `mem_equip_back_depot`");
    v5 = Answer::MySqlDBGuard::query(&db, szSQL_1);
    Answer::MySqlQuery::MySqlQuery(&result_1, v5);
    while ( !Answer::MySqlQuery::eof(&result_1) )
    {
      Type = Answer::MySqlQuery::getIntValue(&result_1, "nType", 0);
      if ( Type == 1 )
      {
        stu_0 = 0;
        stu_0.Count = Answer::MySqlQuery::getIntValue(&result_1, "nCount", 0);
        stu_0.nId = Answer::MySqlQuery::getIntValue(&result_1, "nId", 0);
        v6 = std::map<int,BackDepot>::operator[](&this->m_BackDepotMap, (const int *const)&stu_0);
        *v6 = stu_0;
      }
      else if ( Type == 2 )
      {
        *(_QWORD *)&stu_1.nId = 0;
        stu_1.sLastName._M_dataplus._M_p = 0;
        std::string::string(&stu_1.sLastName);
        stu_1.nId = Answer::MySqlQuery::getIntValue(&result_1, "nId", 0);
        stu_1.nCount = Answer::MySqlQuery::getIntValue(&result_1, "nCount", 0);
        v7 = Answer::MySqlQuery::getStringValue(&result_1, "name", &byte_8D6C66);
        std::string::operator=(&stu_1.sLastName, v7);
        v8 = std::map<int,BackLimitInfo>::operator[](&this->m_BackLimitInfoMap, &stu_1.nId);
        BackLimitInfo::operator=(v8, &stu_1);
        BackLimitInfo::~BackLimitInfo(&stu_1);
      }
      Answer::MySqlQuery::nextRow(&result_1);
    }
    Answer::MySqlQuery::~MySqlQuery(&result_1);
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
int32_t __cdecl CEquipBack::OnGoldBack(CEquipBack *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  int32_t v3; // ebx
  ChrTask *Task; // rax
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  CfgData *v7; // rax
  std::pair<const int,BackLimitInfo> *v8; // rax
  CExtCharBag *Bag; // rax
  GameService *v10; // rax
  int v11; // r12d
  CharId_t Cid; // rax
  ItemData *v13; // rax
  uint32_t WOffset; // eax
  GameService *v15; // rax
  CfgData *v16; // rax
  std::pair<const int,BackLimitInfo> *v17; // rax
  CExtCharBag *v18; // rax
  GameService *v19; // rax
  int v20; // r12d
  CharId_t v21; // rax
  uint32_t v22; // eax
  GameService *v23; // rax
  BackLimitInfo stu_2; // [rsp+20h] [rbp-1E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it_0; // [rsp+30h] [rbp-1D0h] BYREF
  BackLimitInfo stu_1; // [rsp+40h] [rbp-1C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it; // [rsp+50h] [rbp-1B0h] BYREF
  ItemData stu_0; // [rsp+60h] [rbp-1A0h] BYREF
  BackRecord stu; // [rsp+70h] [rbp-190h] BYREF
  ItemDataList ItemList; // [rsp+90h] [rbp-170h] BYREF
  std::_List_const_iterator<int> EquipIt; // [rsp+A0h] [rbp-160h] BYREF
  Int32Vector vSlot; // [rsp+B0h] [rbp-150h] BYREF
  int32_t nId; // [rsp+CCh] [rbp-134h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+D0h] [rbp-130h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v37; // [rsp+E0h] [rbp-120h] BYREF
  _BYTE v38[16]; // [rsp+F0h] [rbp-110h] BYREF
  BackLimitInfo p_stu; // [rsp+100h] [rbp-100h] BYREF
  std::string val; // [rsp+110h] [rbp-F0h] BYREF
  std::_List_iterator<ItemData> v41; // [rsp+120h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v42; // [rsp+130h] [rbp-D0h] BYREF
  _BYTE v43[16]; // [rsp+140h] [rbp-C0h] BYREF
  BackLimitInfo v44; // [rsp+150h] [rbp-B0h] BYREF
  std::string v45; // [rsp+160h] [rbp-A0h] BYREF
  _BYTE v46[16]; // [rsp+170h] [rbp-90h] BYREF
  BackRecord v47; // [rsp+180h] [rbp-80h] BYREF
  BackRecord v48; // [rsp+1A0h] [rbp-60h] BYREF
  const EquipBack *pCfg; // [rsp+1C0h] [rbp-40h]
  int32_t RecovValue; // [rsp+1CCh] [rbp-34h]
  Answer::NetPacket *packet_0; // [rsp+1D0h] [rbp-30h]
  int32_t DayDiff; // [rsp+1DCh] [rbp-24h]
  int32_t DayDiff_0; // [rsp+1E0h] [rbp-20h]
  int32_t RecovValue_0; // [rsp+1E4h] [rbp-1Ch]
  Answer::NetPacket *packet_1; // [rsp+1E8h] [rbp-18h]

  if ( pPlayer && packet )
  {
    Task = Player::GetTask(pPlayer);
    ChrTask::updateTaskCount(Task, 42, 1);
    nId = Answer::NetPacket::readInt32(packet);
    v5 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v5);
    pCfg = CfgEquipTable::GetEquipBackCfg(EquipTable, nId);
    if ( !pCfg )
      return 10002;
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(pPlayer, packet, &vSlot);
    EquipIt._M_node = std::list<int>::begin(&pCfg->nEquipList)._M_node;
    std::list<ItemData>::list(&ItemList);
    while ( 1 )
    {
      __x._M_node = std::list<int>::end(&pCfg->nEquipList)._M_node;
      if ( !std::_List_const_iterator<int>::operator!=(&EquipIt, &__x) )
        break;
      *(_QWORD *)&stu_0.m_nId = 0x200000000LL;
      stu_0.m_nCount = 1;
      stu_0.m_nId = *std::_List_const_iterator<int>::operator*(&EquipIt);
      std::list<ItemData>::push_back(&ItemList, &stu_0);
      std::_List_const_iterator<int>::operator++(&EquipIt, 0);
    }
    if ( !std::list<ItemData>::size(&ItemList) )
    {
      v3 = 10002;
LABEL_50:
      std::list<ItemData>::~list(&ItemList);
      std::vector<int>::~vector(&vSlot);
      return v3;
    }
    if ( pCfg->nType == 1 )
    {
      if ( pCfg->nLimitNum <= 0 )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      if ( pCfg->nDisplayDay > 0 )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        DayDiff = CfgData::getServerDiffDay(v7, SERVER_TYPE::SVT_NORMAL) + 1;
        if ( pCfg->nDisplayDay > DayDiff )
        {
          v3 = 10002;
          goto LABEL_50;
        }
      }
      it._M_node = std::map<int,BackLimitInfo>::find(&this->m_BackLimitInfoMap, &nId)._M_node;
      v37._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&it, &v37) )
      {
        v8 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
        if ( v8->second.nCount >= pCfg->nLimitNum )
        {
          v3 = 10002;
          goto LABEL_50;
        }
      }
      if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      Bag = Player::GetBag(pPlayer);
      if ( !CExtCharBag::RemoveItem(Bag, &vSlot, &ItemList, ITEM_CHANGE_REASON::ICR_EQUIP_GOLD_BACK) )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      RecovValue = pCfg->nRecovValues;
      Player::AddCurrency(
        pPlayer,
        (const CURRENCY_TYPE)pCfg->nRecovType,
        RecovValue,
        CURRENCY_CHANGE_REASON::GCR_EQUIP_GOLD_BACK,
        0);
      stu_1.sLastName._M_dataplus._M_p = 0;
      std::string::string(&stu_1.sLastName);
      stu_1.nCount = 1;
      stu_1.nId = nId;
      Player::getName((const Player *const)v38);
      std::string::operator=(&stu_1.sLastName, v38);
      std::string::~string(v38);
      BackLimitInfo::BackLimitInfo(&p_stu, &stu_1);
      CEquipBack::AddLimitCount(this, &p_stu);
      BackLimitInfo::~BackLimitInfo(&p_stu);
      CEquipBack::SendEquipBackLimitChange(this, pPlayer, nId);
      v10 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v10, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet_0 )
      {
        Answer::NetPacket::writeInt32(packet_0, 451);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet_0, &val);
        std::string::~string(&val);
        Cid = Player::getCid(pPlayer);
        Answer::NetPacket::writeInt64(packet_0, Cid);
        v41._M_node = std::list<ItemData>::begin(&ItemList)._M_node;
        v13 = std::_List_iterator<ItemData>::operator->(&v41);
        Answer::NetPacket::writeInt32(packet_0, v13->m_nId);
        Answer::NetPacket::writeInt32(packet_0, RecovValue);
        WOffset = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, WOffset);
        v15 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v15, 0, packet_0);
        v11 = 1;
      }
      else
      {
        v3 = 10002;
        v11 = 0;
      }
      BackLimitInfo::~BackLimitInfo(&stu_1);
      if ( !v11 )
        goto LABEL_50;
    }
    else
    {
      if ( pCfg->nType != 2 )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      v16 = Answer::Singleton<CfgData>::instance();
      DayDiff_0 = CfgData::getServerDiffDay(v16, SERVER_TYPE::SVT_NORMAL);
      if ( DayDiff_0 + 1 > pCfg->nOpenDay )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      if ( pCfg->nLimitNum <= 0 )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      it_0._M_node = std::map<int,BackLimitInfo>::find(&this->m_BackLimitInfoMap, &nId)._M_node;
      v42._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&it_0, &v42) )
      {
        v17 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it_0);
        if ( v17->second.nCount >= pCfg->nLimitNum )
        {
          v3 = 10002;
          goto LABEL_50;
        }
      }
      if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      v18 = Player::GetBag(pPlayer);
      if ( !CExtCharBag::RemoveItem(v18, &vSlot, &ItemList, ITEM_CHANGE_REASON::ICR_EQUIP_GOLD_BACK) )
      {
        v3 = 10002;
        goto LABEL_50;
      }
      RecovValue_0 = pCfg->nRecovValues;
      Player::AddCurrency(
        pPlayer,
        (const CURRENCY_TYPE)pCfg->nRecovType,
        RecovValue_0,
        CURRENCY_CHANGE_REASON::GCR_EQUIP_GOLD_BACK,
        0);
      stu_2.sLastName._M_dataplus._M_p = 0;
      std::string::string(&stu_2.sLastName);
      stu_2.nCount = 1;
      stu_2.nId = nId;
      Player::getName((const Player *const)v43);
      std::string::operator=(&stu_2.sLastName, v43);
      std::string::~string(v43);
      BackLimitInfo::BackLimitInfo(&v44, &stu_2);
      CEquipBack::AddLimitCount(this, &v44);
      BackLimitInfo::~BackLimitInfo(&v44);
      CEquipBack::SendEquipBackLimitChange(this, pPlayer, nId);
      v19 = Answer::Singleton<GameService>::instance();
      packet_1 = GameService::popNetpacket(v19, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet_1 )
      {
        Answer::NetPacket::writeInt32(packet_1, 443);
        v21 = Player::getCid(pPlayer);
        Answer::NetPacket::writeInt64(packet_1, v21);
        Player::getName((const Player *const)&v45);
        Answer::NetPacket::writeUTF8(packet_1, &v45);
        std::string::~string(&v45);
        Answer::NetPacket::writeInt32(packet_1, nId);
        Answer::NetPacket::writeInt8(packet_1, pCfg->nRecovType);
        Answer::NetPacket::writeInt32(packet_1, RecovValue_0);
        v22 = Answer::NetPacket::getWOffset(packet_1);
        Answer::NetPacket::setSize(packet_1, v22);
        v23 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v23, packet_1);
        v20 = 1;
      }
      else
      {
        v3 = 10002;
        v20 = 0;
      }
      BackLimitInfo::~BackLimitInfo(&stu_2);
      if ( !v20 )
        goto LABEL_50;
    }
    memset(&stu, 0, sizeof(stu));
    std::string::string(&stu.name);
    stu.nId = nId;
    stu.nType = 1;
    stu.nTime = Answer::DayTime::now();
    Player::getName((const Player *const)v46);
    std::string::operator=(&stu.name, v46);
    std::string::~string(v46);
    BackRecord::BackRecord(&v47, &stu);
    CEquipBack::SendEquipBackOnRecord(this, pPlayer, &v47);
    BackRecord::~BackRecord(&v47);
    BackRecord::BackRecord(&v48, &stu);
    CEquipBack::AddRecord(this, &v48);
    BackRecord::~BackRecord(&v48);
    v3 = 0;
    BackRecord::~BackRecord(&stu);
    goto LABEL_50;
  }
  return 10002;
}


#####################################
void __cdecl CEquipBack::AddLimitCount(CEquipBack *const this, BackLimitInfo *p_stu)
{
  std::pair<const int,BackLimitInfo> *v2; // rax
  std::pair<const int,BackLimitInfo> *v3; // rax
  BackLimitInfo *v4; // rax
  std::pair<const int,BackLimitInfo> *v5; // rax
  int32_t nCount; // r12d
  int first; // ebx
  DBService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > itTmp; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it; // [rsp+20h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > __x; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v13; // [rsp+50h] [rbp-30h] BYREF
  std::string p_name; // [rsp+60h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_DepotLock);
  it._M_node = std::map<int,BackLimitInfo>::find(&this->m_BackLimitInfoMap, &p_stu->nId)._M_node;
  __x._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&it, &__x) )
  {
    v2 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
    v2->second.nCount += p_stu->nCount;
    v3 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
    std::string::operator=(&v3->second.sLastName, &p_stu->sLastName);
    std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it)->second.nId = p_stu->nId;
  }
  else
  {
    v4 = std::map<int,BackLimitInfo>::operator[](&this->m_BackLimitInfoMap, &p_stu->nId);
    BackLimitInfo::operator=(v4, p_stu);
  }
  itTmp._M_node = std::map<int,BackLimitInfo>::find(&this->m_BackLimitInfoMap, &p_stu->nId)._M_node;
  v13._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&itTmp, &v13) )
  {
    v5 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&itTmp);
    std::string::string(&p_name, &v5->second.sLastName);
    nCount = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&itTmp)->second.nCount;
    first = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&itTmp)->first;
    v8 = Answer::Singleton<DBService>::instance();
    DBService::SaveEquipBackCount(v8, first, 2, nCount, &p_name);
    std::string::~string(&p_name);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CEquipBack::ChangeDeptCount(CEquipBack *const this, BackDepot stu)
{
  std::pair<const int,BackDepot> *v2; // rax
  std::pair<const int,BackDepot> *v3; // rax
  BackDepot *v4; // rax
  int32_t Count; // r12d
  int first; // ebx
  DBService *v7; // rax
  BackDepot stua; // [rsp+0h] [rbp-80h] BYREF
  CEquipBack *thisa; // [rsp+8h] [rbp-78h]
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > itTmp; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > it; // [rsp+20h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > __x; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > v14; // [rsp+50h] [rbp-30h] BYREF
  std::string p_name; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v16[17]; // [rsp+6Fh] [rbp-11h] BYREF

  thisa = this;
  stua = stu;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_DepotLock);
  it._M_node = std::map<int,BackDepot>::find(&this->m_BackDepotMap, (const int *const)&stua)._M_node;
  __x._M_node = std::map<int,BackDepot>::end(&thisa->m_BackDepotMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator!=(&it, &__x) )
  {
    v2 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
    v2->second.Count += stua.Count;
    v3 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
    v3->second.nId = stua.nId;
  }
  else
  {
    v4 = std::map<int,BackDepot>::operator[](&thisa->m_BackDepotMap, (const int *const)&stua);
    *v4 = stua;
  }
  itTmp._M_node = std::map<int,BackDepot>::find(&thisa->m_BackDepotMap, (const int *const)&stua)._M_node;
  v14._M_node = std::map<int,BackDepot>::end(&thisa->m_BackDepotMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator!=(&itTmp, &v14) )
  {
    std::allocator<char>::allocator(v16);
    std::string::string(&p_name, &byte_8D6C66, v16);
    Count = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&itTmp)->second.Count;
    first = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&itTmp)->first;
    v7 = Answer::Singleton<DBService>::instance();
    DBService::SaveEquipBackCount(v7, first, 1, Count, &p_name);
    std::string::~string(&p_name);
    std::allocator<char>::~allocator(v16);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CEquipBack::AddRecord(CEquipBack *const this, BackRecord *p_stu)
{
  int32_t nTime; // r13d
  int8_t nType; // r12
  int32_t nId; // ebx
  DBService *v5; // rax
  Answer::MutexGuard lock; // [rsp+10h] [rbp-40h] BYREF
  std::string p_name; // [rsp+20h] [rbp-30h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_RecordLock);
  if ( std::list<BackRecord>::size(&this->m_BackRecord) > 0x32 )
    std::list<BackRecord>::pop_front(&this->m_BackRecord);
  std::string::string(&p_name, &p_stu->name);
  nTime = p_stu->nTime;
  nType = p_stu->nType;
  nId = p_stu->nId;
  v5 = Answer::Singleton<DBService>::instance();
  DBService::SaveEquipBackRecord(v5, nId, nType, nTime, &p_name);
  std::string::~string(&p_name);
  std::list<BackRecord>::push_back(&this->m_BackRecord, p_stu);
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CEquipBack::KiaFuEquipBack(
        CEquipBack *const this,
        int32_t Index,
        int32_t EquipId,
        int32_t Mid,
        Player *pPlayer)
{
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  CfgData *v7; // rax
  std::pair<const int,BackLimitInfo> *v8; // rax
  std::_Ios_Openmode v9; // eax
  CharId_t Cid; // rbx
  DBService *v11; // rax
  GameService *v12; // rax
  CharId_t v13; // rax
  uint32_t WOffset; // eax
  GameService *v15; // rax
  int32_t Indexa; // [rsp+24h] [rbp-26Ch] BYREF
  CEquipBack *thisa; // [rsp+28h] [rbp-268h]
  _BYTE v20[16]; // [rsp+30h] [rbp-260h] BYREF
  __int64 v21; // [rsp+40h] [rbp-250h] BYREF
  MemChrBag item; // [rsp+1A0h] [rbp-F0h] BYREF
  BackLimitInfo stu; // [rsp+1C0h] [rbp-D0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it; // [rsp+1D0h] [rbp-C0h] BYREF
  ItemDataList ItemList; // [rsp+1E0h] [rbp-B0h] BYREF
  std::_List_const_iterator<int> EquipIt; // [rsp+1F0h] [rbp-A0h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+200h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v28; // [rsp+210h] [rbp-80h] BYREF
  std::string Param; // [rsp+220h] [rbp-70h] BYREF
  std::string val; // [rsp+230h] [rbp-60h] BYREF
  _BYTE v31[16]; // [rsp+240h] [rbp-50h] BYREF
  BackLimitInfo p_stu; // [rsp+250h] [rbp-40h] BYREF
  const EquipBack *pCfg; // [rsp+268h] [rbp-28h]
  int32_t DayDiff; // [rsp+274h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+278h] [rbp-18h]

  thisa = this;
  Indexa = Index;
  if ( pPlayer )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v5);
    pCfg = CfgEquipTable::GetEquipBackCfg(EquipTable, Indexa);
    if ( pCfg )
    {
      EquipIt._M_node = std::list<int>::begin(&pCfg->nEquipList)._M_node;
      std::list<ItemData>::list(&ItemList);
      while ( 1 )
      {
        __x._M_node = std::list<int>::end(&pCfg->nEquipList)._M_node;
        if ( !std::_List_const_iterator<int>::operator!=(&EquipIt, &__x) )
          break;
        if ( *std::_List_const_iterator<int>::operator*(&EquipIt) != EquipId )
          goto LABEL_17;
        std::_List_const_iterator<int>::operator++(&EquipIt, 0);
      }
      if ( std::list<int>::size(&pCfg->nEquipList) )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        DayDiff = CfgData::getServerDiffDay(v7, SERVER_TYPE::SVT_NORMAL);
        if ( DayDiff + 1 <= pCfg->nOpenDay && pCfg->nLimitNum > 0 )
        {
          it._M_node = std::map<int,BackLimitInfo>::find(&thisa->m_BackLimitInfoMap, &Indexa)._M_node;
          v28._M_node = std::map<int,BackLimitInfo>::end(&thisa->m_BackLimitInfoMap)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&it, &v28)
            || (v8 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it),
                v8->second.nCount < pCfg->nLimitNum) )
          {
            if ( pCfg->nRecovType >= 0 && pCfg->nRecovValues > 0 )
            {
              *(_QWORD *)&item.itemId = 0x400000000LL;
              memset(&item.itemCount, 0, 24);
              item.itemId = TranseCurrencyItem((CURRENCY_TYPE)pCfg->nRecovType);
              item.itemCount = pCfg->nRecovValues;
              v9 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
                v20,
                (unsigned int)v9);
              std::ostream::operator<<(&v21, (unsigned int)EquipId);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, v20);
              Cid = Player::getCid(pPlayer);
              v11 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v11, 0, Cid, 6373, &item, ITEM_CHANGE_REASON::ICR_KAI_HUO_EQUIP_BACK, &Param, 0);
              std::string::~string(&Param);
              v12 = Answer::Singleton<GameService>::instance();
              packet = GameService::popNetpacket(v12, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
              if ( packet )
              {
                Answer::NetPacket::writeInt32(packet, 441);
                v13 = Player::getCid(pPlayer);
                Answer::NetPacket::writeInt64(packet, v13);
                Player::getName((const Player *const)&val);
                Answer::NetPacket::writeUTF8(packet, &val);
                std::string::~string(&val);
                Answer::NetPacket::writeInt8(packet, 2);
                Answer::NetPacket::writeInt32(packet, EquipId);
                Answer::NetPacket::writeInt32(packet, 1);
                Answer::NetPacket::writeInt8(packet, pCfg->nRecovType);
                Answer::NetPacket::writeInt32(packet, pCfg->nRecovValues);
                WOffset = Answer::NetPacket::getWOffset(packet);
                Answer::NetPacket::setSize(packet, WOffset);
                v15 = Answer::Singleton<GameService>::instance();
                GameService::worldBroadcast(v15, packet);
                *(_QWORD *)&stu.nId = 0;
                stu.sLastName._M_dataplus._M_p = 0;
                std::string::string(&stu.sLastName);
                stu.nCount = 1;
                stu.nId = Indexa;
                Player::getName((const Player *const)v31);
                std::string::operator=(&stu.sLastName, v31);
                std::string::~string(v31);
                BackLimitInfo::BackLimitInfo(&p_stu, &stu);
                CEquipBack::AddLimitCount(thisa, &p_stu);
                BackLimitInfo::~BackLimitInfo(&p_stu);
                CEquipBack::SendEquipBackLimitChange(thisa, pPlayer, Indexa);
                BackLimitInfo::~BackLimitInfo(&stu);
              }
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v20);
            }
          }
        }
      }
LABEL_17:
      std::list<ItemData>::~list(&ItemList);
    }
  }
}


#####################################
int32_t __cdecl CEquipBack::OnBuyBack(CEquipBack *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgEquipTable *EquipTable; // rax
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v8; // rax
  GameService *v9; // rax
  CharId_t Cid; // rax
  MemChrBag *v11; // rax
  uint32_t WOffset; // eax
  GameService *v13; // rax
  MemChrBag stu_0; // [rsp+20h] [rbp-140h] BYREF
  BackRecord stu; // [rsp+40h] [rbp-120h] BYREF
  BackDepot Deptstu; // [rsp+60h] [rbp-100h]
  std::_List_const_iterator<int> EquipIt; // [rsp+70h] [rbp-F0h] BYREF
  MemChrBagVector ItemVt; // [rsp+80h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > it; // [rsp+A0h] [rbp-C0h] BYREF
  int32_t nId; // [rsp+ACh] [rbp-B4h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > __x; // [rsp+B0h] [rbp-B0h] BYREF
  std::_List_const_iterator<int> v23; // [rsp+C0h] [rbp-A0h] BYREF
  _BYTE v24[16]; // [rsp+D0h] [rbp-90h] BYREF
  BackRecord p_stu; // [rsp+E0h] [rbp-80h] BYREF
  BackRecord v26; // [rsp+100h] [rbp-60h] BYREF
  std::string val; // [rsp+120h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v28; // [rsp+130h] [rbp-30h] BYREF
  const EquipBack *pCfg; // [rsp+140h] [rbp-20h]
  Answer::NetPacket *SendPacket; // [rsp+148h] [rbp-18h]

  if ( !pPlayer || !packet )
    return 10002;
  nId = Answer::NetPacket::readInt32(packet);
  v4 = Answer::Singleton<CfgData>::instance();
  EquipTable = CfgData::GetEquipTable(v4);
  pCfg = CfgEquipTable::GetEquipBackCfg(EquipTable, nId);
  if ( !pCfg )
    return 10002;
  if ( pCfg->nType != 1 )
    return 10002;
  if ( pCfg->nRecovType < 0 || pCfg->nRecovValues <= 0 )
    return 10002;
  it._M_node = std::map<int,BackDepot>::find(&this->m_BackDepotMap, &nId)._M_node;
  __x._M_node = std::map<int,BackDepot>::end(&this->m_BackDepotMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator==(&it, &__x) )
    return 10002;
  if ( std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it)->second.Count <= 0 )
    return 10002;
  std::vector<MemChrBag>::vector(&ItemVt);
  for ( EquipIt._M_node = std::list<int>::begin(&pCfg->nEquipList)._M_node;
        ;
        std::_List_const_iterator<int>::operator++(&EquipIt, 0) )
  {
    v23._M_node = std::list<int>::end(&pCfg->nEquipList)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&EquipIt, &v23) )
      break;
    *(_QWORD *)&stu_0.itemId = 0x200000000LL;
    *(_QWORD *)&stu_0.itemCount = 1;
    *(_QWORD *)&stu_0.endTime = 0;
    stu_0.srcId = 0;
    stu_0.itemId = *std::_List_const_iterator<int>::operator*(&EquipIt);
    std::vector<MemChrBag>::push_back(&ItemVt, &stu_0);
  }
  Bag = Player::GetBag(pPlayer);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  if ( FreeSlotCount >= (int)std::vector<MemChrBag>::size(&ItemVt) )
  {
    if ( !Player::DecCurrency(
            pPlayer,
            (const CURRENCY_TYPE)pCfg->nBuyBackType,
            pCfg->nBuyBackValue,
            CURRENCY_CHANGE_REASON::GCR_EQUIP_BUY_BACK,
            0) )
    {
      v3 = 10002;
    }
    else
    {
      Deptstu = (BackDepot)((unsigned int)nId | 0xFFFFFFFF00000000LL);
      CEquipBack::ChangeDeptCount(this, Deptstu);
      v8 = Player::GetBag(pPlayer);
      CExtCharBag::AddItem(v8, &ItemVt, ITEM_CHANGE_REASON::ICR_EQUIP_BUY_BACK);
      memset(&stu, 0, sizeof(stu));
      std::string::string(&stu.name);
      stu.nId = nId;
      stu.nType = 2;
      stu.nTime = Answer::DayTime::now();
      Player::getName((const Player *const)v24);
      std::string::operator=(&stu.name, v24);
      std::string::~string(v24);
      BackRecord::BackRecord(&p_stu, &stu);
      CEquipBack::SendEquipBackOnRecord(this, pPlayer, &p_stu);
      BackRecord::~BackRecord(&p_stu);
      CEquipBack::SendEquipBackCountChange(this, pPlayer, nId);
      BackRecord::BackRecord(&v26, &stu);
      CEquipBack::AddRecord(this, &v26);
      BackRecord::~BackRecord(&v26);
      v9 = Answer::Singleton<GameService>::instance();
      SendPacket = GameService::popNetpacket(v9, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( SendPacket )
      {
        Answer::NetPacket::writeInt32(SendPacket, 452);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(SendPacket, &val);
        std::string::~string(&val);
        Cid = Player::getCid(pPlayer);
        Answer::NetPacket::writeInt64(SendPacket, Cid);
        v28._M_current = std::vector<MemChrBag>::begin(&ItemVt)._M_current;
        v11 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&v28);
        Answer::NetPacket::writeInt32(SendPacket, v11->itemId);
        Answer::NetPacket::writeInt32(SendPacket, pCfg->nBuyBackValue);
        WOffset = Answer::NetPacket::getWOffset(SendPacket);
        Answer::NetPacket::setSize(SendPacket, WOffset);
        v13 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v13, 0, SendPacket);
        v3 = 0;
      }
      else
      {
        v3 = 10002;
      }
      BackRecord::~BackRecord(&stu);
    }
  }
  else
  {
    v3 = 10002;
  }
  std::vector<MemChrBag>::~vector(&ItemVt);
  return v3;
}


#####################################
void __cdecl CEquipBack::SendEquipBackInfo(CEquipBack *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  BackRecord *v5; // rax
  BackRecord *v6; // rax
  BackRecord *v7; // rax
  BackRecord *v8; // rax
  int32_t v9; // eax
  std::pair<const int,BackDepot> *v10; // rax
  std::pair<const int,BackDepot> *v11; // rax
  int32_t v12; // eax
  std::pair<const int,BackLimitInfo> *v13; // rax
  std::pair<const int,BackLimitInfo> *v14; // rax
  std::pair<const int,BackLimitInfo> *v15; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v18; // bl
  GameService *v19; // rax
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > LimitIt; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > DepotIt; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<BackRecord> it; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<BackRecord> __x; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > v24; // [rsp+50h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v25; // [rsp+60h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+68h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F4Bu);
    if ( packet )
    {
      v4 = std::list<BackRecord>::size(&this->m_BackRecord);
      Answer::NetPacket::writeInt32(packet, v4);
      for ( it._M_node = std::list<BackRecord>::begin(&this->m_BackRecord)._M_node;
            ;
            std::_List_iterator<BackRecord>::operator++(&it, 0) )
      {
        __x._M_node = std::list<BackRecord>::end(&this->m_BackRecord)._M_node;
        if ( !std::_List_iterator<BackRecord>::operator!=(&it, &__x) )
          break;
        v5 = std::_List_iterator<BackRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->nId);
        v6 = std::_List_iterator<BackRecord>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v6->nType);
        v7 = std::_List_iterator<BackRecord>::operator->(&it);
        Answer::NetPacket::writeUTF8(packet, &v7->name);
        v8 = std::_List_iterator<BackRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v8->nTime);
      }
      v9 = std::map<int,BackDepot>::size(&this->m_BackDepotMap);
      Answer::NetPacket::writeInt32(packet, v9);
      for ( DepotIt._M_node = std::map<int,BackDepot>::begin(&this->m_BackDepotMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator++(&DepotIt) )
      {
        v24._M_node = std::map<int,BackDepot>::end(&this->m_BackDepotMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator!=(&DepotIt, &v24) )
          break;
        v10 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&DepotIt);
        Answer::NetPacket::writeInt32(packet, v10->first);
        v11 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&DepotIt);
        Answer::NetPacket::writeInt32(packet, v11->second.Count);
      }
      v12 = std::map<int,BackLimitInfo>::size(&this->m_BackLimitInfoMap);
      Answer::NetPacket::writeInt32(packet, v12);
      for ( LimitIt._M_node = std::map<int,BackLimitInfo>::begin(&this->m_BackLimitInfoMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator++(&LimitIt) )
      {
        v25._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&LimitIt, &v25) )
          break;
        v13 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&LimitIt);
        Answer::NetPacket::writeInt32(packet, v13->first);
        v14 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&LimitIt);
        Answer::NetPacket::writeInt32(packet, v14->second.nCount);
        v15 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&LimitIt);
        Answer::NetPacket::writeUTF8(packet, &v15->second.sLastName);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v18 = Player::getConnId(pPlayer);
      v19 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v19, v18, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CEquipBack::SendEquipBackOnRecord(CEquipBack *const this, Player *pPlayer, BackRecord *p_stu)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F4Cu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, p_stu->nId);
      Answer::NetPacket::writeInt8(packet, p_stu->nType);
      Answer::NetPacket::writeUTF8(packet, &p_stu->name);
      Answer::NetPacket::writeInt32(packet, p_stu->nTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v7 = Player::getConnId(pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CEquipBack::SendEquipBackCountChange(CEquipBack *const this, Player *pPlayer, int32_t nId)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  std::pair<const int,BackDepot> *v5; // rax
  std::pair<const int,BackDepot> *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int32_t nIda; // [rsp+Ch] [rbp-44h] BYREF
  Player *pPlayera; // [rsp+10h] [rbp-40h]
  CEquipBack *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > __x; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  thisa = this;
  pPlayera = pPlayer;
  nIda = nId;
  if ( pPlayer )
  {
    it._M_node = std::map<int,BackDepot>::find(&thisa->m_BackDepotMap, &nIda)._M_node;
    __x._M_node = std::map<int,BackDepot>::end(&thisa->m_BackDepotMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator==(&it, &__x) )
    {
      ConnId = Player::getConnId(pPlayera);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F4Du);
      if ( packet )
      {
        v5 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->first);
        v6 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->second.Count);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayera);
        v9 = Player::getConnId(pPlayera);
        v10 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v10, v9, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CEquipBack::SendEquipBackLimitChange(CEquipBack *const this, Player *pPlayer, int32_t nId)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  std::pair<const int,BackLimitInfo> *v5; // rax
  std::pair<const int,BackLimitInfo> *v6; // rax
  std::pair<const int,BackLimitInfo> *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  int32_t nIda; // [rsp+Ch] [rbp-44h] BYREF
  Player *pPlayera; // [rsp+10h] [rbp-40h]
  CEquipBack *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > __x; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  thisa = this;
  pPlayera = pPlayer;
  nIda = nId;
  if ( pPlayer )
  {
    it._M_node = std::map<int,BackLimitInfo>::find(&thisa->m_BackLimitInfoMap, &nIda)._M_node;
    __x._M_node = std::map<int,BackLimitInfo>::end(&thisa->m_BackLimitInfoMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator==(&it, &__x) )
    {
      ConnId = Player::getConnId(pPlayera);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F4Eu);
      if ( packet )
      {
        v5 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->first);
        v6 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->second.nCount);
        v7 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it);
        Answer::NetPacket::writeUTF8(packet, &v7->second.sLastName);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayera);
        v10 = Player::getConnId(pPlayera);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v11, v10, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CEquipBack::UpdateEquipRecord(
        CEquipBack *const this,
        int32_t nId,
        int8_t nType,
        int32_t nTime,
        std::string *p_Name)
{
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  BackRecord stu; // [rsp+30h] [rbp-30h] BYREF

  *(&stu.nTime + 1) = 0;
  stu.name._M_dataplus._M_p = 0;
  std::string::string(&stu.name);
  stu.nId = nId;
  *(_DWORD *)&stu.nType = (unsigned __int8)nType;
  stu.nTime = nTime;
  std::string::operator=(&stu.name, p_Name);
  Answer::MutexGuard::MutexGuard(&lock, &this->m_RecordLock);
  if ( std::list<BackRecord>::size(&this->m_BackRecord) > 0x32 )
    std::list<BackRecord>::pop_front(&this->m_BackRecord);
  std::list<BackRecord>::push_back(&this->m_BackRecord, &stu);
  Answer::MutexGuard::~MutexGuard(&lock);
  BackRecord::~BackRecord(&stu);
}


#####################################
void __cdecl CEquipBack::UpdateEquipBackInfo(
        CEquipBack *const this,
        int32_t nId,
        int8_t nType,
        int32_t nCount,
        std::string *p_Name)
{
  std::pair<const int,BackDepot> *v5; // rax
  std::pair<const int,BackDepot> *v6; // rax
  BackDepot *v7; // rax
  std::pair<const int,BackLimitInfo> *v8; // rax
  std::pair<const int,BackLimitInfo> *v9; // rax
  std::pair<const int,BackLimitInfo> *v10; // rax
  BackLimitInfo *v11; // rax
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > it_0; // [rsp+20h] [rbp-90h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-80h] BYREF
  BackLimitInfo stu_0; // [rsp+40h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > it; // [rsp+50h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-50h] BYREF
  BackDepot stu; // [rsp+70h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackDepot> > __x; // [rsp+80h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BackLimitInfo> > v21; // [rsp+90h] [rbp-20h] BYREF

  if ( nType == 1 )
  {
    stu.nId = nId;
    stu.Count = nCount;
    Answer::MutexGuard::MutexGuard(&lock, &this->m_DepotLock);
    it._M_node = std::map<int,BackDepot>::find(&this->m_BackDepotMap, (const int *const)&stu)._M_node;
    __x._M_node = std::map<int,BackDepot>::end(&this->m_BackDepotMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator!=(&it, &__x) )
    {
      v5 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
      v5->second.Count = stu.Count;
      v6 = std::_Rb_tree_iterator<std::pair<int const,BackDepot>>::operator->(&it);
      v6->second.nId = stu.nId;
    }
    else
    {
      v7 = std::map<int,BackDepot>::operator[](&this->m_BackDepotMap, (const int *const)&stu);
      *v7 = stu;
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
  else if ( nType == 2 )
  {
    stu_0.sLastName._M_dataplus._M_p = 0;
    std::string::string(&stu_0.sLastName);
    stu_0.nId = nId;
    stu_0.nCount = nCount;
    std::string::operator=(&stu_0.sLastName, p_Name);
    Answer::MutexGuard::MutexGuard(&lock_0, &this->m_DepotLock);
    it_0._M_node = std::map<int,BackLimitInfo>::find(&this->m_BackLimitInfoMap, &stu_0.nId)._M_node;
    v21._M_node = std::map<int,BackLimitInfo>::end(&this->m_BackLimitInfoMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator!=(&it_0, &v21) )
    {
      v8 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it_0);
      v8->second.nCount = stu_0.nCount;
      v9 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it_0);
      std::string::operator=(&v9->second.sLastName, &stu_0.sLastName);
      v10 = std::_Rb_tree_iterator<std::pair<int const,BackLimitInfo>>::operator->(&it_0);
      v10->second.nId = stu_0.nId;
    }
    else
    {
      v11 = std::map<int,BackLimitInfo>::operator[](&this->m_BackLimitInfoMap, &stu_0.nId);
      BackLimitInfo::operator=(v11, &stu_0);
    }
    Answer::MutexGuard::~MutexGuard(&lock_0);
    BackLimitInfo::~BackLimitInfo(&stu_0);
  }
}


