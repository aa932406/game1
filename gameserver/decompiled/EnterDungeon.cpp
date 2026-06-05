// Decompiled methods for class: EnterDungeon
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl EnterDungeon::~EnterDungeon(EnterDungeon *const this)
{
  EnterDungeon::~EnterDungeon(this);
  operator delete(this);
}


#####################################
int32_t __cdecl EnterDungeon::effect(
        EnterDungeon *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  CExtCharTeamDungeon *CharTeamDungeon; // rax
  int32_t m_DungeonId; // ebx
  CfgData *v8; // rax
  int32_t Record; // ebx
  int32_t v10; // ebx
  MapManager *v11; // rax
  Map *Map; // rax
  int64_t id; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v16; // rax
  int32_t RunnerId; // ebx
  MapManager *v18; // rax
  int32_t group_id; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t v21; // ebx
  CHuoYueDu *PlayerHuoYueDu; // rax
  int8_t v23; // bl
  DBService *v24; // rax
  LogDungeon logDungeon; // [rsp+30h] [rbp-50h] BYREF
  CfgDungeon *pCfgDungeon; // [rsp+50h] [rbp-30h]
  Dungeon *pDungeon; // [rsp+58h] [rbp-28h]

  if ( !StaticObj::getMap(launcher) )
    return 10002;
  if ( StaticObj::InDungeon(launcher) )
    return 10002;
  if ( StaticObj::InActivity(launcher) )
    return 10002;
  if ( Player::IsInStall(launcher) )
    return 10002;
  CharTeamDungeon = Player::GetCharTeamDungeon(launcher);
  if ( CExtCharTeamDungeon::IsInTeamDungeon(CharTeamDungeon) )
    return 10002;
  m_DungeonId = this->m_DungeonId;
  v8 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v8, m_DungeonId);
  if ( !pCfgDungeon )
    return 10002;
  Record = Player::getRecord(launcher, pCfgDungeon->group_id);
  if ( Record >= Player::GetDungeonDailyEnterLimit(launcher, this->m_DungeonId) )
    return 10002;
  v10 = this->m_DungeonId;
  v11 = Answer::Singleton<MapManager>::instance();
  pDungeon = MapManager::NewDungeon(v11, v10);
  if ( !pDungeon )
    return 10002;
  Dungeon::start(pDungeon, 0);
  Player::setOldPosition(launcher);
  Player::broadcastLeave(launcher);
  Map = StaticObj::getMap(launcher);
  (*((void (__fastcall **)(Map *, Player *const, _QWORD))Map->_vptr_Map + 16))(Map, launcher, 0);
  id = pCfgDungeon->id;
  GateIndex = Player::getGateIndex(launcher);
  ConnId = Player::getConnId(launcher);
  v16 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v16, ConnId, GateIndex, 0x12u, id);
  (*((void (__fastcall **)(Dungeon *, Player *const, _QWORD, _QWORD))pDungeon->_vptr_Map + 15))(
    pDungeon,
    launcher,
    (unsigned int)pCfgDungeon->x,
    (unsigned int)pCfgDungeon->y);
  RunnerId = Map::GetRunnerId(pDungeon);
  v18 = Answer::Singleton<MapManager>::instance();
  MapManager::PostMsg(v18, RunnerId, GameMsgCode::GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
  if ( pCfgDungeon->type != 13 && pCfgDungeon->type != 15 && pCfgDungeon->type != 17 )
  {
    group_id = pCfgDungeon->group_id;
    OperateLimit = Player::GetOperateLimit(launcher);
    CExtOperateLimit::AddLimitCount(OperateLimit, group_id, 1);
    v21 = pCfgDungeon->group_id;
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(launcher);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 2, v21, 0);
  }
  *(_QWORD *)&logDungeon.level = 0;
  *(_QWORD *)&logDungeon.start_time = 0;
  logDungeon.cid = Player::getCid(launcher);
  logDungeon.did = Dungeon::getDungeonId(pDungeon);
  logDungeon.type = Dungeon::getDungeonType(pDungeon);
  logDungeon.level = (*((__int64 (__fastcall **)(Player *const))launcher->_vptr_Entity + 9))(launcher);
  logDungeon.start_time = Dungeon::GetStartTime(pDungeon);
  v23 = Player::getConnId(launcher);
  v24 = Answer::Singleton<DBService>::instance();
  DBService::insertDungeon(v24, v23, &logDungeon);
  if ( pCfgDungeon->type == 17 )
    return 10002;
  else
    return 0;
}


#####################################
bool __cdecl EnterDungeon::parseEffect(EnterDungeon *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_DungeonId = atoi(v3);
  return 1;
}


