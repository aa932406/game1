#include "stdafx.h"

#include "DBService.h"
#include "GameService.h"
#include "EquipManager.h"
#include "PetManager.h"
#include "EquipRansom.h"
#include "Timer.h"
#include "ActivityManager.h"
#include "GMBackstage.h"
#include "GuiGuDaoRen.h"
#include "WorldBoss.h"
#include "EquipBack.h"
#include "CfgData.h"
#include "FestivalDoubleEleven.h"
#include "ZongHeYunYingHD.h"
#include "KaiFuHuoDong.h"
#include <string>

using namespace Answer;
using namespace std;

// DB protocol proc codes (0x4E00 range)
#define IM_DB_GAME_SERVICE_CONNECT		0x4EC6
#define IM_DB_FENG_HAO					0x4EC7
#define IM_DB_LOAD_PLAYER				0x4EC8
#define IM_DB_PLAYER_LOADED				0x4EC9
#define IM_DB_SAVE_PLAYER				0x4ECA
#define IM_DB_INSERT_EQUIP				0x4ECD
#define IM_DB_UPDATE_EQUIP				0x4ECE
#define IM_DB_DELETE_EQUIP				0x4ECF
#define IM_DB_EQUIP_UPDATED				0x4ED0
#define IM_DB_MYSJ_REWARD				0x4ED1
#define IM_DB_LOAD_CITYWAR_INFO			0x4ED2
#define IM_DB_CITYWAR_INFO_LOADED		0x4ED3
#define IM_DB_LOAD_PEERLESSWAR_INFO		0x4ED4
#define IM_DB_LOAD_CROSSTOWER_INFO		0x4ED5
#define IM_DB_LOAD_SERVERBATTLE_INFO	0x4ED6
#define IM_DB_LEVEL_UP					0x4EDD
#define IM_DB_LOG_PLAYER_LOGIN			0x4EDB
#define IM_DB_LOG_MYSJ_REWARD			0x4EDA
#define IM_DB_UPDATE_LOGIN_TIME			0x4EF5
#define IM_DB_LOG_PLAYER_STAY			0x4EF6
#define IM_DB_LOG_TASK_RECEIVE			0x4EDF
#define IM_DB_LOG_TASK_SUBMIT			0x4EE0
#define IM_DB_LOG_IN_DUNGEON			0x4EE1
#define IM_DB_LOG_OUT_DUNGEON			0x4EE2
#define IM_DB_PLAYER_SAVED				0x4ECC
#define IM_DB_LOG_ACTIVITY_DATA			0x4EE4
#define IM_DB_LOG_ITEM_CHANGE			0x4EE5
#define IM_DB_LOG_MING_GE				0x4EE6
#define IM_DB_LOG_KILL_BOSS				0x4EE7
#define IM_DB_LOG_DAILY_GIFT			0x4EE8
#define IM_DB_LOG_SHANG_CHENG			0x4EE9
#define IM_DB_LOG_CURRENCY				0x4EEB
#define IM_DB_LOG_ARTIFACT_ADD_EXP		0x4EAB
#define IM_DB_LOG_ARTIFACT_ADD_MAX_LEVEL 0x4EAC
#define IM_DB_LOG_ARTIFACT_ADD_QUALITY	0x4EAD
#define IM_DB_SEND_MAIL_TO_DB			0x4EEC
#define IM_DB_UPDATE_NEW_MAIL			0x4EEE
#define IM_DB_DELETE_MAIL				0x4EED
#define IM_DB_NEW_MINUTE				0x4EEF
#define IM_DB_UPDATE_PAY				0x4EF0
#define IM_DB_SAVE_CITYWAR_RESULT		0x4EF1
#define IM_DB_SAVE_CROSSTOWER_RESULT	0x4EF2
#define IM_DB_UPDATE_CITYWAR_RESULT		0x4EF3
#define IM_DB_UPDATE_KAIFU_TIME			0x4EF4
#define IM_DB_UPDATE_GM_BROADCAST		0x4EF7
#define IM_DB_UPDATE_GM_BAN_CHAT		0x4EF8
#define IM_DB_UPDATE_GM_SEAL			0x4EF9
#define IM_DB_BACKSTAGE_KICK			0x4EFA
#define IM_DB_UPDATE_FAMILY_WAR_RESULT	0x4EFB
#define IM_DB_UPDATE_CROSSTOWER_RESULT	0x4EFC
#define IM_DB_SAVE_PEERLESSWAR_RESULT	0x4EFD
#define IM_DB_UPDATE_PEERLESSWAR_RESULT 0x4EFE
#define IM_DB_UPDATE_BOSS_FIRST_KILLED	0x4EFF
#define IM_DB_SAVE_WORLDBOSS_INFO		0x4F00
#define IM_DB_SAVE_EQUIPBACK_RECORD		0x4F01
#define IM_DB_SAVE_EQUIPBACK_COUNT		0x4F02
#define IM_DB_SAVE_GUIGU_DAOREN			0x4F03
#define IM_DB_SAVE_GUIGU_BACK_COUNT		0x4F04
#define IM_DB_SAVE_GUIGU_BACK_RANK		0x4F05
#define IM_DB_LOAD_DOUBLEELEVEN_RANK	0x4F0B
#define IM_DB_SAVE_DOUBLEELEVEN_RANK	0x4F0C
#define IM_DB_LOAD_ZHYYHD_RANK			0x4F0E
#define IM_DB_SAVE_ZHYYHD_RANK			0x4F0F
#define IM_DB_UPDATE_DOUBLEELEVEN_RANK	0x4F0D
#define IM_DB_UPDATE_ZHYYHD_RANK		0x4F10
#define IM_DB_SAVE_DROP_TIMES			0x4F11
#define IM_DB_CLEAR_DROP_TIMES			0x4F12
#define IM_DB_UPDATE_DROP_TIMES			0x4F13
#define IM_DB_SAVE_DROP_RECORD			0x4F14
#define IM_DB_SAVE_BOSS_FIRST_KILLED	0x4F15
#define IM_DB_LOG_360					0x4F16
#define IM_DB_LOG_PROC					0x4F17
#define IM_DB_LOG_NPC_FUNC				0x4F19
#define IM_DB_LOG_UP_EQUIP_STAR			0x4F1A
#define IM_DB_LOG_EQUIP_DROP			0x4F1B
#define IM_DB_LOG_CHANGE_MAP			0x4F1C
#define IM_DB_SAVE_ONLINE_TIME			0x4F1D
#define IM_DB_RELOAD_TENCENT_INFO		0x4F1E
#define IM_DB_UPDATE_TENCENT_INFO		0x4F1F
#define IM_DB_CHECK_MOBILE_PHONE_GIFT	0x4F20
#define IM_DB_CHECK_GUARD_PRIVILEGE		0x4F22
#define IM_DB_CLICK_GAME				0x4F24
#define IM_DB_LOAD_GM_BACKSTAGE		0x4EFB
// Legacy function proc codes (0x4EA0-0x4EBF range - not in decompiled source, kept for backward compat)
#define IM_DB_USER_PAYED				0x4EDE
#define IM_DB_ADD_RANSOM_INFO			0x4F06
#define IM_DB_DLE_RANSOM_INFO			0x4F07
#define IM_DB_UPDATE_RANSOM				0x4F08
#define IM_DB_INSERT_PET				0x4E90
#define IM_DB_UPDATE_PET				0x4E91
#define IM_DB_DELETE_PET				0x4E92
#define IM_DB_PET_UPDATED				0x4E93
#define IM_DB_PET_DELETED				0x4E94
#define IM_DB_LOG_EQUIP_ENHANCE			0x4EA0
#define IM_DB_LOG_EQUIP_ADD_GEM			0x4EA1
#define IM_DB_LOG_ITEM_COMBINE			0x4EA2
#define IM_DB_LOG_EQUIP_SMITHING		0x4EA3
#define IM_DB_LOG_EQUIP_DISMANTLE		0x4EA4
#define IM_DB_LOG_CREATE_FAMILY			0x4EA5
#define IM_DB_LOG_JOIN_FAMILY			0x4EA6
#define IM_DB_LOG_OUT_FAMILY			0x4EA7
#define IM_DB_LOG_ACHIEVEMENT			0x4EA8
#define IM_DB_INSERT_MEMYELLOWSTONE		0x4EA9
#define IM_DB_LOG_EQUIP_ADD_GEM_SLOT	0x4EB0
#define IM_DB_LOG_EQUIP_APPEND_STAR		0x4EB1
#define IM_DB_LOG_EQUIP_COMBINE			0x4EB2
#define IM_DB_LOG_EQUIP_FORGE			0x4EB3
#define IM_DB_LOG_EQUIP_REFRESH_BIND	0x4EB4
#define IM_DB_LOG_EQUIP_REFRESH_ELEMENT	0x4EB5
#define IM_DB_LOG_EQUIP_REFRESH_FLOAT_ATTR 0x4EB6
#define IM_DB_LOG_EQUIP_REMOVE_GEM		0x4EB7
#define IM_DB_LOG_EQUIP_REMOVE_STAR		0x4EB8
#define IM_DB_LOG_EQUIP_STRENGTHEN		0x4EB9
#define IM_DB_LOG_EQUIP_UPGRADE			0x4EBA
#define IM_DB_LOG_PLAYER_DEAL			0x4EBB
#define IM_DB_SAVE_FAMILY_WAR_RESULT	0x4EBC
#define IM_DB_SAVE_TERRITORY_WAR_RESULT 0x4EBD
#define IM_DB_UPDATE_TERRITORY_WAR_RESULT 0x4EBE
#define IM_DB_LOG_GENERAL				0x4F18

// ==================== Construction / Destruction ====================

DBService::DBService()
{
}

DBService::~DBService()
{
	for (auto& pair : m_mConn)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = NULL;
		}
	}
	m_mConn.clear();
}

// ==================== Multi-connection Management ====================

DBService::ConnType* DBService::GetConn(int8_t index)
{
	auto it = m_mConn.find(index);
	if (it != m_mConn.end())
		return it->second;
	return NULL;
}

bool DBService::Connect(int8_t index, const std::string& host, int32_t port)
{
	ConnType* pConn = new ConnType(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER,
		16384 - NET_PACKET_HEAD_LEN, 0, 2000, "DBService", index, this);
	if (!pConn)
		return false;

	InetAddress serverAddr(host, (uint16_t)port);
	if (!pConn->connect(serverAddr))
	{
		delete pConn;
		return false;
	}

	pConn->start();
	m_mConn[index] = pConn;

	// Send initial connection message
	NetPacket* packet = pConn->popNetpacket();
	if (packet)
	{
		std::string val = pConn->getName();
		packet->writeUTF8(val);
		packet->setType(PACK_PROC);
		packet->setProc(IM_DB_GAME_SERVICE_CONNECT);
		packet->setSize(packet->getWOffset());
		pConn->sendPacket(packet);
	}

	return true;
}

void DBService::Init(int32_t line)
{
	if (line == 9)
		onLoadGMBackstage();
}

// ==================== onNetPacket Dispatcher ====================

void DBService::onNetPacket(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket)
	{
		if (inPacket) inPacket->destroy();
		return;
	}

	uint16_t proc = inPacket->getProc();
	switch (proc)
	{
	case IM_DB_PLAYER_LOADED:				onDBPlayerLoaded(pConn, inPacket); break;
	case IM_DB_PLAYER_SAVED:				onDBPlayerSaved(pConn, inPacket); break;
	case IM_DB_EQUIP_UPDATED:				onDBEquipUpdated(pConn, inPacket); break;
	case IM_DB_MYSJ_REWARD:				onUpdateMYSJReward(pConn, inPacket); break;
	case IM_DB_PET_UPDATED:				onDBPetUpdated(pConn, inPacket); break;
	case IM_DB_PET_DELETED:				onDBPetDeleted(pConn, inPacket); break;
	case IM_DB_CITYWAR_INFO_LOADED:		onCityWarInfoLoaded(pConn, inPacket); break;
	case IM_DB_PEERLESSWAR_INFO_LOADED:	onPeerlessWarInfoLoaded(pConn, inPacket); break;
	case IM_DB_CROSSTOWER_INFO_LOADED:		onCrossTowerInfoLoaded(pConn, inPacket); break;
	case IM_DB_SERVERBATTLE_INFO_LOADED:	onServerBattleLoaded(pConn, inPacket); break;
	case IM_DB_USER_PAYED:					onDBUserPayed(pConn, inPacket); break;
	case IM_DB_UPDATE_NEW_MAIL:			OnUpdateMailInfo(pConn, inPacket); break;
	case IM_DB_UPDATE_CITYWAR_RESULT:		onUpdateCityWarResult(pConn, inPacket); break;
	case IM_DB_UPDATE_KAIFU_TIME:			onUpdateKaiFuTime(pConn, inPacket); break;
	case IM_DB_UPDATE_GM_BROADCAST:		onUpdateGMBroadcast(pConn, inPacket); break;
	case IM_DB_UPDATE_GM_BAN_CHAT:			onUpdateGMBanChat(pConn, inPacket); break;
	case IM_DB_UPDATE_GM_SEAL:				onUpdateGMSeal(pConn, inPacket); break;
	case IM_DB_BACKSTAGE_KICK:				onBackStageKick(pConn, inPacket); break;
	case IM_DB_UPDATE_CROSSTOWER_RESULT:	onUpdateCrossTowerResutl(pConn, inPacket); break;
	case IM_DB_UPDATE_FAMILY_WAR_RESULT:	onUpdateFamilyWarResult(pConn, inPacket); break;
	case IM_DB_UPDATE_PEERLESSWAR_RESULT:	onUpdatePeerlessWarResult(pConn, inPacket); break;
	case IM_DB_UPDATE_BOSS_FIRST_KILLED:	onUpdateBossFirstKilled(pConn, inPacket); break;
	case IM_DB_UPDATE_TERRITORY_WAR_RESULT: onUpdateTerritoryWarResult(pConn, inPacket); break;
	case IM_DB_UPDATE_WORLD_BOSS_INFO:		onUpdateWorldBossInfo(pConn, inPacket); break;
	case IM_DB_UPDATE_EQUIPBACK_RECORD:	onUpdateEquipBackRecord(pConn, inPacket); break;
	case IM_DB_UPDATE_EQUIPBACK_INFO:		onUpdateEquipBackInfo(pConn, inPacket); break;
	case IM_DB_UPDATE_DOUBLEELEVEN_RANK:	onUpdateDoubleElevenRank(pConn, inPacket); break;
	case IM_DB_UPDATE_ZHYYHD_RANK:			onUpdateZHYYHDRank(pConn, inPacket); break;
	case IM_DB_UPDATE_DROP_TIMES:			onUpdateDropTimes(pConn, inPacket); break;
	case IM_DB_UPDATE_TENCENT_INFO:			onUpdateTencentInfo(pConn, inPacket); break;
	case IM_DB_UPDATE_RANSOM:				OnUpdateRansom(inPacket); break;
	default:								onPlayerNetPacket(pConn, inPacket); break;
	}

	inPacket->destroy();
}

// ==================== Player ====================

void DBService::savePlayer(int8_t connid, int32_t reason, int32_t param, PlayerDBData& dbData)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(reason);
	packet->writeInt32(param);
	packet->writeInt32(GAME_SERVICE.getId());
	dbData.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_PLAYER);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::loadPlayer(int8_t connid, int16_t cgindex, int64_t uid, int32_t sid, int32_t reason)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt8(connid);
	packet->writeInt16(cgindex);
	packet->writeInt64(uid);
	packet->writeInt32(sid);
	packet->writeInt32(reason);
	packet->writeInt32(GAME_SERVICE.getId());
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOAD_PLAYER);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::fengHao(int8_t connid, int8_t Type, int64_t Cid, const std::string& name)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt8(Type);
	packet->writeInt64(Cid);
	packet->writeUTF8(name);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_FENG_HAO);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::UpdateLoginTime(int8_t connid, CharId_t cid, int32_t login_time)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->writeInt32(login_time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_UPDATE_LOGIN_TIME);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogPlayerStay(int8_t connid, int32_t nTime, int32_t nDay)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nTime);
	packet->writeInt32(nDay);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_PLAYER_STAY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Equip ====================

void DBService::insertMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nReason);
	equip.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_INSERT_EQUIP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::updateMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nReason);
	equip.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_UPDATE_EQUIP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::deleteMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nReason);
	equip.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_DELETE_EQUIP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Pet ====================

void DBService::insertMemPet(int8_t connid, const MemPetDBData& pet)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	pet.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_INSERT_PET);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::updateMemPet(int8_t connid, const MemPetDBData& pet)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	pet.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_UPDATE_PET);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::deleteMemPet(int8_t connid, PetId_t nPetId)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(nPetId);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_DELETE_PET);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Task ====================

void DBService::insertTaskInfo(int8_t connid, const LogTask& task)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(task.cid);
	packet->writeInt32(task.tid);
	packet->writeInt32(task.type);
	packet->writeInt32(task.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_TASK_RECEIVE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::updateTaskInfo(int8_t connid, const LogTask& task)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(task.cid);
	packet->writeInt32(task.tid);
	packet->writeInt32(task.type);
	packet->writeInt32(task.time);
	packet->writeInt32(task.state);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_TASK_SUBMIT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Equip Logs ====================

void DBService::insertEquipEnhance(int8_t connid, const LogEquipEnhance& equip)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equip.cid);
	packet->writeUTF8(equip.name);
	packet->writeInt64(equip.equip_id);
	packet->writeInt32(equip.base_id);
	packet->writeInt32(equip.equip_quality);
	packet->writeInt32(equip.old_level);
	packet->writeInt32(equip.new_level);
	packet->writeInt32(equip.money_cost);
	packet->writeInt32(equip.sys_gold_cost);
	packet->writeInt32(equip.gold_cost);
	packet->writeInt32(equip.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_ENHANCE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::insertEquipAddgem(int8_t connid, const LogEquipAddGem& equipAddGem)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipAddGem.cid);
	packet->writeUTF8(equipAddGem.name);
	packet->writeUTF8(equipAddGem.equip_name);
	packet->writeInt32(equipAddGem.equip_quality);
	packet->writeUTF8(equipAddGem.gem_name);
	packet->writeInt32(equipAddGem.gem_level);
	packet->writeInt32(equipAddGem.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_ADD_GEM);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::insertItemCombine(int8_t connid, const LogItemCombine& itemCombine)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(itemCombine.cid);
	packet->writeUTF8(itemCombine.name);
	packet->writeInt32(itemCombine.old_item_id);
	packet->writeInt32(itemCombine.old_item_num);
	packet->writeInt32(itemCombine.new_item_id);
	packet->writeInt32(itemCombine.new_item_num);
	packet->writeInt32(itemCombine.money_cost);
	packet->writeInt32(itemCombine.sys_gold_cost);
	packet->writeInt32(itemCombine.gold_cost);
	packet->writeInt32(itemCombine.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ITEM_COMBINE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::insertEquipSmithing(int8_t connid, const LogEquipSmithing& equipSmithing)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipSmithing.cid);
	packet->writeUTF8(equipSmithing.name);
	packet->writeInt64(equipSmithing.equip_id);
	packet->writeInt32(equipSmithing.old_base_id);
	packet->writeInt32(equipSmithing.new_base_id);
	packet->writeInt32(equipSmithing.equip_quality);
	packet->writeInt32(equipSmithing.blueprint_id);
	packet->writeInt32(equipSmithing.blueprint_quality);
	packet->writeInt32(equipSmithing.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_SMITHING);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::insertEquipDismantle(int8_t connid, const LogEquipDismantle& equipDismantle)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipDismantle.cid);
	packet->writeUTF8(equipDismantle.name);
	packet->writeInt64(equipDismantle.equip_id);
	packet->writeInt32(equipDismantle.base);
	packet->writeInt32(equipDismantle.enhance);
	packet->writeInt32(equipDismantle.item1_id);
	packet->writeInt32(equipDismantle.item1_count);
	packet->writeInt32(equipDismantle.item2_id);
	packet->writeInt32(equipDismantle.item2_count);
	packet->writeInt32(equipDismantle.item3_id);
	packet->writeInt32(equipDismantle.item3_count);
	packet->writeInt32(equipDismantle.item4_id);
	packet->writeInt32(equipDismantle.item4_count);
	packet->writeInt32(equipDismantle.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_DISMANTLE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Dungeon ====================

void DBService::insertDungeon(int8_t connid, const LogDungeon& dungeon)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(dungeon.cid);
	packet->writeInt32(dungeon.did);
	packet->writeInt32(dungeon.type);
	packet->writeInt32(dungeon.level);
	packet->writeInt32(dungeon.start_time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_IN_DUNGEON);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::updateDungeon(int8_t connid, const LogDungeon& dungeon)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(dungeon.cid);
	packet->writeInt32(dungeon.did);
	packet->writeInt32(dungeon.state);
	packet->writeInt32(dungeon.start_time);
	packet->writeInt32(dungeon.finish_time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_OUT_DUNGEON);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Family ====================

void DBService::insertFamilyCreate(int8_t connid, const LogFamily& family)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(family.cid);
	packet->writeUTF8(family.name);
	packet->writeUTF8(family.family_name);
	packet->writeInt32(family.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_CREATE_FAMILY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::insertFamilyJoin(int8_t connid, const LogFamily& family)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(family.cid);
	packet->writeUTF8(family.name);
	packet->writeUTF8(family.family_name);
	packet->writeInt32(family.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_JOIN_FAMILY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::updateFamilyOut(int8_t connid, const LogFamily& family)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(family.cid);
	packet->writeUTF8(family.name);
	packet->writeUTF8(family.family_name);
	packet->writeInt32(family.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_OUT_FAMILY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Achievement ====================

void DBService::insertAchievement(int8_t connid, const LogAchievement& achievement)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(achievement.cid);
	packet->writeUTF8(achievement.name);
	packet->writeInt32(achievement.id);
	packet->writeInt32(achievement.type);
	packet->writeInt32(achievement.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ACHIEVEMENT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Yellow Stone ====================

void DBService::insertMemYelloStone(int8_t connid, const MemYellowStone& mys, int16_t type)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt16(type);
	packet->writeInt64(mys.cid);
	packet->writeInt32(mys.id);
	packet->writeInt32(mys.get_time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_INSERT_MEMYELLOWSTONE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Boss ====================

void DBService::InsertBossLog(int8_t connid, const LogBoss& boss)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(boss.mid);
	packet->writeInt32(boss.type);
	packet->writeInt64(boss.killer);
	packet->writeInt32(boss.time);
	packet->writeInt32(boss.mapId);
	packet->writeInt32(boss.MapMonsterId);
	packet->writeInt64(boss.EntityId);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_KILL_BOSS);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::SaveBossFirstKilled(int32_t BossId, CharId_t Cid, const std::string& Name, int32_t time)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeUTF8(Name);
	packet->writeInt64(Cid);
	packet->writeInt32(BossId);
	packet->writeInt32(time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_BOSS_FIRST_KILLED);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Activity / Gift ====================

void DBService::InsertActivityLog(int8_t connid, const LogActivity& activity)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(activity.cid);
	packet->writeInt32(activity.actid);
	packet->writeInt32(activity.acttype);
	packet->writeInt32(activity.time);
	packet->writeInt64(activity.param);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ACTIVITY_DATA);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::InsertDailyGiftLog(int8_t connid, const LogDailyGift& gift)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(gift.cid);
	packet->writeInt32(gift.type);
	packet->writeInt32(gift.giftid);
	packet->writeInt32(gift.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_DAILY_GIFT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Item Change ====================

void DBService::insertItemChange(int8_t connid, const LogItemChange& item)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(item.cid);
	packet->writeUTF8(item.name);
	packet->writeInt8(item.flag);
	packet->writeInt32(item.reason);
	packet->writeInt32(item.id);
	packet->writeInt8(item.itemClass);
	packet->writeInt32(item.count);
	packet->writeInt32(item.time);
	packet->writeInt64(item.srcId);
	packet->writeInt32(item.allCount);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ITEM_CHANGE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== MingGe ====================

void DBService::insertMingGeItem(int8_t connid, const MGLog& logStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	logStu.PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_MING_GE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Level Up ====================

void DBService::logLevelUp(int8_t connid, const LogPlayerLevel& logLevel)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(logLevel.cid);
	packet->writeUTF8(logLevel.name);
	packet->writeInt32(logLevel.level);
	packet->writeInt32(logLevel.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LEVEL_UP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Online Time ====================

void DBService::SaveOnlineTime(int8_t connid, CharId_t nCharId, int32_t nDayTime, int32_t nOnlineTime)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(nCharId);
	packet->writeInt32(nDayTime);
	packet->writeInt32(nOnlineTime);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_ONLINE_TIME);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Artifact Logs ====================

void DBService::logArtifactAddExp(int8_t connid, const LogArtifactAddExp& artifactAddExp)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(artifactAddExp.cid);
	packet->writeUTF8(artifactAddExp.name);
	packet->writeInt32(artifactAddExp.itemid);
	packet->writeInt32(artifactAddExp.baseid);
	packet->writeInt32(artifactAddExp.old_exp);
	packet->writeInt32(artifactAddExp.old_level);
	packet->writeInt32(artifactAddExp.new_exp);
	packet->writeInt32(artifactAddExp.new_level);
	packet->writeInt32(artifactAddExp.stone_id);
	packet->writeInt32(artifactAddExp.stone_count);
	packet->writeInt32(artifactAddExp.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ARTIFACT_ADD_EXP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logArtifactAddMaxLevel(int8_t connid, const LogArtifactAddMaxLevel& artifactAddMaxLevel)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(artifactAddMaxLevel.cid);
	packet->writeUTF8(artifactAddMaxLevel.name);
	packet->writeInt32(artifactAddMaxLevel.itemid);
	packet->writeInt32(artifactAddMaxLevel.baseid);
	packet->writeInt32(artifactAddMaxLevel.old_max_level);
	packet->writeInt32(artifactAddMaxLevel.new_max_level);
	packet->writeInt32(artifactAddMaxLevel.stone_id);
	packet->writeInt32(artifactAddMaxLevel.stone_count);
	packet->writeInt32(artifactAddMaxLevel.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ARTIFACT_ADD_MAX_LEVEL);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logArtifactAddQuality(int8_t connid, const LogArtifactAddQuality& artifactAddQuality)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(artifactAddQuality.cid);
	packet->writeUTF8(artifactAddQuality.name);
	packet->writeInt32(artifactAddQuality.itemid);
	packet->writeInt32(artifactAddQuality.baseid);
	packet->writeInt32(artifactAddQuality.old_quality);
	packet->writeInt32(artifactAddQuality.new_quality);
	packet->writeInt32(artifactAddQuality.stone_id);
	packet->writeInt32(artifactAddQuality.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_ARTIFACT_ADD_QUALITY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Equip Detail Logs ====================

void DBService::logEquipAddGemSlotNum(int8_t connid, const LogEquipAddGemSlot& equipAddGemSlot)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipAddGemSlot.cid);
	packet->writeUTF8(equipAddGemSlot.name);
	packet->writeInt64(equipAddGemSlot.eid);
	packet->writeInt32(equipAddGemSlot.baseid);
	packet->writeInt32(equipAddGemSlot.old_gem_slot_num);
	packet->writeInt32(equipAddGemSlot.new_gem_slot_num);
	packet->writeInt32(equipAddGemSlot.stone_id);
	packet->writeInt32(equipAddGemSlot.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_ADD_GEM_SLOT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipAppendStar(int8_t connid, const LogEquipAppendStar& equipAppendStar)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipAppendStar.cid);
	packet->writeUTF8(equipAppendStar.name);
	packet->writeInt64(equipAppendStar.eid);
	packet->writeInt32(equipAppendStar.baseid);
	packet->writeInt32(equipAppendStar.level);
	packet->writeInt32(equipAppendStar.fuxing_stone_id);
	packet->writeInt32(equipAppendStar.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_APPEND_STAR);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipCombine(int8_t connid, const LogEquipCombine& equipCombine)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipCombine.cid);
	packet->writeUTF8(equipCombine.name);
	packet->writeInt64(equipCombine.eid);
	packet->writeInt32(equipCombine.baseid);
	packet->writeInt32(equipCombine.new_baseid);
	packet->writeInt32(equipCombine.side_equip_1);
	packet->writeInt32(equipCombine.side_equip_2);
	packet->writeInt32(equipCombine.side_equip_3);
	packet->writeInt32(equipCombine.side_equip_4);
	packet->writeInt32(equipCombine.shouhu_stone_id);
	packet->writeInt32(equipCombine.money);
	packet->writeInt32(equipCombine.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_COMBINE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipForge(int8_t connid, const LogEquipForge& equipForge)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipForge.cid);
	packet->writeUTF8(equipForge.name);
	packet->writeInt64(equipForge.eid);
	packet->writeInt32(equipForge.baseid);
	packet->writeInt32(equipForge.item_id);
	packet->writeInt32(equipForge.money);
	packet->writeInt32(equipForge.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_FORGE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipRefreshBind(int8_t connid, const LogEquipRefreshBind& equipRefreshBind)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipRefreshBind.cid);
	packet->writeUTF8(equipRefreshBind.name);
	packet->writeInt64(equipRefreshBind.eid);
	packet->writeInt32(equipRefreshBind.baseid);
	packet->writeInt32(equipRefreshBind.old_bind);
	packet->writeInt32(equipRefreshBind.new_bind);
	packet->writeInt32(equipRefreshBind.stone_id);
	packet->writeInt32(equipRefreshBind.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_REFRESH_BIND);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipRefreshElement(int8_t connid, const LogEquipRefreshElement& equipRefreshElement)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipRefreshElement.cid);
	packet->writeUTF8(equipRefreshElement.name);
	packet->writeInt64(equipRefreshElement.eid);
	packet->writeInt32(equipRefreshElement.baseid);
	packet->writeInt32(equipRefreshElement.old_element);
	packet->writeInt32(equipRefreshElement.new_element);
	packet->writeInt32(equipRefreshElement.stone_id);
	packet->writeInt32(equipRefreshElement.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_REFRESH_ELEMENT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipRefreshFloatAttr(int8_t connid, const LogEquipRefreshFloatAttr& equipRefreshFloatAttr)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipRefreshFloatAttr.cid);
	packet->writeUTF8(equipRefreshFloatAttr.name);
	packet->writeInt64(equipRefreshFloatAttr.eid);
	packet->writeInt32(equipRefreshFloatAttr.baseid);
	packet->writeInt32(equipRefreshFloatAttr.old_float_attr);
	packet->writeInt32(equipRefreshFloatAttr.new_float_attr);
	packet->writeInt32(equipRefreshFloatAttr.stone_id);
	packet->writeInt32(equipRefreshFloatAttr.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_REFRESH_FLOAT_ATTR);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipRemoveGem(int8_t connid, const LogEquipRemoveGem& equipRemoveGem)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipRemoveGem.cid);
	packet->writeUTF8(equipRemoveGem.name);
	packet->writeInt64(equipRemoveGem.eid);
	packet->writeInt32(equipRemoveGem.baseid);
	packet->writeInt32(equipRemoveGem.slot_index);
	packet->writeInt32(equipRemoveGem.stone_id);
	packet->writeInt32(equipRemoveGem.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_REMOVE_GEM);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipRemoveStar(int8_t connid, const LogEquipRemoveStar& equipRemoveStar)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipRemoveStar.cid);
	packet->writeUTF8(equipRemoveStar.name);
	packet->writeInt64(equipRemoveStar.eid);
	packet->writeInt32(equipRemoveStar.baseid);
	packet->writeInt32(equipRemoveStar.level);
	packet->writeInt32(equipRemoveStar.fuxing_stone_id);
	packet->writeInt32(equipRemoveStar.shouhu_stone_id);
	packet->writeInt32(equipRemoveStar.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_REMOVE_STAR);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipStrengthen(int8_t connid, const LogEquipStrengthen& equipStrengthen)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipStrengthen.cid);
	packet->writeUTF8(equipStrengthen.name);
	packet->writeInt64(equipStrengthen.eid);
	packet->writeInt32(equipStrengthen.baseid);
	packet->writeInt32(equipStrengthen.old_strength);
	packet->writeInt32(equipStrengthen.new_strength);
	packet->writeInt32(equipStrengthen.stone_id);
	packet->writeInt32(equipStrengthen.stone_count);
	packet->writeInt32(equipStrengthen.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_STRENGTHEN);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logEquipUpgrade(int8_t connid, const LogEquipUpgrade& equipUpgrade)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(equipUpgrade.cid);
	packet->writeUTF8(equipUpgrade.name);
	packet->writeInt64(equipUpgrade.eid);
	packet->writeInt32(equipUpgrade.baseid);
	packet->writeInt32(equipUpgrade.new_baseid);
	packet->writeInt32(equipUpgrade.upgrade_stone_id);
	packet->writeInt32(equipUpgrade.upgrade_stone_count);
	packet->writeInt32(equipUpgrade.crystal_stone_id);
	packet->writeInt32(equipUpgrade.zhenxing_stone_id);
	packet->writeInt32(equipUpgrade.money);
	packet->writeInt32(equipUpgrade.time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_UPGRADE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Player Login / Deal / Currency ====================

void DBService::logPlayerLogin(int8_t connid, CharId_t cid, int32_t action, int32_t time, int32_t MapId)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->writeInt32(action);
	packet->writeInt32(time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_PLAYER_LOGIN);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logPlayerDeal(int8_t connid, CharId_t cid, const std::string& name, int64_t tcid, const std::string& tname, int32_t reason, int32_t money, const std::string& items, int32_t time)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt64(tcid);
	packet->writeUTF8(tname);
	packet->writeInt32(reason);
	packet->writeInt32(money);
	packet->writeUTF8(items);
	packet->writeInt32(time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_PLAYER_DEAL);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logCurrency(int8_t connid, CharId_t cid, const std::string& name, int32_t nType, int32_t opWay, int32_t nVal, int64_t nParam, int32_t nTime, int64_t LeftVal, int32_t FuLiLevel)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(nType);
	packet->writeInt32(opWay);
	packet->writeInt32(nVal);
	packet->writeInt64(nParam);
	packet->writeInt32(nTime);
	packet->writeInt64(LeftVal);
	packet->writeInt32(FuLiLevel);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_CURRENCY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== MoYuShiJie ====================

void DBService::logMoYuShiJieReward(int8_t connid, const LogMoYuShiJieReward& logInfo)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(logInfo.cid);
	packet->writeUTF8(logInfo.name);
	packet->writeInt32(logInfo.dungeonid);
	packet->writeInt32(logInfo.itemid);
	packet->writeInt8(logInfo.itemclass);
	packet->writeInt32(logInfo.itemcount);
	packet->writeInt32(logInfo.time);
	packet->writeInt8(logInfo.special);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_MYSJ_REWARD);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== ShangCheng (Shop) ====================

void DBService::logShangCheng(int8_t connid, CharId_t cid, const std::string& name, int32_t Type, int32_t ShopId, int32_t ItemClass, int32_t ItemId, int32_t ItemCount, int32_t CostGold, int64_t LeftGold, int32_t Time)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->writeUTF8(name);
	packet->writeInt32(Type);
	packet->writeInt32(ShopId);
	packet->writeInt32(ItemClass);
	packet->writeInt32(ItemId);
	packet->writeInt32(ItemCount);
	packet->writeInt32(CostGold);
	packet->writeInt64(LeftGold);
	packet->writeInt32(Time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_SHANG_CHENG);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Platform Logs ====================

void DBService::log360(int8_t connid, const Log360& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeUTF8(LogStu.Interface);
	packet->writeInt32(LogStu.UseSid);
	packet->writeUTF8(LogStu.passport);
	packet->writeUTF8(LogStu.LogString);
	packet->writeInt64(LogStu.Cid);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_360);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogProc(int8_t connid, const PacketProcLog& stu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(stu.nCid);
	packet->writeUTF8(stu.nName);
	packet->writeInt32(stu.nProcId);
	packet->writeInt32(stu.nTime);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_PROC);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::logGeneral(int8_t connid, const Generallog& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(LogStu.Time);
	packet->writeUTF8(LogStu.sString);
	packet->writeInt64(LogStu.nCid);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_GENERAL);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogUpEquipStar(int8_t connid, const UpStartLog& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(LogStu.nCid);
	packet->writeUTF8(LogStu.nName);
	packet->writeInt32(LogStu.nNewStar);
	packet->writeInt32(LogStu.nEquipId);
	packet->writeInt64(LogStu.nSrcId);
	packet->writeInt32(LogStu.nOpway);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_UP_EQUIP_STAR);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogEquipDrop(int8_t connid, const DropLog& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(LogStu.nCid);
	packet->writeUTF8(LogStu.sName);
	packet->writeInt32(LogStu.nEquipId);
	packet->writeInt64(LogStu.nSrcId);
	packet->writeInt32(LogStu.nMapId);
	packet->writeInt64(LogStu.nKiller);
	packet->writeUTF8(LogStu.sKillerName);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_EQUIP_DROP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogChangeMap(int8_t connid, const ChangeMapLog& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(LogStu.nCid);
	packet->writeUTF8(LogStu.sName);
	packet->writeInt32(LogStu.nCurMapId);
	packet->writeInt32(LogStu.nCurX);
	packet->writeInt32(LogStu.nCurY);
	packet->writeInt32(LogStu.nTarMapId);
	packet->writeInt32(LogStu.nTarX);
	packet->writeInt32(LogStu.nTarY);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_CHANGE_MAP);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::LogNpcFunc(int8_t connid, const NpcFuncLog& LogStu)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(LogStu.nCid);
	packet->writeUTF8(LogStu.sName);
	packet->writeInt32(LogStu.nFuncId);
	packet->writeInt32(LogStu.nMapId);
	packet->writeInt32(LogStu.nX);
	packet->writeInt32(LogStu.nY);
	packet->writeInt32(LogStu.nTime);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_LOG_NPC_FUNC);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== WorldBoss ====================

void DBService::SaveWorldBossInfo(const WorldBossInfo& info)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	info.PackageBossInfo(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_WORLDBOSS_INFO);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Ransom ====================

void DBService::OnAddRansom(DropEquipInfo& DropEquip)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(DropEquip.CharId);
	packet->writeUTF8(DropEquip.CharName);
	packet->writeInt64(DropEquip.KillerId);
	packet->writeUTF8(DropEquip.KillerName);
	packet->writeInt32(DropEquip.CanGetLastTime);
	packet->writeInt32(DropEquip.itemId);
	packet->writeInt8(DropEquip.itemClass);
	packet->writeInt32(DropEquip.itemCount);
	packet->writeInt8(DropEquip.bind);
	packet->writeInt32(DropEquip.endTime);
	packet->writeInt64(DropEquip.srcId);
	packet->writeInt32(DropEquip.Mid);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_ADD_RANSOM_INFO);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::OnDleRansom(EquipId_t EquipId)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(EquipId);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_DLE_RANSOM_INFO);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::OnUpdateRansom(Answer::NetPacket* inPacket)
{
	EQUIP_RANSOM.OnUpdatedRansom(inPacket);
}

// ==================== Mail ====================

void DBService::OnSendMail(int8_t connid, MailInfo& Mail, const std::string& Param, FamilyId_t nFamilyid)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(Mail.MailId);
	packet->writeInt32(Mail.SysMailId);
	packet->writeInt64(Mail.SenderId);
	packet->writeUTF8(Mail.SenderName);
	packet->writeInt64(Mail.ReceiveId);
	packet->writeUTF8(Mail.ReceiveName);
	packet->writeInt32(Mail.SendTime);
	packet->writeInt8(Mail.HasRead);
	packet->writeInt8(Mail.Extract);
	packet->writeUTF8(Mail.MailTitle);
	packet->writeUTF8(Mail.MailContent);
	packet->writeInt32(Mail.nReason);
	packet->writeUTF8(Mail.Param);
	if (Mail.Extract == 1)
	{
		int8_t Count = 0;
		int32_t Offset = packet->getWOffset();
		packet->writeInt8(Count);
		for (int8_t i = 0; i < MAIL_MAX_FU_JIAN_COUNT; ++i)
		{
			if (Mail.Item[i].itemId <= 0 || Mail.Item[i].itemCount <= 0)
				continue;
			packet->writeInt8(i);
			packet->writeInt32(Mail.Item[i].itemId);
			packet->writeInt8(Mail.Item[i].itemClass);
			packet->writeInt32(Mail.Item[i].itemCount);
			packet->writeInt8(Mail.Item[i].bind);
			packet->writeInt32(Mail.Item[i].endTime);
			packet->writeInt64(Mail.Item[i].srcId);
			Count++;
		}
		*(int8_t*)(packet->getBuffer() + Offset) = Count;
	}
	packet->writeInt64(nFamilyid);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SEND_MAIL_TO_DB);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::OnDeleteMail(int8_t connid, int32_t nMailId)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nMailId);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_DELETE_MAIL);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, const std::string& Param, FamilyId_t nFamilyid)
{
	MailInfo Mail = {};
	CfgSysMail* pSysMail = CFG_DATA.GetSysMail(SysMailId);
	if (NULL == pSysMail) return;

	if (pSysMail->sender_name.empty() || StringUtility::utf8Strlen(pSysMail->sender_name.c_str()) > MAX_NAME_CCH_LENGTH)
		return;
	if (pSysMail->title.empty() || StringUtility::utf8Strlen(pSysMail->title.c_str()) > MAIL_TITLE_MAX_LENGTH)
		return;
	if (pSysMail->content.empty() || StringUtility::utf8Strlen(pSysMail->content.c_str()) > MAIL_CONTENT_MAX_LENGTH)
		return;

	Mail.SysMailId = SysMailId;
	Mail.ReceiveId = ReceiverId;
	Mail.SendTime = DayTime::now();
	Mail.Param = Param;
	Mail.nReason = 2;

	int32_t FuJianCount = (int32_t)pSysMail->item.size();
	if (FuJianCount >= 1 && FuJianCount < MAIL_MAX_FU_JIAN_COUNT)
	{
		Mail.Extract = 1;
		for (int32_t i = 0; i < FuJianCount; ++i)
		{
			Mail.Item[i] = pSysMail->item[i];
		}
	}
	OnSendMail(connid, Mail, Param, nFamilyid);
}

void DBService::OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, const MemChrBagVector& items, int32_t nReason, const std::string& Param, FamilyId_t nFamilyid)
{
	MailInfo Mail = {};
	CfgSysMail* pSysMail = CFG_DATA.GetSysMail(SysMailId);
	if (NULL == pSysMail) return;

	if (pSysMail->sender_name.empty() || StringUtility::utf8Strlen(pSysMail->sender_name.c_str()) > MAX_NAME_CCH_LENGTH)
		return;
	if (pSysMail->title.empty() || StringUtility::utf8Strlen(pSysMail->title.c_str()) > MAIL_TITLE_MAX_LENGTH)
		return;
	if (pSysMail->content.empty() || StringUtility::utf8Strlen(pSysMail->content.c_str()) > MAIL_CONTENT_MAX_LENGTH)
		return;

	Mail.SysMailId = SysMailId;
	Mail.ReceiveId = ReceiverId;
	Mail.SendTime = DayTime::now();
	Mail.Param = Param;
	Mail.nReason = nReason;

	int32_t FuJianCount = (int32_t)items.size();
	if (FuJianCount >= 1 && FuJianCount < MAIL_MAX_FU_JIAN_COUNT)
	{
		Mail.Extract = 1;
		for (int32_t i = 0; i < FuJianCount; ++i)
		{
			Mail.Item[i] = items[i];
		}
	}
	OnSendMail(connid, Mail, Param, nFamilyid);
}

void DBService::OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, MemChrBag& item, int32_t nReason, const std::string& Param, FamilyId_t nFamilyid)
{
	MemChrBagVector items;
	if (item.itemId > 0 && item.itemCount > 0)
	{
		items.push_back(item);
	}
	OnSendSysMail(connid, ReceiverId, SysMailId, items, nReason, Param, nFamilyid);
}

void DBService::OnUpdateMailInfo(ConnType* pConn, Answer::NetPacket* inPacket)
{
	GAME_SERVICE.OnUpdateMail(inPacket);
}

// ==================== Timer ====================

void DBService::onNewMinuteCome(int32_t minute)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(minute);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_NEW_MINUTE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::OnUpdatePay()
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt8(0);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_UPDATE_PAY);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== CityWar ====================

void DBService::SaveCityWarResult(int32_t nActId, FamilyId_t nFamilyId, int32_t nWinTime, int32_t nTime,
	CharId_t nLeaderCid, CharId_t First, CharId_t Second, CharId_t Third,
	int32_t nIndex, const std::string& FirstFamilyName, const std::string& SecondFamilyName, const std::string& ThirdFamilyName)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nActId);
	packet->writeInt64(nFamilyId);
	packet->writeInt32(nWinTime);
	packet->writeInt32(nTime);
	packet->writeInt64(nLeaderCid);
	packet->writeInt64(First);
	packet->writeInt64(Second);
	packet->writeInt64(Third);
	packet->writeInt32(nIndex);
	packet->writeUTF8(FirstFamilyName);
	packet->writeUTF8(SecondFamilyName);
	packet->writeUTF8(ThirdFamilyName);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_CITYWAR_RESULT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::onLoadCityWarInfo()
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(pConn->GetId());
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_CITYWAR_INFO);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ==================== CrossTower ====================

void DBService::SaveCrossTowerResult(int32_t nActId, CharId_t Winner, const std::string& name, int32_t battle, int8_t connid, int32_t time)
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			if (pConn->GetId() == connid)
			{
				packet->writeInt32(nActId);
				packet->writeInt64(Winner);
				packet->writeUTF8(name);
				packet->writeInt32(battle);
			}
			else
			{
				packet->writeInt32(nActId);
				packet->writeInt64(0);
				packet->writeUTF8("");
				packet->writeInt32(0);
			}
			packet->writeInt32(time);
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_SAVE_CROSSTOWER_RESULT);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

void DBService::onLoadCrossTowerInfo()
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(pConn->GetId());
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_CROSSTOWER_INFO);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ==================== PeerlessWar ====================

void DBService::SavePeerlessWarResult(int32_t nActId, CharId_t winner, const std::string& name, int32_t nTime)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nActId);
	packet->writeInt32(nTime);
	packet->writeInt64(winner);
	packet->writeUTF8(name);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_PEERLESSWAR_RESULT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::onLoadPeerlessWarInfo()
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(pConn->GetId());
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_PEERLESSWAR_INFO);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ==================== FamilyWar (legacy) ====================

void DBService::SaveFamilyWarResult(int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes, int32_t nTime, const std::string& FamilyName, const std::string& LeaderName)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nActId);
	packet->writeInt64(nFamilyId);
	packet->writeInt16(nWinTimes);
	packet->writeInt32(nTime);
	packet->writeUTF8(FamilyName);
	packet->writeUTF8(LeaderName);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_FAMILY_WAR_RESULT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== TerritoryWar (legacy) ====================

void DBService::SaveTerritoryWarResult(int32_t nActId, const std::string& winners, int32_t nTime)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nActId);
	packet->writeInt32(nTime);
	packet->writeUTF8(winners);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_TERRITORY_WAR_RESULT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== ServerBattle ====================

void DBService::onLoadServerBattle()
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(pConn->GetId());
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_SERVERBATTLE_INFO);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ==================== DoubleEleven ====================

void DBService::LoadDoubleElevenRank(int8_t nType, int8_t nDay)
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(nType);
			packet->writeInt8(nDay);
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_DOUBLEELEVEN_RANK);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

void DBService::SaveDoubleElevenRank(int8_t connid, int8_t nType, int16_t nDay, int16_t nIndex, const FestivalRank& info)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt8(nType);
	packet->writeInt16(nDay);
	packet->writeInt16(nIndex);
	packet->writeInt64(info.nCharId);
	packet->writeUTF8(info.strName);
	packet->writeInt32(info.nScore);
	packet->writeInt32(info.nTime);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_DOUBLEELEVEN_RANK);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== ZHYYHD ====================

void DBService::LoadZHYYHDRank(int8_t nType, int8_t nDay)
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) return;
			packet->writeInt8(nType);
			packet->writeInt8(nDay);
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_ZHYYHD_RANK);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

void DBService::SaveZHYYHDRank(int8_t connid, int8_t nType, int16_t nDay, const FestivalRankVector& vRank)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt8(nType);
	packet->writeInt16(nDay);
	packet->writeInt16((int16_t)vRank.size());
	for (size_t i = 0; i < vRank.size(); ++i)
	{
		packet->writeInt16(vRank[i].nIndex);
		packet->writeInt64(vRank[i].nCharId);
		packet->writeUTF8(vRank[i].strName);
		packet->writeInt32(vRank[i].nScore);
		packet->writeInt32(vRank[i].nTime);
	}
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_ZHYYHD_RANK);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== DropTimes ====================

void DBService::SaveDropTimes(int32_t nGroupId, int32_t nTimes)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nGroupId);
	packet->writeInt32(nTimes);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_DROP_TIMES);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::ClearDropTimes()
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_CLEAR_DROP_TIMES);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== DropRecord ====================

void DBService::SaveDropRecord(const DropRecord& record)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeUTF8(record.strName);
	packet->writeInt64(record.nCharId);
	packet->writeInt32(record.nMapId);
	packet->writeInt32(record.nMid);
	packet->writeInt32(record.nRecord);
	packet->writeInt32(record.nTime);
	packet->writeInt8(record.nSpecial);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_DROP_RECORD);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Tencent ====================

void DBService::ReloadTencentInfo(int8_t connid, CharId_t cid)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(cid);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_RELOAD_TENCENT_INFO);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Mobile Phone / Guard ====================

void DBService::CheckMobilePhoneGiftEffect(int8_t connid, int16_t cgindex, int32_t sid, const std::string& passport, int8_t nType)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt16(cgindex);
	packet->writeInt32(sid);
	packet->writeUTF8(passport);
	packet->writeInt8(nType);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_CHECK_MOBILE_PHONE_GIFT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::CheckGuardPrivilege(int8_t connid, int16_t cgindex, int64_t uid, int32_t sid, int8_t type, int32_t param, int8_t index)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt16(cgindex);
	packet->writeInt64(uid);
	packet->writeInt32(sid);
	packet->writeInt8(type);
	packet->writeInt32(param);
	packet->writeInt8(index);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_CHECK_GUARD_PRIVILEGE);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== DBClick Game ====================

void DBService::OnDBClickGame(int8_t connid, int64_t uid, int32_t sid, int32_t start_time)
{
	ConnType* pConn = GetConn(connid);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt64(uid);
	packet->writeInt32(sid);
	packet->writeInt32(start_time);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_CLICK_GAME);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== Equip Back ====================

void DBService::SaveEquipBackCount(int32_t nId, int8_t nType, int32_t nCount, std::string& name)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nId);
	packet->writeInt8(nType);
	packet->writeInt32(nCount);
	packet->writeUTF8(name);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_EQUIPBACK_COUNT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::SaveEquipBackRecord(int32_t nId, int8_t nType, int32_t nTime, std::string& name)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(nId);
	packet->writeInt8(nType);
	packet->writeInt32(nTime);
	packet->writeUTF8(name);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_EQUIPBACK_RECORD);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== GuiGuDaoRen ====================

void DBService::SaveGuiGuDaoRenData(int32_t NpcId, int32_t Count)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(NpcId);
	packet->writeInt32(Count);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_GUIGU_DAOREN);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::SaveGuiGuBackEquipCount(int32_t Count)
{
	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	packet->writeInt32(Count);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_GUIGU_BACK_COUNT);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

void DBService::SaveGuiGuBackEquipRank(EquipBackRankCfg* p_stu)
{
	if (!p_stu) return;

	ConnType* pConn = GetConn(0);
	if (!pConn) return;

	NetPacket* packet = pConn->popNetpacket();
	if (!packet) return;

	p_stu->PackageData(packet);
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_SAVE_GUIGU_BACK_RANK);
	packet->setSize(packet->getWOffset());
	pConn->sendPacket(packet);
}

// ==================== DB Response Handlers ====================

void DBService::onDBPlayerLoaded(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t reason = inPacket->readInt32();
	PlayerDBData dbData;
	dbData.UnPackageData(inPacket);
	GAME_SERVICE.onPlayerLoaded(dbData, reason, pConn->GetId());
}

void DBService::onDBPlayerSaved(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	CharId_t cid = inPacket->readUInt64();
	string name = inPacket->readUTF8(true);
	int32_t ticks = inPacket->readInt32();
	int64_t uid = inPacket->readInt64();
	int32_t sid = inPacket->readInt32();
	int32_t reason = inPacket->readInt32();
	int32_t param = inPacket->readInt32();

	LOG_DEBUG("use %d ticks to save player cid = %lld, name = %s\n", ticks, cid, name.c_str());
	GAME_SERVICE.onPlayerSaved(pConn->GetId(), uid, sid, reason, param, cid);
}

void DBService::onDBEquipUpdated(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	MemEquipVector equips;
	int32_t count = inPacket->readInt32();
	equips.reserve(count);
	for (int32_t i = 0; i < count; ++i)
	{
		MemEquip equip;
		equip.UnPackageData(inPacket);
		equips.push_back(equip);
	}
	EQUIP_MANAGER.OnEquipUpdated(equips);
}

void DBService::onDBUserPayed(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	GAME_SERVICE.onUserPayed(inPacket);
}

void DBService::onDBPetUpdated(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	MemPetDBData pet;
	pet.UnPackageData(inPacket);
	PET_MANAGER.OnUpdated(pet);
}

void DBService::onDBPetDeleted(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	PetId_t nPetId = inPacket->readInt64();
	PET_MANAGER.OnDeleted(nPetId);
}

void DBService::onUpdateMYSJReward(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	LogMoYuShiJieReward logInfo;
	memset(&logInfo, 0, sizeof(logInfo));
	logInfo.cid = inPacket->readInt64();
	string name = inPacket->readUTF8(true);
	snprintf(logInfo.name, sizeof(logInfo.name), "%s", name.c_str());
	logInfo.dungeonid = inPacket->readInt32();
	logInfo.itemid = inPacket->readInt32();
	logInfo.itemclass = inPacket->readInt8();
	logInfo.itemcount = inPacket->readInt32();
	logInfo.time = inPacket->readInt32();
	logInfo.special = inPacket->readInt8();
	GAME_SERVICE.AddMoYuShiJieRecord(logInfo);
}

void DBService::onCityWarInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int64_t nFamilyId = inPacket->readInt64();
	ACTIVITY_MANAGER.SetCityWarWinner(pConn->GetId(), nFamilyId);
}

void DBService::onPeerlessWarInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int64_t nCharId = inPacket->readInt64();
	ACTIVITY_MANAGER.SetPeerlessWarWinner(pConn->GetId(), nCharId);
}

void DBService::onCrossTowerInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	CharId_t nCharId = inPacket->readInt64();
	int32_t nBattle = inPacket->readInt32();
	string sName = inPacket->readUTF8(true);
	if (nCharId > 0)
	{
		ACTIVITY_MANAGER.SetCrossTowerWinner(nCharId, nBattle, sName);
	}
}

void DBService::onServerBattleLoaded(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t Battle = inPacket->readInt32();
	if (Battle > 0)
	{
		GAME_SERVICE.SetServerBattle(Battle);
	}
}

void DBService::onUpdateCityWarResult(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nActId = inPacket->readInt32();
	FamilyId_t nFamilyId = inPacket->readInt64();
	int32_t nWinTime = inPacket->readInt32();
	int32_t nTime = inPacket->readInt32();
	CharId_t nLeaderCid = inPacket->readInt64();
	CharId_t First = inPacket->readInt64();
	CharId_t Second = inPacket->readInt64();
	CharId_t Third = inPacket->readInt64();
	int32_t nIndex = inPacket->readInt32();
	string FirstFamilyName = inPacket->readUTF8(true);
	string SecondFamilyName = inPacket->readUTF8(true);
	string ThirdFamilyName = inPacket->readUTF8(true);
	ACTIVITY_MANAGER.OnCityWarResult(pConn->GetId(), nActId, nFamilyId, nWinTime, nTime,
		nLeaderCid, First, Second, Third, nIndex, FirstFamilyName, SecondFamilyName, ThirdFamilyName);
}

void DBService::onUpdateKaiFuTime(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t kaiFuTime = inPacket->readInt32();
	CFG_DATA.updateServerStartTime(kaiFuTime);
}

void DBService::onUpdateGMBroadcast(ConnType* pConn, Answer::NetPacket* inPacket)
{
	GM_BACKSTAGE.onUpdateGMBroadcast(inPacket);
}

void DBService::onUpdateGMBanChat(ConnType* pConn, Answer::NetPacket* inPacket)
{
	GM_BACKSTAGE.onUpdateGMBanChat(inPacket);
	if (GAME_SERVICE.getLine() == 1)
	{
		int8_t Id = pConn->GetId();
		NetPacket* packet = GAME_SERVICE.popNetpacket(Id, PACK_DISPATCH, 0x4E4E);
		if (packet)
		{
			uint32_t Size = inPacket->getSize();
			char* Buffer = inPacket->getBuffer();
			packet->write(Buffer, Size);
			packet->setSize(packet->getWOffset());
			GAME_SERVICE.sendPacket(Id, packet);
		}
	}
}

void DBService::onUpdateGMSeal(ConnType* pConn, Answer::NetPacket* inPacket)
{
	GM_BACKSTAGE.onUpdateGMSeal(inPacket);
}

void DBService::onBackStageKick(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	CharId_t nCharId = inPacket->readInt64();
	if (nCharId <= 0)
		GAME_SERVICE.KickAll(1);
	else
		GAME_SERVICE.KickUser(nCharId, 1);
}

void DBService::onUpdateCrossTowerResutl(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nActId = inPacket->readInt32();
	CharId_t Winner = inPacket->readInt64();
	int32_t Battle = inPacket->readInt32();
	string Name = inPacket->readUTF8(true);
	ACTIVITY_MANAGER.OnCrossTower(pConn->GetId(), nActId, Winner, Name, Battle);
}

void DBService::onUpdateFamilyWarResult(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nActId = inPacket->readInt32();
	FamilyId_t familyWarWinner = inPacket->readInt64();
	int16_t familyWarWinTimes = inPacket->readInt16();
	string familyName = inPacket->readUTF8(true);
	string leaderName = inPacket->readUTF8(true);
	ACTIVITY_MANAGER.OnFamilyWarResult(nActId, familyWarWinner, familyWarWinTimes, familyName, leaderName);
}

void DBService::onUpdatePeerlessWarResult(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nActId = inPacket->readInt32();
	CharId_t winner = inPacket->readInt64();
	string name = inPacket->readUTF8(true);
	ACTIVITY_MANAGER.OnPeerlessWarResult(pConn->GetId(), nActId, winner, name);
}

void DBService::onUpdateBossFirstKilled(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	string strName = inPacket->readUTF8(true);
	CharId_t nCharId = inPacket->readInt64();
	int32_t BossId = inPacket->readInt32();
	int32_t time = inPacket->readInt32();
	KAI_FU_HUO_DONG.OnUpdateKilledMonster(BossId, nCharId, strName, time);
}

void DBService::onUpdateTerritoryWarResult(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nActId = inPacket->readInt32();
	string winners = inPacket->readUTF8(true);
	ACTIVITY_MANAGER.OnTerritoryWarResult(nActId, winners);
}

void DBService::onUpdateWorldBossInfo(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	WorldBossInfo info;
	info.UnPackageBossInfo(inPacket);
	WORLD_BOSS.UpdateWorldBossInfo(info);
}

void DBService::onUpdateEquipBackRecord(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nId = inPacket->readInt32();
	int8_t nType = inPacket->readInt8();
	int32_t nTime = inPacket->readInt32();
	string sName = inPacket->readUTF8(true);
	EQUIP_BACK.UpdateEquipRecord(nId, nType, nTime, sName);
}

void DBService::onUpdateEquipBackInfo(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nId = inPacket->readInt32();
	int8_t nType = inPacket->readInt8();
	int32_t nCount = inPacket->readInt32();
	string sName = inPacket->readUTF8(true);
	EQUIP_BACK.UpdateEquipBackInfo(nId, nType, nCount, sName);
}

void DBService::onUpdateDoubleElevenRank(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int8_t nType = inPacket->readInt8();
	int16_t nDay = inPacket->readInt16();
	int16_t nSize = inPacket->readInt16();
	for (int16_t i = 0; i < nSize; ++i)
	{
		FestivalRank info;
		int16_t nIndex = inPacket->readInt16();
		info.nCharId = inPacket->readInt64();
		info.strName = inPacket->readUTF8(true);
		info.nScore = inPacket->readInt32();
		info.nTime = inPacket->readInt32();
		FESTIVAL_DOUBLE_ELEVEN.UpdateRank(pConn->GetId(), nType, nDay, nIndex, info);
	}
}

void DBService::onUpdateZHYYHDRank(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int8_t nType = inPacket->readInt8();
	int16_t nDay = inPacket->readInt16();
	int16_t nSize = inPacket->readInt16();
	FestivalRankVector vRank;
	vRank.resize(nSize);
	for (int16_t i = 0; i < nSize; ++i)
	{
		vRank[i].nIndex = inPacket->readInt16();
		vRank[i].nCharId = inPacket->readInt64();
		vRank[i].strName = inPacket->readUTF8(true);
		vRank[i].nScore = inPacket->readInt32();
		vRank[i].nTime = inPacket->readInt32();
	}
	ZONG_HE_YUN_YING_HD.UpdateRankInfo(pConn->GetId(), nType, nDay, vRank);
}

void DBService::onUpdateDropTimes(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int32_t nGroupId = inPacket->readInt32();
	int32_t nTimes = inPacket->readInt32();
	GAME_SERVICE.UpdateDropTimes(nGroupId, nTimes);
}

void DBService::onUpdateTencentInfo(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	CharId_t cid = inPacket->readInt64();
	TencentInfo info;
	info.UnPacketInfo(inPacket);
	GAME_SERVICE.UpdateTencentInfo(cid, info);
}

// ==================== GM Backstage ====================

void DBService::onLoadGMBackstage()
{
	for (auto& pair : m_mConn)
	{
		ConnType* pConn = pair.second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (!packet) continue;
			packet->writeInt8(pConn->GetId());
			packet->setType(PACK_PROC);
			packet->setProc(IM_DB_LOAD_GM_BACKSTAGE);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ==================== Player Packet Forwarding ====================

void DBService::onPlayerNetPacket(ConnType* pConn, Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int16_t nProc = inPacket->readInt16();
	GAME_SERVICE.OnDBNetPacket(pConn->GetId(), nProc, inPacket);
}
