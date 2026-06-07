// Decompiled methods for class: GameService
// Source: gameserver.cc
// Total methods: 100

#####################################
void __cdecl GameService::~GameService(GameService *const this)
{
  GameService::~GameService(this);
  operator delete(this);
}


#####################################
bool __cdecl GameService::Connect(GameService *const this, int8_t id, std::string *p_host, int32_t port)
{
  std::map<signed char,GameService::ConnType*>::ConnType *v5; // rbx
  bool v6; // bl
  std::map<signed char,GameService::ConnType*>::ConnType **v7; // rax
  uint32_t WOffset; // eax
  uint16_t porta; // [rsp+24h] [rbp-9Ch]
  int8_t ida[4]; // [rsp+34h] [rbp-8Ch] BYREF
  GameService *thisa; // [rsp+38h] [rbp-88h]
  std::string name; // [rsp+40h] [rbp-80h] BYREF
  char v14; // [rsp+4Fh] [rbp-71h] BYREF
  Answer::InetAddress serverAddr; // [rsp+50h] [rbp-70h] BYREF
  std::string val; // [rsp+60h] [rbp-60h] BYREF
  std::string v17; // [rsp+70h] [rbp-50h] BYREF
  std::string v18; // [rsp+80h] [rbp-40h] BYREF
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  thisa = this;
  porta = port;
  ida[0] = id;
  if ( id < 0 || ida[0] > 99 )
    return 0;
  std::allocator<char>::allocator(&v14);
  std::string::string(&name, "GameService", &v14);
  v5 = (std::map<signed char,GameService::ConnType*>::ConnType *)operator new(0x118u);
  MutiConn<GameService>::MutiConn(v5, 0x2000, 0x2000, 0x7F9u, 0, 0x7D0u, (std::string)&name, ida[0], thisa);
  pConn = v5;
  std::string::~string(&name);
  std::allocator<char>::~allocator(&v14);
  if ( !pConn )
    return 0;
  Answer::InetAddress::InetAddress(&serverAddr, p_host, porta);
  v6 = !Answer::TcpClient::connect(pConn, &serverAddr);
  Answer::InetAddress::~InetAddress(&serverAddr);
  if ( v6 )
    return 0;
  Answer::Thread::start(pConn);
  v7 = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::operator[](
         &thisa->m_mConn,
         ida);
  *v7 = pConn;
  packet = Answer::TcpClient::popNetpacket(pConn);
  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt32(packet, thisa->m_line);
  GameService::GetVersion((GameService *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  GetServerVersion();
  Answer::NetPacket::writeUTF8(packet, &v17);
  std::string::~string(&v17);
  Answer::TcpClient::getName((Answer::TcpClient *const)&v18);
  Answer::NetPacket::writeUTF8(packet, &v18);
  std::string::~string(&v18);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  Answer::NetPacket::setType(packet, Answer::PackType::PACK_PROC);
  Answer::NetPacket::setProc(packet, 0x4E22u);
  Answer::TcpClient::sendPacket(pConn, packet);
  return 1;
}


#####################################
std::string __cdecl GameService::GetVersion(GameService *const this)
{
  Answer::Inifile ini; // [rsp+10h] [rbp-90h] BYREF
  std::string inifile; // [rsp+50h] [rbp-50h] BYREF
  char v4; // [rsp+5Fh] [rbp-41h] BYREF
  _BYTE v5[15]; // [rsp+60h] [rbp-40h] BYREF
  char v6; // [rsp+6Fh] [rbp-31h] BYREF
  std::string key; // [rsp+70h] [rbp-30h] BYREF
  _BYTE v8[33]; // [rsp+7Fh] [rbp-21h] BYREF

  std::allocator<char>::allocator(&v4);
  std::string::string(&inifile, "version.ini", &v4);
  std::allocator<char>::~allocator(&v4);
  Answer::Inifile::Inifile(&ini);
  Answer::Inifile::parse(&ini, &inifile);
  std::allocator<char>::allocator(&v6);
  std::string::string(v5, "versionName", &v6);
  std::allocator<char>::allocator(v8);
  std::string::string(&key, "Version", v8);
  Answer::Inifile::getStrValue((Answer::Inifile *const)this, (const std::string *const)&ini, &key);
  std::string::~string(&key);
  std::allocator<char>::~allocator(v8);
  std::string::~string(v5);
  std::allocator<char>::~allocator(&v6);
  Answer::Inifile::~Inifile(&ini);
  std::string::~string(&inifile);
  return (std::string)this;
}


#####################################
void __cdecl GameService::RecalAllPlayerAttr(GameService *const this)
{
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Player *pPlayer; // [rsp+38h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    pPlayer = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( pPlayer )
    {
      Player::RecalcAttr(pPlayer);
      break;
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::AddPlayerVipClubDropTime(GameService *const this)
{
  CVip *PlayerVip; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+40h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+60h] [rbp-20h] BYREF
  Player *pPlayer; // [rsp+68h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    pPlayer = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( pPlayer )
    {
      PlayerVip = Player::GetPlayerVip(pPlayer);
      CVip::AddClubDropTime(PlayerVip);
    }
  }
  v2 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
  Answer::MySqlDBGuard::excute(&db, "update mem_chr_vip set drop_time = 1 where club > 0 and drop_time <= 0");
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::onNetPacket(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int8_t Id; // bl
  CZongHeYunYingHD *v4; // rax
  uint16_t proc; // [rsp+2Ah] [rbp-16h]
  int8_t connid; // [rsp+2Dh] [rbp-13h]
  __int16 cgindex; // [rsp+2Eh] [rbp-12h]

  if ( pConn && inPacket )
  {
    proc = Answer::NetPacket::getProc(inPacket);
    connid = MutiConn<GameService>::GetId(pConn);
    if ( proc <= 0x4E20u || proc > 0x61AAu )
    {
      cgindex = Answer::NetPacket::readInt32(inPacket);
      if ( cgindex > 0 && cgindex <= 9999 )
      {
        if ( proc == 6 )
        {
          GameService::onEnterGame(this, connid, cgindex, inPacket);
        }
        else if ( proc == 7 )
        {
          GameService::onEnterGameRobot(this, connid, cgindex, inPacket);
        }
        else
        {
          GameService::onGameNetpacket(this, connid, cgindex, inPacket);
        }
      }
    }
    else if ( proc <= 0x4E54u || proc > 0x4E77u )
    {
      switch ( proc )
      {
        case 0x4E26u:
          GameService::onAddUser(this, pConn, inPacket);
          break;
        case 0x4E27u:
          GameService::onRemoveUser(this, pConn, inPacket);
          break;
        case 0x4E29u:
          GameService::onGMReloadItem(this, pConn, inPacket);
          break;
        case 0x4E2Du:
          GameService::onGateDisconnect(this, pConn, inPacket);
          break;
        case 0x4E7Eu:
          GameService::onSocialUpdatePetRank(this, pConn, inPacket);
          break;
        case 0x4E7Fu:
          GameService::onSocialUpdateFamilyInfo(this, pConn, inPacket);
          break;
        case 0x4E80u:
          GameService::onSocialUpdateRankMirror(this, pConn, inPacket);
          break;
        case 0x4E81u:
          GameService::onSetWorldLevel(this, pConn, inPacket);
          break;
        case 0x4E82u:
          GameService::OnReceiveDaTiResult(this, pConn, inPacket);
          break;
        case 0x4E83u:
          GameService::OnSocialCityMasterBanChat(this, pConn, inPacket);
          break;
        case 0x4E86u:
          GameService::onSocialInitPetRank(this, pConn, inPacket);
          break;
        case 0x4E87u:
          GameService::onSocialCreateTeamDungeon(this, pConn, inPacket);
          break;
        case 0x4E88u:
          GameService::OnReceiveDaTiRank(this, pConn, inPacket);
          break;
        case 0x4E89u:
          GameService::onSocialSendSystemMail(this, pConn, inPacket);
          break;
        case 0x4E8Au:
          GameService::onSocialSendSystemMail2(this, pConn, inPacket);
          break;
        case 0x4E8Bu:
          GameService::onSocialInitRankMirror(this, pConn, inPacket);
          break;
        case 0x4E8Cu:
          GameService::onSocialQueryPlayerInfo(this, pConn, inPacket);
          break;
        case 0x4E8Du:
          GameService::onRequestDropRecord(this, pConn, inPacket);
          break;
        case 0x4E8Eu:
          GameService::onSocialInitFamilyInfo(this, pConn, inPacket);
          break;
        case 0x4EC1u:
          Id = MutiConn<GameService>::GetId(pConn);
          v4 = Answer::Singleton<CZongHeYunYingHD>::instance();
          CZongHeYunYingHD::UpdatePlayerInfo(v4, Id, inPacket);
          break;
        case 0x4EC4u:
          GameService::onUpdateActivityState(this, pConn, inPacket);
          break;
        case 0x4EEAu:
          GameService::qqToPlayer(this, pConn, inPacket);
          break;
        default:
          break;
      }
    }
    else
    {
      GameService::onSocialNetpacket(this, pConn, inPacket);
    }
    Answer::NetPacket::destroy(inPacket);
  }
}


#####################################
void __cdecl GameService::startGame(GameService *const this)
{
  TileManager *v1; // rax
  MapManager *v2; // rax
  MapManager *v3; // rax
  int32_t m_line; // ebx
  CActivityManager *v5; // rax
  int32_t v6; // ebx
  CGMBackstate *v7; // rax
  int32_t v8; // ebx
  CFestivalDoubleEleven *v9; // rax
  int32_t v10; // ebx
  CZongHeYunYingHD *v11; // rax
  int32_t v12; // ebx
  CKiaFuRecharge *v13; // rax
  CFestivalActivity *v14; // rax
  GameService *v15; // rax
  CfgData *v16; // rax
  int32_t Debug; // edx
  uint32_t WOffset; // edx
  GameService *v19; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  Player::initNetPacketHandlers();
  GameService::InitServerBattle(this);
  v1 = Answer::Singleton<TileManager>::instance();
  TileManager::Init(v1);
  v2 = Answer::Singleton<MapManager>::instance();
  MapManager::Init(v2);
  v3 = Answer::Singleton<MapManager>::instance();
  MapManager::StartAll(v3);
  m_line = this->m_line;
  v5 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::Init(v5, m_line);
  v6 = this->m_line;
  v7 = Answer::Singleton<CGMBackstate>::instance();
  CGMBackstate::Init(v7, v6);
  v8 = this->m_line;
  v9 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::Init(v9, v8);
  v10 = this->m_line;
  v11 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::Init(v11, v10);
  v12 = this->m_line;
  v13 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::Init(v13, v12);
  v14 = Answer::Singleton<CFestivalActivity>::instance();
  CFestivalActivity::Init(v14);
  GameService::InitDropTimes(this);
  GameService::InitMoYuShiJieRecord(this);
  GameService::requestSocialData(this);
  GameService::requestWorldLevel(this);
  if ( this->m_line == 1 )
  {
    GameService::SendServerDiffToGlobal(this);
    v15 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v15, Answer::PackType::PACK_PROC, 0x4E30u);
    if ( packet )
    {
      v16 = Answer::Singleton<CfgData>::instance();
      Debug = CfgData::getDebug(v16);
      Answer::NetPacket::writeInt32(packet, Debug);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v19 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v19, 0, packet);
    }
  }
}


#####################################
void __cdecl GameService::stopGame(GameService *const this)
{
  MapManager *v1; // rax
  GameService *v2; // rax

  v1 = Answer::Singleton<MapManager>::instance();
  MapManager::StopAll(v1);
  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
    GameService::saveAllPlayerToDB(this);
}


#####################################
int8_t __cdecl GameService::GetAutoConnId(GameService *const this)
{
  const MutiConn<GameService> *pConn; // [rsp+18h] [rbp-8h]

  pConn = GameService::GetConn(this);
  if ( pConn )
    return MutiConn<GameService>::GetId(pConn);
  else
    return 0;
}


#####################################
int8_t __cdecl GameService::GetConnId(GameService *const this, CharId_t cid)
{
  int8_t ConnId; // bl
  CharId_t cida; // [rsp+0h] [rbp-50h] BYREF
  GameService *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Player *pPlayer; // [rsp+38h] [rbp-18h]

  thisa = this;
  cida = cid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &cida)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x)
    && (pPlayer = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second) != 0 )
  {
    ConnId = Player::getConnId(pPlayer);
  }
  else
  {
    ConnId = 0;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  return ConnId;
}


#####################################
void __cdecl GameService::onUpdatePay(GameService *const this)
{
  DBService *v1; // rax

  if ( this->m_line == 1 )
  {
    v1 = Answer::Singleton<DBService>::instance();
    DBService::OnUpdatePay(v1);
  }
}


#####################################
void __cdecl GameService::onNewMinuteCome(GameService *const this, int32_t minute)
{
  DBService *v2; // rax
  uint32_t WOffset; // eax
  std::pair<const int,ChatValidate> *v4; // rax
  std::pair<const int,ChatValidate> *v5; // rax
  std::_Rb_tree_iterator<std::pair<const int,ChatValidate> > v6; // rax
  std::_Rb_tree_iterator<std::pair<const int,ChatValidate> > it; // [rsp+10h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ChatValidate> > __x; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-20h]
  int32_t Time; // [rsp+4Ch] [rbp-14h]

  if ( this->m_line == 1 )
  {
    v2 = Answer::Singleton<DBService>::instance();
    DBService::onNewMinuteCome(v2, minute);
    packet = GameService::popNetpacket(this, 0, Answer::PackType::PACK_PROC, 0x4E38u);
    if ( !packet )
      return;
    Answer::NetPacket::writeInt32(packet, minute);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GameService::sendPacket(this, 0, packet);
  }
  if ( !(minute % 5) )
  {
    Time = Answer::DayTime::now();
    Answer::MutexGuard::MutexGuard(&lock, &this->m_ChatValidateLock);
    it._M_node = std::map<int,ChatValidate>::begin(&this->m_ChatValidateMap)._M_node;
    while ( 1 )
    {
      __x._M_node = std::map<int,ChatValidate>::end(&this->m_ChatValidateMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator!=(&it, &__x) )
        break;
      v4 = std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator->(&it);
      if ( Time - v4->second.Time <= 300 )
      {
        std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator++(&it, 0);
      }
      else
      {
        if ( std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator->(&it)->second.SendPacket )
        {
          v5 = std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator->(&it);
          Answer::NetPacket::destroy(v5->second.SendPacket);
        }
        v6._M_node = std::_Rb_tree_iterator<std::pair<int const,ChatValidate>>::operator++(&it, 0)._M_node;
        std::map<int,ChatValidate>::erase(&this->m_ChatValidateMap, v6);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::OnDaySwitch(GameService *const this)
{
  if ( this->m_line == 1 )
  {
    GameService::ResetDropTimes(this);
    GameService::SendServerDiffToGlobal(this);
  }
}


#####################################
void __cdecl GameService::onPlayerLoaded(
        GameService *const this,
        PlayerDBData *const dbData,
        int32_t reason,
        bool isRobot)
{
  int32_t v4; // ebx
  MapManager *v5; // rax
  CfgData *v7; // rax
  int32_t v8; // ebx
  MapManager *v9; // rax
  PlayerRobot *v10; // rbx
  CPoolManager *v11; // rax
  int32_t iparam2; // r12d
  int32_t x; // r13d
  int32_t RunnerId; // ebx
  MapManager *v15; // rax
  CExtOperateLimit *OperateLimit; // rax
  __int16 LimitCount; // bx
  CActivityManager *v18; // rax
  GameService *v19; // rax
  uint32_t WOffset; // eax
  Position pos; // [rsp+30h] [rbp-B0h]
  Answer::MutexGuard lock; // [rsp+40h] [rbp-A0h] BYREF
  TencentInfo info; // [rsp+50h] [rbp-90h] BYREF
  Player *player; // [rsp+70h] [rbp-70h]
  Map *pMap; // [rsp+78h] [rbp-68h]
  int32_t nIndex; // [rsp+84h] [rbp-5Ch]
  User *pUser; // [rsp+88h] [rbp-58h]
  Map *pMap_0; // [rsp+90h] [rbp-50h]
  int32_t mapid; // [rsp+98h] [rbp-48h]
  int32_t nRegion; // [rsp+9Ch] [rbp-44h]
  CfgMapRegion *pCfgRegion; // [rsp+A0h] [rbp-40h]
  Map *pTempMap; // [rsp+A8h] [rbp-38h]
  int32_t nActId; // [rsp+B4h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+B8h] [rbp-28h]

  player = GameService::getPlayer(this, dbData->chr.data.cid, 0, 0);
  if ( player )
  {
    pMap_0 = StaticObj::getMap(player);
    mapid = 0;
    if ( pMap_0 )
      mapid = Map::GetMapId(pMap_0);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_INFO,
      "GameService::onPlayerLoaded player cid = %lld, map = %p, mapid = %d already in game\n",
      dbData->chr.data.cid,
      pMap_0,
      mapid);
  }
  else
  {
    v4 = dbData->chr.data.mapid;
    v5 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v5, v4);
    if ( !pMap )
    {
      nRegion = 20001;
      if ( dbData->chr.data.mapid > 0 )
      {
        if ( reason == 3 && GameService::getLine(this) == 9 )
          nRegion = 20002;
      }
      else
      {
        nRegion = 10002;
      }
      v7 = Answer::Singleton<CfgData>::instance();
      pCfgRegion = CfgData::getMapRegion(v7, nRegion);
      if ( pCfgRegion )
      {
        v8 = pCfgRegion->mapid;
        v9 = Answer::Singleton<MapManager>::instance();
        pTempMap = MapManager::GetMap(v9, v8);
        if ( pTempMap )
        {
          pos = Map::getRandomWalkablePositionInRegion(pTempMap, pCfgRegion);
          if ( pos.x >= 0 && pos.y >= 0 )
          {
            pMap = pTempMap;
            dbData->chr.data.mapid = Map::GetMapId(pTempMap);
            *(Position *)&dbData->chr.data.x = pos;
          }
        }
      }
    }
    if ( pMap )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
      nIndex = getUserIndex(dbData->connid, dbData->cgindex);
      pUser = this->m_users[nIndex];
      if ( pUser )
      {
        if ( User::getPlayer(pUser) )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_ERROR,
            "GameService::onPlayerLoaded user already have player cgindex=%d, cid = %lld\n",
            dbData->cgindex,
            dbData->chr.data.cid);
        }
        else
        {
          if ( isRobot )
          {
            v10 = (PlayerRobot *)operator new(0xDE68u);
            PlayerRobot::PlayerRobot(v10);
            player = v10;
            (*((void (__fastcall **)(PlayerRobot *))v10->_vptr_Entity + 6))(v10);
          }
          else
          {
            v11 = Answer::Singleton<CPoolManager>::instance();
            player = CPoolManager::pop<Player>(v11);
          }
          if ( player )
          {
            User::GetTencentInfo(&info, pUser);
            Player::InitTencentInfo(player, &info);
            TencentInfo::~TencentInfo(&info);
            Player::init(player, dbData);
            User::setPlayer(pUser, player);
            GameService::AddPlayer(this, player, reason);
            if ( !Player::reconnect(player) )
            {
              iparam2 = dbData->chr.data.y;
              x = dbData->chr.data.x;
              RunnerId = Map::GetRunnerId(pMap);
              v15 = Answer::Singleton<MapManager>::instance();
              MapManager::PostMsg(v15, RunnerId, GameMsgCode::GMC_PLAYER_ENTER_MAP, player, pMap, x, iparam2, 0);
              if ( GameService::getLine(this) == 9 )
              {
                OperateLimit = Player::GetOperateLimit(player);
                LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1057);
                v18 = Answer::Singleton<CActivityManager>::instance();
                nActId = CActivityManager::GetCurActivityId(v18, LimitCount);
                LOBYTE(LimitCount) = Player::getConnId(player);
                v19 = Answer::Singleton<GameService>::instance();
                packet = GameService::popNetpacket(v19, LimitCount, Answer::PackType::PACK_DISPATCH, 0x1Du);
                if ( packet )
                {
                  Answer::NetPacket::writeInt32(packet, nActId);
                  WOffset = Answer::NetPacket::getWOffset(packet);
                  Answer::NetPacket::setSize(packet, WOffset);
                  Player::addNetPacket(player, packet, 0);
                  Answer::NetPacket::destroy(packet);
                }
              }
            }
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_DEBUG,
              "GameService::onPlayerLoaded pop player %p\n",
              player);
          }
          else
          {
            Answer::Logger::print(
              Answer::LogLevel::LOG_LEVEL_ERROR,
              "GameService::onPlayerLoaded create player fail cgindex=%d, cid = %lld\n",
              dbData->cgindex,
              dbData->chr.data.cid);
          }
        }
      }
      else
      {
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "GameService::onPlayerLoaded null user cgindex=%d, cid = %lld\n",
          dbData->cgindex,
          dbData->chr.data.cid);
      }
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "GameService::onPlayerLoaded player cid=%lld can't find map with mapid = %d\n",
        dbData->chr.data.cid,
        dbData->chr.data.mapid);
    }
  }
}


#####################################
void __cdecl GameService::onPlayerLogout(GameService *const this, Player *player)
{
  CPoolManager *v2; // rax
  Answer::MutexGuard lock; // [rsp+10h] [rbp-30h] BYREF
  int8_t connid; // [rsp+21h] [rbp-1Fh]
  int16_t cgindex; // [rsp+22h] [rbp-1Eh]
  int32_t nIndex; // [rsp+24h] [rbp-1Ch]
  User *user; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    connid = Player::getConnId(player);
    cgindex = Player::getGateIndex(player);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_DEBUG,
      "GameService::onPlayerLogout push player %p, cgindex = %d\n",
      player,
      cgindex);
    GameService::removePlayer(this, player);
    if ( Player::getGateIndex(player) > 0 )
    {
      Player::setGateIndex(player, -1);
      if ( (*((unsigned __int8 (__fastcall **)(Player *))player->_vptr_Entity + 34))(player) )
      {
        (*((void (__fastcall **)(Player *))player->_vptr_Entity + 1))(player);
      }
      else
      {
        v2 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<Player>(v2, player);
      }
    }
    if ( (unsigned __int8)connid < 0x64u && (unsigned __int16)cgindex < 0x2710u )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
      nIndex = getUserIndex(connid, cgindex);
      user = this->m_users[nIndex];
      if ( user )
        User::setPlayer(user, 0);
      Answer::MutexGuard::~MutexGuard(&lock);
    }
  }
}


#####################################
void __cdecl GameService::onPlayerSaved(
        GameService *const this,
        int8_t connid,
        int64_t uid,
        int32_t sid,
        int32_t reason,
        int32_t param,
        CharId_t cid)
{
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  packet = GameService::popNetpacket(this, connid, Answer::PackType::PACK_PROC, 0x4E25u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, uid);
    Answer::NetPacket::writeInt32(packet, sid);
    Answer::NetPacket::writeInt32(packet, reason);
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeInt32(packet, param);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GameService::sendPacket(this, connid, packet);
  }
}


#####################################
void __cdecl GameService::sendPacket(GameService *const this, int8_t connid, Answer::NetPacket *packet)
{
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+28h] [rbp-8h]

  pConn = GameService::GetConn(this, connid);
  if ( pConn )
    Answer::TcpClient::sendPacket(pConn, packet);
}


#####################################
void __cdecl GameService::sendPacketTo(
        GameService *const this,
        int8_t connid,
        int16_t index,
        Answer::NetPacket *inPacket)
{
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+28h] [rbp-18h]

  pConn = GameService::GetConn(this, connid);
  if ( pConn )
    Answer::TcpService::sendPacketTo(pConn, index, inPacket);
}


#####################################
int32_t __cdecl GameService::replySuccess(
        GameService *const this,
        int8_t connid,
        int16_t index,
        uint16_t proc,
        int64_t addon)
{
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+28h] [rbp-18h]

  pConn = GameService::GetConn(this, connid);
  if ( pConn )
    return Answer::TcpService::replySuccess(pConn, index, proc, addon);
  else
    return 10002;
}


#####################################
int32_t __cdecl GameService::replyfailure(
        GameService *const this,
        int8_t connid,
        int16_t index,
        uint16_t proc,
        int32_t errcode,
        int64_t addon)
{
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+28h] [rbp-18h]

  pConn = GameService::GetConn(this, connid);
  if ( pConn )
    return Answer::TcpService::replyfailure(pConn, index, proc, errcode, addon);
  else
    return 10002;
}


#####################################
void __cdecl GameService::broadcastHuoDongDaTingIcon(GameService *const this)
{
  std::pair<const long int,Player*> *v1; // rax
  DailyActivity *PlayerDailyActivity; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  if ( !std::map<long,Player *>::empty(&this->m_players) )
  {
    for ( it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&it) )
    {
      __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
        break;
      v1 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
      PlayerDailyActivity = Player::GetPlayerDailyActivity(v1->second);
      DailyActivity::SendHuoDongDaTingIcon(PlayerDailyActivity);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::SendOpenBetaIcon(GameService *const this)
{
  Player *second; // rbx
  COpenBeta *v2; // rax
  std::pair<const long int,Player*> *v3; // rax
  ShowIcon stu; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+30h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+50h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  if ( !std::map<long,Player *>::empty(&this->m_players) )
  {
    for ( it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&it) )
    {
      __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
        break;
      second = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it)->second;
      v2 = Answer::Singleton<COpenBeta>::instance();
      COpenBeta::getIconState(&stu, v2, second);
      v3 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
      Player::SendIconState(v3->second, &stu);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::broadFamilyWarIcon(GameService *const this)
{
  std::pair<const long int,Player*> *v1; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  if ( !std::map<long,Player *>::empty(&this->m_players) )
  {
    for ( it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&it) )
    {
      __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
        break;
      v1 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
      Player::SendFamilyWarIcon(v1->second);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::broadcast(
        GameService *const this,
        Answer::NetPacket *inPacket,
        const IndexMap *const indexMap)
{
  std::list<short int> *p_second; // r12
  char first; // dl
  std::_Rb_tree_const_iterator<std::pair<const signed char,std::list<short int> > > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,std::list<short int> > > __x; // [rsp+30h] [rbp-20h] BYREF

  if ( inPacket )
  {
    if ( std::map<signed char,std::list<short>>::empty(indexMap) )
    {
      Answer::NetPacket::destroy(inPacket);
    }
    else
    {
      for ( iter._M_node = std::map<signed char,std::list<short>>::begin(indexMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<signed char const,std::list<short>>>::operator++(&iter) )
      {
        __x._M_node = std::map<signed char,std::list<short>>::end(indexMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,std::list<short>>>::operator!=(&iter, &__x) )
          break;
        p_second = &std::_Rb_tree_const_iterator<std::pair<signed char const,std::list<short>>>::operator->(&iter)->second;
        first = std::_Rb_tree_const_iterator<std::pair<signed char const,std::list<short>>>::operator->(&iter)->first;
        GameService::broadcast(this, inPacket, first, p_second);
      }
      Answer::NetPacket::destroy(inPacket);
    }
  }
}


#####################################
void __cdecl GameService::broadcast(
        GameService *const this,
        Answer::NetPacket *inPacket,
        int8_t connid,
        const Int16List *const indexList)
{
  unsigned int v4; // r13d
  uint16_t Proc; // r12
  Answer::PackType Type; // edx
  int16_t *v7; // rax
  uint32_t Size; // ebx
  char *Buffer; // rax
  uint32_t WOffset; // eax
  std::_List_const_iterator<short int> iter; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<short int> __x; // [rsp+30h] [rbp-40h] BYREF
  int32_t nsize; // [rsp+44h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]

  if ( inPacket )
  {
    if ( std::list<short>::empty(indexList) )
    {
      Answer::NetPacket::destroy(inPacket);
    }
    else
    {
      nsize = std::list<short>::size(indexList);
      v4 = 2 * (nsize + 1) + Answer::NetPacket::getSize(inPacket);
      Proc = Answer::NetPacket::getProc(inPacket);
      Type = Answer::NetPacket::getType(inPacket);
      packet = GameService::popNetpacket(this, connid, Type, Proc, v4);
      if ( packet )
      {
        Answer::NetPacket::writeInt16(packet, nsize);
        for ( iter._M_node = std::list<short>::begin(indexList)._M_node;
              ;
              std::_List_const_iterator<short>::operator++(&iter) )
        {
          __x._M_node = std::list<short>::end(indexList)._M_node;
          if ( !std::_List_const_iterator<short>::operator!=(&iter, &__x) )
            break;
          v7 = (int16_t *)std::_List_const_iterator<short>::operator*(&iter);
          Answer::NetPacket::writeInt16(packet, *v7);
        }
        Size = Answer::NetPacket::getSize(inPacket);
        Buffer = Answer::NetPacket::getBuffer(inPacket);
        Answer::NetPacket::write(packet, Buffer, Size);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GameService::sendPacket(this, connid, packet);
      }
    }
  }
}


#####################################
void __cdecl GameService::broadcast(GameService *const this, Answer::NetPacket *inPacket)
{
  std::list<short int> *v2; // rax
  IndexMap indexMap; // [rsp+10h] [rbp-A0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,Player*> > iter; // [rsp+40h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __it; // [rsp+60h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,Player*> > v7; // [rsp+70h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > v8; // [rsp+80h] [rbp-30h] BYREF
  __int16 __x; // [rsp+94h] [rbp-1Ch] BYREF
  char __k; // [rsp+97h] [rbp-19h] BYREF
  Player *player; // [rsp+98h] [rbp-18h]

  if ( inPacket )
  {
    std::map<signed char,std::list<short>>::map(&indexMap);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    __it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
    std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::_Rb_tree_const_iterator(&iter, &__it);
    while ( 1 )
    {
      v8._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
      std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::_Rb_tree_const_iterator(&v7, &v8);
      if ( !std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator!=(&iter, &v7) )
        break;
      player = std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
      if ( player )
      {
        __x = Player::getGateIndex(player);
        __k = Player::getConnId(player);
        v2 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
        std::list<short>::push_back(v2, &__x);
      }
      std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator++(&iter);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
    GameService::broadcast(this, inPacket, &indexMap);
    std::map<signed char,std::list<short>>::~map(&indexMap);
  }
}


#####################################
void __cdecl GameService::broadcast(GameService *const this, Answer::NetPacket *inPacket, const CharIdList *const cids)
{
  const __int64 *v3; // rax
  std::list<short int> *v4; // rax
  IndexMap indexMap; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > findIter; // [rsp+50h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-60h] BYREF
  std::_List_const_iterator<long int> iter; // [rsp+70h] [rbp-50h] BYREF
  std::_List_const_iterator<long int> v10; // [rsp+80h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+90h] [rbp-30h] BYREF
  __int16 GateIndex; // [rsp+A4h] [rbp-1Ch] BYREF
  char __k; // [rsp+A7h] [rbp-19h] BYREF
  Player *player; // [rsp+A8h] [rbp-18h]

  if ( inPacket )
  {
    if ( std::list<long>::empty(cids) )
    {
      Answer::NetPacket::destroy(inPacket);
    }
    else
    {
      std::map<signed char,std::list<short>>::map(&indexMap);
      for ( iter._M_node = std::list<long>::begin(cids)._M_node; ; std::_List_const_iterator<long>::operator++(&iter) )
      {
        v10._M_node = std::list<long>::end(cids)._M_node;
        if ( !std::_List_const_iterator<long>::operator!=(&iter, &v10) )
          break;
        Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
        v3 = std::_List_const_iterator<long>::operator*(&iter);
        findIter._M_node = std::map<long,Player *>::find(&this->m_players, v3)._M_node;
        __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&findIter, &__x) )
        {
          player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&findIter)->second;
          if ( player )
          {
            GateIndex = Player::getGateIndex(player);
            __k = Player::getConnId(player);
            v4 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
            std::list<short>::push_back(v4, &GateIndex);
          }
        }
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      GameService::broadcast(this, inPacket, &indexMap);
      std::map<signed char,std::list<short>>::~map(&indexMap);
    }
  }
}


#####################################
void __cdecl GameService::broadcastToFamily(
        GameService *const this,
        Answer::NetPacket *inPacket,
        FamilyId_t nFamilyId,
        int32_t nLevel)
{
  std::list<short int> *v5; // rax
  IndexMap indexMap; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,Player*> > iter; // [rsp+50h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __it; // [rsp+70h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,Player*> > v12; // [rsp+80h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > v13; // [rsp+90h] [rbp-30h] BYREF
  __int16 __x; // [rsp+A4h] [rbp-1Ch] BYREF
  char __k; // [rsp+A7h] [rbp-19h] BYREF
  Player *player; // [rsp+A8h] [rbp-18h]

  if ( inPacket )
  {
    if ( nFamilyId > 0 )
    {
      std::map<signed char,std::list<short>>::map(&indexMap);
      Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
      __it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
      std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::_Rb_tree_const_iterator(&iter, &__it);
      while ( 1 )
      {
        v13._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
        std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::_Rb_tree_const_iterator(&v12, &v13);
        if ( !std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator!=(&iter, &v12) )
          break;
        player = std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
        if ( player
          && Player::getFamilyId(player) == nFamilyId
          && (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) > nLevel )
        {
          __x = Player::getGateIndex(player);
          __k = Player::getConnId(player);
          v5 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
          std::list<short>::push_back(v5, &__x);
        }
        std::_Rb_tree_const_iterator<std::pair<long const,Player *>>::operator++(&iter);
      }
      Answer::MutexGuard::~MutexGuard(&lock);
      GameService::broadcast(this, inPacket, &indexMap);
      std::map<signed char,std::list<short>>::~map(&indexMap);
    }
    else
    {
      Answer::NetPacket::destroy(inPacket);
    }
  }
}


#####################################
void __cdecl GameService::worldBroadcast(GameService *const this, int8_t connid, Answer::NetPacket *inPacket)
{
  unsigned int v3; // r13d
  uint16_t Proc; // r12
  Answer::PackType Type; // edx
  uint32_t Size; // ebx
  char *Buffer; // rcx
  uint32_t WOffset; // edx
  uint32_t oldSize; // [rsp+20h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( inPacket )
  {
    oldSize = Answer::NetPacket::getSize(inPacket);
    if ( Answer::NetPacket::rightShift(inPacket, 2u) )
    {
      Answer::NetPacket::writeInt16(inPacket, -1);
      Answer::NetPacket::setSize(inPacket, oldSize + 2);
      GameService::sendPacket(this, connid, inPacket);
    }
    else
    {
      v3 = Answer::NetPacket::getSize(inPacket) + 2;
      Proc = Answer::NetPacket::getProc(inPacket);
      Type = Answer::NetPacket::getType(inPacket);
      packet = GameService::popNetpacket(this, connid, Type, Proc, v3);
      if ( packet )
      {
        Answer::NetPacket::writeInt16(packet, -1);
        Size = Answer::NetPacket::getSize(inPacket);
        Buffer = Answer::NetPacket::getBuffer(inPacket);
        Answer::NetPacket::write(packet, Buffer, Size);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GameService::sendPacket(this, connid, packet);
        Answer::NetPacket::destroy(inPacket);
      }
    }
  }
}


#####################################
void __cdecl GameService::worldBroadcast(GameService *const this, Answer::NetPacket *inPacket)
{
  uint32_t Size; // eax
  uint32_t v3; // ebx
  char *Buffer; // rax
  uint32_t WOffset; // eax
  Answer::PackType Type; // eax
  uint16_t Proc; // ax
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > __x; // [rsp+20h] [rbp-30h] BYREF
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( inPacket )
  {
    for ( iter._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::begin(&this->m_mConn)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::end(&this->m_mConn)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator!=(&iter, &__x) )
        break;
      pConn = std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator->(&iter)->second;
      if ( pConn )
      {
        Size = Answer::NetPacket::getSize(inPacket);
        packet = Answer::TcpClient::popNetpacket(pConn, Size + 2);
        if ( packet )
        {
          Answer::NetPacket::writeInt16(packet, -1);
          v3 = Answer::NetPacket::getSize(inPacket);
          Buffer = Answer::NetPacket::getBuffer(inPacket);
          Answer::NetPacket::write(packet, Buffer, v3);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          Type = Answer::NetPacket::getType(inPacket);
          Answer::NetPacket::setType(packet, Type);
          Proc = Answer::NetPacket::getProc(inPacket);
          Answer::NetPacket::setProc(packet, Proc);
          Answer::TcpClient::sendPacket(pConn, packet);
        }
      }
    }
    Answer::NetPacket::destroy(inPacket);
  }
}


#####################################
void __cdecl GameService::broadcastActivityState(GameService *const this, int32_t nId, int8_t nState)
{
  uint32_t WOffset; // eax
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > __x; // [rsp+20h] [rbp-20h] BYREF
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+30h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  for ( iter._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::begin(&this->m_mConn)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::end(&this->m_mConn)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator!=(&iter, &__x) )
      break;
    pConn = std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator->(&iter)->second;
    if ( pConn )
    {
      packet = Answer::TcpClient::popNetpacket(pConn);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, nId);
        Answer::NetPacket::writeInt8(packet, nState);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Answer::NetPacket::setType(packet, Answer::PackType::PACK_DISPATCH);
        Answer::NetPacket::setProc(packet, 0x4EC4u);
        Answer::TcpClient::sendPacket(pConn, packet);
      }
    }
  }
}


#####################################
void __cdecl GameService::AddPlayer(GameService *const this, Player *player, int32_t reason)
{
  FamilyId_t FamilyId; // rbx
  int8_t ConnId; // r12
  CActivityManager *v5; // rax
  CharId_t Cid; // rcx
  int32_t LastLoginTime; // r13d
  CharId_t v9; // r12
  int8_t v10; // bl
  DBService *v11; // rax
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  __int64 __k; // [rsp+28h] [rbp-38h] BYREF
  std::string strName; // [rsp+30h] [rbp-30h] BYREF

  if ( player )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    __k = Player::getCid(player);
    *std::map<long,Player *>::operator[](&this->m_players, &__k) = player;
    Answer::MutexGuard::~MutexGuard(&lock);
    if ( reason != 3 )
    {
      FamilyId = Player::getFamilyId(player);
      ConnId = Player::getConnId(player);
      v5 = Answer::Singleton<CActivityManager>::instance();
      if ( FamilyId == CActivityManager::GetCityWarWinner(v5, ConnId) && Player::getFamilyPosition(player) == 3 )
      {
        Player::getName((const Player *const)&strName);
        Cid = Player::getCid(player);
        GameService::broadcastCityWarWinnerLogin(this, Cid, &strName);
        std::string::~string(&strName);
      }
    }
    GameService::sendSocialAddPlayer(this, player);
    Player::sendBasicInfo(player, reason);
    LastLoginTime = Player::getLastLoginTime(player);
    v9 = Player::getCid(player);
    v10 = Player::getConnId(player);
    v11 = Answer::Singleton<DBService>::instance();
    DBService::UpdateLoginTime(v11, v10, v9, LastLoginTime);
  }
}


#####################################
void __cdecl GameService::removePlayer(GameService *const this, Player *player)
{
  CharId_t Cid; // rax
  std::pair<const long int,Player*> *v3; // rax
  __int64 v4; // rbx
  std::pair<const long int,Player*> *v5; // rax
  CharId_t v6; // r13
  std::pair<const long int,Player*> *v7; // rax
  __int64 v8; // r12
  CharId_t v9; // rbx
  __int64 v10; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  __int64 __x; // [rsp+28h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > v14; // [rsp+30h] [rbp-30h] BYREF

  if ( player )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    __x = Player::getCid(player);
    it._M_node = std::map<long,Player *>::find(&this->m_players, &__x)._M_node;
    v14._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator==(&it, &v14) )
    {
      Cid = Player::getCid(player);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_INFO,
        "GameService::removePlayer player = %p, cid = %lld not in m_players\n",
        player,
        Cid);
    }
    else
    {
      v3 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
      v4 = (*((__int64 (__fastcall **)(Player *))v3->second->_vptr_Entity + 2))(v3->second);
      if ( v4 == (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 2))(player) )
      {
        std::map<long,Player *>::erase(&this->m_players, it);
        GameService::sendSocialRemovePlayer(this, player);
      }
      else
      {
        v5 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
        v6 = Player::getCid(v5->second);
        v7 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
        v8 = (*((__int64 (__fastcall **)(Player *))v7->second->_vptr_Entity + 2))(v7->second);
        v9 = Player::getCid(player);
        v10 = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 2))(player);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_INFO,
          "GameService::removePlayer player entityid = %lld, cid = %lld not equal with it->seconde entity id = %lld, cid =%lld\n",
          v10,
          v9,
          v8,
          v6);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
bool __cdecl GameService::SendChatValidate(
        GameService *const this,
        Player *Owner,
        int32_t Channel,
        Answer::NetPacket *inPacket)
{
  bool v4; // bl
  int8_t ConnId; // bl
  std::_Ios_Openmode v6; // eax
  std::_Ios_Openmode v7; // eax
  CharId_t v8; // rax
  uint32_t Size; // ebx
  char *Buffer; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  ChatValidate *v13; // rbx
  ChatValidate *v14; // rbx
  ChatValidate *v15; // rbx
  _BYTE v19[16]; // [rsp+20h] [rbp-300h] BYREF
  _BYTE v20[352]; // [rsp+30h] [rbp-2F0h] BYREF
  std::string Key; // [rsp+190h] [rbp-190h] BYREF
  std::string Md5String; // [rsp+1A0h] [rbp-180h] BYREF
  std::string Cid; // [rsp+1B0h] [rbp-170h] BYREF
  std::string Sid; // [rsp+1C0h] [rbp-160h] BYREF
  std::string Name; // [rsp+1D0h] [rbp-150h] BYREF
  std::string PassPort; // [rsp+1E0h] [rbp-140h] BYREF
  Answer::MutexGuard lockChat; // [rsp+1F0h] [rbp-130h] BYREF
  Answer::MutexGuard lock; // [rsp+200h] [rbp-120h] BYREF
  char v29; // [rsp+20Eh] [rbp-112h] BYREF
  char v30; // [rsp+20Fh] [rbp-111h] BYREF
  _BYTE v31[16]; // [rsp+210h] [rbp-110h] BYREF
  std::string v32; // [rsp+220h] [rbp-100h] BYREF
  std::string __rhs; // [rsp+230h] [rbp-F0h] BYREF
  std::string __lhs[2]; // [rsp+240h] [rbp-E0h] BYREF
  Answer::MD5 v35; // [rsp+250h] [rbp-D0h] BYREF
  Answer::NetPacket *packet; // [rsp+300h] [rbp-20h]
  int32_t SidInt; // [rsp+30Ch] [rbp-14h]

  if ( !inPacket || !Owner )
    return 0;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  Answer::MutexGuard::MutexGuard(&lockChat, &this->m_ChatValidateLock);
  ConnId = Player::getConnId(Owner);
  packet = GameService::popNetpacket(this, ConnId, Answer::PackType::PACK_DISPATCH, 0x2ED8u);
  if ( packet )
  {
    Player::GetPassport((Player *const)&PassPort);
    Player::getName((const Player *const)&Name);
    SidInt = Player::getSid(Owner);
    std::allocator<char>::allocator(&v29);
    std::string::string(&Sid, byte_8DA6C0, &v29);
    std::allocator<char>::~allocator(&v29);
    v6 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v19, (unsigned int)v6);
    std::ostream::operator<<(v20, (unsigned int)SidInt);
    std::operator>><char>(v19, &Sid);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v19);
    std::allocator<char>::allocator(&v30);
    std::string::string(&Cid, byte_8DA6C0, &v30);
    std::allocator<char>::~allocator(&v30);
    v7 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v19, (unsigned int)v7);
    v8 = Player::getCid(Owner);
    std::ostream::operator<<(v20, v8);
    std::operator>><char>(v19, &Cid);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v19);
    Player::GetPlatform((const Player *const)v31);
    std::operator+<char>((const char *)__lhs, &stru_8DF6CD);
    std::operator+<char>(&__rhs, __lhs);
    std::operator+<char>(&v32, &__rhs);
    std::operator+<char>(&Md5String, &v32);
    std::string::~string(&v32);
    std::string::~string(&__rhs);
    std::string::~string(__lhs);
    std::string::~string(v31);
    Answer::MD5::MD5((Answer::MD5 *const)v35.count);
    Answer::MD5::md5sum(&v35, (const std::string *const)v35.count);
    std::operator+<char>(&Key, (const std::string *const)&v35);
    std::string::~string(&v35);
    Answer::MD5::~MD5((Answer::MD5 *const)v35.count);
    ++*(_DWORD *)((char *)&loc_7A1530 + (_QWORD)this);
    Answer::NetPacket::writeInt8(packet, 1);
    Answer::NetPacket::writeInt32(packet, *(_DWORD *)((char *)&loc_7A1530 + (_QWORD)this));
    Answer::NetPacket::writeUTF8(packet, &Key);
    Size = Answer::NetPacket::getSize(inPacket);
    Buffer = Answer::NetPacket::getBuffer(inPacket);
    Answer::NetPacket::write(packet, Buffer, Size);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(Owner);
    LOBYTE(Size) = Player::getConnId(Owner);
    GameService::sendPacketTo(this, Size, GateIndex, packet);
    std::map<int,ChatValidate>::operator[](
      &this->m_ChatValidateMap,
      (const int *const)((char *)&loc_7A1530 + (_QWORD)this))->SendPacket = inPacket;
    v13 = std::map<int,ChatValidate>::operator[](
            &this->m_ChatValidateMap,
            (const int *const)((char *)&loc_7A1530 + (_QWORD)this));
    v13->CharId = Player::getCid(Owner);
    v14 = std::map<int,ChatValidate>::operator[](
            &this->m_ChatValidateMap,
            (const int *const)((char *)&loc_7A1530 + (_QWORD)this));
    v14->Time = Unit::getNow(Owner);
    std::map<int,ChatValidate>::operator[](
      &this->m_ChatValidateMap,
      (const int *const)((char *)&loc_7A1530 + (_QWORD)this))->Channel = Channel;
    v15 = std::map<int,ChatValidate>::operator[](
            &this->m_ChatValidateMap,
            (const int *const)((char *)&loc_7A1530 + (_QWORD)this));
    v15->SendCharId = Player::getCid(Owner);
    v4 = 1;
    std::string::~string(&Key);
    std::string::~string(&Md5String);
    std::string::~string(&Cid);
    std::string::~string(&Sid);
    std::string::~string(&Name);
    std::string::~string(&PassPort);
  }
  else
  {
    v4 = 0;
  }
  Answer::MutexGuard::~MutexGuard(&lockChat);
  Answer::MutexGuard::~MutexGuard(&lock);
  return v4;
}


#####################################
void __cdecl GameService::addPet(GameService *const this, CObjPet *pPet)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __k[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( pPet )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_petsLock);
    __k[0] = CObjPet::GetPetId(pPet);
    *std::map<long,CObjPet *>::operator[](&this->m_pets, __k) = pPet;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::removePet(GameService *const this, CObjPet *pPet)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __x[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( pPet )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_petsLock);
    __x[0] = CObjPet::GetPetId(pPet);
    std::map<long,CObjPet *>::erase(&this->m_pets, __x);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::addMonster(GameService *const this, Monster *monster)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __k[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( monster )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_monstersLock);
    __k[0] = (*((__int64 (__fastcall **)(Monster *))monster->_vptr_Entity + 2))(monster);
    *std::map<long,Monster *>::operator[](&this->m_monsters, __k) = monster;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::removeMonster(GameService *const this, Monster *monster)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __x[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( monster )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_monstersLock);
    __x[0] = (*((__int64 (__fastcall **)(Monster *))monster->_vptr_Entity + 2))(monster);
    std::map<long,Monster *>::erase(&this->m_monsters, __x);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::addTrailer(GameService *const this, Trailer *trailer)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __k[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( trailer )
  {
    Answer::MutexGuard::MutexGuard(&lock, (Answer::Mutex *const)((char *)&loc_7A13A8 + (_QWORD)this));
    __k[0] = (*((__int64 (__fastcall **)(Trailer *))trailer->_vptr_Entity + 2))(trailer);
    *std::map<long,Trailer *>::operator[](&this->m_trailers, __k) = trailer;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::removeTrailer(GameService *const this, Trailer *trailer)
{
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF
  __int64 __x[3]; // [rsp+18h] [rbp-18h] BYREF

  if ( trailer )
  {
    Answer::MutexGuard::MutexGuard(&lock, (Answer::Mutex *const)((char *)&loc_7A13A8 + (_QWORD)this));
    __x[0] = (*((__int64 (__fastcall **)(Trailer *))trailer->_vptr_Entity + 2))(trailer);
    std::map<long,Trailer *>::erase(&this->m_trailers, __x);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::saveAllPlayerToDB(GameService *const this)
{
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-30h] BYREF
  int32_t nNowTime; // [rsp+44h] [rbp-1Ch]
  Player *player; // [rsp+48h] [rbp-18h]

  nNowTime = Answer::DayTime::now();
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( it._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&it) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
      break;
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it)->second;
    if ( player )
      Player::onLogout(player, 1, 0);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::onUserPayed(GameService *const this, Answer::NetPacket *inPacket)
{
  std::pair<const long int,Player*> *v2; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  CharId_t Cid; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF

  if ( inPacket )
  {
    Cid = Answer::NetPacket::readInt64(inPacket);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    it._M_node = std::map<long,Player *>::find(&this->m_players, &Cid)._M_node;
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
    {
      if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it)->second )
      {
        v2 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
        Player::addNetPacket(v2->second, inPacket, 8u);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::onAddUser(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CPoolManager *v3; // rax
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  int16_t cgindex; // [rsp+2Eh] [rbp-32h]
  int64_t uid; // [rsp+30h] [rbp-30h]
  int32_t sid; // [rsp+3Ch] [rbp-24h]
  int8_t connid; // [rsp+43h] [rbp-1Dh]
  int32_t nIndex; // [rsp+44h] [rbp-1Ch]
  User *user; // [rsp+48h] [rbp-18h]

  if ( inPacket )
  {
    cgindex = Answer::NetPacket::readInt16(inPacket);
    uid = Answer::NetPacket::readInt64(inPacket);
    sid = Answer::NetPacket::readInt32(inPacket);
    connid = MutiConn<GameService>::GetId(pConn);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
    if ( (unsigned __int8)connid < 0x64u && cgindex > 0 && cgindex <= 9999 && uid > 0 && sid > 0 )
    {
      nIndex = getUserIndex(connid, cgindex);
      v3 = Answer::Singleton<CPoolManager>::instance();
      user = CPoolManager::pop<User>(v3);
      if ( user )
      {
        User::init(user, uid, sid);
        this->m_users[nIndex] = user;
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::qqToPlayer(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  TencentInfo info; // [rsp+20h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-30h] BYREF
  int16_t cgindex; // [rsp+50h] [rbp-20h]
  int8_t connid; // [rsp+53h] [rbp-1Dh]
  int32_t nIndex; // [rsp+54h] [rbp-1Ch]
  User *user; // [rsp+58h] [rbp-18h]

  if ( inPacket )
  {
    cgindex = Answer::NetPacket::readInt16(inPacket);
    connid = MutiConn<GameService>::GetId(pConn);
    TencentInfo::TencentInfo(&info);
    TencentInfo::UnPacketInfo(&info, inPacket);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
    nIndex = getUserIndex(connid, cgindex);
    user = this->m_users[cgindex];
    if ( user )
      User::SetTencentInfo(user, &info);
    Answer::MutexGuard::~MutexGuard(&lock);
    TencentInfo::~TencentInfo(&info);
  }
}


#####################################
void __cdecl GameService::onRemoveUser(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int8_t v3; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  CharId_t Cid; // rax
  void (__fastcall *v7)(Player *, _QWORD, _QWORD, _QWORD); // r12
  unsigned int Now; // eax
  CPoolManager *v9; // rax
  CPoolManager *v10; // rax
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  int16_t cgindex; // [rsp+28h] [rbp-38h]
  int8_t connid; // [rsp+2Bh] [rbp-35h]
  int32_t nIndex; // [rsp+2Ch] [rbp-34h]
  User *user; // [rsp+30h] [rbp-30h]
  Player *player; // [rsp+38h] [rbp-28h]
  int32_t reason; // [rsp+40h] [rbp-20h]
  int32_t param; // [rsp+44h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( inPacket )
  {
    cgindex = Answer::NetPacket::readInt16(inPacket);
    connid = MutiConn<GameService>::GetId(pConn);
    if ( (unsigned __int8)connid < 0x64u && cgindex > 0 && cgindex <= 9999 )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
      nIndex = getUserIndex(connid, cgindex);
      user = this->m_users[nIndex];
      if ( user )
      {
        player = User::getPlayer(user);
        if ( !player )
        {
LABEL_15:
          this->m_users[nIndex] = 0;
          User::reset(user);
          v10 = Answer::Singleton<CPoolManager>::instance();
          CPoolManager::push<User>(v10, user);
          goto LABEL_16;
        }
        Answer::NetPacket::readInt64(inPacket);
        reason = Answer::NetPacket::readInt32(inPacket);
        param = Answer::NetPacket::readInt32(inPacket);
        if ( !StaticObj::getMap(player) )
        {
          Cid = Player::getCid(player);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_INFO,
            "GameService::onRemoveUser remove player with m_pMap == NULL, cid = %lld\n",
            Cid);
          v7 = (void (__fastcall *)(Player *, _QWORD, _QWORD, _QWORD))*((_QWORD *)player->_vptr_Entity + 35);
          Now = Unit::getNow(player);
          v7(player, (unsigned int)reason, (unsigned int)param, Now);
          GameService::removePlayer(this, player);
          if ( Player::getGateIndex(player) > 0 )
          {
            Player::setGateIndex(player, -1);
            if ( (*((unsigned __int8 (__fastcall **)(Player *))player->_vptr_Entity + 34))(player) )
            {
              if ( player )
                (*((void (__fastcall **)(Player *))player->_vptr_Entity + 1))(player);
            }
            else
            {
              v9 = Answer::Singleton<CPoolManager>::instance();
              CPoolManager::push<Player>(v9, player);
            }
          }
          goto LABEL_15;
        }
        v3 = Player::getConnId(player);
        v4 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v4, v3, Answer::PackType::PACK_DISPATCH, 8u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, reason);
          Answer::NetPacket::writeInt32(packet, param);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          Player::addNetPacket(player, packet, 0);
          Answer::NetPacket::destroy(packet);
          goto LABEL_15;
        }
      }
LABEL_16:
      Answer::MutexGuard::~MutexGuard(&lock);
    }
  }
}


#####################################
void __cdecl GameService::onGMReloadItem(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax

  v3 = Answer::Singleton<CfgData>::instance();
  CfgData::reload(v3);
}


#####################################
void __cdecl GameService::onSocialNetpacket(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  __int16 cgindex; // [rsp+2Ch] [rbp-14h]
  int8_t connid; // [rsp+2Fh] [rbp-11h]

  if ( inPacket )
  {
    cgindex = Answer::NetPacket::readInt32(inPacket);
    connid = MutiConn<GameService>::GetId(pConn);
    if ( (unsigned __int8)connid < 0x64u && cgindex > 0 && cgindex <= 9999 )
      GameService::onGameNetpacket(this, connid, cgindex, inPacket);
  }
}


#####################################
void __cdecl GameService::onGateDisconnect(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  std::_Ios_Openmode v3; // eax
  unsigned int v4; // eax
  __int64 v5; // rax
  uint32_t WOffset; // eax
  _BYTE v7[512]; // [rsp+20h] [rbp-250h] BYREF
  char filename[56]; // [rsp+220h] [rbp-50h] BYREF
  Answer::NetPacket *packet; // [rsp+258h] [rbp-18h]

  if ( pConn && inPacket )
  {
    strcpy(filename, "./log/GameConnErr.txt");
    memset(&filename[22], 0, 28);
    v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_trunc);
    std::ofstream::basic_ofstream(v7, filename, (unsigned int)v3);
    v4 = Answer::DayTime::now();
    v5 = std::ostream::operator<<(v7, v4);
    std::ostream::operator<<(v5, &std::endl<char,std::char_traits<char>>);
    packet = GameService::popNetpacket(this, Answer::PackType::PACK_PROC, 0x4E2Eu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Answer::TcpClient::sendPacket(pConn, packet);
    }
    std::ofstream::~ofstream(v7);
  }
}


#####################################
void __cdecl GameService::onEnterGame(
        GameService *const this,
        int8_t connid,
        int16_t cgindex,
        Answer::NetPacket *inPacket)
{
  int v4; // ebx
  DBService *v5; // rax
  Answer::MutexGuard lock; // [rsp+20h] [rbp-40h] BYREF
  CharId_t cid; // [rsp+28h] [rbp-38h]
  int32_t line; // [rsp+30h] [rbp-30h]
  int32_t reason; // [rsp+34h] [rbp-2Ch]
  int64_t uid; // [rsp+38h] [rbp-28h]
  int32_t sid; // [rsp+40h] [rbp-20h]
  int32_t nIndex; // [rsp+44h] [rbp-1Ch]
  User *user; // [rsp+48h] [rbp-18h]

  cid = Answer::NetPacket::readInt64(inPacket);
  line = Answer::NetPacket::readInt32(inPacket);
  reason = Answer::NetPacket::readInt32(inPacket);
  printf("GameService::onEnterGame() cid=%lld, line=%d, reason=%d \n", cid, line, reason);
  uid = 0;
  sid = 0;
  nIndex = getUserIndex(connid, cgindex);
  Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
  user = this->m_users[nIndex];
  if ( user )
  {
    uid = User::getUid(user);
    sid = User::getSid(user);
    v4 = 1;
  }
  else
  {
    v4 = 0;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  if ( v4 )
  {
    v5 = Answer::Singleton<DBService>::instance();
    DBService::loadPlayer(v5, connid, cgindex, uid, sid, reason);
  }
}


#####################################
void __cdecl GameService::onEnterGameRobot(
        GameService *const this,
        int8_t connid,
        int16_t cgindex,
        Answer::NetPacket *inPacket)
{
  int v5; // ebx
  const char *v6; // rax
  Answer::Random *v7; // rax
  PlayerDBData dbData; // [rsp+20h] [rbp-B980h] BYREF
  int32_t id[4]; // [rsp+B940h] [rbp-60h]
  Answer::MutexGuard lock; // [rsp+B950h] [rbp-50h] BYREF
  Answer::NetPacket v13; // [rsp+B960h] [rbp-40h] BYREF

  if ( inPacket )
  {
    *(_QWORD *)&v13.m_wOffset = Answer::NetPacket::readInt32(inPacket);
    *(_DWORD *)&v13.m_proc = getUserIndex(connid, cgindex);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_userLock);
    *(_QWORD *)&v13.m_size = this->m_users[*(int *)&v13.m_proc];
    if ( *(_QWORD *)&v13.m_size && !User::getCid(*(const User *const *)&v13.m_size) )
    {
      User::setCid(*(User *const *)&v13.m_size, *(CharId_t *)&v13.m_wOffset);
      v5 = 1;
    }
    else
    {
      v5 = 0;
    }
    Answer::MutexGuard::~MutexGuard(&lock);
    if ( v5 )
    {
      if ( *(__int64 *)&v13.m_wOffset > 19088743 )
      {
        PlayerDBData::PlayerDBData(&dbData);
        Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.cid = *(_QWORD *)&v13.m_wOffset;
        Answer::NetPacket::readUTF8(&v13, (bool)inPacket);
        v6 = (const char *)std::string::c_str((std::string *)&v13);
        snprintf(dbData.chr.data.name, 0x1Eu, v6);
        std::string::~string(&v13);
        dbData.chr.data.sex = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.job = Answer::NetPacket::readInt32(inPacket);
        Answer::NetPacket::readInt32(inPacket);
        Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.level = 60;
        dbData.chr.data.mapid = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.x = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.y = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.hp = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.mp = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.kun_li = Answer::NetPacket::readInt32(inPacket);
        dbData.chr.data.head = Answer::NetPacket::readInt32(inPacket);
        id[0] = 10001;
        id[1] = 10006;
        id[2] = 10011;
        v7 = Answer::Singleton<Answer::Random>::instance();
        HIWORD(v13.m_refCount) = id[Answer::Random::generate(v7, 0, 0)];
        GameService::onPlayerLoaded(this, &dbData, 0, 0);
        PlayerDBData::~PlayerDBData(&dbData);
      }
    }
  }
}


#####################################
void __cdecl GameService::onGameNetpacket(
        GameService *const this,
        int8_t connid,
        int16_t cgindex,
        Answer::NetPacket *inPacket)
{
  Player *player; // [rsp+28h] [rbp-18h]

  if ( inPacket )
  {
    player = GameService::getUserPlayer(this, connid, cgindex);
    if ( player )
      Player::addNetPacket(player, inPacket, 4u);
  }
}


#####################################
void __cdecl GameService::OnDBNetPacket(
        GameService *const this,
        int8_t connid,
        int16_t cgindex,
        Answer::NetPacket *inPacket)
{
  Player *player; // [rsp+28h] [rbp-18h]

  if ( inPacket )
  {
    player = GameService::getUserPlayer(this, connid, cgindex);
    if ( player )
      Player::addNetPacket(player, inPacket, 2u);
  }
}


#####################################
void __cdecl GameService::sendSocialAddPlayer(GameService *const this, Player *player)
{
  int8_t ConnId; // bl
  int32_t GateIndex; // edx
  CharId_t Cid; // rdx
  int64_t Uid; // rdx
  int32_t Sid; // edx
  int8_t GMLevel; // dl
  uint32_t WOffset; // edx
  int8_t v9; // cl
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    packet = GameService::popNetpacket(this, ConnId, Answer::PackType::PACK_PROC, 0x4E34u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(player);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      Uid = Player::getUid(player);
      Answer::NetPacket::writeInt64(packet, Uid);
      Sid = Player::getSid(player);
      Answer::NetPacket::writeInt32(packet, Sid);
      Answer::NetPacket::writeInt32(packet, this->m_line);
      GMLevel = Player::GetGMLevel(player);
      Answer::NetPacket::writeInt8(packet, GMLevel);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v9 = Player::getConnId(player);
      GameService::sendPacket(this, v9, packet);
    }
  }
}


#####################################
void __cdecl GameService::sendSocialRemovePlayer(GameService *const this, Player *player)
{
  int8_t ConnId; // bl
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  int8_t v5; // cl
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    packet = GameService::popNetpacket(this, ConnId, Answer::PackType::PACK_PROC, 0x4E35u);
    if ( packet )
    {
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Player::getConnId(player);
      GameService::sendPacket(this, v5, packet);
    }
  }
}


#####################################
void __cdecl GameService::onSocialUpdatePetRank(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CPetManager *v3; // rax

  v3 = Answer::Singleton<CPetManager>::instance();
  CPetManager::OnUpdatePetRank(v3, inPacket);
}


#####################################
void __cdecl GameService::onSocialUpdateFamilyInfo(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  FamilyManager *v3; // rax

  v3 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::OnUpdateFamilyInfo(v3, inPacket);
}


#####################################
void __cdecl GameService::onSocialInitPetRank(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CPetManager *v3; // rax

  v3 = Answer::Singleton<CPetManager>::instance();
  CPetManager::OnInitPetRank(v3, inPacket);
}


#####################################
void __cdecl GameService::onSocialInitRankMirror(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CRankMirror *v3; // rax

  v3 = Answer::Singleton<CRankMirror>::instance();
  CRankMirror::OnSocialUpdateRank(v3, inPacket);
}


#####################################
void __cdecl GameService::onSocialUpdateRankMirror(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  CRankMirror *v3; // rax

  v3 = Answer::Singleton<CRankMirror>::instance();
  CRankMirror::OnSocialUpdateRank(v3, inPacket);
}


#####################################
void __cdecl GameService::onSocialQueryPlayerInfo(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int16_t v3; // bx
  int8_t Id; // al
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-40h] BYREF
  CharId_t cid; // [rsp+38h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-30h] BYREF
  int16_t cgindex; // [rsp+56h] [rbp-1Ah]
  Player *pPlayer; // [rsp+58h] [rbp-18h]

  if ( pConn && inPacket )
  {
    cid = Answer::NetPacket::readInt64(inPacket);
    cgindex = Answer::NetPacket::readInt16(inPacket);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    iter._M_node = std::map<long,Player *>::find(&this->m_players, &cid)._M_node;
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
    {
      pPlayer = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
      if ( pPlayer )
      {
        v3 = cgindex;
        Id = MutiConn<GameService>::GetId(pConn);
        Player::SendOtherPlayerInfo(pPlayer, Id, v3);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::onSocialCreateTeamDungeon(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  MapManager *v3; // rax
  int32_t RunnerId; // ebx
  MapManager *v5; // rax
  CharId_t memberId; // [rsp+38h] [rbp-48h] BYREF
  CharIdList memberList; // [rsp+40h] [rbp-40h] BYREF
  int32_t nDungeonId; // [rsp+5Ch] [rbp-24h]
  Dungeon *pDungeon; // [rsp+60h] [rbp-20h]
  int32_t i; // [rsp+6Ch] [rbp-14h]

  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<MapManager>::instance();
  pDungeon = MapManager::NewDungeon(v3, nDungeonId);
  if ( pDungeon )
  {
    std::list<long>::list(&memberList);
    for ( i = 0; i <= 3; ++i )
    {
      memberId = Answer::NetPacket::readInt64(inPacket);
      if ( memberId > 0 )
        std::list<long>::push_back(&memberList, &memberId);
    }
    Dungeon::InitTeamMember(pDungeon, &memberList);
    Dungeon::start(pDungeon, 0);
    RunnerId = Map::GetRunnerId(pDungeon);
    v5 = Answer::Singleton<MapManager>::instance();
    MapManager::PostMsg(v5, RunnerId, GameMsgCode::GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
    std::list<long>::~list(&memberList);
  }
}


#####################################
void __cdecl GameService::onSocialSendSystemMail(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int32_t v3; // r12d
  DBService *v4; // rax
  DBService *v5; // rax
  MemChrBag item; // [rsp+30h] [rbp-50h] BYREF
  std::string mailParam; // [rsp+50h] [rbp-30h] BYREF
  CharId_t nReceiver; // [rsp+60h] [rbp-20h]
  int32_t nMailId; // [rsp+68h] [rbp-18h]
  int32_t nReason; // [rsp+6Ch] [rbp-14h]

  if ( pConn && inPacket )
  {
    nReceiver = Answer::NetPacket::readInt64(inPacket);
    nMailId = Answer::NetPacket::readInt32(inPacket);
    nReason = Answer::NetPacket::readInt32(inPacket);
    *(&item.endTime + 1) = 0;
    item.itemId = Answer::NetPacket::readInt32(inPacket);
    *(_DWORD *)&item.itemClass = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    item.itemCount = Answer::NetPacket::readInt32(inPacket);
    item.srcId = Answer::NetPacket::readInt64(inPacket);
    *(_DWORD *)&item.bind = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    item.endTime = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&mailParam, (bool)inPacket);
    if ( item.itemId <= 0 || item.itemCount <= 0 )
    {
      v5 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v5, 0, nReceiver, nMailId, &mailParam, 0);
    }
    else
    {
      v3 = nReason;
      v4 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v4, 0, nReceiver, nMailId, &item, (ITEM_CHANGE_REASON)v3, &mailParam, 0);
    }
    std::string::~string(&mailParam);
  }
}


#####################################
void __cdecl GameService::onSocialSendSystemMail2(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  MemChrBag *v3; // rbx
  MemChrBag *v4; // rbx
  MemChrBag *v5; // rbx
  int32_t v6; // r12d
  DBService *v7; // rax
  DBService *v8; // rax
  MemChrBag __x; // [rsp+0h] [rbp-D0h]
  MemChrBagVector vItem; // [rsp+40h] [rbp-90h] BYREF
  MemChrBag v12; // [rsp+60h] [rbp-70h]
  std::string Param; // [rsp+80h] [rbp-50h] BYREF
  char v14; // [rsp+8Fh] [rbp-41h] BYREF
  std::string v15; // [rsp+90h] [rbp-40h] BYREF
  char v16; // [rsp+A7h] [rbp-29h] BYREF
  CharId_t nReceiver; // [rsp+A8h] [rbp-28h]
  int32_t nMailId; // [rsp+B0h] [rbp-20h]
  int32_t nReason; // [rsp+B4h] [rbp-1Ch]
  int32_t nSize; // [rsp+B8h] [rbp-18h]
  int32_t i; // [rsp+BCh] [rbp-14h]

  if ( pConn && inPacket )
  {
    nReceiver = Answer::NetPacket::readInt64(inPacket);
    nMailId = Answer::NetPacket::readInt32(inPacket);
    nReason = Answer::NetPacket::readInt32(inPacket);
    nSize = Answer::NetPacket::readInt32(inPacket);
    if ( nSize <= 0 )
    {
      std::allocator<char>::allocator(&v16);
      std::string::string(&v15, byte_8DA6C0, &v16);
      v8 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v8, 0, nReceiver, nMailId, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(&v16);
    }
    else
    {
      std::vector<MemChrBag>::vector(&vItem);
      v12.itemId = 0;
      v12.itemClass = 0;
      v12.itemCount = 0;
      v12.bind = 0;
      v12.endTime = 0;
      v12.srcId = 0;
      *(_OWORD *)&__x.itemId = *(_OWORD *)&v12.itemId;
      *(_OWORD *)&__x.endTime = *(unsigned __int64 *)&v12.endTime;
      std::vector<MemChrBag>::resize(&vItem, nSize, __x);
      for ( i = 0; i < nSize; ++i )
      {
        v3 = std::vector<MemChrBag>::operator[](&vItem, i);
        v3->itemClass = Answer::NetPacket::readInt8(inPacket);
        v4 = std::vector<MemChrBag>::operator[](&vItem, i);
        v4->itemId = Answer::NetPacket::readInt32(inPacket);
        v5 = std::vector<MemChrBag>::operator[](&vItem, i);
        v5->itemCount = Answer::NetPacket::readInt32(inPacket);
        std::vector<MemChrBag>::operator[](&vItem, i)->srcId = 0;
        std::vector<MemChrBag>::operator[](&vItem, i)->bind = 0;
        std::vector<MemChrBag>::operator[](&vItem, i)->endTime = 0;
      }
      std::allocator<char>::allocator(&v14);
      std::string::string(&Param, byte_8DA6C0, &v14);
      v6 = nReason;
      v7 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v7, 0, nReceiver, nMailId, &vItem, (ITEM_CHANGE_REASON)v6, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v14);
      std::vector<MemChrBag>::~vector(&vItem);
    }
  }
}


#####################################
void __cdecl GameService::onSetWorldLevel(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx

  if ( pConn )
  {
    if ( inPacket )
    {
      Int32 = Answer::NetPacket::readInt32(inPacket);
      GameService::SetWorldLevel(this, Int32);
    }
  }
}


#####################################
int32_t __cdecl GameService::GetDropTimes(GameService *const this, int32_t nGroupId)
{
  int32_t second; // ebx
  int32_t nGroupIda; // [rsp+4h] [rbp-4Ch] BYREF
  GameService *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nGroupIda = nGroupId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_dropControlLock);
  iter._M_node = std::map<int,int>::find((std::map<int,int> *const)((char *)&loc_7A13D0 + (_QWORD)this), &nGroupIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_dropControl)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
  else
    second = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return second;
}


#####################################
void __cdecl GameService::AddDropTimes(GameService *const this, int32_t nGroupId, int32_t nAddTimes)
{
  std::pair<const int,int> *v3; // rax
  GameService *v4; // rax
  CTimer *v5; // rax
  Answer::DBPool *v6; // rax
  int32_t v7; // ebx
  DBService *v8; // rax
  int32_t nGroupIda; // [rsp+24h] [rbp-107Ch] BYREF
  GameService *thisa; // [rsp+28h] [rbp-1078h]
  char szSQL[4096]; // [rsp+30h] [rbp-1070h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1030h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+1060h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+1070h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+1080h] [rbp-20h] BYREF
  int32_t nTimes; // [rsp+1088h] [rbp-18h]
  int32_t nowTime; // [rsp+108Ch] [rbp-14h]

  thisa = this;
  nGroupIda = nGroupId;
  nTimes = nAddTimes;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_dropControlLock);
  iter._M_node = std::map<int,int>::find((std::map<int,int> *const)((char *)&loc_7A13D0 + (_QWORD)this), &nGroupIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_dropControl)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter);
    v3->second += nAddTimes;
    nTimes = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
  }
  else
  {
    *std::map<int,int>::operator[]((std::map<int,int> *const)((char *)&loc_7A13D0 + (_QWORD)thisa), &nGroupIda) = nAddTimes;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
  {
    v5 = Answer::Singleton<CTimer>::instance();
    nowTime = CTimer::GetNow(v5);
    v6 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v6);
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(
      szSQL,
      0xFFFu,
      "INSERT INTO `cross_drop_control` ( `id`, `group_id`, `times`, `time`) VALUES (%d,%d,%d,%d)  ON DUPLICATE KEY UPDAT"
      "E `times`=%d,`time`=%d",
      thisa->m_id,
      nGroupIda,
      nTimes,
      nowTime,
      nTimes,
      nowTime);
    Answer::MySqlDBGuard::excute(&db, szSQL);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
  else
  {
    v7 = nGroupIda;
    v8 = Answer::Singleton<DBService>::instance();
    DBService::SaveDropTimes(v8, v7, nTimes);
  }
}


#####################################
void __cdecl GameService::UpdateDropTimes(GameService *const this, int32_t nGroupId, int32_t nTimes)
{
  GameService *v3; // rax
  int32_t nGroupIda; // [rsp+4h] [rbp-2Ch] BYREF
  GameService *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  nGroupIda = nGroupId;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) != 9 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_dropControlLock);
    *std::map<int,int>::operator[]((std::map<int,int> *const)((char *)&loc_7A13D0 + (_QWORD)thisa), &nGroupIda) = nTimes;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::ResetDropTimes(GameService *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  DBService *v3; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1050h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+1040h] [rbp-20h] BYREF

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "DELETE FROM `cross_drop_control` WHERE `id`=%d", this->m_id);
    Answer::MySqlDBGuard::excute(&db, szSQL);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
  else
  {
    v3 = Answer::Singleton<DBService>::instance();
    DBService::ClearDropTimes(v3);
  }
  Answer::MutexGuard::MutexGuard(&lock, &this->m_dropControlLock);
  std::map<int,int>::clear(&this->m_dropControl);
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::InitDropTimes(GameService *const this)
{
  Answer::DBPool *v1; // rax
  GameService *v2; // rax
  int32_t v3; // eax
  int v4; // eax
  int32_t v5; // eax
  int v6; // eax
  Answer::MySqlQuery *v7; // rax
  int *v8; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1060h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-60h] BYREF
  int32_t nGroupId; // [rsp+103Ch] [rbp-34h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-30h] BYREF
  int32_t nTimes; // [rsp+105Ch] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  memset(szSQL, 0, sizeof(szSQL));
  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
  {
    v3 = Answer::DayTime::now();
    v4 = Answer::DayTime::dayzero(v3);
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `cross_drop_control` WHERE `id`=%d AND `time`>=%d", this->m_id, v4);
  }
  else
  {
    v5 = Answer::DayTime::now();
    v6 = Answer::DayTime::dayzero(v5);
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `mem_drop_control` WHERE `time`>=%d", v6);
  }
  v7 = Answer::MySqlDBGuard::query(&db, szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v7);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    nGroupId = Answer::MySqlQuery::getIntValue(&result, "group_id", 0);
    nTimes = Answer::MySqlQuery::getIntValue(&result, "times", 0);
    v8 = std::map<int,int>::operator[]((std::map<int,int> *const)((char *)&loc_7A13D0 + (_QWORD)this), &nGroupId);
    *v8 = nTimes;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl GameService::TeamDungeonEnterDungeon(
        GameService *const this,
        Dungeon *pDungeon,
        const CharIdList *const lst)
{
  int32_t DungeonId; // ebx
  CfgData *v4; // rax
  const __int64 *v5; // rax
  int32_t DungeonGroupId; // eax
  int32_t v7; // ebx
  int32_t v8; // eax
  int32_t v9; // ebx
  CHuoYueDu *PlayerHuoYueDu; // rax
  int64_t v11; // r13
  int16_t GateIndex; // r12
  GameService *v13; // rax
  void (__fastcall *v14)(Dungeon *, Player *, __int64, _QWORD); // r13
  unsigned int y; // r12d
  __int64 x; // rdx
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+20h] [rbp-80h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-70h] BYREF
  std::_List_const_iterator<long int> eiter; // [rsp+40h] [rbp-60h] BYREF
  std::_List_const_iterator<long int> iter; // [rsp+50h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+60h] [rbp-40h] BYREF
  CfgDungeon *pCfgDungeon; // [rsp+68h] [rbp-38h]
  Player *pPlayer; // [rsp+70h] [rbp-30h]
  Map *pMap; // [rsp+78h] [rbp-28h]

  DungeonId = Dungeon::getDungeonId(pDungeon);
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v4, DungeonId);
  if ( pDungeon && pCfgDungeon )
  {
    iter._M_node = std::list<long>::begin(lst)._M_node;
    eiter._M_node = std::list<long>::end(lst)._M_node;
    while ( std::_List_const_iterator<long>::operator!=(&iter, &eiter) )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
      v5 = std::_List_const_iterator<long>::operator*(&iter);
      it._M_node = std::map<long,Player *>::find(&this->m_players, v5)._M_node;
      __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
      {
        pPlayer = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it)->second;
        if ( pPlayer )
        {
          Player::setOldPosition(pPlayer);
          pMap = StaticObj::getMap(pPlayer);
          if ( pMap )
          {
            Player::broadcastLeave(pPlayer);
            (*((void (__fastcall **)(Map *, Player *, _QWORD))pMap->_vptr_Map + 16))(pMap, pPlayer, 0);
          }
          DungeonGroupId = Dungeon::getDungeonGroupId(pDungeon);
          v7 = Player::getRecord(pPlayer, DungeonGroupId) + 1;
          v8 = Dungeon::getDungeonGroupId(pDungeon);
          Player::updateRecord(pPlayer, v8, v7);
          v9 = Dungeon::getDungeonGroupId(pDungeon);
          PlayerHuoYueDu = Player::GetPlayerHuoYueDu(pPlayer);
          CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 2, v9, 0);
          v11 = Dungeon::getDungeonId(pDungeon);
          GateIndex = Player::getGateIndex(pPlayer);
          LOBYTE(v9) = Player::getConnId(pPlayer);
          v13 = Answer::Singleton<GameService>::instance();
          GameService::replySuccess(v13, v9, GateIndex, 0x12u, v11);
          v14 = (void (__fastcall *)(Dungeon *, Player *, __int64, _QWORD))*((_QWORD *)pDungeon->_vptr_Map + 15);
          y = Dungeon::GetCfgDungeon(pDungeon)->y;
          x = (unsigned int)Dungeon::GetCfgDungeon(pDungeon)->x;
          v14(pDungeon, pPlayer, x, y);
        }
      }
      Answer::MutexGuard::~MutexGuard(&lock);
      std::_List_const_iterator<long>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl GameService::OnUpdateMail(GameService *const this, Answer::NetPacket *inPacket)
{
  std::pair<const long int,Player*> *v2; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  CharId_t Cid; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF

  if ( inPacket )
  {
    Cid = Answer::NetPacket::readInt64(inPacket);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    it._M_node = std::map<long,Player *>::find(&this->m_players, &Cid)._M_node;
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
    {
      if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it)->second )
      {
        v2 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
        Player::addNetPacket(v2->second, inPacket, 8u);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::requestSocialData(GameService *const this)
{
  uint32_t WOffset; // eax
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > __x; // [rsp+20h] [rbp-20h] BYREF
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+30h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  for ( iter._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::begin(&this->m_mConn)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::end(&this->m_mConn)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator!=(&iter, &__x) )
      break;
    pConn = std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator->(&iter)->second;
    if ( pConn )
    {
      packet = Answer::TcpClient::popNetpacket(pConn);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_line);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Answer::NetPacket::setProc(packet, 0x4E42u);
        Answer::NetPacket::setType(packet, Answer::PackType::PACK_DISPATCH);
        Answer::TcpClient::sendPacket(pConn, packet);
      }
    }
  }
}


#####################################
void __cdecl GameService::OnReceiveDaTiRank(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  int8_t v4; // bl
  DBService *v5; // rax
  GameService *v6; // rax
  int v7; // ebx
  uint32_t WOffset; // eax
  int8_t v9; // bl
  DBService *v10; // rax
  int8_t v11; // bl
  DBService *v12; // rax
  int8_t v13; // bl
  DBService *v14; // rax
  int8_t v15; // bl
  DBService *v16; // rax
  int8_t v17; // bl
  DBService *v18; // rax
  int8_t v19; // bl
  CFestivalDoubleEleven *v20; // rax
  CTimer *v21; // rax
  int8_t v22; // bl
  DBService *v23; // rax
  LogActivity logActivity; // [rsp+20h] [rbp-C0h] BYREF
  std::string Name; // [rsp+40h] [rbp-A0h] BYREF
  std::string Param; // [rsp+50h] [rbp-90h] BYREF
  char v28; // [rsp+5Fh] [rbp-81h] BYREF
  std::string v29; // [rsp+60h] [rbp-80h] BYREF
  char v30; // [rsp+6Fh] [rbp-71h] BYREF
  std::string v31; // [rsp+70h] [rbp-70h] BYREF
  char v32; // [rsp+7Fh] [rbp-61h] BYREF
  std::string v33; // [rsp+80h] [rbp-60h] BYREF
  char v34; // [rsp+8Fh] [rbp-51h] BYREF
  std::string v35; // [rsp+90h] [rbp-50h] BYREF
  char v36; // [rsp+9Fh] [rbp-41h] BYREF
  std::string v37; // [rsp+A0h] [rbp-40h] BYREF
  char v38; // [rsp+AFh] [rbp-31h] BYREF
  int32_t nSize; // [rsp+B0h] [rbp-30h]
  int32_t i; // [rsp+B4h] [rbp-2Ch]
  CharId_t CharId; // [rsp+B8h] [rbp-28h]
  int32_t Index; // [rsp+C0h] [rbp-20h]
  int8_t connid; // [rsp+C7h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+C8h] [rbp-18h]

  if ( pConn && inPacket )
  {
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; ; ++i )
    {
      if ( i >= nSize )
        return;
      CharId = Answer::NetPacket::readInt64(inPacket);
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Name, (bool)inPacket);
      Index = Answer::NetPacket::readInt32(inPacket);
      v3 = Answer::Singleton<GameService>::instance();
      connid = GameService::GetConnId(v3, CharId);
      switch ( Index )
      {
        case 1:
          std::allocator<char>::allocator(&v28);
          std::string::string(&Param, byte_8DA6C0, &v28);
          v4 = connid;
          v5 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v5, v4, CharId, 6203, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v28);
          v6 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
          {
            v7 = 0;
            goto LABEL_18;
          }
          Answer::NetPacket::writeInt32(packet, 28);
          Answer::NetPacket::writeUTF8(packet, &Name);
          Answer::NetPacket::writeInt64(packet, CharId);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GameService::worldBroadcast(this, 0, packet);
          break;
        case 2:
          std::allocator<char>::allocator(&v30);
          std::string::string(&v29, byte_8DA6C0, &v30);
          v9 = connid;
          v10 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v10, v9, CharId, 6204, &v29, 0);
          std::string::~string(&v29);
          std::allocator<char>::~allocator(&v30);
          break;
        case 3:
          std::allocator<char>::allocator(&v32);
          std::string::string(&v31, byte_8DA6C0, &v32);
          v11 = connid;
          v12 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v12, v11, CharId, 6205, &v31, 0);
          std::string::~string(&v31);
          std::allocator<char>::~allocator(&v32);
          break;
        default:
          if ( Index > 10 )
          {
            if ( Index > 20 )
            {
              std::allocator<char>::allocator(&v38);
              std::string::string(&v37, byte_8DA6C0, &v38);
              v17 = connid;
              v18 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v18, v17, CharId, 6206, &v37, 0);
              std::string::~string(&v37);
              std::allocator<char>::~allocator(&v38);
            }
            else
            {
              std::allocator<char>::allocator(&v36);
              std::string::string(&v35, byte_8DA6C0, &v36);
              v15 = connid;
              v16 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v16, v15, CharId, 6269, &v35, 0);
              std::string::~string(&v35);
              std::allocator<char>::~allocator(&v36);
            }
          }
          else
          {
            std::allocator<char>::allocator(&v34);
            std::string::string(&v33, byte_8DA6C0, &v34);
            v13 = connid;
            v14 = Answer::Singleton<DBService>::instance();
            DBService::OnSendSysMail(v14, v13, CharId, 6268, &v33, 0);
            std::string::~string(&v33);
            std::allocator<char>::~allocator(&v34);
          }
          break;
      }
      v19 = connid;
      v20 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      CFestivalDoubleEleven::SendDaTiReward(v20, v19, Index, CharId);
      *(_QWORD *)&logActivity.actid = 0x500000000LL;
      *(_QWORD *)&logActivity.time = 0;
      logActivity.param = 0;
      logActivity.cid = CharId;
      v21 = Answer::Singleton<CTimer>::instance();
      logActivity.time = CTimer::GetNow(v21);
      logActivity.param = Index;
      v22 = connid;
      v23 = Answer::Singleton<DBService>::instance();
      DBService::InsertActivityLog(v23, v22, &logActivity);
      v7 = 1;
LABEL_18:
      std::string::~string(&Name);
      if ( !v7 )
        return;
    }
  }
}


#####################################
void __cdecl GameService::OnReceiveDaTiResult(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int8_t v3; // bl
  std::pair<const long int,Player*> *v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > it; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  int64_t Cid; // [rsp+38h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF
  int32_t Index; // [rsp+48h] [rbp-18h]
  int8_t Result; // [rsp+4Fh] [rbp-11h]

  if ( pConn && inPacket )
  {
    Cid = Answer::NetPacket::readInt64(inPacket);
    Index = Answer::NetPacket::readInt32(inPacket);
    Result = Answer::NetPacket::readInt8(inPacket);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
    it._M_node = std::map<long,Player *>::find(&this->m_players, &Cid)._M_node;
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&it, &__x) )
    {
      v3 = Result;
      v4 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&it);
      Player::AddDaTiExp(v4->second, Index, v3);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl GameService::SendServerDiffToGlobal(GameService *const this)
{
  CfgData *v1; // rax
  int32_t ServerDiffDay; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+10h] [rbp-10h]

  packet = GameService::popNetpacket(this, 0, Answer::PackType::PACK_PROC, 0x4E49u);
  if ( packet )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    ServerDiffDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
    Answer::NetPacket::writeInt32(packet, ServerDiffDay);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GameService::sendPacket(this, 0, packet);
  }
}


#####################################
void __cdecl GameService::UpdateCityWarTitle(GameService *const this, FamilyId_t OldFamilyId, FamilyId_t NewFamilyId)
{
  std::pair<const long int,Player*> *v3; // rax
  std::pair<const long int,Player*> *v4; // rax
  CExtCharTitle *CharTitle; // rax
  std::pair<const long int,Player*> *v6; // rax
  std::pair<const long int,Player*> *v7; // rax
  int32_t FamilyPosition; // ebx
  std::pair<const long int,Player*> *v9; // rax
  CExtCharTitle *v10; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
    if ( Player::getFamilyId(v3->second) == OldFamilyId )
    {
      v4 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
      CharTitle = Player::GetCharTitle(v4->second);
      CExtCharTitle::RemoveTitle(CharTitle, 1, 0);
    }
    v6 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
    if ( Player::getFamilyId(v6->second) == NewFamilyId )
    {
      v7 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
      FamilyPosition = Player::getFamilyPosition(v7->second);
      v9 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
      v10 = Player::GetCharTitle(v9->second);
      CExtCharTitle::CheckAddTitle(v10, 1, FamilyPosition);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::UpdateCityActState(GameService *const this, FamilyId_t FamilyId, int8_t ActState)
{
  std::pair<const long int,Player*> *v3; // rax
  std::pair<const long int,Player*> *v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
    if ( Player::getFamilyId(v3->second) == FamilyId )
    {
      v4 = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter);
      Player::SetActState(v4->second, ActState);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::SetFamilyMemberNeedSync(GameService *const this, FamilyId_t nFamilyId)
{
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player && Player::getFamilyId(player) == nFamilyId )
      Player::SetNeedSyncAround(player);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::GetFamilyMemberInMap(
        GameService *const this,
        FamilyId_t nFamilyId,
        int32_t nMapId,
        PlayerList *const pList,
        CharIdList *const farList,
        int32_t nLevel)
{
  Player *player; // [rsp+38h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+40h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > v14; // [rsp+60h] [rbp-20h] BYREF
  __int64 __x[3]; // [rsp+68h] [rbp-18h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    v14._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &v14) )
      break;
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player
      && Player::getFamilyId(player) == nFamilyId
      && (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) > nLevel )
    {
      if ( StaticObj::getMapId(player) == nMapId )
      {
        std::list<Player *>::push_back(pList, &player);
      }
      else
      {
        __x[0] = Player::getCid(player);
        std::list<long>::push_back(farList, __x);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::onUpdateActivityState(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int8_t Int8; // bl
  CActivityManager *v4; // rax
  int32_t nId; // [rsp+28h] [rbp-18h]

  if ( pConn )
  {
    if ( inPacket )
    {
      nId = Answer::NetPacket::readInt32(inPacket);
      Int8 = Answer::NetPacket::readInt8(inPacket);
      v4 = Answer::Singleton<CActivityManager>::instance();
      CActivityManager::UpdateActivityState(v4, nId, Int8);
    }
  }
}


#####################################
void __cdecl GameService::OnSocialCityMasterBanChat(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int *v3; // rax
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  CharId_t nCharId; // [rsp+30h] [rbp-20h] BYREF
  int32_t nEndTime; // [rsp+3Ch] [rbp-14h]

  if ( pConn )
  {
    if ( inPacket )
    {
      nCharId = Answer::NetPacket::readInt64(inPacket);
      nEndTime = Answer::NetPacket::readInt32(inPacket);
      Answer::MutexGuard::MutexGuard(&lock, &this->m_cityMasterBanChatLock);
      v3 = std::map<long,int>::operator[](&this->m_mCityMasterBanChatMap, &nCharId);
      *v3 = nEndTime;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
  }
}


#####################################
int32_t __cdecl GameService::GetCityMasterBanChatTime(GameService *const this, CharId_t nCharId)
{
  int32_t v2; // ebx
  CharId_t nCharIda; // [rsp+0h] [rbp-30h] BYREF
  GameService *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_cityMasterBanChatLock);
  v2 = *std::map<long,int>::operator[](&this->m_mCityMasterBanChatMap, &nCharIda);
  Answer::MutexGuard::~MutexGuard(&lock);
  return v2;
}


#####################################
void __cdecl GameService::KickUser(GameService *const this, CharId_t cid, int32_t opWay)
{
  int8_t ConnId; // al
  int64_t Uid; // rax
  int32_t Sid; // eax
  uint32_t WOffset; // eax
  int8_t v7; // al
  CharId_t cida; // [rsp+10h] [rbp-60h] BYREF
  GameService *thisa; // [rsp+18h] [rbp-58h]
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-30h] BYREF
  Player *player; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  thisa = this;
  cida = cid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &cida)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator==(&iter, &__x) )
  {
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      ConnId = Player::getConnId(player);
      packet = GameService::popNetpacket(thisa, ConnId, Answer::PackType::PACK_PROC, 0x4E2Au);
      if ( packet )
      {
        Uid = Player::getUid(player);
        Answer::NetPacket::writeInt64(packet, Uid);
        Sid = Player::getSid(player);
        Answer::NetPacket::writeInt32(packet, Sid);
        Answer::NetPacket::writeInt32(packet, opWay);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v7 = Player::getConnId(player);
        GameService::sendPacket(thisa, v7, packet);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::KickAll(GameService *const this, int32_t opWay)
{
  uint32_t WOffset; // eax
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,GameService::ConnType*> > __x; // [rsp+20h] [rbp-20h] BYREF
  std::map<signed char,GameService::ConnType*>::ConnType *pConn; // [rsp+30h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  for ( iter._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::begin(&this->m_mConn)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,MutiConn<GameService> *,std::less<signed char>,std::allocator<std::pair<signed char const,MutiConn<GameService> *>>>::end(&this->m_mConn)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator!=(&iter, &__x) )
      break;
    pConn = std::_Rb_tree_iterator<std::pair<signed char const,MutiConn<GameService> *>>::operator->(&iter)->second;
    if ( pConn )
    {
      packet = Answer::TcpClient::popNetpacket(pConn);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, opWay);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Answer::NetPacket::setType(packet, Answer::PackType::PACK_PROC);
        Answer::NetPacket::setProc(packet, 0x4E2Bu);
        Answer::TcpClient::sendPacket(pConn, packet);
      }
    }
  }
}


#####################################
void __cdecl GameService::onCheckTitle(GameService *const this, CharId_t nCharId, int8_t nType, int32_t nParam)
{
  CExtCharTitle *CharTitle; // rax
  CharId_t nCharIda; // [rsp+10h] [rbp-50h] BYREF
  GameService *thisa; // [rsp+18h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &nCharIda)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator==(&iter, &__x) )
  {
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      CharTitle = Player::GetCharTitle(player);
      CExtCharTitle::CheckAddTitle(CharTitle, nType, nParam);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::onCheckTeShuTitle(GameService *const this, CharId_t nCharId, int8_t nType, int32_t nParam)
{
  Answer::DBPool *v4; // rax
  int32_t Now; // eax
  CExtCharTitle *CharTitle; // rax
  CharId_t nCharIda; // [rsp+20h] [rbp-1090h] BYREF
  GameService *thisa; // [rsp+28h] [rbp-1088h]
  char szSQL[4096]; // [rsp+30h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1030h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+1060h] [rbp-50h] BYREF
  Answer::MutexGuard lock; // [rsp+1070h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+1080h] [rbp-30h] BYREF
  Player *player; // [rsp+1090h] [rbp-20h]
  int32_t Time; // [rsp+109Ch] [rbp-14h]

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &nCharIda)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator==(&iter, &__x) )
  {
    v4 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v4);
    Time = Answer::DayTime::now() + 86340;
    memset(szSQL, 0, sizeof(szSQL));
    bzero(szSQL, 0x1000u);
    snprintf(
      szSQL,
      0xFFFu,
      "INSERT `mem_char_operate_limit`(cid,LimitId,LimitCount) VALUES (%lld,%d,%d) ON DUPLICATE KEY UPDATE LimitCount=%d",
      nCharIda,
      nParam + 31301,
      Time,
      Time);
    Answer::MySqlDBGuard::excute(&db, szSQL);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
  else
  {
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      Now = Unit::getNow(player);
      Player::updateRecord(player, nParam + 31301, Now + 86340);
      CharTitle = Player::GetCharTitle(player);
      CExtCharTitle::CheckAddTitle(CharTitle, nType, nParam);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::onRemoveTitle(GameService *const this, CharId_t nCharId, int8_t nType)
{
  CExtCharTitle *CharTitle; // rax
  CharId_t nCharIda; // [rsp+10h] [rbp-50h] BYREF
  GameService *thisa; // [rsp+18h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &nCharIda)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator==(&iter, &__x) )
  {
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      CharTitle = Player::GetCharTitle(player);
      CExtCharTitle::RemoveTitle(CharTitle, nType, 0);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::requestWorldLevel(GameService *const this)
{
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  packet = GameService::popNetpacket(this, 0, Answer::PackType::PACK_PROC, 0x4E4Bu);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GameService::sendPacket(this, 0, packet);
  }
}


#####################################
void __cdecl GameService::onRequestDropRecord(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  int16_t Int16; // r12
  int8_t Id; // bl
  CWorldBoss *v5; // rax

  if ( pConn )
  {
    if ( inPacket )
    {
      Int16 = Answer::NetPacket::readInt16(inPacket);
      Id = MutiConn<GameService>::GetId(pConn);
      v5 = Answer::Singleton<CWorldBoss>::instance();
      CWorldBoss::SendDropRecord(v5, Id, Int16);
    }
  }
}


#####################################
void __cdecl GameService::InitServerBattle(GameService *const this)
{
  GameService *v1; // rax
  DBService *v2; // rax
  Answer::DBPool *v3; // rax
  Answer::MySqlQuery *v4; // rax
  const char *StringValue; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
  {
    v2 = Answer::Singleton<DBService>::instance();
    DBService::onLoadServerBattle(v2);
  }
  else
  {
    v3 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v3);
    v4 = Answer::MySqlDBGuard::query(&db, "SELECT * FROM `sys_server_config` WHERE `name`='BATTLE'");
    Answer::MySqlQuery::MySqlQuery(&result, v4);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      StringValue = Answer::MySqlQuery::getStringValue(&result, "value", byte_8DA6C0);
      this->m_Battle = atoi(StringValue);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl GameService::SetServerBattle(GameService *const this, int32_t Battle)
{
  if ( this->m_Battle < Battle )
    this->m_Battle = Battle;
}


#####################################
void __cdecl GameService::InitMoYuShiJieRecord(GameService *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery *v5; // rax
  const char *v6; // rax
  LogMoYuShiJieReward record; // [rsp+10h] [rbp-A0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+50h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-30h] BYREF
  int32_t nSize; // [rsp+9Ch] [rbp-14h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    nSize = 0;
    v3 = Answer::MySqlDBGuard::query(
           &db,
           "SELECT * FROM `log_moyushijie_reward` WHERE `special`=1 ORDER BY `time` DESC LIMIT 5");
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      memset(&record, 0, sizeof(record));
      record.cid = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", byte_8DA6C0);
      snprintf(record.name, 0x1Eu, StringValue);
      record.dungeonid = Answer::MySqlQuery::getIntValue(&result, "dungeonid", 0);
      record.itemid = Answer::MySqlQuery::getIntValue(&result, "itemid", 0);
      record.itemclass = Answer::MySqlQuery::getIntValue(&result, "itemclass", 0);
      record.itemcount = Answer::MySqlQuery::getIntValue(&result, "itemcount", 0);
      record.time = Answer::MySqlQuery::getIntValue(&result, "time", 0);
      record.special = Answer::MySqlQuery::getIntValue(&result, "special", 0);
      std::list<LogMoYuShiJieReward>::push_front(&this->m_lMYSJRecordSpecial, &record);
      if ( ++nSize > 4 )
        break;
      Answer::MySqlQuery::nextRow(&result);
    }
    v5 = Answer::MySqlDBGuard::query(
           &db,
           "SELECT * FROM `log_moyushijie_reward` WHERE `special`=0 ORDER BY `time` DESC LIMIT 30");
    Answer::MySqlQuery::operator=(&result, v5);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      memset(&record, 0, sizeof(record));
      record.cid = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      v6 = Answer::MySqlQuery::getStringValue(&result, "name", byte_8DA6C0);
      snprintf(record.name, 0x1Eu, v6);
      record.dungeonid = Answer::MySqlQuery::getIntValue(&result, "dungeonid", 0);
      record.itemid = Answer::MySqlQuery::getIntValue(&result, "itemid", 0);
      record.itemclass = Answer::MySqlQuery::getIntValue(&result, "itemclass", 0);
      record.itemcount = Answer::MySqlQuery::getIntValue(&result, "itemcount", 0);
      record.time = Answer::MySqlQuery::getIntValue(&result, "time", 0);
      record.special = Answer::MySqlQuery::getIntValue(&result, "special", 0);
      std::list<LogMoYuShiJieReward>::push_front(&this->m_lMYSJRecord, &record);
      if ( ++nSize > 29 )
        break;
      Answer::MySqlQuery::nextRow(&result);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl GameService::SendMoYuShiJieRecord(GameService *const this, Player *player)
{
  int8_t ConnId; // bl
  __int16 v3; // bx
  __int16 v4; // ax
  const LogMoYuShiJieReward *v5; // rax
  const LogMoYuShiJieReward *v6; // rax
  const LogMoYuShiJieReward *v7; // rax
  const LogMoYuShiJieReward *v8; // rax
  const LogMoYuShiJieReward *v9; // rax
  const LogMoYuShiJieReward *v10; // rax
  const LogMoYuShiJieReward *v11; // rax
  const LogMoYuShiJieReward *v12; // rax
  const LogMoYuShiJieReward *v13; // rax
  const LogMoYuShiJieReward *v14; // rax
  const LogMoYuShiJieReward *v15; // rax
  const LogMoYuShiJieReward *v16; // rax
  const LogMoYuShiJieReward *v17; // rax
  const LogMoYuShiJieReward *v18; // rax
  const LogMoYuShiJieReward *v19; // rax
  const LogMoYuShiJieReward *v20; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v23; // bl
  std::_List_const_iterator<LogMoYuShiJieReward> iter_0; // [rsp+10h] [rbp-D0h] BYREF
  std::_List_const_iterator<LogMoYuShiJieReward> iter; // [rsp+20h] [rbp-C0h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-B0h] BYREF
  std::_List_iterator<LogMoYuShiJieReward> __x; // [rsp+40h] [rbp-A0h] BYREF
  std::_List_const_iterator<LogMoYuShiJieReward> v28; // [rsp+50h] [rbp-90h] BYREF
  std::_List_iterator<LogMoYuShiJieReward> v29; // [rsp+60h] [rbp-80h] BYREF
  std::string val; // [rsp+70h] [rbp-70h] BYREF
  char v31; // [rsp+7Fh] [rbp-61h] BYREF
  std::_List_iterator<LogMoYuShiJieReward> v32; // [rsp+80h] [rbp-60h] BYREF
  std::_List_const_iterator<LogMoYuShiJieReward> v33; // [rsp+90h] [rbp-50h] BYREF
  std::_List_iterator<LogMoYuShiJieReward> v34; // [rsp+A0h] [rbp-40h] BYREF
  std::string v35; // [rsp+B0h] [rbp-30h] BYREF
  char v36; // [rsp+C7h] [rbp-19h] BYREF
  Answer::NetPacket *packet; // [rsp+C8h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    packet = GameService::popNetpacket(this, ConnId, Answer::PackType::PACK_DISPATCH, 0x2ED7u);
    if ( packet )
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_mysjRecordLock);
      v3 = std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecord);
      v4 = std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecordSpecial);
      Answer::NetPacket::writeInt16(packet, v3 + v4);
      __x._M_node = std::list<LogMoYuShiJieReward>::begin(&this->m_lMYSJRecordSpecial)._M_node;
      std::_List_const_iterator<LogMoYuShiJieReward>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v29._M_node = std::list<LogMoYuShiJieReward>::end(&this->m_lMYSJRecordSpecial)._M_node;
        std::_List_const_iterator<LogMoYuShiJieReward>::_List_const_iterator(&v28, &v29);
        if ( !std::_List_const_iterator<LogMoYuShiJieReward>::operator!=(&iter, &v28) )
          break;
        v5 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt64(packet, v5->cid);
        std::allocator<char>::allocator(&v31);
        v6 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        std::string::string(&val, v6->name, &v31);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        std::allocator<char>::~allocator(&v31);
        v7 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v7->dungeonid);
        v8 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v8->itemid);
        v9 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v9->itemclass);
        v10 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v10->itemcount);
        v11 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v11->time);
        v12 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v12->special);
        std::_List_const_iterator<LogMoYuShiJieReward>::operator++(&iter);
      }
      v32._M_node = std::list<LogMoYuShiJieReward>::begin(&this->m_lMYSJRecord)._M_node;
      std::_List_const_iterator<LogMoYuShiJieReward>::_List_const_iterator(&iter_0, &v32);
      while ( 1 )
      {
        v34._M_node = std::list<LogMoYuShiJieReward>::end(&this->m_lMYSJRecord)._M_node;
        std::_List_const_iterator<LogMoYuShiJieReward>::_List_const_iterator(&v33, &v34);
        if ( !std::_List_const_iterator<LogMoYuShiJieReward>::operator!=(&iter_0, &v33) )
          break;
        v13 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt64(packet, v13->cid);
        std::allocator<char>::allocator(&v36);
        v14 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        std::string::string(&v35, v14->name, &v36);
        Answer::NetPacket::writeUTF8(packet, &v35);
        std::string::~string(&v35);
        std::allocator<char>::~allocator(&v36);
        v15 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt32(packet, v15->dungeonid);
        v16 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt32(packet, v16->itemid);
        v17 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt8(packet, v17->itemclass);
        v18 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt32(packet, v18->itemcount);
        v19 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt32(packet, v19->time);
        v20 = std::_List_const_iterator<LogMoYuShiJieReward>::operator->(&iter_0);
        Answer::NetPacket::writeInt8(packet, v20->special);
        std::_List_const_iterator<LogMoYuShiJieReward>::operator++(&iter_0);
      }
      Answer::MutexGuard::~MutexGuard(&lock);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v23 = Player::getConnId(player);
      GameService::sendPacketTo(this, v23, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl GameService::AddMoYuShiJieRecord(GameService *const this, const LogMoYuShiJieReward *const logReward)
{
  GameService *v2; // rax
  size_t v3; // rbx
  size_t v4; // rbx
  Answer::MutexGuard lock_0; // [rsp+10h] [rbp-30h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 && logReward->special >= 0 )
  {
    if ( logReward->special )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_mysjRecordLock);
      std::list<LogMoYuShiJieReward>::push_front(&this->m_lMYSJRecordSpecial, logReward);
      if ( std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecordSpecial) <= 5 )
      {
        v4 = std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecordSpecial);
        if ( v4 + std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecord) > 0x1E )
          std::list<LogMoYuShiJieReward>::pop_front(&this->m_lMYSJRecord);
      }
      else
      {
        std::list<LogMoYuShiJieReward>::pop_back(&this->m_lMYSJRecordSpecial);
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
    }
    else
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_mysjRecordLock);
      std::list<LogMoYuShiJieReward>::push_front(&this->m_lMYSJRecord, logReward);
      v3 = std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecord);
      if ( v3 + std::list<LogMoYuShiJieReward>::size(&this->m_lMYSJRecordSpecial) > 0x1E )
        std::list<LogMoYuShiJieReward>::pop_back(&this->m_lMYSJRecord);
      Answer::MutexGuard::~MutexGuard(&lock);
    }
  }
}


#####################################
void __cdecl GameService::ResetFestivalData(GameService *const this, int32_t nVersion)
{
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
      Player::ResetFestivalData(player, nVersion);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::UpdateTencentInfo(GameService *const this, CharId_t cid, const TencentInfo *const info)
{
  CExtCharTencent *CharTencent; // rax
  CharId_t cida; // [rsp+10h] [rbp-50h] BYREF
  GameService *thisa; // [rsp+18h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+40h] [rbp-20h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  thisa = this;
  cida = cid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  iter._M_node = std::map<long,Player *>::find(&this->m_players, &cida)._M_node;
  __x._M_node = std::map<long,Player *>::end(&thisa->m_players)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
  {
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      CharTencent = Player::GetCharTencent(player);
      CExtCharTencent::UpdateTencentInfo(CharTencent, info);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl GameService::FamilyBroadcast(
        GameService *const this,
        int8_t connid,
        FamilyId_t nFamilyId,
        Answer::NetPacket *inPacket)
{
  uint16_t Proc; // dx
  uint32_t Size; // ebx
  char *Buffer; // rcx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( inPacket )
  {
    packet = GameService::popNetpacket(this, connid, Answer::PackType::PACK_DISPATCH, 0x4E4Fu);
    if ( packet )
    {
      Answer::NetPacket::writeInt64(packet, nFamilyId);
      Proc = Answer::NetPacket::getProc(inPacket);
      Answer::NetPacket::writeUInt16(packet, Proc);
      Size = Answer::NetPacket::getSize(inPacket);
      Buffer = Answer::NetPacket::getBuffer(inPacket);
      Answer::NetPacket::write(packet, Buffer, Size);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GameService::sendPacket(this, connid, packet);
    }
    Answer::NetPacket::destroy(inPacket);
  }
}


#####################################
void __cdecl GameService::onSocialInitFamilyInfo(
        GameService *const this,
        std::map<signed char,GameService::ConnType*>::ConnType *pConn,
        Answer::NetPacket *inPacket)
{
  FamilyManager *v3; // rax

  if ( pConn )
  {
    if ( inPacket )
    {
      v3 = Answer::Singleton<FamilyManager>::instance();
      FamilyManager::OnInitFamilyInfo(v3, inPacket);
    }
  }
}


#####################################
void __cdecl GameService::broadcastCityWarWinnerLogin(
        GameService *const this,
        CharId_t nCharId,
        const std::string *const strName)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 334);
    Answer::NetPacket::writeUTF8(packet, strName);
    Answer::NetPacket::writeInt64(packet, nCharId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, packet);
  }
}


#####################################
void __cdecl GameService::broadCastKiaFuHuoDongIcon(GameService *const this)
{
  CKaiFuHuoDong *v1; // rax
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Player*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_playerLock);
  for ( iter._M_node = std::map<long,Player *>::begin(&this->m_players)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,Player *>::end(&this->m_players)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator!=(&iter, &__x) )
      break;
    player = std::_Rb_tree_iterator<std::pair<long const,Player *>>::operator->(&iter)->second;
    if ( player )
    {
      v1 = Answer::Singleton<CKaiFuHuoDong>::instance();
      CKaiFuHuoDong::SendKaiFuHuoDongIcon(v1, player);
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


