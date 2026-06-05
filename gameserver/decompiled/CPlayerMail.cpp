// Decompiled methods for class: CPlayerMail
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CPlayerMail::~CPlayerMail(CPlayerMail *const this)
{
  CPlayerMail::~CPlayerMail(this);
  operator delete(this);
}


#####################################
void __cdecl CPlayerMail::OnLoadFromDB(CPlayerMail *const this, const PlayerDBData *const dbData)
{
  std::map<int,MailInfo>::operator=(&this->m_MailInfo, &dbData->m_MailDBData.m_MailInfo);
}


#####################################
void __cdecl CPlayerMail::OnSaveToDB(CPlayerMail *const this, PlayerDBData *const dbData)
{
  std::map<int,MailInfo>::operator=(&dbData->m_MailDBData.m_MailInfo, &this->m_MailInfo);
}


#####################################
void __cdecl CPlayerMail::GetInterestsProtocol(CPlayerMail *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v3; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v4; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v5; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v6; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 429;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 430;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 431;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 432;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 20206;
  std::list<unsigned short>::push_back(procList, &v6);
}


#####################################
int32_t __cdecl CPlayerMail::DispatchNetDatas(CPlayerMail *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 431 )
    return CPlayerMail::OnGetFuJian(this, inPacket);
  if ( nProcId > 0x1AFu )
  {
    if ( nProcId == 432 )
      return CPlayerMail::OnDeleteMail(this, inPacket);
    if ( nProcId == 20206 )
      return CPlayerMail::OnReciveNewMail(this, inPacket);
  }
  else
  {
    if ( nProcId == 429 )
      return CPlayerMail::OnReadMail(this, inPacket);
    if ( nProcId == 430 )
      return CPlayerMail::OnRequestMailList(this, inPacket);
  }
  return 2;
}


#####################################
int32_t __cdecl CPlayerMail::OnReadMail(CPlayerMail *const this, Answer::NetPacket *inPacket)
{
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > it; // [rsp+10h] [rbp-20h] BYREF
  int32_t MailId; // [rsp+1Ch] [rbp-14h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  MailId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,MailInfo>::find(&this->m_MailInfo, &MailId)._M_node;
  __x._M_node = std::map<int,MailInfo>::end(&this->m_MailInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator==(&it, &__x) )
    return 2;
  std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.HasRead = 1;
  CPlayerMail::SendMailContent(this, MailId);
  return 0;
}


#####################################
int32_t __cdecl CPlayerMail::OnRequestMailList(CPlayerMail *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  CPlayerMail::SendMailList(this);
  return 0;
}


#####################################
int32_t __cdecl CPlayerMail::OnGetFuJian(CPlayerMail *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::pair<const int,MailInfo> *v3; // rax
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t nReason; // ebx
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  MemChrBagVector ItemFuJian; // [rsp+10h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > it; // [rsp+30h] [rbp-60h] BYREF
  int32_t MailId; // [rsp+3Ch] [rbp-54h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > __x; // [rsp+40h] [rbp-50h] BYREF
  MailInfo *mail; // [rsp+50h] [rbp-40h]
  int32_t FuJianCount; // [rsp+5Ch] [rbp-34h]
  const CfgEquip *pCfgEquip; // [rsp+60h] [rbp-30h]
  int32_t i; // [rsp+6Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  MailId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,MailInfo>::find(&this->m_MailInfo, &MailId)._M_node;
  __x._M_node = std::map<int,MailInfo>::end(&this->m_MailInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator==(&it, &__x) )
    return 2;
  v3 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
  mail = &v3->second;
  if ( v3->second.Extract != 1 )
    return 2;
  FuJianCount = 6;
  if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.SysMailId == 2000 )
  {
    FuJianCount = 1;
    if ( mail->Item[0].itemClass != 2 )
      return 2;
    itemId = mail->Item[0].itemId;
    v5 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v5);
    pCfgEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( !pCfgEquip )
      return 2;
    if ( pCfgEquip->m_BackGold <= 0 )
      return 2;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            pCfgEquip->m_BackGold,
            CURRENCY_CHANGE_REASON::GCR_RANSOM_ITEM,
            0) )
      return 2;
  }
  std::vector<MemChrBag>::vector(&ItemFuJian);
  std::vector<MemChrBag>::reserve(&ItemFuJian, FuJianCount);
  for ( i = 0; i < FuJianCount; ++i )
  {
    if ( mail->Item[i].itemId > 0 && mail->Item[i].itemCount > 0 )
      std::vector<MemChrBag>::push_back(&ItemFuJian, &mail->Item[i]);
  }
  if ( mail->nReason <= 0 )
    nReason = 2;
  else
    nReason = mail->nReason;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItemsAndMingGe(Bag, &ItemFuJian, (ITEM_CHANGE_REASON)nReason) )
  {
    v2 = 2;
  }
  else
  {
    std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.HasRead = 1;
    std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.Extract = 2;
    CPlayerMail::SendMailContent(this, MailId);
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v12 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v12, ConnId, GateIndex, Proc, 0);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&ItemFuJian);
  return v2;
}


#####################################
int32_t __cdecl CPlayerMail::OnDeleteMail(CPlayerMail *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // r12d
  int8_t ConnId; // bl
  DBService *v5; // rax
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > it; // [rsp+10h] [rbp-30h] BYREF
  int32_t MailId; // [rsp+1Ch] [rbp-24h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > __x; // [rsp+20h] [rbp-20h] BYREF

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  MailId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,MailInfo>::find(&this->m_MailInfo, &MailId)._M_node;
  __x._M_node = std::map<int,MailInfo>::end(&this->m_MailInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator==(&it, &__x) )
    return 2;
  std::map<int,MailInfo>::erase(&this->m_MailInfo, it);
  CPlayerMail::SendMailList(this);
  v3 = MailId;
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<DBService>::instance();
  DBService::OnDeleteMail(v5, ConnId, v3);
  return 0;
}


#####################################
int32_t __cdecl CPlayerMail::OnReciveNewMail(CPlayerMail *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  EquipId_t srcId; // rbx
  CEquipManager *v4; // rax
  MailInfo *v5; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v7; // rax
  MailInfo mail; // [rsp+10h] [rbp-200h] BYREF
  MemEquip equip; // [rsp+120h] [rbp-F0h] BYREF
  MemChrBag item; // [rsp+160h] [rbp-B0h] BYREF
  MemEquipVector vEquip; // [rsp+180h] [rbp-90h] BYREF
  Answer::NetPacket v13; // [rsp+1A0h] [rbp-70h] BYREF
  _BYTE v14[23]; // [rsp+1E0h] [rbp-30h] BYREF
  int8_t Count; // [rsp+1F7h] [rbp-19h]
  int32_t i; // [rsp+1F8h] [rbp-18h]
  int8_t nIndex; // [rsp+1FFh] [rbp-11h]

  if ( inPacket )
  {
    std::vector<MemEquip>::vector(&vEquip);
    std::vector<MemEquip>::reserve(&vEquip, 6u);
    memset(&mail, 0, 268);
    std::string::string(&mail.SenderName);
    std::string::string(&mail.ReceiveName);
    std::string::string(&mail.MailTitle);
    std::string::string(&mail.MailContent);
    std::string::string(&mail.Param);
    mail.MailId = Answer::NetPacket::readInt32(inPacket);
    mail.SysMailId = Answer::NetPacket::readInt32(inPacket);
    mail.SenderId = Answer::NetPacket::readInt64(inPacket);
    Answer::NetPacket::readUTF8(&v13, (bool)inPacket);
    std::string::operator=(&mail.SenderName, &v13);
    std::string::~string(&v13);
    mail.ReceiveId = Answer::NetPacket::readInt64(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v13.m_wOffset, (bool)inPacket);
    std::string::operator=(&mail.ReceiveName, &v13.m_wOffset);
    std::string::~string(&v13.m_wOffset);
    mail.SendTime = Answer::NetPacket::readInt32(inPacket);
    mail.HasRead = Answer::NetPacket::readInt8(inPacket);
    mail.Extract = Answer::NetPacket::readInt8(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v13.m_size, (bool)inPacket);
    std::string::operator=(&mail.MailTitle, &v13.m_size);
    std::string::~string(&v13.m_size);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v13.m_pool, (bool)inPacket);
    std::string::operator=(&mail.MailContent, &v13.m_pool);
    std::string::~string(&v13.m_pool);
    mail.nReason = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v14, (bool)inPacket);
    std::string::operator=(&mail.Param, v14);
    std::string::~string(v14);
    if ( mail.Extract == 1 )
    {
      Count = Answer::NetPacket::readInt8(inPacket);
      if ( Count > 5 || Count <= 0 )
      {
        v2 = 2;
LABEL_19:
        MailInfo::~MailInfo(&mail);
        std::vector<MemEquip>::~vector(&vEquip);
        return v2;
      }
      for ( i = 0; Count > i; ++i )
      {
        nIndex = Answer::NetPacket::readInt8(inPacket);
        if ( (unsigned __int8)nIndex <= 5u )
        {
          memset(&item, 0, sizeof(item));
          item.itemId = Answer::NetPacket::readInt32(inPacket);
          item.itemClass = Answer::NetPacket::readInt8(inPacket);
          item.itemCount = Answer::NetPacket::readInt32(inPacket);
          item.bind = Answer::NetPacket::readInt8(inPacket);
          item.endTime = Answer::NetPacket::readInt32(inPacket);
          item.srcId = Answer::NetPacket::readInt64(inPacket);
          mail.Item[nIndex] = item;
          if ( item.itemClass == 2 && item.srcId > 0 )
          {
            srcId = item.srcId;
            v4 = Answer::Singleton<CEquipManager>::instance();
            CEquipManager::GetMemEquip(&equip, v4, srcId);
            if ( equip.base == item.itemId )
              std::vector<MemEquip>::push_back(&vEquip, &equip);
            MemEquip::~MemEquip(&equip);
          }
        }
      }
    }
    v5 = std::map<int,MailInfo>::operator[](&this->m_MailInfo, &mail.MailId);
    MailInfo::operator=(v5, &mail);
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v7 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v7, m_pPlayer, &vEquip);
    }
    CPlayerMail::SendNewMail(this);
    v2 = 0;
    goto LABEL_19;
  }
  return 2;
}


#####################################
void __cdecl CPlayerMail::SendMailList(CPlayerMail *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,MailInfo> *v3; // rax
  std::pair<const int,MailInfo> *v4; // rax
  std::pair<const int,MailInfo> *v5; // rax
  std::pair<const int,MailInfo> *v6; // rax
  std::pair<const int,MailInfo> *v7; // rax
  std::pair<const int,MailInfo> *v8; // rax
  std::pair<const int,MailInfo> *v9; // rax
  std::pair<const int,MailInfo> *v10; // rax
  std::pair<const int,MailInfo> *v11; // rax
  std::pair<const int,MailInfo> *v12; // rax
  std::pair<const int,MailInfo> *v13; // rax
  std::pair<const int,MailInfo> *v14; // rax
  std::pair<const int,MailInfo> *v15; // rax
  char *Buffer; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t CurTime; // [rsp+38h] [rbp-18h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CACu);
    if ( packet )
    {
      CurTime = Unit::getNow(this->m_pPlayer);
      it._M_node = std::map<int,MailInfo>::begin(&this->m_MailInfo)._M_node;
      nSize = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      while ( 1 )
      {
        __x._M_node = std::map<int,MailInfo>::end(&this->m_MailInfo)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
        if ( v3->second.SendTime + 1209600 >= CurTime )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->second.MailId);
          v5 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v5->second.SysMailId);
          v6 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt64(packet, v6->second.SenderId);
          v7 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeUTF8(packet, &v7->second.SenderName);
          v8 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt64(packet, v8->second.ReceiveId);
          v9 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeUTF8(packet, &v9->second.ReceiveName);
          v10 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v10->second.SendTime);
          v11 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt8(packet, v11->second.HasRead);
          v12 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeInt8(packet, v12->second.Extract);
          v13 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
          Answer::NetPacket::writeUTF8(packet, &v13->second.MailTitle);
          if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.Extract == 1 )
          {
            v14 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
            Answer::NetPacket::writeInt32(packet, v14->second.Item[0].itemId);
            v15 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
            Answer::NetPacket::writeInt8(packet, v15->second.Item[0].itemClass);
          }
          else
          {
            Answer::NetPacket::writeInt32(packet, 0);
            Answer::NetPacket::writeInt8(packet, 0);
          }
          ++nSize;
        }
        std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator++(&it);
      }
      Buffer = Answer::NetPacket::getBuffer(packet);
      *(_DWORD *)Buffer = nSize;
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v19 = Player::getConnId(this->m_pPlayer);
      v20 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v20, v19, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CPlayerMail::SendMailContent(CPlayerMail *const this, int32_t MailId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,MailInfo> *v4; // rax
  std::pair<const int,MailInfo> *v5; // rax
  std::pair<const int,MailInfo> *v6; // rax
  std::pair<const int,MailInfo> *v8; // rax
  std::pair<const int,MailInfo> *v9; // rax
  std::pair<const int,MailInfo> *v11; // rax
  std::pair<const int,MailInfo> *v12; // rax
  std::pair<const int,MailInfo> *v13; // rax
  std::pair<const int,MailInfo> *v14; // rax
  std::pair<const int,MailInfo> *v15; // rax
  std::pair<const int,MailInfo> *v16; // rax
  std::pair<const int,MailInfo> *v17; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v20; // bl
  GameService *v21; // rax
  int32_t MailIda; // [rsp+4h] [rbp-5Ch] BYREF
  CPlayerMail *thisa; // [rsp+8h] [rbp-58h]
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > it; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MailInfo> > __x; // [rsp+20h] [rbp-40h] BYREF
  std::string p_Param; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]
  int8_t nCount; // [rsp+43h] [rbp-1Dh]
  uint32_t nOldOffset; // [rsp+44h] [rbp-1Ch]
  uint32_t nNewOffset; // [rsp+48h] [rbp-18h]
  int8_t i; // [rsp+4Fh] [rbp-11h]

  thisa = this;
  MailIda = MailId;
  if ( this->m_pPlayer )
  {
    it._M_node = std::map<int,MailInfo>::find(&thisa->m_MailInfo, &MailIda)._M_node;
    __x._M_node = std::map<int,MailInfo>::end(&thisa->m_MailInfo)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator==(&it, &__x) )
    {
      ConnId = Player::getConnId(thisa->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CADu);
      if ( packet )
      {
        v4 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second.MailId);
        v5 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
        Answer::NetPacket::writeUTF8(packet, &v5->second.MailContent);
        v6 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v6->second.Extract);
        if ( std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.Extract == 1
          || std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it)->second.Extract == 2 )
        {
          nCount = 0;
          nOldOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::writeInt8(packet, nCount);
          for ( i = 0; i <= 5; ++i )
          {
            v8 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
            if ( v8->second.Item[i].itemId > 0 )
            {
              v9 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
              if ( v9->second.Item[i].itemCount > 0 )
              {
                Answer::NetPacket::writeInt8(packet, i);
                v11 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt32(packet, v11->second.Item[i].itemId);
                v12 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt8(packet, v12->second.Item[i].itemClass);
                v13 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt32(packet, v13->second.Item[i].itemCount);
                v14 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt8(packet, v14->second.Item[i].bind);
                v15 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt32(packet, v15->second.Item[i].endTime);
                v16 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
                Answer::NetPacket::writeInt64(packet, v16->second.Item[i].srcId);
                ++nCount;
              }
            }
          }
          nNewOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setWOffset(packet, nOldOffset);
          Answer::NetPacket::writeInt8(packet, nCount);
          Answer::NetPacket::setWOffset(packet, nNewOffset);
        }
        v17 = std::_Rb_tree_iterator<std::pair<int const,MailInfo>>::operator->(&it);
        std::string::string(&p_Param, &v17->second.Param);
        CPlayerMail::PackParam(thisa, &p_Param, packet);
        std::string::~string(&p_Param);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(thisa->m_pPlayer);
        v20 = Player::getConnId(thisa->m_pPlayer);
        v21 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v21, v20, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CPlayerMail::PackParam(CPlayerMail *const this, std::string *p_Param, Answer::NetPacket *inPacket)
{
  std::string *v3; // rdx
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+20h] [rbp-60h] BYREF
  StringVector vStr; // [rsp+30h] [rbp-50h] BYREF
  std::string delims; // [rsp+50h] [rbp-30h] BYREF
  char v8; // [rsp+5Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+60h] [rbp-20h] BYREF
  int32_t nSize; // [rsp+6Ch] [rbp-14h]

  if ( inPacket )
  {
    if ( (unsigned __int8)std::string::empty(p_Param) )
    {
      Answer::NetPacket::writeInt32(inPacket, 0);
    }
    else
    {
      std::allocator<char>::allocator(&v8);
      std::string::string(&delims, &unk_8EE9E7);
      Answer::StringUtility::split(&vStr, p_Param, &delims, 0);
      std::string::~string(&delims);
      std::allocator<char>::~allocator(&v8);
      nSize = std::vector<std::string>::size(&vStr);
      Answer::NetPacket::writeInt32(inPacket, nSize);
      for ( it._M_current = std::vector<std::string>::begin(&vStr)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
        Answer::NetPacket::writeUTF8(inPacket, v3);
      }
      std::vector<std::string>::~vector(&vStr);
    }
  }
}


#####################################
void __cdecl CPlayerMail::SendNewMail(CPlayerMail *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CAEu);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 0);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


