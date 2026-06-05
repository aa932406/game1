// Decompiled methods for class: SummonBoss
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl SummonBoss::~SummonBoss(SummonBoss *const this)
{
  SummonBoss::~SummonBoss(this);
  operator delete(this);
}


#####################################
int32_t __cdecl SummonBoss::effect(
        SummonBoss *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  GameService *v5; // rax
  CPoolManager *v6; // rax
  int8_t ConnId; // bl
  GameService *v8; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v11; // bl
  GameService *v12; // rax
  CfgMapMonster cfgMapMonster; // [rsp+20h] [rbp-80h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+40h] [rbp-60h] BYREF
  std::string val; // [rsp+60h] [rbp-40h] BYREF
  Map *pMap; // [rsp+68h] [rbp-38h]
  int32_t nMapId; // [rsp+74h] [rbp-2Ch]
  int32_t nPosX; // [rsp+78h] [rbp-28h]
  int32_t nPosY; // [rsp+7Ch] [rbp-24h]
  Monster *pMonster; // [rsp+80h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+88h] [rbp-18h]

  if ( !this->m_pCfgMapMonster || !this->m_pCfgMonster )
    return 10002;
  v5 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v5) != 1 )
    return 10002;
  pMap = StaticObj::getMap(launcher);
  if ( !pMap )
    return 10002;
  nMapId = Map::GetMapId(pMap);
  nPosX = StaticObj::GetPosX(launcher);
  nPosY = StaticObj::GetPosY(launcher);
  if ( this->m_pCfgMapMonster->mapid != nMapId )
    return 10002;
  cfgMapMonster = *this->m_pCfgMapMonster;
  cfgMapMonster.x = nPosX;
  cfgMapMonster.y = nPosY;
  v6 = Answer::Singleton<CPoolManager>::instance();
  pMonster = CPoolManager::pop<Monster>(v6);
  if ( !pMonster )
    return 10002;
  std::vector<AttrAddon>::vector(&vAttrAddon);
  Monster::init(pMonster, this->m_pCfgMonster, &cfgMapMonster, MonsterState::MS_STAND, &vAttrAddon);
  std::vector<AttrAddon>::~vector(&vAttrAddon);
  (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
    pMap,
    pMonster,
    (unsigned int)nPosX,
    (unsigned int)nPosY);
  ConnId = Player::getConnId(launcher);
  v8 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v8, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 299);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(launcher);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, nMapId);
    Answer::NetPacket::writeInt32(packet, nPosX);
    Answer::NetPacket::writeInt32(packet, nPosY);
    Answer::NetPacket::writeInt32(packet, this->m_pCfgMonster->mid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v11 = Player::getConnId(launcher);
    v12 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v12, v11, packet);
  }
  return 0;
}


#####################################
bool __cdecl SummonBoss::parseEffect(SummonBoss *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // bl
  std::string *v4; // rax
  const char *v5; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  int32_t monsterid; // ebx
  CfgData *v9; // rax
  StringVector vStr; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v14[17]; // [rsp+4Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v14);
  std::string::string(&delims, ":");
  Answer::StringUtility::split(&vStr, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(v14);
  if ( std::vector<std::string>::empty(&vStr) )
  {
    v3 = 0;
  }
  else
  {
    v4 = std::vector<std::string>::operator[](&vStr, 0);
    v5 = (const char *)std::string::c_str(v4);
    v6 = atoi(v5);
    v7 = Answer::Singleton<CfgData>::instance();
    this->m_pCfgMapMonster = CfgData::GetMapMonsterInfo(v7, v6);
    if ( this->m_pCfgMapMonster )
    {
      monsterid = this->m_pCfgMapMonster->monsterid;
      v9 = Answer::Singleton<CfgData>::instance();
      this->m_pCfgMonster = CfgData::getMonster(v9, monsterid);
      v3 = this->m_pCfgMonster != 0;
    }
    else
    {
      v3 = 0;
    }
  }
  std::vector<std::string>::~vector(&vStr);
  return v3;
}


