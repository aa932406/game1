// Decompiled methods for class: Curse
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl Curse::~Curse(Curse *const this)
{
  Curse::~Curse(this);
  operator delete(this);
}


#####################################
void __cdecl Curse::GetInterestsProtocol(Curse *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 268;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl Curse::DispatchNetDatas(Curse *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 268 )
    return Curse::OnCurseLevelUp(this, inPacket);
  return 10002;
}


#####################################
void __cdecl Curse::AddCharAttr(Curse *const this)
{
  CfgData *v1; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t CurLevel; // [rsp+34h] [rbp-1Ch]
  DamnationCfg *CurCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CurLevel = Player::getRecord(this->m_pPlayer, 1150);
    v1 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetDamnationCfg(v1, CurLevel);
    if ( CurCfg )
    {
      for ( it._M_node = std::list<AddAttribute>::begin(&CurCfg->AttrList)._M_node;
            ;
            std::_List_iterator<AddAttribute>::operator++(&it, 0) )
      {
        __x._M_node = std::list<AddAttribute>::end(&CurCfg->AttrList)._M_node;
        if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
          break;
        m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
        v3 = std::_List_iterator<AddAttribute>::operator->(&it);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
      }
    }
  }
}


#####################################
int32_t __cdecl Curse::OnCurseLevelUp(Curse *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CfgData *v4; // rax
  CExtCurrency *Currency; // rax
  CExtCharBag *Bag; // rax
  int64_t CostMoney; // rbx
  CExtCurrency *v8; // rax
  Player *m_pPlayer; // rbx
  CKaiFuHuoDong *v10; // rax
  int8_t ConnId; // bl
  GameService *v12; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  int8_t v17; // bl
  DBService *v18; // rax
  important_system_log stu; // [rsp+10h] [rbp-A0h] BYREF
  std::string val; // [rsp+50h] [rbp-60h] BYREF
  _BYTE v22[16]; // [rsp+60h] [rbp-50h] BYREF
  _BYTE v23[20]; // [rsp+70h] [rbp-40h] BYREF
  int32_t CurLevel; // [rsp+84h] [rbp-2Ch]
  DamnationCfg *CurCfg; // [rsp+88h] [rbp-28h]
  DamnationCfg *NextCfg; // [rsp+90h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CurLevel = Player::getRecord(this->m_pPlayer, 1150);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetDamnationCfg(v3, CurLevel);
  v4 = Answer::Singleton<CfgData>::instance();
  NextCfg = CfgData::GetDamnationCfg(v4, CurLevel + 1);
  if ( !CurCfg || !NextCfg )
    return 10002;
  if ( CurCfg->CostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < CurCfg->CostMoney )
      return 10002;
  }
  if ( std::list<ItemData>::size(&CurCfg->CostItems) )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, &CurCfg->CostItems, ITEM_CHANGE_REASON::ICR_CURSE_LEVEL_UP) )
      return 10002;
  }
  if ( CurCfg->CostMoney <= 0
    || (CostMoney = CurCfg->CostMoney,
        v8 = Player::GetCurrency(this->m_pPlayer),
        CExtCurrency::DecMoneyAndNoBind(v8, CostMoney, CURRENCY_CHANGE_REASON::MCR_CURSE_LEVEL_UP, 0)) )
  {
    Player::updateRecord(this->m_pPlayer, 1150, CurLevel + 1);
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_ZU_ZHOU, CurLevel + 1);
    Player::RecalcAttr(this->m_pPlayer);
    m_pPlayer = this->m_pPlayer;
    v10 = Answer::Singleton<CKaiFuHuoDong>::instance();
    CKaiFuHuoDong::SendKaiFuHuoDongIcon(v10, m_pPlayer);
    if ( NextCfg->GongGaoId > 0 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v12, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
        return 10002;
      Answer::NetPacket::writeInt32(packet, NextCfg->GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, CurLevel + 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v15 = Player::getConnId(this->m_pPlayer);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v16, v15, packet);
    }
    important_system_log::important_system_log(&stu);
    stu.log_Sid = Player::getSid(this->m_pPlayer);
    stu.log_time = Unit::getNow(this->m_pPlayer);
    Player::GetPassport((Player *const)v22);
    std::string::operator=(&stu.passport, v22);
    std::string::~string(v22);
    stu.cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)v23);
    std::string::operator=(&stu.name, v23);
    std::string::~string(v23);
    stu.up_time = Unit::getNow(this->m_pPlayer);
    stu.sys_name = 11;
    stu.oper_id = 1;
    stu.level = CurLevel + 1;
    v17 = Player::getConnId(this->m_pPlayer);
    v18 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v18, v17, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
    v2 = 0;
    important_system_log::~important_system_log(&stu);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl Curse::DamageValue(Curse *const this, int64_t MaxHp)
{
  __int64 v2; // rax
  CfgData *v3; // rax
  Answer::Random *v4; // rax
  int32_t CurLevel; // [rsp+14h] [rbp-1Ch]
  DamnationCfg *CurCfg; // [rsp+18h] [rbp-18h]
  int32_t nRand; // [rsp+24h] [rbp-Ch]

  if ( this->m_pPlayer )
  {
    CurLevel = Player::getRecord(this->m_pPlayer, 1150);
    v3 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetDamnationCfg(v3, CurLevel);
    if ( CurCfg )
    {
      if ( CurCfg->HpPecent > 0 && CurCfg->Probability > 0 )
      {
        v4 = Answer::Singleton<Answer::Random>::instance();
        nRand = Answer::Random::generate(v4, 1, 1000);
        if ( Player::getRecord(this->m_pPlayer, 1155) > 0 )
          Player::getRecord(this->m_pPlayer, 1155);
        if ( CurCfg->Probability <= nRand )
          LODWORD(v2) = 0;
        else
          return MaxHp * CurCfg->HpPecent / 100;
      }
      else
      {
        LODWORD(v2) = 0;
      }
    }
    else
    {
      LODWORD(v2) = 0;
    }
  }
  else
  {
    LODWORD(v2) = 10002;
  }
  return v2;
}


