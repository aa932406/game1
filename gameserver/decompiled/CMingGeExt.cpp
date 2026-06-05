// Decompiled methods for class: CMingGeExt
// Source: gameserver.cc
// Total methods: 34

#####################################
void __cdecl CMingGeExt::~CMingGeExt(CMingGeExt *const this)
{
  CMingGeExt::~CMingGeExt(this);
  operator delete(this);
}


#####################################
void __cdecl CMingGeExt::OnLoadFromDB(CMingGeExt *const this, const PlayerDBData *const dbData)
{
  memcpy(this->m_MingGeBag, dbData->m_CMingGeData.m_MingGeBag, sizeof(this->m_MingGeBag));
  memcpy(this->m_LieMingBag, dbData->m_CMingGeData.m_LieMingBag, sizeof(this->m_LieMingBag));
  memcpy(this->m_MingGeEquip, dbData->m_CMingGeData.m_MingGeEquip, sizeof(this->m_MingGeEquip));
  memcpy(this->m_MingGeNpc, dbData->m_CMingGeData.m_MingGeNpc, sizeof(this->m_MingGeNpc));
  this->m_MingGeExp = dbData->m_CMingGeData.m_MingGeExp;
  this->m_MingChip = dbData->m_CMingGeData.m_MingChip;
}


#####################################
void __cdecl CMingGeExt::OnSaveToDB(CMingGeExt *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->m_CMingGeData.m_MingGeBag, this->m_MingGeBag, sizeof(dbData->m_CMingGeData.m_MingGeBag));
  memcpy(dbData->m_CMingGeData.m_LieMingBag, this->m_LieMingBag, sizeof(dbData->m_CMingGeData.m_LieMingBag));
  memcpy(dbData->m_CMingGeData.m_MingGeEquip, this->m_MingGeEquip, sizeof(dbData->m_CMingGeData.m_MingGeEquip));
  memcpy(dbData->m_CMingGeData.m_MingGeNpc, this->m_MingGeNpc, sizeof(dbData->m_CMingGeData.m_MingGeNpc));
  dbData->m_CMingGeData.m_MingGeExp = this->m_MingGeExp;
  dbData->m_CMingGeData.m_MingChip = this->m_MingChip;
}


#####################################
void __cdecl CMingGeExt::GetInterestsProtocol(CMingGeExt *const this, ProcIdList *const procList)
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

  __x = 671;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 672;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 673;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 674;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 675;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 676;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 677;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 678;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 679;
  std::list<unsigned short>::push_back(procList, &v10);
}


#####################################
int32_t __cdecl CMingGeExt::DispatchNetDatas(CMingGeExt *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x29Fu:
      result = CMingGeExt::OnMingGeLevelUp(this, inPacket);
      break;
    case 0x2A0u:
      result = CMingGeExt::OnPickupMingGe(this, inPacket);
      break;
    case 0x2A1u:
      result = CMingGeExt::OnLock(this, inPacket);
      break;
    case 0x2A2u:
      result = CMingGeExt::OnDecMingGe(this, inPacket);
      break;
    case 0x2A3u:
      result = CMingGeExt::OnDuiHuan(this, inPacket);
      break;
    case 0x2A4u:
      result = CMingGeExt::OnLieMing(this, inPacket);
      break;
    case 0x2A5u:
      result = CMingGeExt::OnDress(this, inPacket);
      break;
    case 0x2A6u:
      result = CMingGeExt::OnUnDress(this, inPacket);
      break;
    case 0x2A7u:
      result = CMingGeExt::OnBuyNpc(this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
void __cdecl CMingGeExt::OnCleanUp(CMingGeExt *const this)
{
  bzero(this->m_MingGeBag, 0x320u);
  bzero(this->m_LieMingBag, 0xF0u);
  bzero(this->m_MingGeEquip, 0x40u);
  bzero(this->m_MingGeNpc, 0x14u);
  this->m_MingGeExp = 0;
  this->m_MingChip = 0;
}


#####################################
void __cdecl CMingGeExt::SendMingGeInfo(CMingGeExt *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DC9u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_MingGeExp);
      Answer::NetPacket::writeInt32(packet, this->m_MingChip);
      for ( i = 0; i <= 4; ++i )
      {
        if ( i )
          Answer::NetPacket::writeInt32(packet, this->m_MingGeNpc[i]);
        else
          Answer::NetPacket::writeInt32(packet, 1);
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
void __cdecl CMingGeExt::SendMingGeBagInfo(CMingGeExt *const this, int32_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( nType > 0 && nType <= 3 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DCAu);
      if ( packet )
      {
        if ( nType == 1 )
        {
          CMingGeExt::PackMingGeBagInfo(this, packet);
        }
        else if ( nType == 2 )
        {
          CMingGeExt::PackLeiMingBagInfo(this, packet);
        }
        else
        {
          CMingGeExt::PackMingGeEquipBagInfo(this, packet);
        }
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
void __cdecl CMingGeExt::PackMingGeBagInfo(CMingGeExt *const this, Answer::NetPacket *packet)
{
  int32_t Count; // [rsp+10h] [rbp-10h]
  int32_t OldOffet; // [rsp+14h] [rbp-Ch]
  int32_t NewOffet; // [rsp+18h] [rbp-8h]
  int i; // [rsp+1Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, 1);
  Count = 0;
  OldOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 99; ++i )
  {
    if ( !MingGe::IsEmpty(&this->m_MingGeBag[i]) )
    {
      ++Count;
      Answer::NetPacket::writeInt32(packet, i);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeBag[i].nId);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeBag[i].IsLock);
    }
  }
  NewOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, OldOffet);
  Answer::NetPacket::writeInt32(packet, Count);
  Answer::NetPacket::setWOffset(packet, NewOffet);
}


#####################################
void __cdecl CMingGeExt::PackLeiMingBagInfo(CMingGeExt *const this, Answer::NetPacket *packet)
{
  int32_t Count; // [rsp+10h] [rbp-10h]
  int32_t OldOffet; // [rsp+14h] [rbp-Ch]
  int32_t NewOffet; // [rsp+18h] [rbp-8h]
  int i; // [rsp+1Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, 3);
  Count = 0;
  OldOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 7; ++i )
  {
    if ( !MingGe::IsEmpty(&this->m_MingGeEquip[i]) )
    {
      ++Count;
      Answer::NetPacket::writeInt32(packet, i);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeEquip[i].nId);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeEquip[i].IsLock);
    }
  }
  NewOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, OldOffet);
  Answer::NetPacket::writeInt32(packet, Count);
  Answer::NetPacket::setWOffset(packet, NewOffet);
}


#####################################
void __cdecl CMingGeExt::PackMingGeEquipBagInfo(CMingGeExt *const this, Answer::NetPacket *packet)
{
  int32_t Count; // [rsp+10h] [rbp-10h]
  int32_t OldOffet; // [rsp+14h] [rbp-Ch]
  int32_t NewOffet; // [rsp+18h] [rbp-8h]
  int i; // [rsp+1Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, 2);
  Count = 0;
  OldOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 29; ++i )
  {
    if ( !MingGe::IsEmpty(&this->m_LieMingBag[i]) )
    {
      ++Count;
      Answer::NetPacket::writeInt32(packet, i);
      Answer::NetPacket::writeInt32(packet, this->m_LieMingBag[i].nId);
      Answer::NetPacket::writeInt32(packet, this->m_LieMingBag[i].IsLock);
    }
  }
  NewOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, OldOffet);
  Answer::NetPacket::writeInt32(packet, Count);
  Answer::NetPacket::setWOffset(packet, NewOffet);
}


#####################################
void __cdecl CMingGeExt::SendMingGeBagInfo(CMingGeExt *const this, int32_t nType, int32_t nSlot)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  MingGe Stu; // [rsp+10h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DCBu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nType);
      Answer::NetPacket::writeInt32(packet, nSlot);
      Stu = CMingGeExt::GetSlotItem(this, nType, nSlot);
      Answer::NetPacket::writeInt32(packet, Stu.nId);
      Answer::NetPacket::writeInt32(packet, Stu.IsLock);
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
void __cdecl CMingGeExt::AddAttr(CMingGeExt *const this)
{
  int32_t nId; // ebx
  CfgData *v2; // rax
  const CMingGeTable *CMingGeTable; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v5; // rax
  std::_List_const_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t i; // [rsp+34h] [rbp-1Ch]
  const CMingGeCfg *pCMingGeCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 7; ++i )
    {
      if ( !MingGe::IsEmpty(&this->m_MingGeEquip[i]) )
      {
        nId = this->m_MingGeEquip[i].nId;
        v2 = Answer::Singleton<CfgData>::instance();
        CMingGeTable = CfgData::GetCMingGeTable(v2);
        pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, nId);
        if ( pCMingGeCfg )
        {
          for ( it._M_node = std::list<AddAttribute>::begin(&pCMingGeCfg->lAttrList)._M_node;
                ;
                std::_List_const_iterator<AddAttribute>::operator++(&it, 0) )
          {
            __x._M_node = std::list<AddAttribute>::end(&pCMingGeCfg->lAttrList)._M_node;
            if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it, &__x) )
              break;
            m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
            v5 = std::_List_const_iterator<AddAttribute>::operator->(&it);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->m_nAddAttrType, m_nAddAttrValue);
          }
        }
      }
    }
  }
}


#####################################
bool __cdecl CMingGeExt::AddMingGeChip(CMingGeExt *const this, int32_t Count)
{
  if ( !this->m_pPlayer || Count <= 0 )
    return 0;
  this->m_MingChip += Count;
  CMingGeExt::SendMingGeInfo(this);
  return 1;
}


#####################################
bool __cdecl CMingGeExt::AddItem(CMingGeExt *const this, int32_t nId, ITEM_CHANGE_REASON Reason)
{
  CfgData *v3; // rax
  const CMingGeTable *CMingGeTable; // rax
  int FreeSlot; // [rsp+2Ch] [rbp-14h]

  v3 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v3);
  if ( !CMingGeTable::GetCMingGeCfg(CMingGeTable, nId) )
    return 0;
  FreeSlot = CMingGeExt::GetBagFreeSlot(this, 1);
  return FreeSlot >= 0 && CMingGeExt::AddBagItem(this, 1, FreeSlot, (MingGe)(unsigned int)nId, Reason);
}


#####################################
bool __cdecl CMingGeExt::AddExp(CMingGeExt *const this, int32_t Exp)
{
  if ( Exp <= 0 )
    return 0;
  this->m_MingGeExp += Exp;
  CMingGeExt::SendMingGeInfo(this);
  return 1;
}


#####################################
int32_t __cdecl CMingGeExt::OnMingGeLevelUp(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  int32_t nId; // ebx
  CfgData *v4; // rax
  const CMingGeTable *CMingGeTable; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  MingGe MG; // [rsp+10h] [rbp-40h] BYREF
  int32_t nSlot; // [rsp+24h] [rbp-2Ch]
  const CMingGeCfg *pCMingGeCfg; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nSlot = Answer::NetPacket::readInt32(inPacket);
  if ( IsInvalidSlot(3, nSlot) )
    return 2;
  MG = CMingGeExt::GetSlotItem(this, 3, nSlot);
  if ( MingGe::IsEmpty(&MG) )
    return 2;
  nId = MG.nId;
  v4 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v4);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, nId);
  if ( !pCMingGeCfg )
    return 2;
  if ( pCMingGeCfg->nNextId <= 0 || pCMingGeCfg->nUpExp <= 0 )
    return 2;
  if ( this->m_MingGeExp < pCMingGeCfg->nUpExp )
    return 2;
  this->m_MingGeExp -= pCMingGeCfg->nUpExp;
  MG.nId = pCMingGeCfg->nNextId;
  CMingGeExt::SetSlot(this, 3, nSlot, MG, ITEM_CHANGE_REASON::ICR_MING_GE_LEVEL_UP);
  CMingGeExt::SendMingGeInfo(this);
  Player::RecalcAttr(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnPickupMingGe(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  int32_t nId; // ebx
  CfgData *v4; // rax
  const CMingGeTable *CMingGeTable; // rax
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  MingGe MG; // [rsp+10h] [rbp-40h] BYREF
  int32_t nSlot; // [rsp+18h] [rbp-38h]
  int8_t IsAuto; // [rsp+1Fh] [rbp-31h]
  const CMingGeCfg *pCMingGeCfg; // [rsp+20h] [rbp-30h]
  int32_t FreeSlot; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nSlot = Answer::NetPacket::readInt32(inPacket);
  IsAuto = Answer::NetPacket::readInt8(inPacket);
  if ( IsInvalidSlot(2, nSlot) )
    return 2;
  MG = CMingGeExt::GetSlotItem(this, 2, nSlot);
  if ( MingGe::IsEmpty(&MG) )
    return 2;
  nId = MG.nId;
  v4 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v4);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, nId);
  if ( !pCMingGeCfg )
    return 2;
  if ( pCMingGeCfg->nCanPickup )
    return 2;
  FreeSlot = CMingGeExt::GetBagFreeSlot(this, 1);
  if ( FreeSlot < 0 )
    return 2;
  if ( CMingGeExt::RemoveItem(this, 2, nSlot, ITEM_CHANGE_REASON::ICR_SHI_QU_MING_GE) )
    CMingGeExt::AddBagItem(this, 1, FreeSlot, MG, ITEM_CHANGE_REASON::ICR_SHI_QU_MING_GE);
  v6 = IsAuto;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnLock(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  MingGe MG; // [rsp+10h] [rbp-30h] BYREF
  int32_t nSlot; // [rsp+18h] [rbp-28h]
  int8_t State; // [rsp+1Fh] [rbp-21h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nSlot = Answer::NetPacket::readInt32(inPacket);
  State = Answer::NetPacket::readInt8(inPacket);
  if ( IsInvalidSlot(1, nSlot) )
    return 2;
  MG = CMingGeExt::GetSlotItem(this, 1, nSlot);
  if ( MingGe::IsEmpty(&MG) )
    return 2;
  MG.IsLock = State == 1;
  CMingGeExt::SetSlot(this, 1, nSlot, MG, ITEM_CHANGE_REASON::ICR_MING_GE_LOCK);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnDecMingGe(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  int32_t nId; // ebx
  CfgData *v4; // rax
  const CMingGeTable *CMingGeTable; // rax
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  MingGe MG; // [rsp+10h] [rbp-40h] BYREF
  int32_t nBagType; // [rsp+20h] [rbp-30h]
  int32_t nSlot; // [rsp+24h] [rbp-2Ch]
  const CMingGeCfg *pCMingGeCfg; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nBagType = Answer::NetPacket::readInt32(inPacket);
  nSlot = Answer::NetPacket::readInt32(inPacket);
  if ( nBagType == 3 )
    return 2;
  if ( IsInvalidSlot(nBagType, nSlot) )
    return 2;
  MG = CMingGeExt::GetSlotItem(this, nBagType, nSlot);
  if ( MingGe::IsEmpty(&MG) )
    return 2;
  if ( MG.IsLock > 0 )
    return 2;
  nId = MG.nId;
  v4 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v4);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, nId);
  if ( !pCMingGeCfg )
    return 2;
  if ( !CMingGeExt::RemoveItem(this, nBagType, nSlot, ITEM_CHANGE_REASON::ICR_MING_GE_DEC) )
    return 2;
  if ( pCMingGeCfg->nDecExp > 0 )
    this->m_MingGeExp += pCMingGeCfg->nDecExp;
  if ( pCMingGeCfg->nDecMoney > 0 )
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_BIND_MONEY,
      pCMingGeCfg->nDecMoney,
      CURRENCY_CHANGE_REASON::GCR_DEC_MING_GE,
      0);
  CMingGeExt::SendMingGeInfo(this);
  v6 = nBagType;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnDuiHuan(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CMingGeTable *CMingGeTable; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  unsigned int nId; // [rsp+1Ch] [rbp-34h]
  const CMingGeCfg *pCMingGeCfg; // [rsp+20h] [rbp-30h]
  int nFreeSlot; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v3);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, nId);
  if ( !pCMingGeCfg )
    return 2;
  if ( pCMingGeCfg->nCostChip <= 0 )
    return 2;
  nFreeSlot = CMingGeExt::GetBagFreeSlot(this, 1);
  if ( nFreeSlot < 0 )
    return 2;
  if ( this->m_MingChip < pCMingGeCfg->nCostChip )
    return 2;
  this->m_MingChip -= pCMingGeCfg->nCostChip;
  CMingGeExt::AddBagItem(this, 1, nFreeSlot, (MingGe)nId, ITEM_CHANGE_REASON::ICR_MING_GE_DUI_HUAN);
  CMingGeExt::SendMingGeInfo(this);
  CMingGeExt::GongGao(this, 510, nId);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnLieMing(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CMingGeTable *CMingGeTable; // rax
  CfgData *v5; // rax
  const CMingGeTable *v6; // rax
  CfgData *v7; // rax
  const CMingGeTable *v8; // rax
  CExtCurrency *Currency; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCurrency *v11; // rax
  Answer::Random *v12; // rax
  CExtOperateLimit *v13; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v17; // rax
  float v18; // [rsp+Ch] [rbp-74h]
  int nType; // [rsp+30h] [rbp-50h]
  int32_t nTypea; // [rsp+30h] [rbp-50h]
  int8_t IsAuto; // [rsp+37h] [rbp-49h]
  const MingGeDrawCost *pMingGeCost; // [rsp+38h] [rbp-48h]
  int MingGeId; // [rsp+44h] [rbp-3Ch]
  const CMingGeCfg *pCMingGeCfg; // [rsp+48h] [rbp-38h]
  int nFreeSlot; // [rsp+50h] [rbp-30h]
  int LieMingTimes; // [rsp+54h] [rbp-2Ch]
  int ConstMoney; // [rsp+58h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nType = Answer::NetPacket::readInt32(inPacket);
  IsAuto = Answer::NetPacket::readInt8(inPacket);
  if ( nType != 1 )
  {
    if ( nType <= 1 || nType > 5 )
      return 2;
    if ( *(&this->m_MingChip + nType) <= 0 )
      return 2;
  }
  v3 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v3);
  pMingGeCost = CMingGeTable::GetMingGeDrawCost(CMingGeTable, nType);
  if ( !pMingGeCost )
    return 2;
  v5 = Answer::Singleton<CfgData>::instance();
  v6 = CfgData::GetCMingGeTable(v5);
  MingGeId = CMingGeTable::RandMingGe(v6, nType);
  if ( MingGeId <= 0 )
    return 2;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetCMingGeTable(v7);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(v8, MingGeId);
  if ( !pCMingGeCfg )
    return 2;
  nFreeSlot = CMingGeExt::GetBagFreeSlot(this, 2);
  if ( nFreeSlot < 0 )
    return 2;
  if ( pMingGeCost->nConstMoney > 0 )
  {
    LieMingTimes = Player::getRecord(this->m_pPlayer, 2108);
    if ( LieMingTimes > 1000 )
      LieMingTimes = 1000;
    v18 = (float)(pMingGeCost->nConstMoney * (LieMingTimes / 20));
    ConstMoney = (int)(float)(CMingGeExt::GetRate(this, LieMingTimes) * v18) + pMingGeCost->nConstMoney;
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(Currency, ConstMoney, CURRENCY_CHANGE_REASON::GCR_LIE_MING, LieMingTimes) )
      return 2;
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 2109, ConstMoney);
    v11 = Player::GetCurrency(this->m_pPlayer);
    CExtCurrency::SendCurrencyInfo(v11, 0);
  }
  CMingGeExt::AddBagItem(this, 2, nFreeSlot, (MingGe)(unsigned int)MingGeId, ITEM_CHANGE_REASON::ICR_MING_GE_LIE_MING);
  *(&this->m_MingChip + nType) = 0;
  if ( pMingGeCost->nRate > 0 )
  {
    v12 = Answer::Singleton<Answer::Random>::instance();
    if ( pMingGeCost->nRate >= Answer::Random::generate(v12, 1, 10000) )
    {
      nTypea = nType + 1;
      if ( nTypea > 0 && nTypea <= 5 )
        *(&this->m_MingChip + nTypea) = 1;
    }
  }
  v13 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::AddLimitCount(v13, 2108, 1);
  CMingGeExt::SendMingGeInfo(this);
  if ( pCMingGeCfg->nQuality > 4 && !pCMingGeCfg->nCanPickup )
    CMingGeExt::GongGao(this, 509, MingGeId);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v17 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v17, ConnId, GateIndex, Proc, IsAuto);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnDress(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  MingGe SlotItem; // rcx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax
  MingGe BagMingGe; // [rsp+10h] [rbp-40h]
  int32_t nBagSlot; // [rsp+24h] [rbp-2Ch]
  int32_t nEquipSlot; // [rsp+28h] [rbp-28h]
  int SameMingGeSlot; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nBagSlot = Answer::NetPacket::readInt32(inPacket);
  nEquipSlot = Answer::NetPacket::readInt32(inPacket);
  if ( IsInvalidSlot(1, nBagSlot) )
    return 2;
  if ( IsInvalidSlot(3, nEquipSlot) )
    return 2;
  BagMingGe = CMingGeExt::GetSlotItem(this, 1, nBagSlot);
  SameMingGeSlot = CMingGeExt::GetSameTypeMingGe(this, BagMingGe.nId);
  if ( SameMingGeSlot >= 0 && SameMingGeSlot != nEquipSlot )
    return 2;
  SlotItem = CMingGeExt::GetSlotItem(this, 3, nEquipSlot);
  CMingGeExt::SetSlot(this, 1, nBagSlot, SlotItem, ITEM_CHANGE_REASON::ICR_MING_GE_DRESS);
  CMingGeExt::SetSlot(this, 3, nEquipSlot, BagMingGe, ITEM_CHANGE_REASON::ICR_MING_GE_DRESS);
  Player::RecalcAttr(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnUnDress(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  MingGe Stu; // [rsp+20h] [rbp-30h]
  int32_t nEquipSlot; // [rsp+28h] [rbp-28h]
  int nFreeSlot; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nEquipSlot = Answer::NetPacket::readInt32(inPacket);
  if ( IsInvalidSlot(3, nEquipSlot) )
    return 2;
  nFreeSlot = CMingGeExt::GetBagFreeSlot(this, 1);
  if ( nFreeSlot < 0 )
    return 2;
  Stu = CMingGeExt::GetSlotItem(this, 3, nEquipSlot);
  CMingGeExt::SetSlot(this, 3, nEquipSlot, 0, ITEM_CHANGE_REASON::ICR_MING_GE_UNDRESS);
  CMingGeExt::AddBagItem(this, 1, nFreeSlot, Stu, ITEM_CHANGE_REASON::ICR_MING_GE_UNDRESS);
  Player::RecalcAttr(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::OnBuyNpc(CMingGeExt *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CMingGeTable *CMingGeTable; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  int nType; // [rsp+14h] [rbp-2Ch]
  const MingGeDrawCost *pMingGeCost; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nType = Answer::NetPacket::readInt32(inPacket);
  if ( nType <= 1 || nType > 5 )
    return 2;
  if ( *(&this->m_MingChip + nType) > 0 )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v3);
  pMingGeCost = CMingGeTable::GetMingGeDrawCost(CMingGeTable, nType);
  if ( !pMingGeCost )
    return 2;
  if ( pMingGeCost->nConstGold <= 0 )
    return 2;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          pMingGeCost->nConstGold,
          CURRENCY_CHANGE_REASON::GCR_BUY_NPC,
          0) )
    return 2;
  *(&this->m_MingChip + nType) = 1;
  CMingGeExt::SendMingGeInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMingGeExt::GetBagFreeSlot(CMingGeExt *const this, int32_t nType)
{
  int i; // [rsp+14h] [rbp-Ch]
  int i_0; // [rsp+18h] [rbp-8h]
  int i_1; // [rsp+1Ch] [rbp-4h]

  switch ( nType )
  {
    case 1:
      for ( i = 0; i <= 99; ++i )
      {
        if ( MingGe::IsEmpty(&this->m_MingGeBag[i]) )
          return i;
      }
      break;
    case 2:
      for ( i_0 = 0; i_0 <= 29; ++i_0 )
      {
        if ( MingGe::IsEmpty(&this->m_LieMingBag[i_0]) )
          return i_0;
      }
      break;
    case 3:
      for ( i_1 = 0; i_1 <= 7; ++i_1 )
      {
        if ( MingGe::IsEmpty(&this->m_MingGeEquip[i_1]) )
          return i_1;
      }
      break;
  }
  return -1;
}


#####################################
int32_t __cdecl CMingGeExt::GetBagFreeSlotCount(CMingGeExt *const this, int32_t nType)
{
  int32_t Count; // [rsp+10h] [rbp-10h]
  int32_t i; // [rsp+14h] [rbp-Ch]
  int32_t i_0; // [rsp+18h] [rbp-8h]
  int32_t i_1; // [rsp+1Ch] [rbp-4h]

  Count = 0;
  switch ( nType )
  {
    case 1:
      for ( i = 0; i <= 99; ++i )
      {
        if ( MingGe::IsEmpty(&this->m_MingGeBag[i]) )
          ++Count;
      }
      break;
    case 2:
      for ( i_0 = 0; i_0 <= 29; ++i_0 )
      {
        if ( MingGe::IsEmpty(&this->m_LieMingBag[i_0]) )
          ++Count;
      }
      break;
    case 3:
      for ( i_1 = 0; i_1 <= 7; ++i_1 )
      {
        if ( MingGe::IsEmpty(&this->m_MingGeEquip[i_1]) )
          ++Count;
      }
      break;
  }
  return Count;
}


#####################################
int32_t __cdecl CMingGeExt::GetSameTypeMingGe(CMingGeExt *const this, int32_t MingGeId)
{
  CfgData *v2; // rax
  const CMingGeTable *CMingGeTable; // rax
  int32_t nId; // ebx
  CfgData *v6; // rax
  const CMingGeTable *v7; // rax
  const CMingGeCfg *pCMingGeCfg; // [rsp+18h] [rbp-28h]
  int i; // [rsp+24h] [rbp-1Ch]
  const CMingGeCfg *pCEquipMingGeCfg; // [rsp+28h] [rbp-18h]

  v2 = Answer::Singleton<CfgData>::instance();
  CMingGeTable = CfgData::GetCMingGeTable(v2);
  pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, MingGeId);
  if ( !pCMingGeCfg )
    return 2;
  for ( i = 0; i <= 7; ++i )
  {
    nId = this->m_MingGeEquip[i].nId;
    v6 = Answer::Singleton<CfgData>::instance();
    v7 = CfgData::GetCMingGeTable(v6);
    pCEquipMingGeCfg = CMingGeTable::GetCMingGeCfg(v7, nId);
    if ( pCEquipMingGeCfg && pCMingGeCfg->nType == pCEquipMingGeCfg->nType )
      return i;
  }
  return -1;
}


#####################################
bool __cdecl CMingGeExt::AddBagItem(
        CMingGeExt *const this,
        int32_t nType,
        int32_t Slot,
        MingGe stu,
        ITEM_CHANGE_REASON Reason)
{
  MingGe SlotItem; // [rsp+30h] [rbp-20h] BYREF

  SlotItem = CMingGeExt::GetSlotItem(this, nType, Slot);
  return MingGe::IsEmpty(&SlotItem) && CMingGeExt::SetSlot(this, nType, Slot, stu, Reason);
}


#####################################
void __cdecl CMingGeExt::AddMingGeLog(CMingGeExt *const this, MGLog Stu)
{
  int8_t ConnId; // bl
  DBService *v3; // rax

  ConnId = Player::getConnId(this->m_pPlayer);
  v3 = Answer::Singleton<DBService>::instance();
  DBService::insertMingGeItem(v3, ConnId, &Stu);
}


#####################################
bool __cdecl CMingGeExt::SetSlot(
        CMingGeExt *const this,
        int32_t nType,
        int32_t Slot,
        MingGe stu,
        ITEM_CHANGE_REASON Reason)
{
  MingGe stua; // [rsp+30h] [rbp-40h] BYREF
  int32_t Slota; // [rsp+40h] [rbp-30h]
  int32_t nTypea; // [rsp+44h] [rbp-2Ch]
  CMingGeExt *thisa; // [rsp+48h] [rbp-28h]
  MGLog LogStu; // [rsp+50h] [rbp-20h] BYREF

  thisa = this;
  nTypea = nType;
  Slota = Slot;
  stua = stu;
  if ( IsInvalidSlot(nType, Slot) || !thisa->m_pPlayer )
    return 0;
  memset(&LogStu, 0, sizeof(LogStu));
  LogStu.Cid = Player::getCid(thisa->m_pPlayer);
  LogStu.Time = Unit::getNow(thisa->m_pPlayer);
  LogStu.Reason = Reason;
  LogStu.BagType = nTypea;
  switch ( nTypea )
  {
    case 1:
      if ( MingGe::IsEmpty(&thisa->m_MingGeBag[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_MingGeBag[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
        LogStu.MingGeId = thisa->m_MingGeBag[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_MingGeBag[Slota]) && MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = thisa->m_MingGeBag[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      thisa->m_MingGeBag[Slota] = stua;
      break;
    case 2:
      if ( MingGe::IsEmpty(&thisa->m_LieMingBag[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_LieMingBag[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
        LogStu.MingGeId = thisa->m_LieMingBag[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_LieMingBag[Slota]) && MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = thisa->m_LieMingBag[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      thisa->m_LieMingBag[Slota] = stua;
      break;
    case 3:
      if ( MingGe::IsEmpty(&thisa->m_MingGeEquip[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_MingGeEquip[Slota]) && !MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = stua.nId;
        LogStu.Flag = 1;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
        LogStu.MingGeId = thisa->m_MingGeEquip[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      else if ( !MingGe::IsEmpty(&thisa->m_MingGeEquip[Slota]) && MingGe::IsEmpty(&stua) )
      {
        LogStu.MingGeId = thisa->m_MingGeEquip[Slota].nId;
        LogStu.Flag = 2;
        CMingGeExt::AddMingGeLog(thisa, LogStu);
      }
      thisa->m_MingGeEquip[Slota] = stua;
      break;
    default:
      return 0;
  }
  CMingGeExt::SendMingGeBagInfo(thisa, nTypea, Slota);
  return 1;
}


#####################################
bool __cdecl CMingGeExt::RemoveItem(CMingGeExt *const this, int32_t nType, int32_t Slot, ITEM_CHANGE_REASON Reason)
{
  return !IsInvalidSlot(nType, Slot) && CMingGeExt::SetSlot(this, nType, Slot, 0, Reason);
}


#####################################
void __cdecl CMingGeExt::GongGao(CMingGeExt *const this, int32_t GongGaoId, int32_t MingGeId)
{
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v6; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, MingGeId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v6, 0, packet);
    }
  }
}


#####################################
float __cdecl CMingGeExt::GetRate(CMingGeExt *const this, int32_t Times)
{
  if ( Times > 100 )
    return 0.2;
  else
    return 0.0;
}


