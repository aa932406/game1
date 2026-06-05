// Decompiled methods for class: CGoblinData
// Source: gameserver.cc
// Total methods: 18

#####################################
void __cdecl CGoblinData::~CGoblinData(CGoblinData *const this)
{
  CGoblinData::~CGoblinData(this);
  operator delete(this);
}


#####################################
void __cdecl CGoblinData::CleanUp(CGoblinData *const this)
{
  std::map<int,GoblinInfo>::clear(&this->m_GoblinInfoMap);
  std::map<int,int>::clear(&this->m_ShouHuRefiningLeveMap);
  std::map<int,int>::clear(&this->m_WingEquipPolishMap);
  std::map<int,int>::clear(&this->m_MoFuZhuNengMap);
  std::map<int,int>::clear(&this->m_WingEquipRefiningMap);
  std::map<int,int>::clear(&this->m_VipEquipPosLevelMap);
}


#####################################
void __cdecl CGoblinData::SaveToSqlString(
        CGoblinData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r15
  const char *v5; // r14
  const char *v6; // r13
  const char *v7; // r12
  const char *v8; // rbx
  const char *v9; // rax
  const char *v10; // [rsp+50h] [rbp-150h]
  const char *v11; // [rsp+58h] [rbp-148h]
  const char *v12; // [rsp+60h] [rbp-140h]
  const char *v13; // [rsp+68h] [rbp-138h]
  const char *v14; // [rsp+70h] [rbp-130h]
  const char *v15; // [rsp+78h] [rbp-128h]
  std::string v18; // [rsp+A0h] [rbp-100h] BYREF
  std::string v19; // [rsp+B0h] [rbp-F0h] BYREF
  std::string v20; // [rsp+C0h] [rbp-E0h] BYREF
  std::string v21; // [rsp+D0h] [rbp-D0h] BYREF
  std::string v22; // [rsp+E0h] [rbp-C0h] BYREF
  std::string v23; // [rsp+F0h] [rbp-B0h] BYREF
  std::string v24; // [rsp+100h] [rbp-A0h] BYREF
  std::string v25; // [rsp+110h] [rbp-90h] BYREF
  std::string v26; // [rsp+120h] [rbp-80h] BYREF
  std::string v27; // [rsp+130h] [rbp-70h] BYREF
  std::string v28; // [rsp+140h] [rbp-60h] BYREF
  std::string v29; // [rsp+150h] [rbp-50h] BYREF
  std::string __x; // [rsp+160h] [rbp-40h] BYREF
  _BYTE v31[49]; // [rsp+16Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  CGoblinData::GetVipPosString((CGoblinData *const)&v18);
  v10 = (const char *)std::string::c_str(&v18);
  CGoblinData::GetWingEquipRefiningString((CGoblinData *const)&v19);
  v11 = (const char *)std::string::c_str(&v19);
  CGoblinData::GetMoFuString((CGoblinData *const)&v20);
  v12 = (const char *)std::string::c_str(&v20);
  CGoblinData::GetWingEquipPolishString((CGoblinData *const)&v21);
  v13 = (const char *)std::string::c_str(&v21);
  CGoblinData::GetShouHuRefiningString((CGoblinData *const)&v22);
  v14 = (const char *)std::string::c_str(&v22);
  CGoblinData::GetGoblinInfoString((CGoblinData *const)&v23);
  v4 = (const char *)std::string::c_str(&v23);
  CGoblinData::GetVipPosString((CGoblinData *const)&v24);
  v5 = (const char *)std::string::c_str(&v24);
  CGoblinData::GetWingEquipRefiningString((CGoblinData *const)&v25);
  v6 = (const char *)std::string::c_str(&v25);
  CGoblinData::GetMoFuString((CGoblinData *const)&v26);
  v7 = (const char *)std::string::c_str(&v26);
  CGoblinData::GetWingEquipPolishString((CGoblinData *const)&v27);
  v8 = (const char *)std::string::c_str(&v27);
  CGoblinData::GetShouHuRefiningString((CGoblinData *const)&v28);
  v15 = (const char *)std::string::c_str(&v28);
  CGoblinData::GetGoblinInfoString((CGoblinData *const)&v29);
  v9 = (const char *)std::string::c_str(&v29);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_goblin` (`cid`,`goblin_info`,`shou_hu_info`,`wing_equip_polish`,`mo_fu`,`wing_refining`,`vip_po"
    "s`) VALUES (%lld,'%s','%s','%s','%s','%s','%s') ON DUPLICATE KEY UPDATE `goblin_info`='%s',`shou_hu_info`='%s',wing_"
    "equip_polish='%s',mo_fu='%s',`wing_refining`='%s',`vip_pos`='%s'",
    nCid,
    v9,
    v15,
    v8,
    v7,
    v6,
    v5,
    v4,
    v14,
    v13,
    v12,
    v11,
    v10);
  std::string::~string(&v29);
  std::string::~string(&v28);
  std::string::~string(&v27);
  std::string::~string(&v26);
  std::string::~string(&v25);
  std::string::~string(&v24);
  std::string::~string(&v23);
  std::string::~string(&v22);
  std::string::~string(&v21);
  std::string::~string(&v20);
  std::string::~string(&v19);
  std::string::~string(&v18);
  std::allocator<char>::allocator(v31);
  std::string::string(&__x, (char *)szSQL, v31);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v31);
}


#####################################
bool __cdecl CGoblinData::LoadFromDB(
        CGoblinData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  const char *v9; // rax
  const char *v10; // rax
  const char *v11; // rax
  const char *v12; // rax
  std::string VipPosString; // [rsp+30h] [rbp-F0h] BYREF
  std::string WingRefining; // [rsp+40h] [rbp-E0h] BYREF
  std::string MoFuString; // [rsp+50h] [rbp-D0h] BYREF
  std::string WingEquipPolishString; // [rsp+60h] [rbp-C0h] BYREF
  std::string ShouHuInfoString; // [rsp+70h] [rbp-B0h] BYREF
  std::string GoblinInfoString; // [rsp+80h] [rbp-A0h] BYREF
  Answer::MySqlQuery result; // [rsp+90h] [rbp-90h] BYREF
  char v23; // [rsp+AFh] [rbp-71h] BYREF
  std::string p_GoblinInfoString; // [rsp+B0h] [rbp-70h] BYREF
  char v25; // [rsp+BFh] [rbp-61h] BYREF
  std::string p_ShouHuRefiningString; // [rsp+C0h] [rbp-60h] BYREF
  char v27; // [rsp+CFh] [rbp-51h] BYREF
  std::string p_WingEquipPolishString; // [rsp+D0h] [rbp-50h] BYREF
  char v29; // [rsp+DFh] [rbp-41h] BYREF
  std::string p_MoFuString; // [rsp+E0h] [rbp-40h] BYREF
  char v31; // [rsp+EFh] [rbp-31h] BYREF
  std::string p_WingEquipRefiningString; // [rsp+F0h] [rbp-30h] BYREF
  char v33; // [rsp+FFh] [rbp-21h] BYREF
  std::string p_VipPosString; // [rsp+100h] [rbp-20h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_goblin` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    std::allocator<char>::allocator(&v23);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "goblin_info", byte_8CFE00);
    std::string::string(&GoblinInfoString, StringValue, &v23);
    std::allocator<char>::~allocator(&v23);
    std::string::string(&p_GoblinInfoString, &GoblinInfoString);
    CGoblinData::ParesGoblinInfoString(this, &p_GoblinInfoString);
    std::string::~string(&p_GoblinInfoString);
    std::allocator<char>::allocator(&v25);
    v8 = Answer::MySqlQuery::getStringValue(&result, "shou_hu_info", byte_8CFE00);
    std::string::string(&ShouHuInfoString, v8, &v25);
    std::allocator<char>::~allocator(&v25);
    std::string::string(&p_ShouHuRefiningString, &ShouHuInfoString);
    CGoblinData::ParesShouHuRefiningString(this, &p_ShouHuRefiningString);
    std::string::~string(&p_ShouHuRefiningString);
    std::allocator<char>::allocator(&v27);
    v9 = Answer::MySqlQuery::getStringValue(&result, "wing_equip_polish", byte_8CFE00);
    std::string::string(&WingEquipPolishString, v9, &v27);
    std::allocator<char>::~allocator(&v27);
    std::string::string(&p_WingEquipPolishString, &WingEquipPolishString);
    CGoblinData::ParesWingEquipPolishString(this, &p_WingEquipPolishString);
    std::string::~string(&p_WingEquipPolishString);
    std::allocator<char>::allocator(&v29);
    v10 = Answer::MySqlQuery::getStringValue(&result, "mo_fu", byte_8CFE00);
    std::string::string(&MoFuString, v10, &v29);
    std::allocator<char>::~allocator(&v29);
    std::string::string(&p_MoFuString, &MoFuString);
    CGoblinData::ParesMoFuString(this, &p_MoFuString);
    std::string::~string(&p_MoFuString);
    std::allocator<char>::allocator(&v31);
    v11 = Answer::MySqlQuery::getStringValue(&result, "wing_refining", byte_8CFE00);
    std::string::string(&WingRefining, v11, &v31);
    std::allocator<char>::~allocator(&v31);
    std::string::string(&p_WingEquipRefiningString, &WingRefining);
    CGoblinData::ParesWingEquipRefiningString(this, &p_WingEquipRefiningString);
    std::string::~string(&p_WingEquipRefiningString);
    std::allocator<char>::allocator(&v33);
    v12 = Answer::MySqlQuery::getStringValue(&result, "vip_pos", byte_8CFE00);
    std::string::string(&VipPosString, v12, &v33);
    std::allocator<char>::~allocator(&v33);
    std::string::string(&p_VipPosString, &VipPosString);
    CGoblinData::ParesVipPosString(this, &p_VipPosString);
    std::string::~string(&p_VipPosString);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&VipPosString);
    std::string::~string(&WingRefining);
    std::string::~string(&MoFuString);
    std::string::~string(&WingEquipPolishString);
    std::string::~string(&ShouHuInfoString);
    std::string::~string(&GoblinInfoString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CGoblinData::PackageData(CGoblinData *const this, Answer::NetPacket *packet)
{
  int8_t v2; // dl
  int first; // edx
  int32_t GoblinLevel; // edx
  int32_t GoblinRes; // edx
  int8_t v6; // dl
  int v7; // edx
  int32_t second; // edx
  int8_t v9; // dl
  int v10; // edx
  int32_t v11; // edx
  int8_t v12; // dl
  int v13; // edx
  int32_t v14; // edx
  int8_t v15; // dl
  int v16; // edx
  int32_t v17; // edx
  int8_t v18; // dl
  int v19; // edx
  int32_t v20; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > vipIt; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > WingRefiningIt; // [rsp+20h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > MoFuIt; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itWin; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+50h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > iter; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v28; // [rsp+80h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v29; // [rsp+90h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v30; // [rsp+A0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v31; // [rsp+B0h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v32; // [rsp+C0h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::map<int,GoblinInfo>::size(&this->m_GoblinInfoMap);
    Answer::NetPacket::writeInt8(packet, v2);
    for ( iter._M_node = std::map<int,GoblinInfo>::begin(&this->m_GoblinInfoMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator++(&iter, 0) )
    {
      __x._M_node = std::map<int,GoblinInfo>::end(&this->m_GoblinInfoMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&iter, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&iter)->first;
      Answer::NetPacket::writeInt32(packet, first);
      GoblinLevel = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&iter)->second.GoblinLevel;
      Answer::NetPacket::writeInt32(packet, GoblinLevel);
      GoblinRes = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&iter)->second.GoblinRes;
      Answer::NetPacket::writeInt32(packet, GoblinRes);
    }
    v6 = std::map<int,int>::size(&this->m_ShouHuRefiningLeveMap);
    Answer::NetPacket::writeInt8(packet, v6);
    for ( it._M_node = std::map<int,int>::begin(&this->m_ShouHuRefiningLeveMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      v28._M_node = std::map<int,int>::end(&this->m_ShouHuRefiningLeveMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v28) )
        break;
      v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, v7);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
    v9 = std::map<int,int>::size(&this->m_WingEquipPolishMap);
    Answer::NetPacket::writeInt8(packet, v9);
    for ( itWin._M_node = std::map<int,int>::begin(&this->m_WingEquipPolishMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itWin, 0) )
    {
      v29._M_node = std::map<int,int>::end(&this->m_WingEquipPolishMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itWin, &v29) )
        break;
      v10 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itWin)->first;
      Answer::NetPacket::writeInt32(packet, v10);
      v11 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itWin)->second;
      Answer::NetPacket::writeInt32(packet, v11);
    }
    v12 = std::map<int,int>::size(&this->m_MoFuZhuNengMap);
    Answer::NetPacket::writeInt8(packet, v12);
    for ( MoFuIt._M_node = std::map<int,int>::begin(&this->m_MoFuZhuNengMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&MoFuIt, 0) )
    {
      v30._M_node = std::map<int,int>::end(&this->m_MoFuZhuNengMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&MoFuIt, &v30) )
        break;
      v13 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&MoFuIt)->first;
      Answer::NetPacket::writeInt32(packet, v13);
      v14 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&MoFuIt)->second;
      Answer::NetPacket::writeInt32(packet, v14);
    }
    v15 = std::map<int,int>::size(&this->m_WingEquipRefiningMap);
    Answer::NetPacket::writeInt8(packet, v15);
    for ( WingRefiningIt._M_node = std::map<int,int>::begin(&this->m_WingEquipRefiningMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&WingRefiningIt, 0) )
    {
      v31._M_node = std::map<int,int>::end(&this->m_WingEquipRefiningMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&WingRefiningIt, &v31) )
        break;
      v16 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&WingRefiningIt)->first;
      Answer::NetPacket::writeInt32(packet, v16);
      v17 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&WingRefiningIt)->second;
      Answer::NetPacket::writeInt32(packet, v17);
    }
    v18 = std::map<int,int>::size(&this->m_VipEquipPosLevelMap);
    Answer::NetPacket::writeInt8(packet, v18);
    for ( vipIt._M_node = std::map<int,int>::begin(&this->m_VipEquipPosLevelMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&vipIt, 0) )
    {
      v32._M_node = std::map<int,int>::end(&this->m_VipEquipPosLevelMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&vipIt, &v32) )
        break;
      v19 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&vipIt)->first;
      Answer::NetPacket::writeInt32(packet, v19);
      v20 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&vipIt)->second;
      Answer::NetPacket::writeInt32(packet, v20);
    }
  }
}


#####################################
void __cdecl CGoblinData::UnPackageData(CGoblinData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  GoblinInfo *v3; // rbx
  GoblinInfo *v4; // rbx
  int *v5; // rbx
  int *v6; // rbx
  int *v7; // rbx
  int *v8; // rbx
  int *v9; // rbx
  int32_t VipEquipSlot; // [rsp+20h] [rbp-30h] BYREF
  int32_t WingRefiningSlot; // [rsp+24h] [rbp-2Ch] BYREF
  int32_t MoFuSlot; // [rsp+28h] [rbp-28h] BYREF
  int32_t WinEquipSlot; // [rsp+2Ch] [rbp-24h] BYREF
  int32_t ShouHuType; // [rsp+30h] [rbp-20h] BYREF
  int32_t GoblinType; // [rsp+34h] [rbp-1Ch] BYREF
  int8_t nSize; // [rsp+39h] [rbp-17h]
  int8_t i; // [rsp+3Ah] [rbp-16h]
  int8_t i_0; // [rsp+3Bh] [rbp-15h]
  int8_t i_1; // [rsp+3Ch] [rbp-14h]
  int8_t i_2; // [rsp+3Dh] [rbp-13h]
  int8_t i_3; // [rsp+3Eh] [rbp-12h]
  int8_t i_4; // [rsp+3Fh] [rbp-11h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      GoblinType = Answer::NetPacket::readInt32(inPacket);
      if ( !IsGoblinType(GoblinType) )
      {
        Answer::NetPacket::readInt32(inPacket);
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v3 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &GoblinType);
        v3->GoblinLevel = Answer::NetPacket::readInt32(inPacket);
        v4 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &GoblinType);
        v4->GoblinRes = Answer::NetPacket::readInt32(inPacket);
      }
    }
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i_0 = 0; i_0 < nSize; ++i_0 )
    {
      ShouHuType = Answer::NetPacket::readInt32(inPacket);
      if ( !IsShouHunType(ShouHuType) )
      {
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v5 = std::map<int,int>::operator[](&this->m_ShouHuRefiningLeveMap, &ShouHuType);
        *v5 = Answer::NetPacket::readInt32(inPacket);
      }
    }
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i_1 = 0; i_1 < nSize; ++i_1 )
    {
      WinEquipSlot = Answer::NetPacket::readInt32(inPacket);
      if ( !IsWingEquipSlot(WinEquipSlot) )
      {
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v6 = std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &WinEquipSlot);
        *v6 = Answer::NetPacket::readInt32(inPacket);
      }
    }
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i_2 = 0; i_2 < nSize; ++i_2 )
    {
      MoFuSlot = Answer::NetPacket::readInt32(inPacket);
      if ( !IsMoFuSlot(MoFuSlot) )
      {
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v7 = std::map<int,int>::operator[](&this->m_MoFuZhuNengMap, &MoFuSlot);
        *v7 = Answer::NetPacket::readInt32(inPacket);
      }
    }
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i_3 = 0; i_3 < nSize; ++i_3 )
    {
      WingRefiningSlot = Answer::NetPacket::readInt32(inPacket);
      if ( !IsWingEquipSlot(WingRefiningSlot) )
      {
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v8 = std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &WingRefiningSlot);
        *v8 = Answer::NetPacket::readInt32(inPacket);
      }
    }
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i_4 = 0; i_4 < nSize; ++i_4 )
    {
      VipEquipSlot = Answer::NetPacket::readInt32(inPacket);
      if ( !IsVipEquipSlot(VipEquipSlot) )
      {
        Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        v9 = std::map<int,int>::operator[](&this->m_VipEquipPosLevelMap, &VipEquipSlot);
        *v9 = Answer::NetPacket::readInt32(inPacket);
      }
    }
  }
}


#####################################
std::string __cdecl CGoblinData::GetGoblinInfoString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,GoblinInfo> *v3; // rax
  std::pair<const int,GoblinInfo> *v4; // rax
  std::pair<const int,GoblinInfo> *v5; // rax
  _BYTE v7[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v8[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GoblinInfo> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v7, (unsigned int)v2);
  for ( it._M_node = std::map<int,GoblinInfo>::begin((std::map<int,GoblinInfo> *const)(v1 + 8))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,GoblinInfo>::end((std::map<int,GoblinInfo> *const)(v1 + 8))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
    std::ostream::operator<<(v8, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v8, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
    std::ostream::operator<<(v8, (unsigned int)v4->second.GoblinLevel);
    std::operator<<<std::char_traits<char>>(v8, ":");
    v5 = std::_Rb_tree_iterator<std::pair<int const,GoblinInfo>>::operator->(&it);
    std::ostream::operator<<(v8, (unsigned int)v5->second.GoblinRes);
    std::operator<<<std::char_traits<char>>(v8, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v7);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v7);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesGoblinInfoString(CGoblinData *const this, std::string *p_GoblinInfoString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  GoblinInfo *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  GoblinInfo *v8; // rbx
  std::string *v9; // rax
  const char *v10; // rax
  int32_t nType; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v15; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v16; // [rsp+70h] [rbp-30h] BYREF
  char v17; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_GoblinInfoString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v15);
    std::string::string(&delims, "|", &v15);
    Answer::StringUtility::split(&vStr, p_GoblinInfoString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v15);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v17);
      std::string::string(&v16, ":", &v17);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v16, 0);
      std::string::~string(&v16);
      std::allocator<char>::~allocator(&v17);
      if ( std::vector<std::string>::size(&tv) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( IsGoblinType(nType) )
        {
          v5 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          v5->GoblinLevel = atoi(v7);
          v8 = std::map<int,GoblinInfo>::operator[](&this->m_GoblinInfoMap, &nType);
          v9 = std::vector<std::string>::operator[](&tv, 2u);
          v10 = (const char *)std::string::c_str(v9);
          v8->GoblinRes = atoi(v10);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CGoblinData::GetShouHuRefiningString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 56))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 56))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesShouHuRefiningString(CGoblinData *const this, std::string *p_ShouHuRefiningString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nType; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_ShouHuRefiningString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_ShouHuRefiningString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( IsShouHunType(nType) )
        {
          v5 = std::map<int,int>::operator[](&this->m_ShouHuRefiningLeveMap, &nType);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CGoblinData::GetWingEquipPolishString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 104))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 104))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesWingEquipPolishString(CGoblinData *const this, std::string *p_WingEquipPolishString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nType; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_WingEquipPolishString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_WingEquipPolishString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( IsWingEquipSlot(nType) )
        {
          v5 = std::map<int,int>::operator[](&this->m_WingEquipPolishMap, &nType);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CGoblinData::GetMoFuString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 152))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 152))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesMoFuString(CGoblinData *const this, std::string *p_MoFuString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nSlot; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_MoFuString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_MoFuString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nSlot = atoi(v4);
        if ( IsMoFuSlot(nSlot) )
        {
          v5 = std::map<int,int>::operator[](&this->m_MoFuZhuNengMap, &nSlot);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CGoblinData::GetWingEquipRefiningString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 200))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 200))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesWingEquipRefiningString(CGoblinData *const this, std::string *p_WingEquipRefiningString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nType; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_WingEquipRefiningString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_WingEquipRefiningString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( IsWingEquipSlot(nType) )
        {
          v5 = std::map<int,int>::operator[](&this->m_WingEquipRefiningMap, &nType);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CGoblinData::GetVipPosString(CGoblinData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 248))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 248))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CGoblinData::ParesVipPosString(CGoblinData *const this, std::string *p_VipPosString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nSlot; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_VipPosString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_VipPosString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nSlot = atoi(v4);
        if ( IsVipEquipSlot(nSlot) )
        {
          v5 = std::map<int,int>::operator[](&this->m_VipEquipPosLevelMap, &nSlot);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


