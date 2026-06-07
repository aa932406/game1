#include "stdafx.h"

#include "ActivityManager.h"
#include "CfgData.h"
#include "DBService.h"
#include "GameService.h"
#include "Map.h"
#include "MapManager.h"
#include "Monster.h"
#include "MonsterActivity.h"
#include "NpcActivity.h"
#include "PlantActivity.h"
#include "Player.h"
#include "PlayerRobot.h"
#include "Tile.h"
#include "Trailer.h"
#include "EquipManager.h"
#include "PoolManager.h"
#include "PetManager.h"
#include "FamilyManager.h"
#include "Timer.h"
#include "DaTiHD.h"
#include "KaiFuHuoDong.h"
#include "GMBackstage.h"
#include "FestivalDoubleEleven.h"
#include "RankMirror.h"
#include "GuiGuDaoRen.h"
#include "Tencent.h"
#include <string>
using namespace Answer;
using namespace std;

// ============================================================
// Helper
// ============================================================
inline int32_t getUserIndex(int8_t connid, int16_t cgindex)
{
	return static_cast<int32_t>(connid) * MAX_CONNECTION + cgindex;
}

// ============================================================
// Constructor / Destructor
// ============================================================
GameService::GameService()
	: TcpService(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER, 2048-NET_PACKET_HEAD_LEN, 0, 2000, "GameService")
	, m_line(0)
	, m_id(0)
	, m_serverBattle(0)
{
	bzero(m_users, sizeof(m_users));
	bzero(m_onLineBroadcast, sizeof(m_onLineBroadcast));
}

GameService::~GameService()
{
}

// ============================================================
// Multi-connection support (2019)
// ============================================================
void GameService::setId(int32_t id)
{
	m_id = id;
}

void GameService::setLine(int32_t line)
{
	m_line = line;
}

bool GameService::Connect(int8_t index, const std::string& host, int32_t port)
{
	if (index < 0 || index >= MAX_GATE_CONNS)
		return false;

	GameConn* pConn = new GameConn(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER,
		2048 - NET_PACKET_HEAD_LEN, 0, 2000, "GameService", index, this);

	if (!pConn)
		return false;

	InetAddress serverAddr(host, port);
	if (pConn->connect(serverAddr))
	{
		pConn->start();
		m_mConn[index] = pConn;

		// Send connection handshake
		NetPacket* packet = pConn->popNetpacket();
		if (packet)
		{
			packet->writeInt32(m_line);
			packet->writeUTF8(GetVersion());
			packet->writeUTF8(GetServerVersion());
			packet->writeUTF8(pConn->getName());
			packet->setSize(packet->getWOffset());
			packet->setType(PACK_PROC);
			packet->setProc(0x4E22);
			pConn->sendPacket(packet);
		}
		return true;
	}

	delete pConn;
	return false;
}

GameConn* GameService::GetConn(int8_t connid)
{
	std::map<int8_t, GameConn*>::iterator it = m_mConn.find(connid);
	if (it != m_mConn.end())
		return it->second;
	return NULL;
}

int8_t GameService::GetAutoConnId()
{
	if (m_mConn.empty())
		return 0;
	return m_mConn.begin()->first;
}

int8_t GameService::GetConnId(CharId_t cid)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(cid);
	if (iter != m_players.end())
	{
		Player* pPlayer = iter->second;
		if (pPlayer)
			return pPlayer->getConnId();
	}
	return 0;
}

std::string GameService::GetVersion()
{
	Answer::Inifile ini;
	ini.parse(std::string("version.ini"));
	return ini.getStrValue("Version", "versionName");
}

// ============================================================
// onNetPacket — 2019 multi-connection dispatch
// ============================================================
void GameService::onNetPacket(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == pConn || NULL == inPacket)
		return;

	uint16_t proc = inPacket->getProc();
	int8_t connid = pConn->GetId();

	if (proc > IM_MIN && proc < IM_MAX)
	{
		// Gate/Social range
		if (proc > 0x4E20 && proc <= 0x61AA)  // IM_GATE range
		{
			if (proc > IM_SOCIAL_GAME_MIN && proc < IM_SOCIAL_GAME_MAX)
			{
				onSocialNetpacket(pConn, inPacket);
			}
			else if (proc <= 0x4E54 || proc > 0x4E77)
			{
				switch (proc)
				{
				case 0x4E26:  onAddUser(pConn, inPacket); break;
				case 0x4E27:  onRemoveUser(pConn, inPacket); break;
				case 0x4E29:  onGMReloadItem(pConn, inPacket); break;
				case 0x4E2D:  onGateDisconnect(pConn, inPacket); break;
				case 0x4E7E:  onSocialUpdatePetRank(pConn, inPacket); break;
				case 0x4E7F:  onSocialUpdateFamilyInfo(pConn, inPacket); break;
				case 0x4E80:  onSocialUpdateRankMirror(pConn, inPacket); break;
				case 0x4E81:  onSetWorldLevel(pConn, inPacket); break;
				case 0x4E82:  OnReceiveDaTiResult(pConn, inPacket); break;
				case 0x4E83:  OnSocialCityMasterBanChat(pConn, inPacket); break;
				case 0x4E86:  onSocialInitPetRank(pConn, inPacket); break;
				case 0x4E87:  onSocialCreateTeamDungeon(pConn, inPacket); break;
				case 0x4E88:  OnReceiveDaTiRank(pConn, inPacket); break;
				case 0x4E89:  onSocialSendSystemMail(pConn, inPacket); break;
				case 0x4E8A:  onSocialSendSystemMail2(pConn, inPacket); break;
				case 0x4E8B:  onSocialInitRankMirror(pConn, inPacket); break;
				case 0x4E8C:  onSocialQueryPlayerInfo(pConn, inPacket); break;
				case 0x4E8D:  onRequestDropRecord(pConn, inPacket); break;
				case 0x4E8E:  onSocialInitFamilyInfo(pConn, inPacket); break;
				case 0x4EC1:  // ZongHeYunYing update
					ZONG_HE_YUN_YING_HD.UpdatePlayerInfo(connid, inPacket); break;
				case 0x4EC4:  onUpdateActivityState(pConn, inPacket); break;
				case 0x4EEA:  qqToPlayer(pConn, inPacket); break;
				default: break;
				}
			}
			else
			{
				onSocialNetpacket(pConn, inPacket);
			}
		}
		// Legacy range — fallthrough to index-based
	}
	else
	{
		int16_t cgindex = static_cast<int16_t>(inPacket->readInt32());
		if (cgindex > 0 && cgindex < MAX_CONNECTION)
		{
			switch (proc)
			{
			case CM_ENTER_GAME:       onEnterGame(connid, cgindex, inPacket); break;
			case CM_ENTER_GAME_ROBOT: onEnterGameRobot(connid, cgindex, inPacket); break;
			default: onGameNetpacket(connid, cgindex, inPacket); break;
			}
		}
	}

	inPacket->destroy();
}

// ============================================================
// startGame / stopGame
// ============================================================
void GameService::startGame(int32_t line)
{
	m_line = line;

	Player::initNetPacketHandlers();
	InitServerBattle();

	TILE_MANAGER.Init();
	MAP_MANAGER.Init();
	MAP_MANAGER.StartAll();

	ACTIVITY_MANAGER.Init(line);
	GM_BACKSTAGE.Init(line);
	FESTIVAL_DOUBLE_ELEVEN->Init(line);
	ZONG_HE_YUN_YING_HD.Init(line);
	KAI_FU_RECHARGE.Init(line);
	FESTIVAL_ACTIVITY.Init();

	InitDropTimes();
	InitMoYuShiJieRecord();

	requestSocialData();
	requestWorldLevel();

	if (m_line == GAME_SERVICE_LINE_SOCIAL)
	{
		SendServerDiffToGlobal();
		NetPacket* packet = popNetpacket(PACK_PROC, 0x4E30);
		if (packet)
		{
			packet->writeInt32(CFG_DATA.getDebug());
			packet->setSize(packet->getWOffset());
			sendPacket(0, packet);
		}
	}
}

void GameService::stopGame()
{
	MAP_MANAGER.StopAll();

	if (getLine() != GAME_SERVICE_LINE_CROSS)
		saveAllPlayerToDB();
}

int32_t GameService::getLine()
{
	return m_line;
}

// ============================================================
// onNewMinuteCome / OnDaySwitch / onUpdatePay
// ============================================================
void GameService::onNewMinuteCome(int32_t minute)
{
	FESTIVAL_DOUBLE_ELEVEN->OnNewMinute(minute);
	GUI_GU_DAO_REN.OnNewMinute(minute);

	if (m_line == GAME_SERVICE_LINE_SOCIAL)
	{
		DB_SERVICE.onNewMinuteCome(0, minute);

		NetPacket* packet = popNetpacket(0, PACK_PROC, 0x4E38);
		if (NULL == packet)
			return;
		packet->writeInt32(minute);
		packet->setSize(packet->getWOffset());
		sendPacket(0, packet);
	}

	// Every 5 minutes, clean expired ChatValidate entries
	if (!(minute % 5))
	{
		int32_t Time = DayTime::now();
		Answer::MutexGuard lock(m_ChatValidateLock);
		std::map<int32_t, ChatValidate>::iterator it = m_ChatValidateMap.begin();
		while (it != m_ChatValidateMap.end())
		{
			if (Time - it->second.Time > 300)
			{
				if (it->second.SendPacket)
					it->second.SendPacket->destroy();
				m_ChatValidateMap.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}
}

void GameService::OnDaySwitch()
{
	if (m_line == GAME_SERVICE_LINE_SOCIAL)
	{
		ResetDropTimes();
		SendServerDiffToGlobal();
	}
}

void GameService::onUpdatePay()
{
	if (m_line == GAME_SERVICE_LINE_SOCIAL)
	{
		DB_SERVICE.OnUpdatePay(0);
	}
}

// ============================================================
// onPlayerLoaded / onPlayerLogout / onPlayerSaved
// ============================================================
void GameService::onPlayerLoaded(PlayerDBData& dbData, int32_t reason, bool isRobot)
{
	Player* player = getPlayer(dbData.chr.data.cid, 0, false);
	if (player != NULL)
	{
		Map* pMap = player->getMap();
		int32_t mapid = 0;
		if (pMap != NULL)
			mapid = pMap->GetId();

		LOG_INFO("GameService::onPlayerLoaded player cid = %lld, map = %p, mapid = %d already in game\n",
			dbData.chr.data.cid, pMap, mapid);
		return;
	}

	Map* pMap = MAP_MANAGER.GetMap(dbData.chr.data.mapid);
	if (pMap == NULL)
	{
		int32_t nRegion = 20001;
		if (dbData.chr.data.mapid > 0)
		{
			if (reason == 3 && getLine() == GAME_SERVICE_LINE_CROSS)
				nRegion = 20002;
		}
		else
		{
			nRegion = 10002;
		}

		CfgMapRegion* pCfgRegion = CFG_DATA.getMapRegion(nRegion);
		if (pCfgRegion != NULL)
		{
			Map* pTempMap = MAP_MANAGER.GetMap(pCfgRegion->mapid);
			if (pTempMap != NULL)
			{
				Position pos = pTempMap->getRandomWalkablePositionInRegion(*pCfgRegion);
				if (pos.x >= 0 && pos.y >= 0)
				{
					pMap = pTempMap;
					dbData.chr.data.mapid = pMap->GetId();
					dbData.chr.data.x = pos.x;
					dbData.chr.data.y = pos.y;
				}
			}
		}
	}

	if (pMap != NULL)
	{
		int32_t nIndex = getUserIndex(dbData.connid, dbData.cgindex);
		User* pUser = NULL;
		{
			Answer::MutexGuard lock(m_userLock);
			pUser = m_users[nIndex];
		}

		if (pUser != NULL)
		{
			if (pUser->getPlayer() != NULL)
			{
				LOG_ERROR("GameService::onPlayerLoaded user already have player cgindex=%d, cid = %lld\n",
					dbData.cgindex, dbData.chr.data.cid);
			}
			else
			{
				if (isRobot)
				{
					player = new PlayerRobot;
					player->reset();
				}
				else
				{
					player = POOL_MANAGER.pop<Player>();
				}

				if (player != NULL)
				{
					// Init TencentInfo from User
					TencentInfo info;
					pUser->GetTencentInfo(info);
					player->InitTencentInfo(&info);

					player->init(dbData);
					pUser->setPlayer(player);
					AddPlayer(player, reason);

					if (!player->reconnect())
					{
						MAP_MANAGER.PostMsg(pMap->GetRunnerId(), GMC_PLAYER_ENTER_MAP,
							player, pMap, dbData.chr.data.x, dbData.chr.data.y, 0);

						// Cross-server activity info
						if (getLine() == GAME_SERVICE_LINE_CROSS)
						{
							int32_t nActId = ACTIVITY_MANAGER.GetCurActivityId(
								player->GetOperateLimit().GetLimitCount(1057));
							NetPacket* packet = popNetpacket(player->getConnId(), PACK_DISPATCH, 0x1D);
							if (packet)
							{
								packet->writeInt32(nActId);
								packet->setSize(packet->getWOffset());
								player->addNetPacket(packet, 0);
								packet->destroy();
							}
						}
					}

					LOG_DEBUG("GameService::onPlayerLoaded pop player %p\n", player);
				}
				else
				{
					LOG_ERROR("GameService::onPlayerLoaded create player fail cgindex=%d, cid = %lld\n",
						dbData.cgindex, dbData.chr.data.cid);
				}
			}
		}
		else
		{
			LOG_ERROR("GameService::onPlayerLoaded null user cgindex=%d, cid = %lld\n",
				dbData.cgindex, dbData.chr.data.cid);
		}
	}
	else
	{
		LOG_INFO("GameService::onPlayerLoaded player cid=%lld can't find map with mapid = %d\n",
			dbData.chr.data.cid, dbData.chr.data.mapid);
	}
}

void GameService::onPlayerLogout(Player* player)
{
	if (player != NULL)
	{
		int8_t connid = player->getConnId();
		int16_t cgindex = player->getGateIndex();

		LOG_DEBUG("GameService::onPlayerLogout push player %p, cgindex = %d\n",
			player, static_cast<int32_t>(cgindex));

		removePlayer(player);

		if (player->getGateIndex() > 0)
		{
			player->setGateIndex(-1);
			if (player->isRobot())
			{
				delete player;
			}
			else
			{
				POOL_MANAGER.push<Player>(player);
			}
		}

		if (connid >= 0 && connid < MAX_GATE_CONNS && cgindex > 0 && cgindex < MAX_CONNECTION)
		{
			int32_t nIndex = getUserIndex(connid, cgindex);
			Answer::MutexGuard lock(m_userLock);
			User* user = m_users[nIndex];
			if (user != NULL)
				user->setPlayer(NULL);
		}
	}
}

void GameService::onPlayerSaved(int8_t connid, int64_t uid, int32_t sid,
	int32_t reason, int32_t param, CharId_t cid)
{
	NetPacket* packet = popNetpacket(connid, PACK_PROC, 0x4E25);
	if (NULL == packet)
		return;
	packet->writeInt64(uid);
	packet->writeInt32(sid);
	packet->writeInt32(reason);
	packet->writeInt64(cid);
	packet->writeInt32(param);
	packet->setSize(packet->getWOffset());
	sendPacket(connid, packet);
}

// ============================================================
// Network send helpers (2019 multi-conn)
// ============================================================
void GameService::sendPacket(int8_t connid, Answer::NetPacket* packet)
{
	GameConn* pConn = GetConn(connid);
	if (pConn)
		pConn->sendPacket(packet);
}

void GameService::sendPacketTo(int8_t connid, int16_t index, Answer::NetPacket* inPacket)
{
	GameConn* pConn = GetConn(connid);
	if (pConn)
		TcpService::sendPacketTo(pConn, index, inPacket);
}

int32_t GameService::replySuccess(int8_t connid, int16_t index, uint16_t proc, int64_t addon)
{
	GameConn* pConn = GetConn(connid);
	if (pConn)
		return TcpService::replySuccess(pConn, index, proc, addon);
	return 10002;
}

int32_t GameService::replyfailure(int8_t connid, int16_t index, uint16_t proc,
	int32_t errcode, int64_t addon)
{
	GameConn* pConn = GetConn(connid);
	if (pConn)
		return TcpService::replyfailure(pConn, index, proc, errcode, addon);
	return 10002;
}

// Old compat wrappers (use connid=0)
Answer::NetPacket* GameService::popNetpacket(Answer::PackType packType, uint16_t proc)
{
	return popNetpacket(0, packType, proc);
}

Answer::NetPacket* GameService::popNetpacket(Answer::PackType packType, uint16_t proc, unsigned int buffersize)
{
	return popNetpacket(0, packType, proc, buffersize);
}

Answer::NetPacket* GameService::popNetpacket(int8_t connid, Answer::PackType packType, uint16_t proc)
{
	GameConn* pConn = GetConn(connid);
	NetPacket* packet = NULL;
	if (pConn)
		packet = pConn->popNetpacket();
	else
		packet = TcpService::popNetpacket();

	if (packet != NULL)
	{
		packet->setType(packType);
		packet->setProc(proc);
	}
	return packet;
}

Answer::NetPacket* GameService::popNetpacket(int8_t connid, Answer::PackType packType,
	uint16_t proc, unsigned int buffersize)
{
	GameConn* pConn = GetConn(connid);
	NetPacket* packet = NULL;
	if (pConn)
		packet = pConn->popNetpacket(buffersize);
	else
		packet = TcpService::popNetpacket(buffersize);

	if (packet != NULL)
	{
		packet->setType(packType);
		packet->setProc(proc);
	}
	return packet;
}

// ============================================================
// Broadcast
// ============================================================
void GameService::broadcast(Answer::NetPacket* inPacket)
{
	if (inPacket == NULL)
		return;

	IndexMap indexMap;
	{
		Answer::MutexGuard lock(m_playerLock);
		for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			Player* player = it->second;
			if (player)
			{
				int8_t connid = player->getConnId();
				int16_t gateIndex = player->getGateIndex();
				indexMap[connid].push_back(gateIndex);
			}
		}
	}

	if (indexMap.empty())
	{
		inPacket->destroy();
		return;
	}

	// Send to each conn
	for (IndexMap::iterator it = indexMap.begin(); it != indexMap.end(); ++it)
	{
		int8_t connid = it->first;
		Int16List& indexList = it->second;
		if (indexList.empty()) continue;

		int32_t nsize = static_cast<int32_t>(indexList.size());
		uint32_t newSize = 2 * (nsize + 1) + inPacket->getSize();
		NetPacket* packet = popNetpacket(connid, inPacket->getType(), inPacket->getProc(), newSize);
		if (packet)
		{
			packet->writeInt16(static_cast<int16_t>(nsize));
			for (Int16List::iterator sit = indexList.begin(); sit != indexList.end(); ++sit)
				packet->writeInt16(*sit);
			packet->write(inPacket->getBuffer(), inPacket->getSize());
			packet->setSize(packet->getWOffset());
			sendPacket(connid, packet);
		}
	}
	inPacket->destroy();
}

void GameService::broadcast(Answer::NetPacket* inPacket, const CharIdList& cids)
{
	if (NULL == inPacket || cids.empty())
	{
		if (inPacket) inPacket->destroy();
		return;
	}

	IndexMap indexMap;
	for (CharIdList::const_iterator iter = cids.begin(); iter != cids.end(); ++iter)
	{
		Answer::MutexGuard lock(m_playerLock);
		CharIdPlayerMap::iterator findIter = m_players.find(*iter);
		if (findIter != m_players.end())
		{
			Player* pPlayer = findIter->second;
			if (pPlayer)
				indexMap[pPlayer->getConnId()].push_back(pPlayer->getGateIndex());
		}
	}

	if (indexMap.empty())
	{
		inPacket->destroy();
		return;
	}

	for (IndexMap::iterator it = indexMap.begin(); it != indexMap.end(); ++it)
	{
		int8_t connid = it->first;
		Int16List& indexList = it->second;
		int32_t nsize = static_cast<int32_t>(indexList.size());
		uint32_t newSize = 2 * (nsize + 1) + inPacket->getSize();
		NetPacket* packet = popNetpacket(connid, inPacket->getType(), inPacket->getProc(), newSize);
		if (packet)
		{
			packet->writeInt16(static_cast<int16_t>(nsize));
			for (Int16List::iterator sit = indexList.begin(); sit != indexList.end(); ++sit)
				packet->writeInt16(*sit);
			packet->write(inPacket->getBuffer(), inPacket->getSize());
			packet->setSize(packet->getWOffset());
			sendPacket(connid, packet);
		}
	}
	inPacket->destroy();
}

void GameService::broadcastToFamily(Answer::NetPacket* inPacket, FamilyId_t nFamilyId, int32_t nLevel)
{
	if (NULL == inPacket || nFamilyId <= 0)
	{
		if (inPacket) inPacket->destroy();
		return;
	}

	IndexMap indexMap;
	{
		Answer::MutexGuard lock(m_playerLock);
		for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			Player* player = it->second;
			if (player && player->getFamilyId() == nFamilyId)
			{
				if (nLevel < 0 || player->getLevel() > nLevel)
				{
					indexMap[player->getConnId()].push_back(player->getGateIndex());
				}
			}
		}
	}

	for (IndexMap::iterator it = indexMap.begin(); it != indexMap.end(); ++it)
	{
		int8_t connid = it->first;
		Int16List& indexList = it->second;
		int32_t nsize = static_cast<int32_t>(indexList.size());
		uint32_t newSize = 2 * (nsize + 1) + inPacket->getSize();
		NetPacket* packet = popNetpacket(connid, inPacket->getType(), inPacket->getProc(), newSize);
		if (packet)
		{
			packet->writeInt16(static_cast<int16_t>(nsize));
			for (Int16List::iterator sit = indexList.begin(); sit != indexList.end(); ++sit)
				packet->writeInt16(*sit);
			packet->write(inPacket->getBuffer(), inPacket->getSize());
			packet->setSize(packet->getWOffset());
			sendPacket(connid, packet);
		}
	}
	inPacket->destroy();
}

void GameService::worldBroadcast(Answer::NetPacket* inPacket)
{
	if (inPacket == NULL)
		return;

	// Send to all connections
	for (std::map<int8_t, GameConn*>::iterator it = m_mConn.begin(); it != m_mConn.end(); ++it)
	{
		GameConn* pConn = it->second;
		if (pConn)
		{
			uint32_t packetSize = inPacket->getSize() + 2;
			NetPacket* packet = pConn->popNetpacket(packetSize);
			if (packet)
			{
				packet->writeInt16(-1);
				packet->write(inPacket->getBuffer(), inPacket->getSize());
				packet->setSize(packet->getWOffset());
				packet->setType(inPacket->getType());
				packet->setProc(inPacket->getProc());
				pConn->sendPacket(packet);
			}
		}
	}
	inPacket->destroy();
}

void GameService::worldBroadcast(int8_t connid, Answer::NetPacket* inPacket)
{
	if (inPacket == NULL)
		return;

	uint32_t oldSize = inPacket->getSize();
	if (inPacket->rightShift(2))
	{
		inPacket->writeInt16(-1);
		inPacket->setSize(oldSize + 2);
		sendPacket(connid, inPacket);
	}
	else
	{
		NetPacket* packet = popNetpacket(connid, inPacket->getType(), inPacket->getProc(),
			inPacket->getSize() + 2);
		if (packet)
		{
			packet->writeInt16(-1);
			packet->write(inPacket->getBuffer(), inPacket->getSize());
			packet->setSize(packet->getWOffset());
			sendPacket(connid, packet);
			inPacket->destroy();
		}
	}
}

void GameService::broadcastActivityState(int32_t nId, int8_t nState)
{
	for (std::map<int8_t, GameConn*>::iterator it = m_mConn.begin(); it != m_mConn.end(); ++it)
	{
		GameConn* pConn = it->second;
		if (pConn)
		{
			NetPacket* packet = pConn->popNetpacket();
			if (packet)
			{
				packet->writeInt32(nId);
				packet->writeInt8(nState);
				packet->setSize(packet->getWOffset());
				packet->setType(PACK_DISPATCH);
				packet->setProc(0x4EC4);
				pConn->sendPacket(packet);
			}
		}
	}
}

void GameService::broadcastHuoDongDaTingIcon()
{
	Answer::MutexGuard lock(m_playerLock);
	if (m_players.empty())
		return;
	for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		it->second->GetPlayerDailyActivity().SendHuoDongDaTingIcon();
	}
}

void GameService::SendOpenBetaIcon()
{
	Answer::MutexGuard lock(m_playerLock);
	if (m_players.empty())
		return;
	for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		ShowIcon stu;
		OPEN_BETA.getIconState(stu, it->second);
		it->second->SendIconState(stu);
	}
}

void GameService::broadFamilyWarIcon()
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		it->second->SendFamilyWarIcon();
	}
}

void GameService::broadCastKiaFuHuoDongIcon()
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		KAI_FU_HUO_DONG.SendKiaFuHuoDongIconToPlayer(it->second);
	}
}

void GameService::FamilyBroadcast(int32_t nFamilyId, Answer::NetPacket* inPacket)
{
	broadcastToFamily(inPacket, nFamilyId, -1);
}

void GameService::broadcastCityWarWinnerLogin(CharId_t Cid, const std::string& strName)
{
	NetPacket* packet = popNetpacket(PACK_DISPATCH, SM_GAME_EVENT);
	if (packet)
	{
		packet->writeInt32(0); // event type
		packet->writeInt64(Cid);
		packet->writeUTF8(strName);
		packet->setSize(packet->getWOffset());
		worldBroadcast(packet);
	}
}

// ============================================================
// AddPlayer / removePlayer / getPlayer
// ============================================================
void GameService::AddPlayer(Player* player, int32_t reason)
{
	if (player != NULL)
	{
		{
			Answer::MutexGuard lock(m_playerLock);
			m_players[player->getCid()] = player;
		}

		if (reason != 3)
		{
			FamilyId_t FamilyId = player->getFamilyId();
			int8_t ConnId = player->getConnId();
			if (FamilyId == ACTIVITY_MANAGER.GetCityWarWinner(ConnId)
				&& player->getFamilyPosition() == 3)
			{
				broadcastCityWarWinnerLogin(player->getCid(), player->getName());
			}
		}

		sendSocialAddPlayer(player);
		player->sendBasicInfo(reason);

		int8_t connid = player->getConnId();
		DB_SERVICE.UpdateLoginTime(connid, player->getCid(), player->getLastLoginTime());
	}
}

void GameService::removePlayer(Player* player)
{
	if (player != NULL)
	{
		Answer::MutexGuard lock(m_playerLock);
		CharIdPlayerMap::iterator it = m_players.find(player->getCid());
		if (it == m_players.end())
		{
			LOG_INFO("GameService::removePlayer player = %p, cid = %lld not in m_players\n",
				player, player->getCid());
		}
		else if (it->second->getEntityId() != player->getEntityId())
		{
			LOG_INFO("GameService::removePlayer player entityid = %lld, cid = %lld not equal with it->second entity id = %lld, cid =%lld\n",
				player->getEntityId(), player->getCid(),
				it->second->getEntityId(), it->second->getCid());
		}
		else
		{
			m_players.erase(it);
			sendSocialRemovePlayer(player);
		}
	}
}

Player* GameService::getPlayer(CharId_t cid, int32_t nRunnerId, bool bCheck)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(cid);
	if (iter != m_players.end())
	{
		Player* pPlayer = iter->second;
		if (pPlayer != NULL)
		{
			if (bCheck)
			{
				if (pPlayer->GetRunnerId() == nRunnerId)
					return pPlayer;
			}
			else
			{
				return pPlayer;
			}
		}
	}
	return NULL;
}

// ============================================================
// Pet / Monster / Trailer
// ============================================================
void GameService::addPet(CObjPet* pPet)
{
	if (pPet != NULL)
	{
		Answer::MutexGuard lock(m_petsLock);
		m_pets[pPet->GetPetId()] = pPet;
	}
}

void GameService::removePet(CObjPet* pPet)
{
	if (pPet != NULL)
	{
		Answer::MutexGuard lock(m_petsLock);
		m_pets.erase(pPet->GetPetId());
	}
}

CObjPet* GameService::getPet(PetId_t pid, int32_t nRunnerId)
{
	Answer::MutexGuard lock(m_petsLock);
	PetIdObjPetMap::iterator iter = m_pets.find(pid);
	if (iter != m_pets.end())
	{
		CObjPet* pPet = iter->second;
		if (pPet != NULL && pPet->GetRunnerId() == nRunnerId)
			return pPet;
	}
	return NULL;
}

void GameService::addMonster(Monster* monster)
{
	if (monster != NULL)
	{
		Answer::MutexGuard lock(m_monstersLock);
		m_monsters[monster->getUnitId()] = monster;
	}
}

void GameService::removeMonster(Monster* monster)
{
	if (monster != NULL)
	{
		Answer::MutexGuard lock(m_monstersLock);
		m_monsters.erase(monster->getUnitId());
	}
}

Monster* GameService::getMonster(EntityId_t unitid, int32_t nRunnerId)
{
	Answer::MutexGuard lock(m_monstersLock);
	EntityIdMonsterMap::iterator iter = m_monsters.find(unitid);
	if (iter != m_monsters.end())
	{
		Monster* pMonster = iter->second;
		if (pMonster != NULL && pMonster->GetRunnerId() == nRunnerId)
			return pMonster;
	}
	return NULL;
}

void GameService::addTrailer(Trailer* trailer)
{
	if (trailer != NULL)
	{
		Answer::MutexGuard lock(m_trailersLock);
		m_trailers[trailer->getUnitId()] = trailer;
	}
}

void GameService::removeTrailer(Trailer* trailer)
{
	if (trailer != NULL)
	{
		Answer::MutexGuard lock(m_trailersLock);
		m_trailers.erase(trailer->getUnitId());
	}
}

Trailer* GameService::getTrailer(EntityId_t unitid, int32_t nRunnerId)
{
	Answer::MutexGuard lock(m_trailersLock);
	EntityIdTrailerMap::iterator iter = m_trailers.find(unitid);
	if (iter != m_trailers.end())
	{
		Trailer* pTrailer = iter->second;
		if (pTrailer != NULL && pTrailer->GetRunnerId() == nRunnerId)
			return pTrailer;
	}
	return NULL;
}

Unit* GameService::getUnit(EntityId_t unitid, int32_t unittype, int32_t nRunnerId)
{
	switch (unittype)
	{
	case ET_PLAYER:  return getPlayer(unitid, nRunnerId);
	case ET_MONSTER: return getMonster(unitid, nRunnerId);
	case ET_PET:     return getPet(unitid, nRunnerId);
	case ET_TRAILER: return getTrailer(unitid, nRunnerId);
	default: return NULL;
	}
}

// ============================================================
// saveAllPlayerToDB
// ============================================================
void GameService::saveAllPlayerToDB()
{
	int32_t nNowTime = DayTime::now();
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		Player* player = it->second;
		if (player != NULL)
			player->onLogout(1, 0);
	}
}

// ============================================================
// onUserPayed
// ============================================================
void GameService::onUserPayed(Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	CharId_t Cid = inPacket->readInt64();
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator it = m_players.find(Cid);
	if (it != m_players.end() && it->second != NULL)
		it->second->addNetPacket(inPacket, 8);
}

// ============================================================
// onAddUser / onRemoveUser / onUpdateBanChat / onGMReloadItem
// ============================================================
void GameService::onAddUser(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	int16_t cgindex = inPacket->readInt16();
	int64_t uid = inPacket->readInt64();
	int32_t sid = inPacket->readInt32();
	int8_t connid = pConn->GetId();

	Answer::MutexGuard lock(m_userLock);
	if (connid >= 0 && connid < MAX_GATE_CONNS && cgindex > 0 && cgindex < MAX_CONNECTION
		&& uid > 0 && sid > 0)
	{
		int32_t nIndex = getUserIndex(connid, cgindex);
		User* user = POOL_MANAGER.pop<User>();
		if (user)
		{
			user->init(uid, sid);
			m_users[nIndex] = user;
#ifdef _DEBUG
			printf("GameService::onAddUser() connid=%d, index=%d, uid=%lld\n", connid, cgindex, uid);
#endif
		}
	}
}

void GameService::qqToPlayer(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	int16_t cgindex = inPacket->readInt16();
	int8_t connid = pConn->GetId();

	TencentInfo info;
	info.UnPacketInfo(inPacket);

	Answer::MutexGuard lock(m_userLock);
	int32_t nIndex = getUserIndex(connid, cgindex);
	User* user = m_users[nIndex];
	if (user != NULL)
		user->SetTencentInfo(info);
}

void GameService::onRemoveUser(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	int16_t cgindex = inPacket->readInt16();
	int8_t connid = pConn->GetId();

	if (connid >= 0 && connid < MAX_GATE_CONNS && cgindex > 0 && cgindex < MAX_CONNECTION)
	{
		Answer::MutexGuard lock(m_userLock);
		int32_t nIndex = getUserIndex(connid, cgindex);
		User* user = m_users[nIndex];
		if (user != NULL)
		{
			Player* player = user->getPlayer();
			if (!player)
			{
				// No player — just clean up user
				m_users[nIndex] = NULL;
				user->reset();
				POOL_MANAGER.push<User>(user);
			}
			else
			{
				inPacket->readInt64(); // uid
				int32_t reason = inPacket->readInt32();
				int32_t param = inPacket->readInt32();

				if (!player->getMap())
				{
					// Player has no map — immediate save + remove
					LOG_INFO("GameService::onRemoveUser remove player with m_pMap == NULL, cid = %lld\n",
						player->getCid());
					player->saveToDB(reason, param);
					removePlayer(player);

					if (player->getGateIndex() > 0)
					{
						player->setGateIndex(-1);
						if (player->isRobot())
							delete player;
						else
							POOL_MANAGER.push<Player>(player);
					}

					m_users[nIndex] = NULL;
					user->reset();
					POOL_MANAGER.push<User>(user);
				}
				else
				{
					// Player in map — send disconnect notification first
					int8_t pConnId = player->getConnId();
					NetPacket* packet = GAME_SERVICE.popNetpacket(pConnId, PACK_DISPATCH, 0x08);
					if (packet)
					{
						packet->writeInt32(reason);
						packet->writeInt32(param);
						packet->setSize(packet->getWOffset());
						player->addNetPacket(packet, 0);
						packet->destroy();
					}

					m_users[nIndex] = NULL;
					user->reset();
					POOL_MANAGER.push<User>(user);
				}
			}
		}
	}
}

void GameService::onUpdateBanChat(Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;
	int32_t action = inPacket->readInt32();
	int32_t uid = inPacket->readInt32();
	int32_t expire_time = inPacket->readInt32();
	CFG_DATA.onBanChatUpdated(action, uid, expire_time);
}

void GameService::onGMReloadItem(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	CFG_DATA.reload();
}

void GameService::onAvgLevel(Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;
	CFG_DATA.onAvgLevelUpdated(0);
}

// ============================================================
// Gate disconnect
// ============================================================
void GameService::onGateDisconnect(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (pConn && inPacket)
	{
		LOG_INFO("GameService::onGateDisconnect");

		NetPacket* packet = popNetpacket(PACK_PROC, 0x4E2E);
		if (packet)
		{
			packet->writeInt32(1);
			packet->setSize(packet->getWOffset());
			pConn->sendPacket(packet);
		}
	}
}

// ============================================================
// Social packet dispatchers
// ============================================================
void GameService::onSocialNetpacket(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	int16_t cgindex = static_cast<int16_t>(inPacket->readInt32());
	int8_t connid = pConn->GetId();
	if (connid >= 0 && connid < MAX_GATE_CONNS && cgindex > 0 && cgindex < MAX_CONNECTION)
		onGameNetpacket(connid, cgindex, inPacket);
}

void GameService::onEnterGame(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket)
{
	CharId_t cid = inPacket->readInt64();
	int32_t line = inPacket->readInt32();
	int32_t reason = inPacket->readInt32();

	printf("GameService::onEnterGame() cid=%lld, line=%d, reason=%d\n", cid, line, reason);

	int32_t nIndex = getUserIndex(connid, cgindex);
	int64_t uid = 0;
	int32_t sid = 0;
	bool bHasUser = false;

	{
		Answer::MutexGuard lock(m_userLock);
		User* user = m_users[nIndex];
		if (user)
		{
			uid = user->getUid();
			sid = user->getSid();
			bHasUser = true;
		}
	}

	if (bHasUser)
	{
		DB_SERVICE.loadPlayer(connid, cgindex, uid, sid, reason);
	}
}

void GameService::onEnterGameRobot(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	CharId_t cid = inPacket->readInt32();
	int32_t nIndex = getUserIndex(connid, cgindex);

	User* user = NULL;
	{
		Answer::MutexGuard lock(m_userLock);
		user = m_users[nIndex];
		if (user != NULL && user->getCid() == 0)
			user->setCid(cid);
		else
			user = NULL;
	}

	if (user != NULL && cid > 0x1234567)
	{
		PlayerDBData dbData;
		inPacket->readInt32(); // line
		dbData.chr.data.cid = cid;
		snprintf(dbData.chr.data.name, MAX_NAME_CCH_LENGTH, inPacket->readUTF8(true).c_str());
		dbData.chr.data.sex = inPacket->readInt32();
		dbData.chr.data.job = inPacket->readInt32();
		inPacket->readInt32();
		inPacket->readInt32();
		dbData.chr.data.level = 60;
		dbData.chr.data.mapid = inPacket->readInt32();
		dbData.chr.data.x = inPacket->readInt32();
		dbData.chr.data.y = inPacket->readInt32();
		dbData.chr.data.hp = inPacket->readInt32();
		dbData.chr.data.mp = inPacket->readInt32();
		dbData.chr.data.head = inPacket->readInt32();

		int32_t id[] = { 10001, 10006, 10011 };
		dbData.cgindex = cgindex;
		dbData.connid = connid;
		onPlayerLoaded(dbData, 0, true);
	}
}

void GameService::onGameNetpacket(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	// GuiGuDaoRen protocol dispatch
	ProcId_t proc = inPacket->getProc();
	if (proc >= CM_GUI_GU_DAO_REN_ASK_BACK_ITEM_COUNT && proc <= CM_GUI_GU_DAO_REN_ASK_EQUIP_BACK_RANK)
	{
		Player* player = getUserPlayer(connid, cgindex);
		if (player != NULL)
		{
			switch (proc)
			{
			case CM_GUI_GU_DAO_REN_ASK_BACK_ITEM_COUNT:  GUI_GU_DAO_REN.OnAskBackItemCount(player, inPacket); break;
			case CM_GUI_GU_DAO_REN_BACK_ITEM:             GUI_GU_DAO_REN.OnBackItem(player, inPacket); break;
			case CM_GUI_GU_DAO_REN_ASK_BACK_EQUIP_COUNT:  GUI_GU_DAO_REN.OnAskBackEquipCount(player, inPacket); break;
			case CM_GUI_GU_DAO_REN_BACK_EQUIP:            GUI_GU_DAO_REN.OnBackEquipCount(player, inPacket); break;
			case CM_GUI_GU_DAO_REN_ASK_EQUIP_BACK_RANK:   GUI_GU_DAO_REN.OnAskEquipBackRank(player, inPacket); break;
			}
			inPacket->destroy();
			return;
		}
	}

	Player* player = getUserPlayer(connid, cgindex);
	if (player != NULL)
		player->addNetPacket(inPacket, sizeof(int32_t));
}

void GameService::OnDBNetPacket(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket)
{
	if (inPacket)
	{
		Player* player = getUserPlayer(connid, cgindex);
		if (player)
			player->addNetPacket(inPacket, 2);
	}
}

User* GameService::getUser(int8_t connid, int16_t cgindex)
{
	Answer::MutexGuard lock(m_userLock);
	int32_t nIndex = getUserIndex(connid, cgindex);
	return m_users[nIndex];
}

Player* GameService::getUserPlayer(int8_t connid, int16_t cgindex)
{
	User* user = getUser(connid, cgindex);
	if (user)
		return user->getPlayer();
	return NULL;
}

// ============================================================
// sendSocialAddPlayer / sendSocialRemovePlayer
// ============================================================
void GameService::sendSocialAddPlayer(Player* player)
{
	if (player == NULL)
		return;

	int8_t connid = player->getConnId();
	NetPacket* packet = popNetpacket(connid, PACK_PROC, 0x4E34);
	if (NULL == packet)
		return;

	packet->writeInt32(player->getGateIndex());
	packet->writeInt64(player->getCid());
	packet->writeInt64(player->getUid());
	packet->writeInt32(player->getSid());
	packet->writeInt32(m_line);
	packet->writeInt8(player->GetGMLevel());
	packet->setSize(packet->getWOffset());
	sendPacket(player->getConnId(), packet);
}

void GameService::sendSocialRemovePlayer(Player* player)
{
	if (player == NULL)
		return;

	int8_t connid = player->getConnId();
	NetPacket* packet = popNetpacket(connid, PACK_PROC, 0x4E35);
	if (NULL == packet)
		return;

	packet->writeInt64(player->getCid());
	packet->setSize(packet->getWOffset());
	sendPacket(player->getConnId(), packet);
}

// ============================================================
// Social handler delegates
// ============================================================
void GameService::onSocialUpdatePetRank(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	PET_MANAGER.OnUpdatePetRank(inPacket);
}

void GameService::onSocialUpdateFamilyInfo(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	FAMILY_MANAGER.OnUpdateFamilyInfo(inPacket);
}

void GameService::onSocialInitPetRank(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	PET_MANAGER.OnInitPetRank(inPacket);
}

void GameService::onSocialInitRankMirror(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	RANK_MIRROR.OnSocialUpdateRank(inPacket);
}

void GameService::onSocialUpdateRankMirror(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	RANK_MIRROR.OnSocialUpdateRank(inPacket);
}

void GameService::onSocialQueryPlayerInfo(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (pConn && inPacket)
	{
		CharId_t cid = inPacket->readInt64();
		int16_t cgindex = inPacket->readInt16();

		Answer::MutexGuard lock(m_playerLock);
		CharIdPlayerMap::iterator iter = m_players.find(cid);
		if (iter != m_players.end())
		{
			Player* pPlayer = iter->second;
			if (pPlayer)
				pPlayer->SendOtherPlayerInfo(pConn->GetId(), cgindex);
		}
	}
}

void GameService::onSocialCreateTeamDungeon(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	int32_t nDungeonId = inPacket->readInt32();
	Dungeon* pDungeon = MAP_MANAGER.NewDungeon(nDungeonId);
	if (pDungeon == NULL)
		return;

	CharIdList memberList;
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		CharId_t memberId = inPacket->readInt64();
		if (memberId > 0)
			memberList.push_back(memberId);
	}

	pDungeon->InitTeamMember(memberList);
	pDungeon->start(0);
	MAP_MANAGER.PostMsg(pDungeon->GetRunnerId(), GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
}

void GameService::onSocialSendSystemMail(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket || pConn == NULL)
		return;

	int8_t connid = pConn->GetId();
	CharId_t nReceiver = inPacket->readInt64();
	int32_t nMailId = inPacket->readInt32();
	int32_t nReason = inPacket->readInt32();

	MemChrBag item = {};
	item.itemId = inPacket->readInt32();
	item.itemClass = inPacket->readInt8();
	item.itemCount = inPacket->readInt32();
	item.srcId = inPacket->readInt64();
	item.bind = inPacket->readInt8();
	item.endTime = inPacket->readInt32();
	std::string mailParam = inPacket->readUTF8(true);

	if (item.itemId > 0 && item.itemCount > 0)
	{
		DB_SERVICE.OnSendSysMail(connid, nReceiver, nMailId, item, (ITEM_CHANGE_REASON)nReason, mailParam);
	}
	else
	{
		DB_SERVICE.OnSendSysMail(connid, nReceiver, nMailId, mailParam);
	}
}

void GameService::onSocialSendSystemMail2(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket || pConn == NULL)
		return;

	int8_t connid = pConn->GetId();
	CharId_t nReceiver = inPacket->readInt64();
	int32_t nMailId = inPacket->readInt32();
	int32_t nReason = inPacket->readInt32();
	int32_t nSize = inPacket->readInt32();

	if (nSize > 0)
	{
		MemChrBagVector vItem;
		vItem.resize(nSize);
		for (int32_t i = 0; i < nSize; ++i)
		{
			vItem[i].itemClass = inPacket->readInt8();
			vItem[i].itemId = inPacket->readInt32();
			vItem[i].itemCount = inPacket->readInt32();
			vItem[i].srcId = 0;
			vItem[i].bind = 0;
			vItem[i].endTime = 0;
		}
		DB_SERVICE.OnSendSysMail(connid, nReceiver, nMailId, vItem, (ITEM_CHANGE_REASON)nReason, "");
	}
	else
	{
		DB_SERVICE.OnSendSysMail(connid, nReceiver, nMailId, "");
	}
}

void GameService::onSocialChangeOwner(Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	int8_t nClass = inPacket->readInt8();
	int64_t nSrcId = inPacket->readInt64();
	CharId_t nOwner = inPacket->readInt64();

	if (nClass == IC_EQUIP)
		EQUIP_MANAGER.ChangeOwner(nSrcId, nOwner);
	else if (nClass == IC_PET)
		PET_MANAGER.ChangeOwner(nSrcId, nOwner);
}

void GameService::onSocialUpdateRank(Answer::NetPacket* inPacket)
{
	RANK_MIRROR.OnSocialUpdateRank(inPacket);
}

void GameService::onSocialInitFamilyInfo(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	RANK_MIRROR.OnSocialUpdateRank(inPacket);
}

void GameService::onUpdateActivityState(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	int32_t nId = inPacket->readInt32();
	int8_t nState = inPacket->readInt8();
	// Handle activity state update
}

void GameService::onRequestDropRecord(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	int32_t nGroupId = inPacket->readInt32();
	// Request drop record from DB
}

// ============================================================
// TeamDungeon / Mail / PetRank / DaTi / ServerDiff / Family
// ============================================================
void GameService::TeamDungeonEnterDungeon(Dungeon* pDungeon, const CharIdList& lst)
{
	if (NULL == pDungeon)
		return;

	for (CharIdList::const_iterator iter = lst.begin(); iter != lst.end(); ++iter)
	{
		Answer::MutexGuard lock(m_playerLock);
		CharIdPlayerMap::iterator it = m_players.find(*iter);
		if (it != m_players.end())
		{
			Player* pPlayer = it->second;
			if (pPlayer != NULL)
			{
				pPlayer->setOldPosition();
				Map* pMap = pPlayer->getMap();
				if (pMap != NULL)
				{
					pPlayer->broadcastLeave();
					pMap->removePlayer(pPlayer, false);
				}

				GAME_SERVICE.replySuccess(pPlayer->getConnId(), pPlayer->getGateIndex(),
					CM_ENTER_DUNGEON, pDungeon->getDungeonId());
				pDungeon->addPlayer(pPlayer, pDungeon->GetCfgDungeon().x, pDungeon->GetCfgDungeon().y);
			}
		}
	}
}

void GameService::OnUpdateMail(Answer::NetPacket* inPacket)
{
	if (NULL == inPacket)
		return;

	CharId_t Cid = inPacket->readInt64();
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator it = m_players.find(Cid);
	if (it != m_players.end() && it->second != NULL)
		it->second->addNetPacket(inPacket, sizeof(int64_t));
}

void GameService::requestPetRankInfo()
{
	NetPacket* packet = popNetpacket(0, PACK_DISPATCH, IM_SOCIAL_REQUEST_PET_RANK_DATA);
	if (NULL == packet)
		return;
	packet->writeInt32(m_line);
	packet->setSize(packet->getWOffset());
	sendPacket(0, packet);
}

void GameService::requestSocialData()
{
	requestPetRankInfo();
	SendServerDiffToGlobal();
	requestFamilyInfo();
	PET_MANAGER.UpdataChangedPet();
}

void GameService::requestFamilyInfo()
{
	NetPacket* packet = popNetpacket(0, PACK_PROC, IM_SOCIAL_REQUEST_FAMILY_INFO);
	if (NULL == packet)
		return;
	packet->writeInt8(0);
	packet->setSize(packet->getWOffset());
	sendPacket(0, packet);
}

void GameService::requestWorldLevel()
{
	NetPacket* packet = popNetpacket(0, PACK_PROC, 0x4E40);
	if (packet)
	{
		packet->writeInt32(m_line);
		packet->setSize(packet->getWOffset());
		sendPacket(0, packet);
	}
}

void GameService::OnReceiveDaTiRank(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket || pConn == NULL)
		return;

	int8_t connid = pConn->GetId();
	int32_t nSize = inPacket->readInt32();
	for (int32_t i = 0; i < nSize; ++i)
	{
		CharId_t CharId = inPacket->readInt64();
		std::string Name = inPacket->readUTF8(true);
		int32_t Index = inPacket->readInt32();

		if (Index == 1)
		{
			DB_SERVICE.OnSendSysMail(connid, CharId, DaTiHDFirst, "");
			NetPacket* packet = popNetpacket(PACK_DISPATCH, SM_SEND_NOTICE_PARAM);
			if (packet)
			{
				packet->writeInt32(BCI_DA_TI_FIRST);
				packet->writeUTF8(Name);
				packet->writeInt64(CharId);
				packet->setSize(packet->getWOffset());
				worldBroadcast(packet);
			}
		}
		else if (Index == 2)
			DB_SERVICE.OnSendSysMail(connid, CharId, DaTiHDSecond, "");
		else if (Index == 3)
			DB_SERVICE.OnSendSysMail(connid, CharId, DaTiHDThird, "");
		else
			DB_SERVICE.OnSendSysMail(connid, CharId, DaTiHDChanYu, "");

		LogActivity logActivity = {};
		logActivity.cid = CharId;
		logActivity.acttype = ATI_DA_TI_HUO_DONG;
		logActivity.time = TIMER.GetNow();
		logActivity.param = Index;
		DB_SERVICE.InsertActivityLog(connid, logActivity);
	}
}

void GameService::OnReceiveDaTiResult(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (NULL == inPacket || pConn == NULL)
		return;

	int64_t Cid = inPacket->readInt64();
	int32_t Index = inPacket->readInt32();
	int8_t Result = inPacket->readInt8();

	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator it = m_players.find(Cid);
	if (it != m_players.end() && it->second != NULL)
		it->second->AddDaTiExp(Index, Result);
}

void GameService::SendServerDiffToGlobal()
{
	NetPacket* packet = popNetpacket(0, PACK_PROC, 0x4E49);
	if (NULL == packet)
		return;
	int32_t ServerDiffDay = CFG_DATA.getServerDiffDay(SVT_NORMAL);
	packet->writeInt32(ServerDiffDay);
	packet->setSize(packet->getWOffset());
	sendPacket(0, packet);
}

// ============================================================
// ChatValidate
// ============================================================
bool GameService::SendChatValidate(Player* Owner, int32_t Channel, Answer::NetPacket* inPacket)
{
	if (!inPacket || !Owner)
		return false;

	Answer::MutexGuard lock(m_playerLock);
	Answer::MutexGuard lockChat(m_ChatValidateLock);

	int8_t connid = Owner->getConnId();
	NetPacket* packet = popNetpacket(connid, PACK_DISPATCH, 0x2ED8);
	if (!packet)
		return false;

	std::string PassPort = Owner->GetPassport();
	std::string Name = Owner->getName();
	int32_t SidInt = Owner->getSid();

	// Build MD5 key
	std::string Cid;
	{
		std::stringstream ss;
		ss << Owner->getCid();
		Cid = ss.str();
	}
	std::string Sid;
	{
		std::stringstream ss;
		ss << SidInt;
		Sid = ss.str();
	}
	std::string Platform;
	Owner->GetPlatform(Platform);

	std::string Md5String = Platform + std::string("&") + Cid + std::string("&") + PassPort;
	MD5 md5;
	std::string Key = md5.md5sum(Md5String);

	static int32_t s_nValidateId = 0;
	++s_nValidateId;

	packet->writeInt8(1);
	packet->writeInt32(s_nValidateId);
	packet->writeUTF8(Key);
	uint32_t Size = inPacket->getSize();
	char* Buffer = inPacket->getBuffer();
	packet->write(Buffer, Size);
	packet->setSize(packet->getWOffset());

	sendPacketTo(Owner->getConnId(), Owner->getGateIndex(), packet);

	ChatValidate& validate = m_ChatValidateMap[s_nValidateId];
	validate.SendPacket = inPacket;
	validate.CharId = Owner->getCid();
	validate.Time = Owner->getNow();
	validate.Channel = Channel;
	validate.SendCharId = Owner->getCid();
	return true;
}

void GameService::OnChatValidateResult(Answer::NetPacket* inPacket)
{
	// Process chat validate result from QQ side
}

ChatValidate GameService::GetChatValidate(int32_t nid, CharId_t CharId)
{
	ChatValidate ret;
	Answer::MutexGuard lock(m_ChatValidateLock);
	std::map<int32_t, ChatValidate>::iterator it = m_ChatValidateMap.find(nid);
	if (it != m_ChatValidateMap.end() && it->second.CharId == CharId)
	{
		ret = it->second;
		m_ChatValidateMap.erase(it);
	}
	return ret;
}

void GameService::CheckChatValidateChatSend(CharId_t CharId)
{
	// Check if player passes chat validation
}

// ============================================================
// Drop control
// ============================================================
int32_t GameService::GetDropTimes(int32_t nGroupId)
{
	Answer::MutexGuard lock(m_dropControlLock);
	std::map<int32_t, int32_t>::iterator iter = m_dropControl.find(nGroupId);
	if (iter != m_dropControl.end())
		return iter->second;
	return 0;
}

void GameService::AddDropTimes(int32_t nGroupId, int32_t nAddTimes)
{
	int32_t nTimes = nAddTimes;
	{
		Answer::MutexGuard lock(m_dropControlLock);
		std::map<int32_t, int32_t>::iterator iter = m_dropControl.find(nGroupId);
		if (iter != m_dropControl.end())
		{
			iter->second += nAddTimes;
			nTimes = iter->second;
		}
		else
		{
			m_dropControl[nGroupId] = nAddTimes;
		}
	}

	if (getLine() == GAME_SERVICE_LINE_CROSS)
	{
		// Cross-server: write directly to database
		int32_t nowTime = TIMER.GetNow();
		Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
		char szSQL[4096];
		memset(szSQL, 0, sizeof(szSQL));
		snprintf(szSQL, 4095,
			"INSERT INTO `cross_drop_control` (`id`,`group_id`,`times`,`time`) VALUES (%d,%d,%d,%d) "
			"ON DUPLICATE KEY UPDATE `times`=%d,`time`=%d",
			m_id, nGroupId, nTimes, nowTime, nTimes, nowTime);
		db.excute(szSQL);
	}
	else
	{
		DB_SERVICE.SaveDropTimes(nGroupId, nTimes);
	}
}

void GameService::UpdateDropTimes(int32_t nGroupId, int32_t nTimes)
{
	if (getLine() != GAME_SERVICE_LINE_CROSS)
	{
		Answer::MutexGuard lock(m_dropControlLock);
		m_dropControl[nGroupId] = nTimes;
	}
}

void GameService::ResetDropTimes()
{
	{
		Answer::MutexGuard lock(m_dropControlLock);
		m_dropControl.clear();
	}
	if (getLine() != GAME_SERVICE_LINE_CROSS)
		DB_SERVICE.ClearDropTimes();
}

void GameService::InitDropTimes()
{
	if (getLine() == GAME_SERVICE_LINE_CROSS)
	{
		// Load from cross DB
	}
	else
	{
		// Load from DBService
	}
}

void GameService::ClearDropTimes()
{
	Answer::MutexGuard lock(m_dropControlLock);
	m_dropControl.clear();
}

void GameService::OnDropTimesLoaded(Answer::NetPacket* inPacket)
{
	if (!inPacket) return;
	int32_t nGroupId = inPacket->readInt32();
	int32_t nTimes = inPacket->readInt32();
	Answer::MutexGuard lock(m_dropControlLock);
	m_dropControl[nGroupId] = nTimes;
}

bool GameService::CheckDropLimit(int32_t nGroupId, int32_t nItemId)
{
	int32_t nTimes = GetDropTimes(nGroupId);
	// Check against config limit
	return nTimes > 0;
}

void GameService::OnDropRecordLoaded(Answer::NetPacket* inPacket)
{
	// Handle drop record loaded from DB
}

void GameService::OnDropRecordSaved()
{
	// Handle drop record saved confirmation
}

// ============================================================
// Server battle
// ============================================================
void GameService::InitServerBattle()
{
	m_serverBattle = 0;
}

void GameService::SetServerBattle(int32_t Battle)
{
	m_serverBattle = Battle;
}

// ============================================================
// MoYuShiJie
// ============================================================
void GameService::InitMoYuShiJieRecord()
{
	// Initialize MoYuShiJie records
}

void GameService::SendMoYuShiJieRecord(Player* player)
{
	if (!player) return;
	// Send MoYuShiJie record to player
}

void GameService::AddMoYuShiJieRecord(const LogMoYuShiJieReward& logReward)
{
	// Add a MoYuShiJie reward record
}

// ============================================================
// Festival
// ============================================================
void GameService::ResetFestivalData(int32_t nVersion)
{
	// Reset festival activity data
}

// ============================================================
// Tencent
// ============================================================
void GameService::UpdateTencentInfo(CharId_t cid, const TencentInfo* info)
{
	if (!info) return;
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(cid);
	if (iter != m_players.end() && iter->second != NULL)
		iter->second->UpdateTencentInfo(info);
}

// ============================================================
// CityWar / Title
// ============================================================
void GameService::UpdateCityWarTitle(FamilyId_t OldFamilyId, FamilyId_t NewFamilyId)
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		Player* pPlayer = iter->second;
		if (!pPlayer) continue;

		if (pPlayer->getFamilyId() == OldFamilyId)
			pPlayer->GetCharTitle().RemoveTitle(1, 0);

		if (pPlayer->getFamilyId() == NewFamilyId)
		{
			int32_t FamilyPosition = pPlayer->getFamilyPosition();
			pPlayer->GetCharTitle().CheckAddTitle(1, FamilyPosition);
		}
	}
}

void GameService::UpdateCityActState(FamilyId_t FamilyId, int8_t ActState)
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		if (iter->second && iter->second->getFamilyId() == FamilyId)
			iter->second->SetActState(ActState);
	}
}

void GameService::SetFamilyMemberNeedSync(FamilyId_t nFamilyId)
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		Player* player = iter->second;
		if (player && player->getFamilyId() == nFamilyId)
			player->SetNeedSyncAround();
	}
}

void GameService::GetFamilyMemberInMap(FamilyId_t nFamilyId, int32_t nMapId, CharIdList& lst)
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		Player* player = iter->second;
		if (player && player->getFamilyId() == nFamilyId)
		{
			Map* pMap = player->getMap();
			if (pMap && pMap->GetId() == nMapId)
				lst.push_back(player->getCid());
		}
	}
}

// ============================================================
// onCheckTitle / onCheckTeShuTitle / onRemoveTitle
// ============================================================
void GameService::onCheckTitle(CharId_t nCharId, int8_t nType, int32_t nParam)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(nCharId);
	if (iter != m_players.end())
	{
		Player* player = iter->second;
		if (player != NULL)
			player->GetCharTitle().CheckAddTitle(nType, nParam);
	}
}

void GameService::onCheckTeShuTitle(CharId_t nCharId, int8_t nType, int32_t nParam)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(nCharId);
	if (iter != m_players.end())
	{
		Player* player = iter->second;
		if (player != NULL)
			player->GetCharTitle().CheckAddTitle(nType, nParam);
	}
}

void GameService::onRemoveTitle(CharId_t nCharId, int8_t nType)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(nCharId);
	if (iter != m_players.end())
	{
		Player* player = iter->second;
		if (player != NULL)
			player->GetCharTitle().RemoveTitle(nType, 0);
	}
}

// ============================================================
// Kick
// ============================================================
void GameService::KickUser(CharId_t cid, int32_t opWay)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap::iterator iter = m_players.find(cid);
	if (iter == m_players.end())
		return;

	Player* player = iter->second;
	if (NULL == player)
		return;

	NetPacket* packet = popNetpacket(player->getConnId(), PACK_PROC, IM_GAME_GATE_KICK_USER);
	if (NULL == packet)
		return;

	packet->writeInt32((int32_t)player->getUid());
	packet->writeInt32(player->getSid());
	packet->setSize(packet->getWOffset());
	sendPacket(player->getConnId(), packet);
}

void GameService::KickAll(int32_t opWay)
{
	Answer::MutexGuard lock(m_playerLock);
	CharIdPlayerMap players = m_players; // copy
	lock.~MutexGuard();

	for (CharIdPlayerMap::iterator iter = players.begin(); iter != players.end(); ++iter)
	{
		if (iter->second)
			KickUser(iter->second->getCid(), opWay);
	}
}

// ============================================================
// BanChat (CityMaster)
// ============================================================
void GameService::OnSocialCityMasterBanChat(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (!pConn || !inPacket) return;

	int64_t CharId = inPacket->readInt64();
	int32_t BanTime = inPacket->readInt32();
	int32_t BanChatTime = BanTime + DayTime::now();

	// Store ban chat time
}

int32_t GameService::GetCityMasterBanChatTime(CharId_t nCharId)
{
	return 0;
}

// ============================================================
// setWorldLevel
// ============================================================
void GameService::SetWorldLevel(int32_t nLevel)
{
	CFG_DATA.onAvgLevelUpdated(nLevel);
}

void GameService::onSetWorldLevel(
	GameConn* pConn,
	Answer::NetPacket* inPacket)
{
	if (pConn && inPacket)
	{
		int32_t Int32 = inPacket->readInt32();
		SetWorldLevel(Int32);
	}
}

// ============================================================
// RecalAllPlayerAttr
// ============================================================
void GameService::RecalAllPlayerAttr()
{
	Answer::MutexGuard lock(m_playerLock);
	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		Player* pPlayer = iter->second;
		if (pPlayer)
			pPlayer->RecalcAttr();
	}
}

// ============================================================
// AddPlayerVipClubDropTime
// ============================================================
void GameService::AddPlayerVipClubDropTime()
{
	Answer::MutexGuard lock(m_playerLock);

	for (CharIdPlayerMap::iterator iter = m_players.begin(); iter != m_players.end(); ++iter)
	{
		Player* pPlayer = iter->second;
		if (pPlayer != NULL)
		{
			pPlayer->GetVip().AddClubDropTime();
		}
	}

	// SQL to reset drop_time for VIP club members
	Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
	db.excute("update mem_chr_vip set drop_time = 1 where club > 0 and drop_time <= 0");
}
