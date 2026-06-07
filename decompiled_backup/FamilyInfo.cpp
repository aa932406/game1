// Decompiled methods for class: FamilyInfo
// Source: gameserver.cc
// Total methods: 3

#####################################
bool __cdecl FamilyInfo::IsDeclareWarFamily(FamilyInfo *const this, FamilyId_t nFamilyId)
{
  FamilyId_t nFamilyIda; // [rsp+0h] [rbp-30h] BYREF
  FamilyInfo *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<long int> it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<long int> __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  it._M_node = std::set<long>::find(&this->DeclareFamilies, &nFamilyIda)._M_node;
  __x._M_node = std::set<long>::end(&thisa->DeclareFamilies)._M_node;
  return std::_Rb_tree_const_iterator<long>::operator!=(&it, &__x);
}


#####################################
void __cdecl FamilyInfo::CleanUp(FamilyInfo *const this)
{
  this->nId = 0;
  this->nLevel = 0;
  this->nMemberCard = 0;
  std::string::operator=(&this->strName, byte_8D80C0);
  this->FamilyTaskCount = 0;
  this->nBossPoints = 0;
  this->FamilyLeaderCid = 0;
  std::string::operator=(&this->FamilyLeaderName, byte_8D80C0);
  this->Battle = 0;
  this->Territory = 0;
  this->MedalLevel = 0;
  this->nBossState = 0;
  std::set<long>::clear(&this->DeclareFamilies);
}


#####################################
void __cdecl FamilyInfo::UnPackageData(FamilyInfo *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket v2; // [rsp+20h] [rbp-50h] BYREF

  if ( packet )
  {
    this->nId = Answer::NetPacket::readInt64(packet);
    Answer::NetPacket::readUTF8(&v2, (bool)packet);
    std::string::operator=(&this->strName, &v2);
    std::string::~string(&v2);
    this->nLevel = Answer::NetPacket::readInt32(packet);
    this->nMemberCard = Answer::NetPacket::readInt8(packet);
    this->FamilyTaskCount = Answer::NetPacket::readInt32(packet);
    this->nBossPoints = Answer::NetPacket::readInt32(packet);
    this->FamilyLeaderCid = Answer::NetPacket::readInt64(packet);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v2.m_wOffset, (bool)packet);
    std::string::operator=(&this->FamilyLeaderName, &v2.m_wOffset);
    std::string::~string(&v2.m_wOffset);
    this->Battle = Answer::NetPacket::readInt32(packet);
    this->Territory = Answer::NetPacket::readInt8(packet);
    this->MedalLevel = Answer::NetPacket::readInt32(packet);
    this->nBossState = Answer::NetPacket::readInt8(packet);
    v2.m_autoIncrease = Answer::NetPacket::readInt32(packet);
    for ( *(&v2.m_autoIncrease + 1) = 0; *(&v2.m_autoIncrease + 1) < v2.m_autoIncrease; ++*(&v2.m_autoIncrease + 1) )
    {
      v2.m_pool = (Answer::NetPacketPool *)Answer::NetPacket::readInt64(packet);
      *(std::pair<std::_Rb_tree_const_iterator<long int>,bool> *)&v2.m_size = std::set<long>::insert(
                                                                                &this->DeclareFamilies,
                                                                                (const __int64 *const)&v2.m_pool);
    }
  }
}


