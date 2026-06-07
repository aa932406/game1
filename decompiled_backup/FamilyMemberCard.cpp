// Decompiled methods for class: FamilyMemberCard
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl FamilyMemberCard::~FamilyMemberCard(FamilyMemberCard *const this)
{
  FamilyMemberCard::~FamilyMemberCard(this);
  operator delete(this);
}


#####################################
int32_t __cdecl FamilyMemberCard::effect(
        FamilyMemberCard *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // ebx
  FamilyManager *v5; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  uint32_t WOffset; // eax
  int8_t v9; // bl
  GameService *v10; // rax
  FamilyInfo info; // [rsp+20h] [rbp-90h] BYREF
  FamilyId_t nFamilyId; // [rsp+90h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  nFamilyId = Player::getFamilyId(launcher);
  if ( nFamilyId <= 0 )
    return 10002;
  if ( Player::getFamilyPosition(launcher) != 3 )
    return 10002;
  v5 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v5, nFamilyId);
  if ( info.nMemberCard )
  {
    v4 = 10002;
  }
  else
  {
    ConnId = Player::getConnId(launcher);
    v7 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E4Du);
    if ( packet )
    {
      Answer::NetPacket::writeInt64(packet, nFamilyId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v9 = Player::getConnId(launcher);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v10, v9, packet);
      v4 = 0;
    }
    else
    {
      v4 = 10002;
    }
  }
  FamilyInfo::~FamilyInfo(&info);
  return v4;
}


#####################################
bool __cdecl FamilyMemberCard::parseEffect(
        FamilyMemberCard *const this,
        int32_t id,
        const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_addon = atoi(v3);
  return 1;
}


