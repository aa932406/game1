#include "stdafx.h"
#include "GameLogs.h"
#include "DBService.h"

using namespace Answer;

//////////////////////////////////////////////////////////////////////////
// platform_log_base
//////////////////////////////////////////////////////////////////////////

platform_log_base::platform_log_base()
	: nTime(0), nSid(0)
{
}

platform_log_base::~platform_log_base()
{
}

void platform_log_base::CleanUp()
{
	nTime = 0;
	nSid = 0;
}

void platform_log_base::PackageData(NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt32(nTime);
	packet->writeInt32(nSid);
}

void platform_log_base::UnPackageData(NetPacket* inPacket)
{
	if (!inPacket) return;
	nTime = inPacket->readInt32();
	nSid = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// boss_log
//////////////////////////////////////////////////////////////////////////

boss_log::boss_log()
{
	CleanUp();
}

boss_log::~boss_log()
{
}

void boss_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	kill_time = 0;
	mid = 0;
	boss_id = 0;
}

void boss_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(kill_time);
	packet->writeInt32(mid);
	packet->writeInt32(boss_id);
}

void boss_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	kill_time = inPacket->readInt32();
	mid = inPacket->readInt32();
	boss_id = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// bossjoin_log
//////////////////////////////////////////////////////////////////////////

bossjoin_log::bossjoin_log()
{
	CleanUp();
}

bossjoin_log::~bossjoin_log()
{
}

void bossjoin_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	join_time = 0;
	mid = 0;
	boss_id = 0;
	mapId = 0;
	killed = 0;
}

void bossjoin_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(join_time);
	packet->writeInt32(mid);
	packet->writeInt32(boss_id);
	packet->writeInt32(mapId);
	packet->writeInt32(killed);
}

void bossjoin_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	join_time = inPacket->readInt32();
	mid = inPacket->readInt32();
	boss_id = inPacket->readInt32();
	mapId = inPacket->readInt32();
	killed = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// currency_log
//////////////////////////////////////////////////////////////////////////

currency_log::currency_log()
{
	CleanUp();
}

currency_log::~currency_log()
{
}

void currency_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	time = 0;
	type = 0;
	opway = 0;
	value = 0;
	ids.clear();
	couts.clear();
	level = 0;
}

void currency_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(time);
	packet->writeInt8(type);
	packet->writeInt32(opway);
	packet->writeInt64(value);
	packet->writeUTF8(ids);
	packet->writeUTF8(couts);
	packet->writeInt32(level);
}

void currency_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	time = inPacket->readInt32();
	type = inPacket->readInt8();
	opway = inPacket->readInt32();
	value = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); ids = tmp; }
	{ std::string tmp; inPacket->readUTF8(tmp); couts = tmp; }
	level = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// death_log
//////////////////////////////////////////////////////////////////////////

death_log::death_log()
{
	CleanUp();
}

death_log::~death_log()
{
}

void death_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	level = 0;
	mapId = 0;
	killerType = 0;
	killerId = 0;
	killerName.clear();
}

void death_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(level);
	packet->writeInt32(mapId);
	packet->writeInt32(killerType);
	packet->writeInt64(killerId);
	packet->writeUTF8(killerName);
}

void death_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	level = inPacket->readInt32();
	mapId = inPacket->readInt32();
	killerType = inPacket->readInt32();
	killerId = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); killerName = tmp; }
}

//////////////////////////////////////////////////////////////////////////
// item_log
//////////////////////////////////////////////////////////////////////////

item_log::item_log()
{
	CleanUp();
}

item_log::~item_log()
{
}

void item_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	time = 0;
	itemId = 0;
	opway = 0;
	count = 0;
	level = 0;
}

void item_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(time);
	packet->writeInt32(itemId);
	packet->writeInt32(opway);
	packet->writeInt32(count);
	packet->writeInt32(level);
}

void item_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	time = inPacket->readInt32();
	itemId = inPacket->readInt32();
	opway = inPacket->readInt32();
	count = inPacket->readInt32();
	level = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// level_up_log
//////////////////////////////////////////////////////////////////////////

level_up_log::level_up_log()
{
	CleanUp();
}

level_up_log::~level_up_log()
{
}

void level_up_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	oldLevel = 0;
	newLevel = 0;
}

void level_up_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(oldLevel);
	packet->writeInt32(newLevel);
}

void level_up_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	oldLevel = inPacket->readInt32();
	newLevel = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// logout_log
//////////////////////////////////////////////////////////////////////////

logout_log::logout_log()
{
	CleanUp();
}

logout_log::~logout_log()
{
}

void logout_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	level = 0;
	onlineTime = 0;
}

void logout_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(level);
	packet->writeInt32(onlineTime);
}

void logout_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	level = inPacket->readInt32();
	onlineTime = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// main_task_log
//////////////////////////////////////////////////////////////////////////

main_task_log::main_task_log()
{
	CleanUp();
}

main_task_log::~main_task_log()
{
}

void main_task_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	taskId = 0;
	taskState = 0;
}

void main_task_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(taskId);
	packet->writeInt32(taskState);
}

void main_task_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	taskId = inPacket->readInt32();
	taskState = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// online_user_24th_log
//////////////////////////////////////////////////////////////////////////

online_user_24th_log::online_user_24th_log()
{
	CleanUp();
}

online_user_24th_log::~online_user_24th_log()
{
}

void online_user_24th_log::CleanUp()
{
	platform_log_base::CleanUp();
	nOnlineCount = 0;
	nTime = 0;
}

void online_user_24th_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeInt32(nOnlineCount);
	packet->writeInt32(nTime);
}

void online_user_24th_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	nOnlineCount = inPacket->readInt32();
	nTime = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// proc_log
//////////////////////////////////////////////////////////////////////////

proc_log::proc_log()
{
	CleanUp();
}

proc_log::~proc_log()
{
}

void proc_log::CleanUp()
{
	platform_log_base::CleanUp();
	nProcId = 0;
	nOnlineCount = 0;
	nCpuUsage = 0;
	nMemUsage = 0;
}

void proc_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeInt32(nProcId);
	packet->writeInt32(nOnlineCount);
	packet->writeInt32(nCpuUsage);
	packet->writeInt32(nMemUsage);
}

void proc_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	nProcId = inPacket->readInt32();
	nOnlineCount = inPacket->readInt32();
	nCpuUsage = inPacket->readInt32();
	nMemUsage = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// skill_log
//////////////////////////////////////////////////////////////////////////

skill_log::skill_log()
{
	CleanUp();
}

skill_log::~skill_log()
{
}

void skill_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	skillId = 0;
	skillLevel = 0;
	targetId = 0;
}

void skill_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(skillId);
	packet->writeInt32(skillLevel);
	packet->writeInt32(targetId);
}

void skill_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	skillId = inPacket->readInt32();
	skillLevel = inPacket->readInt32();
	targetId = inPacket->readInt32();
}

//////////////////////////////////////////////////////////////////////////
// log_abnormal
//////////////////////////////////////////////////////////////////////////

log_abnormal::log_abnormal()
	: nCid(0), nType(0), nValue(0), nOpway(0)
{
}

log_abnormal::~log_abnormal()
{
}

void log_abnormal::PackageData(NetPacket* packet)
{
	if (!packet) return;
	packet->writeInt64(nCid);
	packet->writeUTF8(sName);
	packet->writeInt8(nType);
	packet->writeInt32(nValue);
	packet->writeInt32(nOpway);
}

//////////////////////////////////////////////////////////////////////////
// BlackMarketIndex
//////////////////////////////////////////////////////////////////////////

bool BlackMarketIndex::operator<(const BlackMarketIndex& right) const
{
	if (nDays != right.nDays)
		return nDays < right.nDays;
	if (nIndex == right.nIndex)
		return nJob < right.nJob;
	return nIndex < right.nIndex;
}

//////////////////////////////////////////////////////////////////////////
// NpcDungeon
//////////////////////////////////////////////////////////////////////////

NpcDungeon::NpcDungeon()
	: Npc(), m_dungeon(NULL)
{
}

NpcDungeon::~NpcDungeon()
{
}

void NpcDungeon::init(Dungeon* dungeon, const CfgNpc* cfgNpc)
{
	if (dungeon)
	{
		m_dungeon = dungeon;
		Npc::init(cfgNpc, 0);
	}
}

int32_t NpcDungeon::onEndNpc(Player* player, int8_t choice)
{
	if (!player)
		return 10002;
	m_dungeon->OnNpcEnd(this, choice);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// StaticObj
//////////////////////////////////////////////////////////////////////////

StaticObj::StaticObj()
	: m_pMap(NULL)
{
}

StaticObj::~StaticObj()
{
}

void StaticObj::reset()
{
	Entity::generateEntityId(this);
	m_pMap = NULL;
	m_currentTile = Position(0, 0);
	m_currentPos = Position(0, 0);
}

int32_t StaticObj::getMapId()
{
	if (m_pMap)
		return m_pMap->GetMapId();
	return 0;
}

int32_t StaticObj::getMapType()
{
	if (m_pMap)
		return m_pMap->GetType();
	return 0;
}

bool StaticObj::InDungeon()
{
	return m_pMap && m_pMap->IsDungeon();
}

bool StaticObj::InActivity()
{
	return m_pMap && m_pMap->IsActivity();
}

bool StaticObj::InPrison()
{
	return m_pMap && m_pMap->IsPrison();
}

int32_t StaticObj::GetRunnerId()
{
	if (m_pMap)
		return m_pMap->GetRunnerId();
	return 0;
}

bool StaticObj::IsSpecialBossMap()
{
	return m_pMap && m_pMap->IsSpecialBossMap();
}

bool StaticObj::IsCycleTower()
{
	return m_pMap && m_pMap->IsCycleTower();
}

bool StaticObj::IsKuangDong()
{
	return m_pMap && m_pMap->IsKuangDong();
}

bool StaticObj::IsTerritory()
{
	return m_pMap && m_pMap->IsTerritory();
}

//////////////////////////////////////////////////////////////////////////
// important_system_log
//////////////////////////////////////////////////////////////////////////

important_system_log::important_system_log()
{
	CleanUp();
}

important_system_log::~important_system_log()
{
}

void important_system_log::CleanUp()
{
	platform_log_base::CleanUp();
	passport.clear();
	cid = 0;
	name.clear();
	up_time = 0;
	sys_name = 0;
	oper_id = 0;
	level = 0;
}

void important_system_log::PackageData(NetPacket* packet)
{
	platform_log_base::PackageData(packet);
	packet->writeUTF8(passport);
	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(up_time);
	packet->writeInt32(sys_name);
	packet->writeInt32(oper_id);
	packet->writeInt32(level);
}

void important_system_log::UnPackageData(NetPacket* inPacket)
{
	platform_log_base::UnPackageData(inPacket);
	{ std::string tmp; inPacket->readUTF8(tmp); passport = tmp; }
	cid = inPacket->readInt64();
	{ std::string tmp; inPacket->readUTF8(tmp); name = tmp; }
	up_time = inPacket->readInt32();
	sys_name = inPacket->readInt32();
	oper_id = inPacket->readInt32();
	level = inPacket->readInt32();
}
