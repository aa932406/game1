// Decompiled methods for class: CExtCharSkill
// Source: gameserver.cc
// Total methods: 49

#####################################
void __cdecl CExtCharSkill::~CExtCharSkill(CExtCharSkill *const this)
{
  CExtCharSkill::~CExtCharSkill(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharSkill::OnCleanUp(CExtCharSkill *const this)
{
  std::map<int,SkillLevelInfo>::clear(&this->m_SkillLevelMap);
  std::list<AddonSkill>::clear(&this->m_lAddonSkills);
  this->m_nLastAddonTick = 0;
  this->m_PowerLastTick = 0;
  this->m_lastActionTick = 0;
  this->m_nLastEnergyTick = 0;
  std::map<int,long>::clear(&this->m_mSkillCD);
  std::list<int>::clear(&this->m_lActiveSkills);
  std::list<int>::clear(&this->m_lPassiveSkills);
  std::list<int>::clear(&this->m_lTrigSkills);
  this->m_nPower = 0;
  this->m_nDropMoneyRate = 0;
  std::list<SummonSkill>::clear(&this->m_lSummonSkills);
  std::map<int,CfgActiveSkill>::clear(&this->m_mActiveSkills);
  std::list<MemTalent>::clear(&this->m_lActiveTalent);
  this->m_SkillBattle = 0;
  std::map<int,int>::clear(&this->m_OthreSkillLevelMap);
  this->m_SkillPublicCD = 0;
}


#####################################
void __cdecl CExtCharSkill::OnLoadFromDB(CExtCharSkill *const this, const PlayerDBData *const dbData)
{
  int32_t Level; // ebx
  int first; // ecx
  std::_Rb_tree_const_iterator<std::pair<const int,SkillLevelInfo> > it; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __it; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > v7; // [rsp+40h] [rbp-20h] BYREF

  CExtCharSkill::loadTalentPoints(this, &dbData->skillData.talents);
  this->m_nPower = dbData->skillData.m_nPower;
  __it._M_node = std::map<int,SkillLevelInfo>::begin(&this->m_SkillLevelMap)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::_Rb_tree_const_iterator(&it, &__it);
  while ( 1 )
  {
    v7._M_node = std::map<int,SkillLevelInfo>::end(&this->m_SkillLevelMap)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::_Rb_tree_const_iterator(&__x, &v7);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&it, &__x) )
      break;
    Level = std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
    first = std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->first;
    CExtCharSkill::initSkills(this, first, Level);
    std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator++(&it, 0);
  }
  CExtCharSkill::CallSkillBattle(this);
}


#####################################
void __cdecl CExtCharSkill::InitSystem(CExtCharSkill *const this)
{
  int32_t Now; // ebx
  int32_t AddCount; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer && Player::getLastLogoutTime(this->m_pPlayer) > 0 )
  {
    Now = Unit::getNow(this->m_pPlayer);
    AddCount = (Now - Player::getLastLogoutTime(this->m_pPlayer)) / 60;
    if ( AddCount > 0 )
      CExtCharSkill::AddPower(this, 60 * AddCount);
    this->m_PowerLastTick = Unit::getTick(this->m_pPlayer);
  }
}


#####################################
void __cdecl CExtCharSkill::OnSaveToDB(CExtCharSkill *const this, PlayerDBData *const dbData)
{
  _BYTE v2[32]; // [rsp+10h] [rbp-20h] BYREF

  CExtCharSkill::saveTalentPoints((CExtCharSkill *const)v2);
  std::string::operator=(&dbData->skillData.talents, v2);
  std::string::~string(v2);
  dbData->skillData.m_nPower = this->m_nPower;
}


#####################################
std::string __cdecl CExtCharSkill::saveTalentPoints(CExtCharSkill *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int Point; // r12d
  unsigned int Level; // r13d
  const std::pair<const int,SkillLevelInfo> *v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  _BYTE v12[16]; // [rsp+10h] [rbp-1D0h] BYREF
  __int64 v13; // [rsp+20h] [rbp-1C0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SkillLevelInfo> > iter; // [rsp+180h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __it; // [rsp+190h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+1A0h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > v17; // [rsp+1B0h] [rbp-30h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v12, (unsigned int)v2);
  __it._M_node = std::map<int,SkillLevelInfo>::begin((std::map<int,SkillLevelInfo> *const)(v1 + 16))._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::_Rb_tree_const_iterator(&iter, &__it);
  while ( 1 )
  {
    v17._M_node = std::map<int,SkillLevelInfo>::end((std::map<int,SkillLevelInfo> *const)(v1 + 16))._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::_Rb_tree_const_iterator(&__x, &v17);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&iter, &__x) )
      break;
    Point = std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter)->second.Point;
    Level = std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter)->second.Level;
    v5 = std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter);
    v6 = std::ostream::operator<<(&v13, (unsigned int)v5->first);
    v7 = std::operator<<<std::char_traits<char>>(v6, ":");
    v8 = std::ostream::operator<<(v7, Level);
    v9 = std::operator<<<std::char_traits<char>>(v8, ":");
    v10 = std::ostream::operator<<(v9, Point);
    std::operator<<<std::char_traits<char>>(v10, "|");
    std::_Rb_tree_const_iterator<std::pair<int const,SkillLevelInfo>>::operator++(&iter);
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v12);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v12);
  return (std::string)this;
}


#####################################
void __cdecl CExtCharSkill::loadTalentPoints(CExtCharSkill *const this, const std::string *const str)
{
  std::string *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  int32_t v10; // ebx
  CfgData *v11; // rax
  const CfgTalentTable *TalentTable; // rax
  Job_t Job; // bl
  CfgData *v14; // rax
  const CfgTalentTable *v15; // rax
  SkillLevelInfo stu; // [rsp+10h] [rbp-B0h]
  int32_t nTalent; // [rsp+1Ch] [rbp-A4h] BYREF
  StringVector vt; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+50h] [rbp-70h] BYREF
  std::string delims; // [rsp+70h] [rbp-50h] BYREF
  char v22; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  std::string v24; // [rsp+90h] [rbp-30h] BYREF
  char v25; // [rsp+9Fh] [rbp-21h] BYREF

  if ( !std::operator==<char>(str, byte_8CC180) && this->m_pPlayer )
  {
    std::allocator<char>::allocator(&v22);
    std::string::string(&delims, "|", &v22);
    Answer::StringUtility::split(&vStr, str, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v22);
    for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(&v25);
      std::string::string(&v24, ":", &v25);
      v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&vt, v3, &v24, 0);
      std::string::~string(&v24);
      std::allocator<char>::~allocator(&v25);
      if ( std::vector<std::string>::size(&vt) == 3 )
      {
        v4 = std::vector<std::string>::operator[](&vt, 0);
        v5 = (const char *)std::string::c_str(v4);
        nTalent = atoi(v5);
        v6 = std::vector<std::string>::operator[](&vt, 1u);
        v7 = (const char *)std::string::c_str(v6);
        stu.Level = atoi(v7);
        v8 = std::vector<std::string>::operator[](&vt, 2u);
        v9 = (const char *)std::string::c_str(v8);
        stu.Point = atoi(v9);
        v10 = nTalent;
        v11 = Answer::Singleton<CfgData>::instance();
        TalentTable = CfgData::GetTalentTable(v11);
        if ( CfgTalentTable::GetTalent(TalentTable, v10, stu.Level) )
        {
          Job = Player::getJob(this->m_pPlayer);
          v14 = Answer::Singleton<CfgData>::instance();
          v15 = CfgData::GetTalentTable(v14);
          if ( CfgTalentTable::GetTalentPage(v15, Job) )
            *std::map<int,SkillLevelInfo>::operator[](&this->m_SkillLevelMap, &nTalent) = stu;
        }
      }
      std::vector<std::string>::~vector(&vt);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
void __cdecl CExtCharSkill::OnUpdate(CExtCharSkill *const this, int64_t curTick)
{
  CExtCharSkill::checkAddonSkills(this, curTick);
  CExtCharSkill::checkSummonSkills(this, curTick);
  CExtCharSkill::checkSuitSkillEnergy(this, curTick);
  CExtCharSkill::checkActiveList(this);
  if ( curTick - this->m_PowerLastTick > 59999 )
  {
    this->m_PowerLastTick = curTick;
    CExtCharSkill::AddPower(this, 60);
  }
}


#####################################
void __cdecl CExtCharSkill::GetInterestsProtocol(CExtCharSkill *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v3; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v4; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v5; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 111;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 40;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 38;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 37;
  std::list<unsigned short>::push_back(procList, &v5);
}


#####################################
int32_t __cdecl CExtCharSkill::DispatchNetDatas(
        CExtCharSkill *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 40 )
    return CExtCharSkill::onDoUnitSkill(this, inPacket);
  if ( nProcId > 0x28u )
  {
    if ( nProcId == 111 )
      return CExtCharSkill::onAddTalentPoint(this, inPacket);
  }
  else if ( nProcId == 37 )
  {
    CExtCharSkill::SendTalentInfo(this);
  }
  else if ( nProcId == 38 )
  {
    return CExtCharSkill::onDoAddonSkill(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharSkill::onAddTalentPoint(CExtCharSkill *const this, Answer::NetPacket *inPacket)
{
  int32_t Level; // r12d
  int32_t v4; // ebx
  CfgData *v5; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t v7; // r12d
  int32_t v8; // ebx
  CfgData *v9; // rax
  const CfgTalentTable *v10; // rax
  int32_t v11; // eax
  std::pair<const int,SkillLevelInfo> *v12; // rax
  std::pair<const int,SkillLevelInfo> *v13; // rax
  int32_t v15; // ebx
  int first; // ecx
  std::pair<const int,SkillLevelInfo> *v17; // rax
  std::pair<const int,SkillLevelInfo> *v18; // rax
  int32_t v19; // ebx
  int v20; // ecx
  int8_t ConnId; // bl
  GameService *v22; // rax
  CharId_t Cid; // rax
  std::pair<const int,SkillLevelInfo> *v24; // rax
  std::pair<const int,SkillLevelInfo> *v25; // rax
  uint32_t WOffset; // eax
  int8_t v27; // bl
  GameService *v28; // rax
  int8_t v29; // bl
  DBService *v30; // rax
  int64_t v31; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v34; // bl
  GameService *v35; // rax
  skill_log stu; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > it; // [rsp+50h] [rbp-80h] BYREF
  int32_t nId; // [rsp+5Ch] [rbp-74h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+60h] [rbp-70h] BYREF
  std::string val; // [rsp+70h] [rbp-60h] BYREF
  _BYTE v41[16]; // [rsp+80h] [rbp-50h] BYREF
  char v42; // [rsp+90h] [rbp-40h] BYREF
  const CfgTalent *pCfgTalent; // [rsp+98h] [rbp-38h]
  const CfgTalent *pCfgNextTalent; // [rsp+A0h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+A8h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,SkillLevelInfo>::find(&this->m_SkillLevelMap, &nId)._M_node;
  __x._M_node = std::map<int,SkillLevelInfo>::end(&this->m_SkillLevelMap)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&it, &__x) )
    return 10002;
  Level = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
  v4 = nId;
  v5 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v5);
  pCfgTalent = CfgTalentTable::GetTalent(TalentTable, v4, Level);
  if ( !pCfgTalent )
    return 10002;
  v7 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level + 1;
  v8 = nId;
  v9 = Answer::Singleton<CfgData>::instance();
  v10 = CfgData::GetTalentTable(v9);
  pCfgNextTalent = CfgTalentTable::GetTalent(v10, v8, v7);
  if ( !pCfgNextTalent )
    return 10002;
  v11 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  if ( v11 < pCfgNextTalent->Playerlevel )
    return 10002;
  v12 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
  if ( v12->second.Level > pCfgTalent->maxLevel )
    return 10002;
  if ( pCfgTalent->Point < 0 )
    return 10002;
  v13 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
  if ( v13->second.Point < pCfgTalent->Point )
    return 10002;
  v15 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
  first = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->first;
  CExtCharSkill::removeSkillByTalent(this, first, v15);
  v17 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
  v17->second.Point -= pCfgTalent->Point;
  v18 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
  ++v18->second.Level;
  CExtCharSkill::CallSkillBattle(this);
  v19 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
  v20 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->first;
  CExtCharSkill::initSkills(this, v20, v19);
  if ( pCfgTalent->GongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v22 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v22, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 10002;
    Answer::NetPacket::writeInt32(packet, pCfgTalent->GongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    v24 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
    Answer::NetPacket::writeInt32(packet, v24->first);
    v25 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
    Answer::NetPacket::writeInt32(packet, v25->second.Level);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v27 = Player::getConnId(this->m_pPlayer);
    v28 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v28, v27, packet);
  }
  skill_log::skill_log(&stu);
  stu.log_Sid = Player::getSid(this->m_pPlayer);
  stu.log_time = Unit::getNow(this->m_pPlayer);
  Player::GetPassport((Player *const)v41);
  std::string::operator=(&stu.passport, v41);
  std::string::~string(v41);
  stu.cid = Player::getCid(this->m_pPlayer);
  Player::getName((const Player *const)&v42);
  std::string::operator=(&stu.name, &v42);
  std::string::~string(&v42);
  stu.op_time = Unit::getNow(this->m_pPlayer);
  stu.skill_id = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->first;
  stu.oper_id = 2;
  stu.level = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
  v29 = Player::getConnId(this->m_pPlayer);
  v30 = Answer::Singleton<DBService>::instance();
  DBService::AddPlatformLog(v30, v29, PLATFORM_LOG_DATA_TYPE::PLDT_SKILL, &stu);
  skill_log::~skill_log(&stu);
  CExtCharSkill::SendTalentInfo(this);
  v31 = nId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v34 = Player::getConnId(this->m_pPlayer);
  v35 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v35, v34, GateIndex, Proc, v31);
}


#####################################
bool __cdecl CExtCharSkill::CanUseSkillAndMove(CExtCharSkill *const this, int64_t nCurTick, bool ResetTick)
{
  int32_t nPublicCd; // [rsp+24h] [rbp-Ch]

  nPublicCd = CExtCharSkill::calActiveSkillCD(this, 0);
  if ( !ResetTick )
    nPublicCd /= 8;
  if ( nPublicCd > nCurTick - this->m_SkillPublicCD )
    return 0;
  if ( ResetTick )
    this->m_SkillPublicCD = nCurTick;
  return 1;
}


#####################################
int32_t __cdecl CExtCharSkill::onDoUnitSkill(CExtCharSkill *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  Map *Map; // rax
  CExtCharCarrier *CharCarrier; // rax
  CExtCharCarrier *v7; // rax
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<int> v9; // rax
  int32_t Now; // ebx
  int32_t Record; // eax
  int32_t v12; // eax
  int32_t v13; // ebx
  int32_t v14; // eax
  int32_t v15; // eax
  int32_t v16; // ebx
  int32_t v17; // eax
  int32_t v18; // eax
  __int64 *v19; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t MP; // eax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v26; // rax
  int32_t v27; // r12d
  Position CurrentTile; // rsi
  uint16_t v29; // r13
  int16_t v30; // r12
  int8_t v31; // bl
  GameService *v32; // rax
  int64_t Tick; // rax
  CExtOperateLimit *v34; // rax
  int32_t v35; // ebx
  ChrTask *Task; // rax
  __int64 *v37; // rax
  int64_t v38; // r13
  int16_t v39; // r12
  int8_t v40; // bl
  GameService *v41; // rax
  AddonSkill addonSkill; // [rsp+20h] [rbp-A0h] BYREF
  SkillResultVector results; // [rsp+40h] [rbp-80h] BYREF
  int32_t nGroupId; // [rsp+58h] [rbp-68h] BYREF
  int32_t nSkillId; // [rsp+5Ch] [rbp-64h] BYREF
  std::_List_iterator<int> __x; // [rsp+60h] [rbp-60h] BYREF
  std::_List_iterator<int> v49; // [rsp+70h] [rbp-50h] BYREF
  int32_t nSkillFlag; // [rsp+78h] [rbp-48h]
  bool bInCarrier; // [rsp+7Fh] [rbp-41h]
  const CfgActiveSkill *pCfgSkill; // [rsp+80h] [rbp-40h]
  int32_t nCDTime; // [rsp+8Ch] [rbp-34h]
  int64_t nCurTick; // [rsp+90h] [rbp-30h]
  int32_t ret; // [rsp+9Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  if ( StaticObj::getMap(this->m_pPlayer) )
  {
    Map = StaticObj::getMap(this->m_pPlayer);
    if ( Map::GetMapParam(Map) == 21 )
      return 10002;
  }
  if ( !Unit::isAlive(this->m_pPlayer) )
    return 10002;
  if ( Player::IsInStall(this->m_pPlayer) )
    return 10002;
  if ( Unit::HasBuffState(this->m_pPlayer, CObjState::Index_T::OBS_CHENMO)
    || Unit::HasBuffState(this->m_pPlayer, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this->m_pPlayer, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this->m_pPlayer, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this->m_pPlayer, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  nSkillId = Answer::NetPacket::readInt32(inPacket);
  nSkillFlag = Answer::NetPacket::readInt32(inPacket);
  CharCarrier = Player::GetCharCarrier(this->m_pPlayer);
  bInCarrier = CExtCharCarrier::IsInCarrier(CharCarrier);
  if ( bInCarrier )
  {
    v7 = Player::GetCharCarrier(this->m_pPlayer);
    if ( !CExtCharCarrier::HaveSkill(v7, nSkillId) )
      return 10002;
  }
  else
  {
    __x._M_node = std::list<int>::end(&this->m_lActiveSkills)._M_node;
    M_node = std::list<int>::end(&this->m_lActiveSkills)._M_node;
    v9._M_node = std::list<int>::begin(&this->m_lActiveSkills)._M_node;
    v49._M_node = std::find<std::_List_iterator<int>,int>(v9, (std::_List_iterator<int>)M_node, &nSkillId)._M_node;
    if ( std::_List_iterator<int>::operator==(&v49, &__x) )
      return 10002;
  }
  pCfgSkill = CExtCharSkill::getActiveSkill(this, nSkillId);
  if ( !pCfgSkill )
    return 10002;
  nGroupId = pCfgSkill->groupid;
  nCDTime = CExtCharSkill::calActiveSkillCD(this, nSkillId);
  nCurTick = Unit::getTick(this->m_pPlayer);
  if ( !CExtCharSkill::CanUseSkillAndMove(this, nCurTick, 1) )
    return 10002;
  switch ( nGroupId )
  {
    case 4001:
      Now = Unit::getNow(this->m_pPlayer);
      Record = Player::getRecord(this->m_pPlayer, 1927);
      if ( Now - Record < nCDTime / 1000 )
        return 10002;
      v12 = Unit::getNow(this->m_pPlayer);
      Player::updateRecord(this->m_pPlayer, 1927, v12);
      break;
    case 3901:
      v13 = Unit::getNow(this->m_pPlayer);
      v14 = Player::getRecord(this->m_pPlayer, 1928);
      if ( v13 - v14 < nCDTime / 1000 )
        return 10002;
      v15 = Unit::getNow(this->m_pPlayer);
      Player::updateRecord(this->m_pPlayer, 1928, v15);
      break;
    case 5001:
      v16 = Unit::getNow(this->m_pPlayer);
      v17 = Player::getRecord(this->m_pPlayer, 1929);
      if ( v16 - v17 < nCDTime / 1000 )
        return 10002;
      v18 = Unit::getNow(this->m_pPlayer);
      Player::updateRecord(this->m_pPlayer, 1929, v18);
      break;
  }
  v19 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
  if ( nCurTick - *v19 < nCDTime )
    return 10002;
  if ( pCfgSkill->kind == 2 )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    if ( CExtOperateLimit::GetLimitCount(OperateLimit, 1083) <= 99 )
      return 10002;
  }
  else
  {
    MP = Unit::GetMP(this->m_pPlayer);
    if ( MP < pCfgSkill->mp || this->m_nPower < pCfgSkill->power )
    {
      Proc = Answer::NetPacket::getProc(inPacket);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v26 = Answer::Singleton<GameService>::instance();
      return GameService::replyfailure(v26, ConnId, GateIndex, Proc, 10009, 0);
    }
  }
  std::vector<SkillResult>::vector(&results);
  v27 = nSkillId;
  CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
  ret = CExtCharSkill::doSkill(this, inPacket, pCfgSkill, &results, CurrentTile, v27, nSkillFlag, 1);
  if ( ret )
  {
    v29 = Answer::NetPacket::getProc(inPacket);
    v30 = Player::getGateIndex(this->m_pPlayer);
    v31 = Player::getConnId(this->m_pPlayer);
    v32 = Answer::Singleton<GameService>::instance();
    v2 = GameService::replyfailure(v32, v31, v30, v29, ret, 0);
  }
  else
  {
    Unit::setStand(this->m_pPlayer);
    if ( !bInCarrier )
    {
      Unit::checkBuffEffect(this->m_pPlayer, BUFF_EFFECT_TYPE::BET_USE_SKILL);
      CExtCharSkill::checkSkillTrigBuff(this, pCfgSkill, &results);
      CExtCharSkill::CheckSkillTrigBuff(this, pCfgSkill->groupid, this->m_pPlayer, 2);
    }
    if ( pCfgSkill->addon_skill > 0 )
    {
      addonSkill.nEndTick = 0;
      *(_QWORD *)&addonSkill.nTrigTimes = 0;
      addonSkill.nSkillFlag = nSkillFlag;
      addonSkill.nSkillId = nSkillId;
      Tick = Unit::getTick(this->m_pPlayer);
      addonSkill.nEndTick = pCfgSkill->addon_time + Tick;
      CExtCharSkill::addAddonSkill(this, &addonSkill);
    }
    if ( pCfgSkill->kind == 2 )
    {
      v34 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::Reset(v34, 1083);
    }
    else
    {
      if ( pCfgSkill->power )
        CExtCharSkill::AddPower(this, -pCfgSkill->power);
      if ( pCfgSkill->mp )
        Unit::AddMP(this->m_pPlayer, -pCfgSkill->mp);
    }
    Unit::SetSkillFlag(this->m_pPlayer, nSkillFlag);
    Player::SetStartProtect(this->m_pPlayer, 0);
    v35 = nSkillId;
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskSkill(Task, v35);
    v37 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
    *v37 = nCurTick;
    this->m_lastActionTick = nCurTick;
    if ( pCfgSkill->shu_lian_du > 0 )
      CExtCharSkill::AddSkillPoint(this, pCfgSkill->talent, 1);
    v38 = nSkillId;
    v39 = Player::getGateIndex(this->m_pPlayer);
    v40 = Player::getConnId(this->m_pPlayer);
    v41 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v41, v40, v39, 0x28u, v38);
    v2 = 0;
  }
  std::vector<SkillResult>::~vector(&results);
  return v2;
}


#####################################
int32_t __cdecl CExtCharSkill::onDoAddonSkill(CExtCharSkill *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // eax
  SkillResultVector results; // [rsp+20h] [rbp-70h] BYREF
  Position srcPos; // [rsp+40h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+50h] [rbp-40h] BYREF
  int32_t nSkillId; // [rsp+58h] [rbp-38h]
  int32_t nSkillFlag; // [rsp+5Ch] [rbp-34h]
  AddonSkill *pAddonSkill; // [rsp+60h] [rbp-30h]
  const CfgActiveSkill *pCfgSkill; // [rsp+68h] [rbp-28h]
  const CfgActiveSkill *pCfgAddonSkill; // [rsp+70h] [rbp-20h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nSkillId = Answer::NetPacket::readInt32(inPacket);
  nSkillFlag = Answer::NetPacket::readInt32(inPacket);
  Position::Position(&srcPos, 0, 0);
  srcPos.x = Answer::NetPacket::readInt32(inPacket);
  srcPos.y = Answer::NetPacket::readInt32(inPacket);
  pAddonSkill = CExtCharSkill::getAddonSkill(this, nSkillFlag);
  if ( !pAddonSkill )
    return 10002;
  pCfgSkill = CExtCharSkill::getActiveSkill(this, pAddonSkill->nSkillId);
  if ( !pCfgSkill )
    return 10002;
  CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
  v3 = Position::tileDistance(&CurrentTile, &srcPos);
  if ( v3 > pCfgSkill->distance + 10 )
    return 10002;
  if ( pCfgSkill->addon_skill != nSkillId )
    return 10002;
  pCfgAddonSkill = CExtCharSkill::getActiveSkill(this, nSkillId);
  if ( !pCfgAddonSkill )
    return 10002;
  std::vector<SkillResult>::vector(&results);
  if ( CExtCharSkill::doSkill(this, inPacket, pCfgAddonSkill, &results, srcPos, nSkillId, nSkillFlag, 0) )
  {
    v2 = 10002;
  }
  else
  {
    CExtCharSkill::checkSkillTrigBuff(this, pCfgAddonSkill, &results);
    if ( ++pAddonSkill->nTrigTimes >= pCfgSkill->addon_trig_times )
      CExtCharSkill::removeAddonSkill(this, nSkillFlag);
    v2 = 0;
  }
  std::vector<SkillResult>::~vector(&results);
  return v2;
}


#####################################
int32_t __cdecl CExtCharSkill::doSkill(
        CExtCharSkill *const this,
        Answer::NetPacket *inPacket,
        const CfgActiveSkill *pCfgSkill,
        SkillResultVector *const results,
        Position srcPos,
        int32_t nSkillId,
        int32_t nSkillFlag,
        bool bAction)
{
  int32_t v8; // ebx
  int32_t range; // eax
  int32_t v10; // edx
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v14; // rax
  Map *Map; // rax
  CExtCharTeam *CharTeam; // rax
  size_t v18; // rax
  CharId_t Cid; // rax
  int32_t v20; // r12d
  GameService *v21; // rax
  Map *v22; // rax
  int32_t v24; // r13d
  int32_t v25; // r12d
  EntityId_t v26; // rbx
  GameService *v27; // rax
  Map *v28; // rax
  int32_t hpChange; // r12d
  int32_t unitType; // ebx
  SkillResult *v34; // rax
  int32_t v35; // r12d
  EntityId_t unitId; // rbx
  GameService *v37; // rax
  int32_t v38; // r12d
  SummonSkill summon; // [rsp+60h] [rbp-1E0h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > it; // [rsp+80h] [rbp-1C0h] BYREF
  Unit *pTarget_0; // [rsp+88h] [rbp-1B8h] BYREF
  UnitHandle target_0; // [rsp+90h] [rbp-1B0h] BYREF
  UnitVector playerTargets; // [rsp+A0h] [rbp-1A0h] BYREF
  UnitVector targets_0; // [rsp+C0h] [rbp-180h] BYREF
  std::_List_const_iterator<long int> eiter; // [rsp+E0h] [rbp-160h] BYREF
  std::_List_const_iterator<long int> iter; // [rsp+F0h] [rbp-150h] BYREF
  UnitVector targets; // [rsp+100h] [rbp-140h] BYREF
  CharIdList members; // [rsp+120h] [rbp-120h] BYREF
  UnitHandle target; // [rsp+130h] [rbp-110h] BYREF
  Position pos; // [rsp+140h] [rbp-100h]
  Skill skill; // [rsp+150h] [rbp-F0h] BYREF
  UnitHandle targetHandle; // [rsp+160h] [rbp-E0h]
  Unit *__x; // [rsp+178h] [rbp-C8h] BYREF
  std::_List_iterator<long int> v60; // [rsp+180h] [rbp-C0h] BYREF
  std::_List_iterator<long int> v61; // [rsp+190h] [rbp-B0h] BYREF
  Position CurrentTile; // [rsp+1A0h] [rbp-A0h] BYREF
  Position v63; // [rsp+1B0h] [rbp-90h] BYREF
  Unit *v64; // [rsp+1B8h] [rbp-88h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+1C0h] [rbp-80h] BYREF
  UnitHandle v66; // [rsp+1D0h] [rbp-70h] BYREF
  UnitHandle launcher; // [rsp+1E0h] [rbp-60h]
  Map *pMap; // [rsp+1F0h] [rbp-50h]
  Unit *pTarget; // [rsp+1F8h] [rbp-48h]
  CharId_t nCid; // [rsp+200h] [rbp-40h]
  Player *pMember; // [rsp+208h] [rbp-38h]
  int32_t count; // [rsp+210h] [rbp-30h]
  int32_t i; // [rsp+214h] [rbp-2Ch]
  Player *victm; // [rsp+218h] [rbp-28h]
  UnitHandle v75; // 0:rsi.8,8:edx.4

  if ( this->m_pPlayer && inPacket && pCfgSkill )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( !pMap )
      return 10002;
    Skill::Skill(&skill, pCfgSkill, nSkillFlag);
    pos = srcPos;
    range = pCfgSkill->range;
    if ( range == 1 )
    {
      UnitHandle::UnitHandle(&target, 0, 0);
      target.id = Answer::NetPacket::readInt64(inPacket);
      target.type = Answer::NetPacket::readInt32(inPacket);
      if ( (pCfgSkill->attack_type == 7 || pCfgSkill->attack_type == 8) && target.type != 2 )
      {
        v8 = 10002;
        goto LABEL_75;
      }
      RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
      type = target.type;
      id = target.id;
      v14 = Answer::Singleton<GameService>::instance();
      pTarget = GameService::getUnit(v14, id, type, RunnerId);
      if ( !pTarget || (Map = StaticObj::getMap(pTarget), Map != pMap) )
      {
        v8 = 10007;
        goto LABEL_75;
      }
      pos.x = Answer::NetPacket::readInt32(inPacket);
      pos.y = Answer::NetPacket::readInt32(inPacket);
      if ( (*((unsigned __int8 (__fastcall **)(Player *, const CfgActiveSkill *, Unit *))this->m_pPlayer->_vptr_Entity
            + 15))(
             this->m_pPlayer,
             pCfgSkill,
             pTarget) != 1 )
      {
        v8 = 10002;
        goto LABEL_75;
      }
      if ( Skill::unitAction(&skill, this->m_pPlayer, target, results, pos, bAction) < 0 )
      {
        v8 = 10002;
        goto LABEL_75;
      }
    }
    else if ( range == 10 )
    {
      std::list<long>::list(&members);
      CharTeam = Player::GetCharTeam(this->m_pPlayer);
      CExtCharTeam::GetTeamMembers(CharTeam, &members);
      std::vector<Unit *>::vector(&targets);
      v18 = std::list<long>::size(&members);
      std::vector<Unit *>::reserve(&targets, v18);
      __x = this->m_pPlayer;
      std::vector<Unit *>::push_back(&targets, &__x);
      v60._M_node = std::list<long>::begin(&members)._M_node;
      std::_List_const_iterator<long>::_List_const_iterator(&iter, &v60);
      v61._M_node = std::list<long>::end(&members)._M_node;
      std::_List_const_iterator<long>::_List_const_iterator(&eiter, &v61);
      while ( std::_List_const_iterator<long>::operator!=(&iter, &eiter) )
      {
        nCid = *std::_List_const_iterator<long>::operator*(&iter);
        Cid = Player::getCid(this->m_pPlayer);
        if ( Cid != nCid )
        {
          v20 = StaticObj::GetRunnerId(this->m_pPlayer);
          v21 = Answer::Singleton<GameService>::instance();
          pMember = GameService::getPlayer(v21, nCid, v20, 1);
          if ( pMember )
          {
            v22 = StaticObj::getMap(pMember);
            if ( v22 == pMap )
            {
              CurrentTile = StaticObj::getCurrentTile(this->m_pPlayer);
              v63 = StaticObj::getCurrentTile(pMember);
              if ( Position::tileDistance(&v63, &CurrentTile) <= 19 )
              {
                v64 = pMember;
                std::vector<Unit *>::push_back(&targets, &v64);
              }
            }
          }
        }
        std::_List_const_iterator<long>::operator++(&iter);
      }
      Skill::posAction(&skill, this->m_pPlayer, srcPos, srcPos, &targets, results, bAction);
      std::vector<Unit *>::~vector(&targets);
      std::list<long>::~list(&members);
    }
    else if ( range )
    {
      pos.x = Answer::NetPacket::readInt32(inPacket);
      pos.y = Answer::NetPacket::readInt32(inPacket);
      std::vector<Unit *>::vector(&targets_0);
      std::vector<Unit *>::vector(&playerTargets);
      count = Answer::NetPacket::readInt32(inPacket);
      std::vector<Unit *>::reserve(&targets_0, count);
      if ( (unsigned int)count <= 0x64 )
      {
        for ( i = 0; i < count && pCfgSkill->target_num > i; ++i )
        {
          UnitHandle::UnitHandle(&target_0, 0, 0);
          target_0.id = Answer::NetPacket::readInt64(inPacket);
          target_0.type = Answer::NetPacket::readInt32(inPacket);
          v24 = StaticObj::GetRunnerId(this->m_pPlayer);
          v25 = target_0.type;
          v26 = target_0.id;
          v27 = Answer::Singleton<GameService>::instance();
          pTarget_0 = GameService::getUnit(v27, v26, v25, v24);
          if ( pTarget_0 )
          {
            if ( (*((unsigned __int8 (__fastcall **)(Player *, const CfgActiveSkill *, Unit *))this->m_pPlayer->_vptr_Entity
                  + 15))(
                   this->m_pPlayer,
                   pCfgSkill,
                   pTarget_0) )
            {
              v28 = StaticObj::getMap(pTarget_0);
              if ( v28 == pMap )
                std::vector<Unit *>::push_back(&targets_0, &pTarget_0);
            }
          }
        }
      }
      Skill::posAction(&skill, this->m_pPlayer, srcPos, pos, &targets_0, results, bAction);
      std::vector<Unit *>::~vector(&playerTargets);
      std::vector<Unit *>::~vector(&targets_0);
    }
    else
    {
      targetHandle.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
      targetHandle.type = v10;
      if ( Skill::unitAction(&skill, this->m_pPlayer, targetHandle, results, pos, bAction) < 0 )
      {
        v8 = 10002;
LABEL_75:
        Skill::~Skill(&skill);
        return v8;
      }
    }
    if ( !pCfgSkill->beneficial && !std::vector<SkillResult>::empty(results) )
    {
      Player::SetInFight(this->m_pPlayer);
      for ( it._M_current = std::vector<SkillResult>::begin(results)._M_current;
            ;
            __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<SkillResult>::end(results)._M_current;
        if ( !__gnu_cxx::operator!=<SkillResult *,std::vector<SkillResult>>(&it, &__rhs) )
          break;
        hpChange = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->hpChange;
        unitType = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType;
        v34 = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it);
        UnitHandle::UnitHandle(&v66, v34->unitId, unitType);
        Player::onDamageEvent(this->m_pPlayer, v66, hpChange);
        if ( __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 1 )
        {
          v35 = StaticObj::GetRunnerId(this->m_pPlayer);
          unitId = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitId;
          v37 = Answer::Singleton<GameService>::instance();
          victm = GameService::getPlayer(v37, unitId, v35, 1);
          if ( victm )
          {
            v38 = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->hpChange;
            launcher.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
            launcher.type = v75.type;
            v75.id = launcher.id;
            Player::onDamagedEvent(victm, v75, v38);
          }
        }
        if ( __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 1
          || __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 4 )
        {
          Player::SetInPvP(this->m_pPlayer);
        }
      }
    }
    if ( pCfgSkill->summon_id > 0 && pCfgSkill->summon_limit > 0 )
    {
      SummonSkill::SummonSkill(&summon);
      summon.nSkillId = nSkillId;
      summon.nStartTick = pCfgSkill->summon_delay + Unit::getTick(this->m_pPlayer);
      summon.targetPos = pos;
      std::list<SummonSkill>::push_back(&this->m_lSummonSkills, &summon);
    }
    v8 = 0;
    goto LABEL_75;
  }
  return 10002;
}


#####################################
void __cdecl CExtCharSkill::AddCharAttr(CExtCharSkill *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<int> it; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+40h] [rbp-20h] BYREF
  const CfgPassiveSkill *pCfgSkill; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( it._M_node = std::list<int>::begin(&this->m_lPassiveSkills)._M_node; ; std::_List_iterator<int>::operator++(&it) )
    {
      __x._M_node = std::list<int>::end(&this->m_lPassiveSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
        break;
      v1 = *std::_List_iterator<int>::operator*(&it);
      v2 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v2);
      pCfgSkill = CfgSkillTable::GetPassiveSkill(SkillTable, v1);
      if ( pCfgSkill )
      {
        for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgSkill->vAttrs)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&pCfgSkill->vAttrs)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
            break;
          addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
          v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::SendTalentInfo(CExtCharSkill *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int16_t v3; // ax
  std::pair<const int,SkillLevelInfo> *v4; // rax
  std::pair<const int,SkillLevelInfo> *v5; // rax
  std::pair<const int,SkillLevelInfo> *v6; // rax
  int32_t Record; // eax
  int32_t v8; // eax
  int32_t v9; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x276Au);
    if ( packet )
    {
      v3 = std::map<int,SkillLevelInfo>::size(&this->m_SkillLevelMap);
      Answer::NetPacket::writeInt16(packet, v3);
      for ( iter._M_node = std::map<int,SkillLevelInfo>::begin(&this->m_SkillLevelMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,SkillLevelInfo>::end(&this->m_SkillLevelMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&iter, &__x) )
          break;
        v4 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v4->first);
        v5 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v5->second.Level);
        v6 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v6->second.Point);
      }
      Record = Player::getRecord(this->m_pPlayer, 1927);
      Answer::NetPacket::writeInt32(packet, Record);
      v8 = Player::getRecord(this->m_pPlayer, 1928);
      Answer::NetPacket::writeInt32(packet, v8);
      v9 = Player::getRecord(this->m_pPlayer, 1929);
      Answer::NetPacket::writeInt32(packet, v9);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v13, v12, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharSkill::SendTalentAddon(CExtCharSkill *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int16_t v3; // ax
  MemTalent *v4; // rax
  MemTalent *v5; // rax
  MemTalent *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_iterator<MemTalent> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<MemTalent> __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  uint32_t nOldOffset; // [rsp+30h] [rbp-20h]
  int8_t nCount; // [rsp+37h] [rbp-19h]
  uint32_t nNewOffset; // [rsp+38h] [rbp-18h]
  int8_t i; // [rsp+3Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x276Bu);
    if ( packet )
    {
      v3 = std::list<MemTalent>::size(&this->m_lActiveTalent);
      Answer::NetPacket::writeInt16(packet, v3);
      for ( iter._M_node = std::list<MemTalent>::begin(&this->m_lActiveTalent)._M_node;
            ;
            std::_List_iterator<MemTalent>::operator++(&iter) )
      {
        __x._M_node = std::list<MemTalent>::end(&this->m_lActiveTalent)._M_node;
        if ( !std::_List_iterator<MemTalent>::operator!=(&iter, &__x) )
          break;
        v4 = std::_List_iterator<MemTalent>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v4->nId);
        nOldOffset = Answer::NetPacket::getWOffset(packet);
        nCount = 0;
        Answer::NetPacket::writeInt8(packet, 0);
        for ( i = 0; i <= 8; ++i )
        {
          v5 = std::_List_iterator<MemTalent>::operator->(&iter);
          if ( v5->vAddon[i] )
          {
            Answer::NetPacket::writeInt8(packet, i);
            v6 = std::_List_iterator<MemTalent>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v6->vAddon[i]);
            ++nCount;
          }
        }
        nNewOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, nOldOffset);
        Answer::NetPacket::writeInt8(packet, nCount);
        Answer::NetPacket::setWOffset(packet, nNewOffset);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharSkill::checkSkillTrigBuff(
        CExtCharSkill *const this,
        const CfgActiveSkill *pCfgSkill,
        const SkillResultVector *const results)
{
  int32_t RunnerId; // r13d
  int32_t unitType; // r12d
  EntityId_t unitId; // rbx
  GameService *v6; // rax
  __gnu_cxx::__normal_iterator<const SkillResult*,std::vector<SkillResult> > iter; // [rsp+20h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+30h] [rbp-30h] BYREF
  Unit *pTarget; // [rsp+38h] [rbp-28h]

  if ( this->m_pPlayer && pCfgSkill )
  {
    for ( iter._M_current = std::vector<SkillResult>::begin(results)._M_current;
          ;
          __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<SkillResult>::end(results)._M_current;
      if ( !__gnu_cxx::operator!=<SkillResult const*,std::vector<SkillResult>>(&iter, &__rhs) )
        break;
      if ( (__gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&iter)->attackState & 2) == 0 )
      {
        RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
        unitType = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&iter)->unitType;
        unitId = __gnu_cxx::__normal_iterator<SkillResult const*,std::vector<SkillResult>>::operator->(&iter)->unitId;
        v6 = Answer::Singleton<GameService>::instance();
        pTarget = GameService::getUnit(v6, unitId, unitType, RunnerId);
        if ( pTarget )
        {
          CExtCharSkill::CheckSkillTrigBuff(this, pCfgSkill->groupid, pTarget, 1);
          if ( !Unit::isAlive(pTarget) )
            CExtCharSkill::CheckSkillTrigBuff(this, pCfgSkill->groupid, pTarget, 7);
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::CheckSkillTrigBuff(
        CExtCharSkill *const this,
        int32_t nSkillGroup,
        Unit *const target,
        int8_t nTrigType)
{
  int32_t v4; // ebx
  CfgData *v5; // rax
  const CfgSkillTable *SkillTable; // rax
  __int64 *v7; // rax
  Answer::Random *v8; // rax
  int32_t v9; // edx
  int32_t v10; // edx
  __int64 *v11; // rax
  int32_t nGroupId; // [rsp+3Ch] [rbp-74h] BYREF
  std::_List_iterator<int> iter; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<int> __x; // [rsp+50h] [rbp-60h] BYREF
  UnitHandle handler; // [rsp+60h] [rbp-50h] BYREF
  UnitHandle v18; // [rsp+70h] [rbp-40h] BYREF
  int64_t nCurTick; // [rsp+88h] [rbp-28h]
  const CfgTrigSkill *pCfgSkill; // [rsp+90h] [rbp-20h]
  int32_t nRand; // [rsp+9Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nCurTick = Unit::getTick(this->m_pPlayer);
    for ( iter._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node; ; std::_List_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
        break;
      v4 = *std::_List_iterator<int>::operator*(&iter);
      v5 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v5);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, v4);
      if ( pCfgSkill )
      {
        if ( pCfgSkill->trigType == nTrigType )
        {
          nGroupId = pCfgSkill->groupid;
          v7 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
          if ( nCurTick - *v7 >= pCfgSkill->cdTime && CfgTrigSkill::isRespond(pCfgSkill, nSkillGroup) )
          {
            v8 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v8, 1, 1000);
            if ( pCfgSkill->trigRate >= nRand
              && (pCfgSkill->IsPvp <= 0 || Entity::getType(target) == EntityType::ET_PLAYER) )
            {
              if ( pCfgSkill->targetType == 1 )
              {
                handler.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
                handler.type = v9;
                CExtCharSkill::activeSkill(this, pCfgSkill->id, &handler);
              }
              else
              {
                v18.id = (*((__int64 (__fastcall **)(Unit *const))target->_vptr_Entity + 12))(target);
                v18.type = v10;
                CExtCharSkill::activeSkill(this, pCfgSkill->id, &v18);
              }
              v11 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
              *v11 = nCurTick;
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::CheckHPPecentTrigBuff(CExtCharSkill *const this, int32_t nLastPecent, int32_t nNowPecent)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgSkillTable *SkillTable; // rax
  __int64 *v6; // rax
  const char *v7; // rax
  Answer::Random *v8; // rax
  int32_t v9; // edx
  __int64 *v10; // rax
  int32_t nGroupId; // [rsp+2Ch] [rbp-64h] BYREF
  std::_List_iterator<int> iter; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-50h] BYREF
  UnitHandle handler; // [rsp+50h] [rbp-40h] BYREF
  int64_t nCurTick; // [rsp+68h] [rbp-28h]
  const CfgTrigSkill *pCfgSkill; // [rsp+70h] [rbp-20h]
  int32_t trigLine; // [rsp+78h] [rbp-18h]
  int32_t nRand; // [rsp+7Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nCurTick = Unit::getTick(this->m_pPlayer);
    for ( iter._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node; ; std::_List_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
        break;
      v3 = *std::_List_iterator<int>::operator*(&iter);
      v4 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v4);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, v3);
      if ( pCfgSkill )
      {
        if ( pCfgSkill->trigType == 4 )
        {
          nGroupId = pCfgSkill->groupid;
          v6 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
          if ( nCurTick - *v6 >= pCfgSkill->cdTime )
          {
            v7 = (const char *)std::string::c_str(&pCfgSkill->trigParam);
            trigLine = atoi(v7);
            if ( nLastPecent > trigLine && nNowPecent <= trigLine )
            {
              v8 = Answer::Singleton<Answer::Random>::instance();
              nRand = Answer::Random::generate(v8, 1, 100);
              if ( pCfgSkill->trigRate >= nRand )
              {
                handler.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
                handler.type = v9;
                CExtCharSkill::activeSkill(this, pCfgSkill->id, &handler);
                v10 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
                *v10 = nCurTick;
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::CheckPhaseDamageTrigBuff(CExtCharSkill *const this, int8_t nPhase)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  __int64 *v5; // rax
  const char *v6; // rax
  Answer::Random *v7; // rax
  int32_t v8; // edx
  __int64 *v9; // rax
  int32_t nGroupId; // [rsp+2Ch] [rbp-64h] BYREF
  std::_List_iterator<int> iter; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-50h] BYREF
  UnitHandle handler; // [rsp+50h] [rbp-40h] BYREF
  int64_t nCurTick; // [rsp+68h] [rbp-28h]
  const CfgTrigSkill *pCfgSkill; // [rsp+70h] [rbp-20h]
  int32_t phase; // [rsp+78h] [rbp-18h]
  int32_t nRand; // [rsp+7Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nCurTick = Unit::getTick(this->m_pPlayer);
    for ( iter._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node; ; std::_List_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
        break;
      v2 = *std::_List_iterator<int>::operator*(&iter);
      v3 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v3);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, v2);
      if ( pCfgSkill )
      {
        if ( pCfgSkill->trigType == 5 )
        {
          nGroupId = pCfgSkill->groupid;
          v5 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
          if ( nCurTick - *v5 >= pCfgSkill->cdTime )
          {
            v6 = (const char *)std::string::c_str(&pCfgSkill->trigParam);
            phase = atoi(v6);
            if ( !phase || nPhase == phase )
            {
              v7 = Answer::Singleton<Answer::Random>::instance();
              nRand = Answer::Random::generate(v7, 1, 100);
              if ( pCfgSkill->trigRate >= nRand )
              {
                handler.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
                handler.type = v8;
                CExtCharSkill::activeSkill(this, pCfgSkill->id, &handler);
                v9 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
                *v9 = nCurTick;
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::CheckSelfTrigBuff(CExtCharSkill *const this, int8_t nTrigType)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  __int64 *v5; // rax
  Answer::Random *v6; // rax
  int32_t v7; // edx
  __int64 *v8; // rax
  int32_t nGroupId; // [rsp+2Ch] [rbp-64h] BYREF
  std::_List_iterator<int> iter; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-50h] BYREF
  UnitHandle handler; // [rsp+50h] [rbp-40h] BYREF
  int64_t nCurTick; // [rsp+68h] [rbp-28h]
  const CfgTrigSkill *pCfgSkill; // [rsp+70h] [rbp-20h]
  int32_t nRand; // [rsp+7Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nCurTick = Unit::getTick(this->m_pPlayer);
    for ( iter._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node; ; std::_List_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
        break;
      v2 = *std::_List_iterator<int>::operator*(&iter);
      v3 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v3);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, v2);
      if ( pCfgSkill )
      {
        if ( pCfgSkill->trigType == nTrigType )
        {
          nGroupId = pCfgSkill->groupid;
          v5 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
          if ( nCurTick - *v5 >= pCfgSkill->cdTime )
          {
            v6 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v6, 1, 100);
            if ( pCfgSkill->trigRate >= nRand )
            {
              handler.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
              handler.type = v7;
              CExtCharSkill::activeSkill(this, pCfgSkill->id, &handler);
              v8 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
              *v8 = nCurTick;
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::CheckSummonBuff(CExtCharSkill *const this)
{
  CExtCharPet *CharPet; // rax
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  __int64 *v5; // rax
  Answer::Random *v6; // rax
  Player *m_pPlayer; // r13
  int32_t groupid; // r12d
  int32_t v9; // edx
  __int64 *v10; // rax
  int32_t nGroupId; // [rsp+1Ch] [rbp-64h] BYREF
  std::_List_iterator<int> iter; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-50h] BYREF
  bool bAdd; // [rsp+47h] [rbp-39h]
  int64_t nCurTick; // [rsp+48h] [rbp-38h]
  const CfgTrigSkill *pCfgSkill; // [rsp+50h] [rbp-30h]
  int32_t nRand; // [rsp+5Ch] [rbp-24h]

  if ( this->m_pPlayer )
  {
    CharPet = Player::GetCharPet(this->m_pPlayer);
    bAdd = CExtCharPet::HaveSummonAlive(CharPet);
    nCurTick = Unit::getTick(this->m_pPlayer);
    for ( iter._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node; ; std::_List_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
        break;
      v2 = *std::_List_iterator<int>::operator*(&iter);
      v3 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v3);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, v2);
      if ( pCfgSkill && pCfgSkill->trigType == 6 )
      {
        if ( bAdd )
        {
          nGroupId = pCfgSkill->groupid;
          v5 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
          if ( nCurTick - *v5 >= pCfgSkill->cdTime )
          {
            v6 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v6, 1, 100);
            if ( pCfgSkill->trigRate >= nRand )
            {
              m_pPlayer = this->m_pPlayer;
              groupid = pCfgSkill->groupid;
              v9 = *std::_List_iterator<int>::operator*(&iter);
              CExtCharSkill::addSkillBuffTo(this, pCfgSkill->trigBuff, v9, groupid, m_pPlayer);
              v10 = std::map<int,long>::operator[](&this->m_mSkillCD, &nGroupId);
              *v10 = nCurTick;
            }
          }
        }
        else
        {
          Unit::removeBuff(this->m_pPlayer, pCfgSkill->trigBuff);
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::initSkills(CExtCharSkill *const this, int32_t TalentId, int32_t TalentLevel)
{
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v6; // rax
  const CfgSkillTable *SkillTable; // rax
  int SkillType; // eax
  const CfgTalent *pCfg; // [rsp+10h] [rbp-20h]

  v3 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v3);
  pCfg = CfgTalentTable::GetTalent(TalentTable, TalentId, TalentLevel);
  if ( pCfg )
  {
    skillid = pCfg->skillid;
    v6 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v6);
    SkillType = CfgSkillTable::GetSkillType(SkillTable, skillid);
    if ( (char)SkillType == 2 )
    {
      std::list<int>::push_back(&this->m_lPassiveSkills, &pCfg->skillid);
    }
    else if ( SkillType == 3 )
    {
      std::list<int>::push_back(&this->m_lTrigSkills, &pCfg->skillid);
    }
    else if ( SkillType == 1 )
    {
      std::list<int>::push_back(&this->m_lActiveSkills, &pCfg->skillid);
    }
  }
}


#####################################
void __cdecl CExtCharSkill::removeSkillByTalent(CExtCharSkill *const this, int32_t TalentId, int32_t TalentLevel)
{
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v6; // rax
  const CfgSkillTable *SkillTable; // rax
  int *v8; // rax
  int *v9; // rax
  int *v10; // rax
  std::_List_iterator<int> it_1; // [rsp+10h] [rbp-80h] BYREF
  std::_List_iterator<int> it_0; // [rsp+20h] [rbp-70h] BYREF
  std::_List_iterator<int> it; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-50h] BYREF
  std::_List_iterator<int> v16; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<int> v17; // [rsp+60h] [rbp-30h] BYREF
  const CfgTalent *pCfg; // [rsp+70h] [rbp-20h]
  int8_t nSkillType; // [rsp+7Fh] [rbp-11h]

  v3 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v3);
  pCfg = CfgTalentTable::GetTalent(TalentTable, TalentId, TalentLevel);
  if ( pCfg )
  {
    skillid = pCfg->skillid;
    v6 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v6);
    nSkillType = CfgSkillTable::GetSkillType(SkillTable, skillid);
    switch ( nSkillType )
    {
      case 2:
        for ( it_0._M_node = std::list<int>::begin(&this->m_lPassiveSkills)._M_node;
              ;
              std::_List_iterator<int>::operator++(&it_0, 0) )
        {
          v16._M_node = std::list<int>::end(&this->m_lPassiveSkills)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it_0, &v16) )
            break;
          v9 = std::_List_iterator<int>::operator*(&it_0);
          if ( *v9 == pCfg->skillid )
          {
            std::list<int>::erase(&this->m_lPassiveSkills, it_0);
            return;
          }
        }
        break;
      case 3:
        for ( it_1._M_node = std::list<int>::begin(&this->m_lTrigSkills)._M_node;
              ;
              std::_List_iterator<int>::operator++(&it_1, 0) )
        {
          v17._M_node = std::list<int>::end(&this->m_lTrigSkills)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it_1, &v17) )
            break;
          v10 = std::_List_iterator<int>::operator*(&it_1);
          if ( *v10 == pCfg->skillid )
          {
            std::list<int>::erase(&this->m_lTrigSkills, it_1);
            return;
          }
        }
        break;
      case 1:
        for ( it._M_node = std::list<int>::begin(&this->m_lActiveSkills)._M_node;
              ;
              std::_List_iterator<int>::operator++(&it, 0) )
        {
          __x._M_node = std::list<int>::end(&this->m_lActiveSkills)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
            break;
          v8 = std::_List_iterator<int>::operator*(&it);
          if ( *v8 == pCfg->skillid )
          {
            std::list<int>::erase(&this->m_lActiveSkills, it);
            return;
          }
        }
        break;
    }
  }
}


#####################################
void __cdecl CExtCharSkill::checkActiveList(CExtCharSkill *const this)
{
  int32_t nSkillId; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t RunnerId; // r13d
  int32_t nType; // r12d
  EntityId_t nEntityId; // rbx
  GameService *v8; // rax
  std::_List_iterator<ActiveSkill> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<ActiveSkill> __x; // [rsp+20h] [rbp-40h] BYREF
  const CfgTrigSkill *pCfgSkill; // [rsp+30h] [rbp-30h]
  Unit *pTarget; // [rsp+38h] [rbp-28h]

  if ( this->m_pPlayer && !std::list<ActiveSkill>::empty(&this->m_lActive) )
  {
    for ( iter._M_node = std::list<ActiveSkill>::begin(&this->m_lActive)._M_node;
          ;
          std::_List_iterator<ActiveSkill>::operator++(&iter) )
    {
      __x._M_node = std::list<ActiveSkill>::end(&this->m_lActive)._M_node;
      if ( !std::_List_iterator<ActiveSkill>::operator!=(&iter, &__x) )
        break;
      nSkillId = std::_List_iterator<ActiveSkill>::operator->(&iter)->nSkillId;
      v3 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v3);
      pCfgSkill = CfgSkillTable::GetTrigSkill(SkillTable, nSkillId);
      if ( pCfgSkill )
      {
        RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
        nType = std::_List_iterator<ActiveSkill>::operator->(&iter)->nType;
        nEntityId = std::_List_iterator<ActiveSkill>::operator->(&iter)->nEntityId;
        v8 = Answer::Singleton<GameService>::instance();
        pTarget = GameService::getUnit(v8, nEntityId, nType, RunnerId);
        if ( pTarget )
          CExtCharSkill::doSkillActive(this, pCfgSkill, pTarget);
      }
    }
    std::list<ActiveSkill>::clear(&this->m_lActive);
  }
}


#####################################
void __cdecl CExtCharSkill::activeSkill(CExtCharSkill *const this, int32_t nId, const UnitHandle *const handler)
{
  ActiveSkill __x; // [rsp+20h] [rbp-30h] BYREF

  ActiveSkill::ActiveSkill(&__x, nId, handler->id, handler->type);
  std::list<ActiveSkill>::push_back(&this->m_lActive, &__x);
}


#####################################
void __cdecl CExtCharSkill::doSkillActive(CExtCharSkill *const this, const CfgTrigSkill *pCfgSkill, Unit *pTarget)
{
  CExtCharCarrier *CharCarrier; // rax
  CExtCharCarrier *v5; // rax
  int32_t v6; // edx
  CObjCarrier *pTargeta; // [rsp+28h] [rbp-68h]
  int32_t attackState; // [rsp+4Ch] [rbp-44h] BYREF
  UnitHandle launcher; // [rsp+50h] [rbp-40h]
  Player *pPlayer; // [rsp+68h] [rbp-28h]
  int64_t CurHp; // [rsp+70h] [rbp-20h]
  int32_t SubHp; // [rsp+78h] [rbp-18h]
  int32_t ChangeHp; // [rsp+7Ch] [rbp-14h]
  UnitHandle v14; // 0:r8.12

  pTargeta = (CObjCarrier *)pTarget;
  if ( pCfgSkill && pTarget )
  {
    if ( Entity::getType(pTarget) == EntityType::ET_PLAYER )
    {
      pPlayer = (Player *)__dynamic_cast(
                            pTargeta,
                            (const struct __class_type_info *)&`typeinfo for'Unit,
                            (const struct __class_type_info *)&`typeinfo for'Player,
                            0);
      if ( pPlayer )
      {
        CharCarrier = Player::GetCharCarrier(pPlayer);
        if ( CExtCharCarrier::IsInCarrier(CharCarrier) )
        {
          v5 = Player::GetCharCarrier(pPlayer);
          pTargeta = CExtCharCarrier::GetCarrier(v5);
        }
      }
    }
    if ( pCfgSkill->trigBuff > 0 )
      CExtCharSkill::addSkillBuffTo(this, pCfgSkill->trigBuff, pCfgSkill->id, pCfgSkill->groupid, pTargeta);
    if ( pCfgSkill->special == 5 )
    {
      CurHp = (*((__int64 (__fastcall **)(CObjCarrier *))pTargeta->_vptr_Entity + 19))(pTargeta);
      SubHp = CurHp * pCfgSkill->specialParam / 100;
      attackState = 512;
      launcher.id = (*((__int64 (__fastcall **)(CObjCarrier *))pTargeta->_vptr_Entity + 12))(pTargeta);
      launcher.type = v6;
      v14.id = launcher.id;
      v14.type = v6;
      ChangeHp = Unit::struckDamage(pTargeta, SubHp, &attackState, 0, v14, 0);
      if ( ChangeHp )
        CExtCharSkill::broadcastIntervalEffect(this, pTargeta, pCfgSkill->id, -ChangeHp, attackState);
    }
  }
}


#####################################
void __cdecl CExtCharSkill::addSkillBuffTo(
        CExtCharSkill *const this,
        int32_t nBuffId,
        int32_t nSkillId,
        int32_t nGroupId,
        Unit *pTarget)
{
  CfgData *v5; // rax
  int32_t v8; // edx
  SkillBuff *v9; // rbx
  UnitHandle launcher; // [rsp+40h] [rbp-60h] BYREF
  CfgBuff *pCfgBuff; // [rsp+58h] [rbp-48h]
  int32_t atkMin; // [rsp+60h] [rbp-40h]
  int32_t atkMax; // [rsp+64h] [rbp-3Ch]
  int32_t dmgAdd; // [rsp+68h] [rbp-38h]
  int32_t skillModify; // [rsp+6Ch] [rbp-34h]
  SkillBuff *buff; // [rsp+70h] [rbp-30h]
  int32_t attackState; // [rsp+7Ch] [rbp-24h]

  if ( this->m_pPlayer )
  {
    if ( pTarget )
    {
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgBuff = CfgData::getBuff(v5, nBuffId);
      if ( pCfgBuff )
      {
        if ( (pCfgBuff->beneficial || !Unit::HasBuffState(pTarget, CObjState::Index_T::OBS_WUDI))
          && (!pCfgBuff->control || !Unit::HasBuffState(pTarget, CObjState::Index_T::OBS_FREEDOM)) )
        {
          atkMin = Unit::GetAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_ATK_MIN);
          atkMax = Unit::GetAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_ATK_MAX);
          dmgAdd = Unit::GetAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_DMG_ADD_PEC);
          skillModify = pCfgBuff->modify;
          launcher.id = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
          launcher.type = v8;
          v9 = (SkillBuff *)operator new(0x80u);
          SkillBuff::SkillBuff(v9, pTarget, pCfgBuff, &launcher);
          buff = v9;
          if ( v9 )
          {
            SkillBuff::init(buff, nSkillId, atkMin, atkMax, 0, dmgAdd, skillModify, 0);
            Unit::addBuff(pTarget, buff);
            if ( Buff::getSpecial(buff) == 9 )
            {
              attackState = 1024;
              CExtCharSkill::broadcastIntervalEffect(this, pTarget, nSkillId, 0, 1024);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::AddPower(CExtCharSkill *const this, int32_t nValue)
{
  int32_t m_nPower; // edx
  int32_t v3; // edx

  this->m_nPower += nValue;
  m_nPower = 0;
  if ( this->m_nPower >= 0 )
    m_nPower = this->m_nPower;
  this->m_nPower = m_nPower;
  v3 = 3000;
  if ( this->m_nPower <= 3000 )
    v3 = this->m_nPower;
  this->m_nPower = v3;
  if ( this->m_pPlayer )
    Unit::setNeedSyncSelf(this->m_pPlayer);
}


#####################################
bool __cdecl CExtCharSkill::addAddonSkill(CExtCharSkill *const this, const AddonSkill *const addonSkill)
{
  std::_List_iterator<AddonSkill> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<AddonSkill> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<AddonSkill>::begin(&this->m_lAddonSkills)._M_node;
        ;
        std::_List_iterator<AddonSkill>::operator++(&iter) )
  {
    __x._M_node = std::list<AddonSkill>::end(&this->m_lAddonSkills)._M_node;
    if ( !std::_List_iterator<AddonSkill>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<AddonSkill>::operator->(&iter)->nSkillFlag == addonSkill->nSkillFlag )
      return 0;
  }
  std::list<AddonSkill>::push_back(&this->m_lAddonSkills, addonSkill);
  return 1;
}


#####################################
bool __cdecl CExtCharSkill::removeAddonSkill(CExtCharSkill *const this, int32_t nSkillFlag)
{
  std::_List_iterator<AddonSkill> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<AddonSkill> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<AddonSkill>::begin(&this->m_lAddonSkills)._M_node;
        ;
        std::_List_iterator<AddonSkill>::operator++(&iter) )
  {
    __x._M_node = std::list<AddonSkill>::end(&this->m_lAddonSkills)._M_node;
    if ( !std::_List_iterator<AddonSkill>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<AddonSkill>::operator->(&iter)->nSkillFlag == nSkillFlag )
    {
      std::list<AddonSkill>::erase(&this->m_lAddonSkills, iter);
      return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CExtCharSkill::checkAddonSkills(CExtCharSkill *const this, int64_t nCurTick)
{
  std::_List_iterator<AddonSkill> v2; // rax
  std::_List_iterator<AddonSkill> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<AddonSkill> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( nCurTick - this->m_nLastAddonTick > 999 )
  {
    this->m_nLastAddonTick = nCurTick;
    iter._M_node = std::list<AddonSkill>::begin(&this->m_lAddonSkills)._M_node;
    while ( 1 )
    {
      __x._M_node = std::list<AddonSkill>::end(&this->m_lAddonSkills)._M_node;
      if ( !std::_List_iterator<AddonSkill>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<AddonSkill>::operator->(&iter)->nEndTick >= nCurTick )
      {
        std::_List_iterator<AddonSkill>::operator++(&iter);
      }
      else
      {
        v2._M_node = std::_List_iterator<AddonSkill>::operator++(&iter, 0)._M_node;
        std::list<AddonSkill>::erase(&this->m_lAddonSkills, v2);
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::checkSummonSkills(CExtCharSkill *const this, int64_t nCurTick)
{
  Position *p_targetPos; // r12
  int32_t nSkillId; // ebx
  CExtCharPet *CharPet; // rax
  std::_List_iterator<SummonSkill> v5; // rax
  std::_List_iterator<SummonSkill> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<SummonSkill> __x; // [rsp+20h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    iter._M_node = std::list<SummonSkill>::begin(&this->m_lSummonSkills)._M_node;
    while ( 1 )
    {
      __x._M_node = std::list<SummonSkill>::end(&this->m_lSummonSkills)._M_node;
      if ( !std::_List_iterator<SummonSkill>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<SummonSkill>::operator->(&iter)->nStartTick > nCurTick )
      {
        std::_List_iterator<SummonSkill>::operator++(&iter);
      }
      else
      {
        p_targetPos = &std::_List_iterator<SummonSkill>::operator->(&iter)->targetPos;
        nSkillId = std::_List_iterator<SummonSkill>::operator->(&iter)->nSkillId;
        CharPet = Player::GetCharPet(this->m_pPlayer);
        CExtCharPet::OnSummon(CharPet, nSkillId, p_targetPos);
        v5._M_node = std::_List_iterator<SummonSkill>::operator++(&iter, 0)._M_node;
        std::list<SummonSkill>::erase(&this->m_lSummonSkills, v5);
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::checkSuitSkillEnergy(CExtCharSkill *const this, int64_t nCurTick)
{
  if ( nCurTick - this->m_nLastEnergyTick > 999 )
  {
    this->m_nLastEnergyTick = nCurTick;
    CExtCharSkill::AddSuitSkillEnergy(this);
  }
}


#####################################
int32_t __cdecl CExtCharSkill::calActiveSkillCD(CExtCharSkill *const this, int32_t nSkillId)
{
  int32_t nCDTime; // [rsp+1Ch] [rbp-14h]
  int32_t adjust; // [rsp+20h] [rbp-10h]
  int32_t nAtkSpd; // [rsp+24h] [rbp-Ch]
  const CfgActiveSkill *pCfgSkill; // [rsp+28h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 0;
  nCDTime = 800;
  adjust = 400;
  if ( nSkillId > 0 )
  {
    pCfgSkill = CExtCharSkill::getActiveSkill(this, nSkillId);
    if ( !pCfgSkill )
      return 0;
    nCDTime = pCfgSkill->cd;
    adjust = pCfgSkill->cd_adjust;
  }
  nAtkSpd = Unit::GetAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_ATK_SPD) / 10;
  if ( nAtkSpd > 0 )
  {
    if ( nAtkSpd > 99 )
      nCDTime -= adjust;
    else
      nCDTime -= nAtkSpd * adjust / 100;
  }
  return 9 * nCDTime / 10;
}


#####################################
void __cdecl CExtCharSkill::recalTalentAddon(CExtCharSkill *const this)
{
  const TalentAddon *v1; // rdx
  std::_List_const_iterator<TalentAddon> iter; // [rsp+10h] [rbp-60h] BYREF
  TalentAddonList addonList; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<TalentAddon> __x; // [rsp+30h] [rbp-40h] BYREF
  std::_List_const_iterator<TalentAddon> v5; // [rsp+40h] [rbp-30h] BYREF
  std::_List_iterator<TalentAddon> v6; // [rsp+50h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    std::list<MemTalent>::clear(&this->m_lActiveTalent);
    std::list<TalentAddon>::list(&addonList);
    CExtCharSkill::getTalentAddon(this, &addonList);
    if ( !std::list<TalentAddon>::empty(&addonList) )
    {
      __x._M_node = std::list<TalentAddon>::begin(&addonList)._M_node;
      std::_List_const_iterator<TalentAddon>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v6._M_node = std::list<TalentAddon>::end(&addonList)._M_node;
        std::_List_const_iterator<TalentAddon>::_List_const_iterator(&v5, &v6);
        if ( !std::_List_const_iterator<TalentAddon>::operator!=(&iter, &v5) )
          break;
        v1 = std::_List_const_iterator<TalentAddon>::operator*(&iter);
        CExtCharSkill::addTalentAddon(this, v1);
        std::_List_const_iterator<TalentAddon>::operator++(&iter);
      }
    }
    std::list<TalentAddon>::~list(&addonList);
  }
}


#####################################
void __cdecl CExtCharSkill::getTalentAddon(CExtCharSkill *const this, TalentAddonList *const addonList)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  const TalentAddon *v5; // rdx
  std::_List_const_iterator<TalentAddon> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<int> it; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<int> v8; // [rsp+30h] [rbp-30h] BYREF
  std::_List_const_iterator<TalentAddon> __x; // [rsp+40h] [rbp-20h] BYREF
  const CfgPassiveSkill *pCfgSkill; // [rsp+48h] [rbp-18h]

  for ( it._M_node = std::list<int>::begin(&this->m_lPassiveSkills)._M_node; ; std::_List_iterator<int>::operator++(&it) )
  {
    v8._M_node = std::list<int>::end(&this->m_lPassiveSkills)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &v8) )
      break;
    v2 = *std::_List_iterator<int>::operator*(&it);
    v3 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v3);
    pCfgSkill = CfgSkillTable::GetPassiveSkill(SkillTable, v2);
    if ( pCfgSkill )
    {
      for ( iter._M_node = std::list<TalentAddon>::begin(&pCfgSkill->lTalentAddon)._M_node;
            ;
            std::_List_const_iterator<TalentAddon>::operator++(&iter) )
      {
        __x._M_node = std::list<TalentAddon>::end(&pCfgSkill->lTalentAddon)._M_node;
        if ( !std::_List_const_iterator<TalentAddon>::operator!=(&iter, &__x) )
          break;
        v5 = std::_List_const_iterator<TalentAddon>::operator*(&iter);
        std::list<TalentAddon>::push_back(addonList, v5);
      }
    }
  }
}


#####################################
void __cdecl CExtCharSkill::addTalentAddon(CExtCharSkill *const this, const TalentAddon *const stu)
{
  MemTalent *v2; // rax
  MemTalent talent; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<MemTalent> iter; // [rsp+40h] [rbp-30h] BYREF
  std::_List_iterator<MemTalent> __x; // [rsp+50h] [rbp-20h] BYREF

  if ( stu->type <= 8u )
  {
    for ( iter._M_node = std::list<MemTalent>::begin(&this->m_lActiveTalent)._M_node;
          ;
          std::_List_iterator<MemTalent>::operator++(&iter) )
    {
      __x._M_node = std::list<MemTalent>::end(&this->m_lActiveTalent)._M_node;
      if ( !std::_List_iterator<MemTalent>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<MemTalent>::operator->(&iter)->nId == stu->id )
      {
        v2 = std::_List_iterator<MemTalent>::operator->(&iter);
        v2->vAddon[stu->type] += stu->addon;
        return;
      }
    }
    memset(&talent, 0, sizeof(talent));
    talent.nId = stu->id;
    talent.vAddon[stu->type] = stu->addon;
    std::list<MemTalent>::push_back(&this->m_lActiveTalent, &talent);
  }
}


#####################################
void __cdecl CExtCharSkill::recalAcviveSkill(CExtCharSkill *const this)
{
  int v1; // ebx
  CfgData *v2; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t addon_skill; // ebx
  CfgData *v5; // rax
  const CfgSkillTable *v6; // rax
  std::_List_const_iterator<int> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<int> v9; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<int> v10; // [rsp+40h] [rbp-30h] BYREF
  const CfgActiveSkill *pCfgSkill; // [rsp+50h] [rbp-20h]
  const CfgActiveSkill *pCfgAddonSkill; // [rsp+58h] [rbp-18h]

  std::map<int,CfgActiveSkill>::clear(&this->m_mActiveSkills);
  __x._M_node = std::list<int>::begin(&this->m_lActiveSkills)._M_node;
  std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v10._M_node = std::list<int>::end(&this->m_lActiveSkills)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&v9, &v10);
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &v9) )
      break;
    v1 = *std::_List_const_iterator<int>::operator*(&iter);
    v2 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v2);
    pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, v1);
    if ( pCfgSkill )
    {
      CExtCharSkill::addActiveSkill(this, pCfgSkill);
      if ( pCfgSkill->addon_skill > 0 )
      {
        addon_skill = pCfgSkill->addon_skill;
        v5 = Answer::Singleton<CfgData>::instance();
        v6 = CfgData::GetSkillTable(v5);
        pCfgAddonSkill = CfgSkillTable::GetActiveSkill(v6, addon_skill);
        if ( pCfgAddonSkill )
          CExtCharSkill::addActiveSkill(this, pCfgAddonSkill);
      }
    }
    std::_List_const_iterator<int>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtCharSkill::addActiveSkill(CExtCharSkill *const this, const CfgActiveSkill *pCfgSkill)
{
  CfgActiveSkill *v2; // rax
  CfgActiveSkill cfgSkill; // [rsp+10h] [rbp-C0h] BYREF
  const MemTalent *pMemTalent; // [rsp+B8h] [rbp-18h]

  if ( pCfgSkill )
  {
    pMemTalent = CExtCharSkill::getTalentAddon(this, pCfgSkill->talent);
    if ( pMemTalent )
    {
      CfgActiveSkill::CfgActiveSkill(&cfgSkill, pCfgSkill);
      cfgSkill.attack_modify += pMemTalent->vAddon[1];
      cfgSkill.target_num += pMemTalent->vAddon[2];
      cfgSkill.distance += pMemTalent->vAddon[3];
      cfgSkill.area += pMemTalent->vAddon[4];
      cfgSkill.mp += pMemTalent->vAddon[5];
      cfgSkill.buff_rate += pMemTalent->vAddon[6];
      cfgSkill.buff_time += pMemTalent->vAddon[7];
      cfgSkill.cd += pMemTalent->vAddon[8];
      v2 = std::map<int,CfgActiveSkill>::operator[](&this->m_mActiveSkills, &cfgSkill.id);
      CfgActiveSkill::operator=(v2, &cfgSkill);
      CfgActiveSkill::~CfgActiveSkill(&cfgSkill);
    }
  }
}


#####################################
void __cdecl CExtCharSkill::recalDropMoneyRate(CExtCharSkill *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgSkillTable *SkillTable; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-20h] BYREF
  const CfgPassiveSkill *pCfgSkill; // [rsp+28h] [rbp-18h]

  this->m_nDropMoneyRate = 0;
  for ( it._M_node = std::list<int>::begin(&this->m_lPassiveSkills)._M_node; ; std::_List_iterator<int>::operator++(&it) )
  {
    __x._M_node = std::list<int>::end(&this->m_lPassiveSkills)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    v1 = *std::_List_iterator<int>::operator*(&it);
    v2 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v2);
    pCfgSkill = CfgSkillTable::GetPassiveSkill(SkillTable, v1);
    if ( pCfgSkill )
    {
      if ( pCfgSkill->dropMoneyRate > 0 )
        this->m_nDropMoneyRate += pCfgSkill->dropMoneyRate;
    }
  }
}


#####################################
void __cdecl CExtCharSkill::AddSkillPoint(CExtCharSkill *const this, int32_t Id, int32_t Points)
{
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  Job_t Job; // al
  int32_t Level; // r12d
  int32_t v7; // ebx
  CfgData *v8; // rax
  const CfgTalentTable *v9; // rax
  std::pair<const int,SkillLevelInfo> *v10; // rax
  std::pair<const int,SkillLevelInfo> *v11; // rax
  std::pair<const int,SkillLevelInfo> *v12; // rax
  std::pair<const int,SkillLevelInfo> *v13; // rax
  int32_t Ida; // [rsp+4h] [rbp-CCh] BYREF
  CExtCharSkill *thisa; // [rsp+8h] [rbp-C8h]
  CfgTalentTable Cfg; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > it; // [rsp+A0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+B0h] [rbp-20h] BYREF
  const CfgTalent *pCfgTalent; // [rsp+B8h] [rbp-18h]

  thisa = this;
  Ida = Id;
  v3 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v3);
  CfgTalentTable::CfgTalentTable(&Cfg, TalentTable);
  Job = Player::getJob(this->m_pPlayer);
  if ( CfgTalentTable::IsTalentSkill(&Cfg, Job, Id) )
  {
    it._M_node = std::map<int,SkillLevelInfo>::find(&thisa->m_SkillLevelMap, &Ida)._M_node;
    __x._M_node = std::map<int,SkillLevelInfo>::end(&thisa->m_SkillLevelMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&it, &__x) )
    {
      Level = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
      v7 = Ida;
      v8 = Answer::Singleton<CfgData>::instance();
      v9 = CfgData::GetTalentTable(v8);
      pCfgTalent = CfgTalentTable::GetTalent(v9, v7, Level);
      if ( pCfgTalent )
      {
        v10 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
        if ( v10->second.Point < pCfgTalent->Point )
        {
          v11 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
          v11->second.Point += Points;
          v12 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
          if ( v12->second.Point > pCfgTalent->Point )
          {
            v13 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
            v13->second.Point = pCfgTalent->Point;
          }
        }
      }
    }
  }
  CfgTalentTable::~CfgTalentTable(&Cfg);
}


#####################################
bool __cdecl CExtCharSkill::UseSkillBook(CExtCharSkill *const this, int32_t Id)
{
  CfgData *v2; // rax
  const CfgTalentTable *TalentTable; // rax
  Job_t Job; // al
  bool v5; // bl
  SkillLevelInfo *v6; // rax
  int8_t ConnId; // bl
  DBService *v8; // rax
  int32_t Ida; // [rsp+4h] [rbp-13Ch] BYREF
  CExtCharSkill *thisa; // [rsp+8h] [rbp-138h]
  CfgTalentTable Cfg; // [rsp+10h] [rbp-130h] BYREF
  skill_log skill_stu; // [rsp+A0h] [rbp-A0h] BYREF
  SkillLevelInfo stu; // [rsp+E0h] [rbp-60h]
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > it; // [rsp+F0h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+100h] [rbp-40h] BYREF
  _BYTE v17[16]; // [rsp+110h] [rbp-30h] BYREF
  _BYTE v18[32]; // [rsp+120h] [rbp-20h] BYREF

  thisa = this;
  Ida = Id;
  v2 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v2);
  CfgTalentTable::CfgTalentTable(&Cfg, TalentTable);
  Job = Player::getJob(this->m_pPlayer);
  if ( !CfgTalentTable::IsTalentSkill(&Cfg, Job, Id) )
  {
    v5 = 0;
  }
  else
  {
    it._M_node = std::map<int,SkillLevelInfo>::find(&thisa->m_SkillLevelMap, &Ida)._M_node;
    __x._M_node = std::map<int,SkillLevelInfo>::end(&thisa->m_SkillLevelMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator==(&it, &__x) )
    {
      stu = (SkillLevelInfo)0x100000000LL;
      v6 = std::map<int,SkillLevelInfo>::operator[](&thisa->m_SkillLevelMap, &Ida);
      *v6 = stu;
      CExtCharSkill::initSkills(thisa, Ida, 1);
      CExtCharSkill::SendTalentInfo(thisa);
      CExtCharSkill::SendlearedSkill(thisa, Ida);
      CExtCharSkill::CallSkillBattle(thisa);
      skill_log::skill_log(&skill_stu);
      skill_stu.log_Sid = Player::getSid(thisa->m_pPlayer);
      skill_stu.log_time = Unit::getNow(thisa->m_pPlayer);
      Player::GetPassport((Player *const)v17);
      std::string::operator=(&skill_stu.passport, v17);
      std::string::~string(v17);
      skill_stu.cid = Player::getCid(thisa->m_pPlayer);
      Player::getName((const Player *const)v18);
      std::string::operator=(&skill_stu.name, v18);
      std::string::~string(v18);
      skill_stu.op_time = Unit::getNow(thisa->m_pPlayer);
      skill_stu.skill_id = Ida;
      skill_stu.oper_id = 1;
      skill_stu.level = 1;
      ConnId = Player::getConnId(thisa->m_pPlayer);
      v8 = Answer::Singleton<DBService>::instance();
      DBService::AddPlatformLog(v8, ConnId, PLATFORM_LOG_DATA_TYPE::PLDT_SKILL, &skill_stu);
      v5 = 1;
      skill_log::~skill_log(&skill_stu);
    }
    else
    {
      v5 = 0;
    }
  }
  CfgTalentTable::~CfgTalentTable(&Cfg);
  return v5;
}


#####################################
bool __cdecl CExtCharSkill::AddSkillBookPoint(CExtCharSkill *const this, int32_t Id, int32_t Points)
{
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  Job_t Job; // al
  bool v6; // bl
  int32_t Level; // r12d
  int32_t v8; // ebx
  CfgData *v9; // rax
  const CfgTalentTable *v10; // rax
  std::pair<const int,SkillLevelInfo> *v11; // rax
  std::pair<const int,SkillLevelInfo> *v12; // rax
  std::pair<const int,SkillLevelInfo> *v13; // rax
  std::pair<const int,SkillLevelInfo> *v14; // rax
  int32_t Ida; // [rsp+4h] [rbp-CCh] BYREF
  CExtCharSkill *thisa; // [rsp+8h] [rbp-C8h]
  CfgTalentTable Cfg; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > it; // [rsp+A0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SkillLevelInfo> > __x; // [rsp+B0h] [rbp-20h] BYREF
  const CfgTalent *pCfgTalent; // [rsp+B8h] [rbp-18h]

  thisa = this;
  Ida = Id;
  v3 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v3);
  CfgTalentTable::CfgTalentTable(&Cfg, TalentTable);
  Job = Player::getJob(this->m_pPlayer);
  if ( !CfgTalentTable::IsTalentSkill(&Cfg, Job, Id) )
  {
    v6 = 0;
  }
  else
  {
    it._M_node = std::map<int,SkillLevelInfo>::find(&thisa->m_SkillLevelMap, &Ida)._M_node;
    __x._M_node = std::map<int,SkillLevelInfo>::end(&thisa->m_SkillLevelMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator!=(&it, &__x) )
    {
      Level = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it)->second.Level;
      v8 = Ida;
      v9 = Answer::Singleton<CfgData>::instance();
      v10 = CfgData::GetTalentTable(v9);
      pCfgTalent = CfgTalentTable::GetTalent(v10, v8, Level);
      if ( pCfgTalent )
      {
        v11 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
        if ( v11->second.Point >= pCfgTalent->Point )
        {
          v6 = 0;
        }
        else
        {
          v12 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
          v12->second.Point += Points;
          v13 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
          if ( v13->second.Point > pCfgTalent->Point )
          {
            v14 = std::_Rb_tree_iterator<std::pair<int const,SkillLevelInfo>>::operator->(&it);
            v14->second.Point = pCfgTalent->Point;
          }
          v6 = 1;
        }
      }
      else
      {
        v6 = 0;
      }
    }
    else
    {
      v6 = 0;
    }
  }
  CfgTalentTable::~CfgTalentTable(&Cfg);
  return v6;
}


#####################################
void __cdecl CExtCharSkill::SendlearedSkill(CExtCharSkill *const this, int32_t TalentId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x276Du);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, TalentId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v6 = Player::getConnId(this->m_pPlayer);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, GateIndex, packet);
  }
}


#####################################
void __cdecl CExtCharSkill::AddOtherSkill(CExtCharSkill *const this, int32_t TalentId, int32_t TalentLevel)
{
  int32_t TalentIda; // [rsp+4h] [rbp-2Ch] BYREF
  CExtCharSkill *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  TalentIda = TalentId;
  if ( TalentLevel > 0 && TalentIda > 0 )
  {
    it._M_node = std::map<int,int>::find(&thisa->m_OthreSkillLevelMap, &TalentIda)._M_node;
    __x._M_node = std::map<int,int>::end(&thisa->m_OthreSkillLevelMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second = TalentLevel;
    else
      *std::map<int,int>::operator[](&thisa->m_OthreSkillLevelMap, &TalentIda) = TalentLevel;
    CExtCharSkill::initSkills(thisa, TalentIda, TalentLevel);
    CExtCharSkill::CallSkillBattle(thisa);
  }
}


#####################################
void __cdecl CExtCharSkill::broadcastIntervalEffect(
        CExtCharSkill *const this,
        Unit *pUnit,
        int32_t SkillId,
        int32_t hpchange,
        int32_t attackState)
{
  int8_t v5; // dl
  GameService *v6; // rax
  int16_t x; // dx
  int16_t y; // dx
  int64_t v9; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  int64_t v12; // [rsp+0h] [rbp-50h]
  int16_t attackStatea; // [rsp+14h] [rbp-3Ch]
  int16_t SkillIda; // [rsp+1Ch] [rbp-34h]
  int8_t launcher_8; // [rsp+38h] [rbp-18h]
  Map *pMap; // [rsp+40h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-8h]

  SkillIda = SkillId;
  attackStatea = attackState;
  if ( pUnit )
  {
    if ( this->m_pPlayer )
    {
      pMap = StaticObj::getMap(pUnit);
      if ( pMap )
      {
        v12 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 12))(this->m_pPlayer);
        launcher_8 = v5;
        v6 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v6, Answer::PackType::PACK_DISPATCH, 0x2738u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt16(packet, SkillIda);
          Answer::NetPacket::writeInt64(packet, v12);
          Answer::NetPacket::writeInt8(packet, launcher_8);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          x = StaticObj::getCurrentTile(pUnit).x;
          Answer::NetPacket::writeInt16(packet, x);
          y = StaticObj::getCurrentTile(pUnit).y;
          Answer::NetPacket::writeInt16(packet, y);
          Answer::NetPacket::writeInt8(packet, 0);
          Answer::NetPacket::writeInt16(packet, 1);
          v9 = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 2))(pUnit);
          Answer::NetPacket::writeInt64(packet, v9);
          Type = Entity::getType(pUnit);
          Answer::NetPacket::writeInt8(packet, Type);
          Answer::NetPacket::writeInt32(packet, hpchange);
          Answer::NetPacket::writeInt16(packet, attackStatea);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          Map::broadcastAreaAround(pMap, packet, pUnit);
        }
      }
    }
  }
}


