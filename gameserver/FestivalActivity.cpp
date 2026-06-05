#include "stdafx.h"
#include "FestivalActivity.h"
#include "Timer.h"
#include "Player.h"
#include "CfgData.h"
#include "ItemHelper.h"
#include "MapManager.h"
#include "Map.h"
#include "Plant.h"
#include "Npc.h"
#include "Bag.h"
#include "Currency.h"
#include "GameService.h"

using namespace Answer;

CFestivalActivity::CFestivalActivity()
	: m_nVersion(0)
	, m_nStartDay(0)
	, m_nEndDay(0)
	, m_nIcon(0)
	, m_nDay(0)
	, m_nMinute(0)
	, m_PlantId(0)
	, m_PlantCount(0)
	, m_Times(0)
	, m_NpcId(0)
	, m_NpcCount(0)
	, m_PlantTime(0)
	, m_DuiHuanSize(0)
{
	memset(m_vOpen, 0, sizeof(m_vOpen));
	memset(m_vStartDay, 0, sizeof(m_vStartDay));
	memset(m_vEndDay, 0, sizeof(m_vEndDay));
	memset(&m_DayGift, 0, sizeof(m_DayGift));
	memset(&m_ActGift, 0, sizeof(m_ActGift));
}

CFestivalActivity::~CFestivalActivity()
{
}

void CFestivalActivity::Init()
{
	initCfgData();

	int32_t nVersion = loadVersion();
	if (nVersion > 0 && m_nVersion != nVersion || !nVersion)
	{
		saveVersion();
	}

	const tm& nowTime = TIMER.GetLocalNow();
	m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
}

void CFestivalActivity::OnDaySwitch()
{
	int32_t nowTime = TIMER.GetNow();
	m_nDay = (DayTime::dayzero(nowTime) - DayTime::dayzero(m_nStartDay)) / 86400;
	if (m_nDay == m_nEndDay)
	{
		hideIcon(m_nIcon);
	}
}

void CFestivalActivity::hideIcon(int32_t nIconId)
{
	if (GAME_SERVICE.getLine() == 1)
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CC3);
		if (packet)
		{
			packet->writeInt32(nIconId);
			packet->writeInt8(4);
			packet->writeInt32(0);
			packet->writeInt8(0);
			packet->writeInt32(0);
			packet->writeInt8(0);
			packet->setSize(packet->getWOffset());
			GAME_SERVICE.worldBroadcast(packet);
		}
	}
}

void CFestivalActivity::OnNewMinute(int32_t nMinute)
{
	m_nMinute = nMinute;
	int32_t nLeftTime = getLeftTime();

	if (nLeftTime > 0 && !m_nDay && !nMinute)
	{
		// COLLECTION - spawn plants
		if (m_PlantId > 0)
		{
			const CfgPlant* pCfgPlant = CFG_DATA.getPlant(m_PlantId);
			if (pCfgPlant)
			{
				std::random_shuffle(m_PlantMapPosVt.begin(), m_PlantMapPosVt.end());
				int32_t nFreshCount = std::min(m_PlantCount, (int32_t)m_PlantMapPosVt.size());

				for (int32_t i = 0; i < nFreshCount; ++i)
				{
					Map* pMap = MAP_MANAGER.GetMap(m_PlantMapPosVt[i].m_MapId);
					if (pMap)
					{
						Plant* plant = new Plant();
						if (plant)
						{
							CfgMapPlant stu;
							memset(&stu, 0, sizeof(stu));
							stu.mapid = m_PlantMapPosVt[i].m_MapId;
							stu.plantid = m_PlantId;
							stu.x = m_PlantMapPosVt[i].m_Pos.x;
							stu.y = m_PlantMapPosVt[i].m_Pos.y;
							plant->init(pMap, *pCfgPlant, stu);
							pMap->addPlant(plant);
						}
					}
				}
			}
		}

		// NPC - spawn NPCs
		if (m_NpcId > 0)
		{
			const CfgNpc* pCfgNpc = CFG_DATA.getNpc(m_NpcId);
			if (pCfgNpc)
			{
				std::random_shuffle(m_NpcMapPosVt.begin(), m_NpcMapPosVt.end());
				int32_t nFreshCount = std::min(m_NpcCount, (int32_t)m_NpcMapPosVt.size());

				for (int32_t i = 0; i < nFreshCount; ++i)
				{
					Map* pMap = MAP_MANAGER.GetMap(m_NpcMapPosVt[i].m_MapId);
					if (pMap)
					{
						Npc* npc = new Npc();
						if (npc)
						{
							int32_t nEndTime = DayTime::now() + nLeftTime;
							npc->init(*pCfgNpc, nEndTime);
							pMap->addNpc(npc, m_NpcMapPosVt[i].m_Pos.x, m_NpcMapPosVt[i].m_Pos.y);
						}
					}
				}
			}
		}
	}
}

void CFestivalActivity::initCfgData()
{
	Answer::Inifile ini;
	ini.parse("./ServerConfig/Tables/FestivalActivity.cfg");

	// CONFIG section
	m_nVersion = ini.getIntValue("CONFIG", "version");

	std::string strStartTime = ini.getStrValue("CONFIG", "start_time");
	m_nStartDay = DayTime::StringToIntTime(strStartTime);

	m_nEndDay = ini.getIntValue("CONFIG", "end_day");
	m_nIcon = ini.getIntValue("CONFIG", "icon");

	std::string strOpen = ini.getStrValue("CONFIG", "open");
	initOpenList(strOpen);

	m_nDay = (DayTime::dayzero(DayTime::now()) - DayTime::dayzero(m_nStartDay)) / 86400;

	// COLLECTION section
	if (isOpen(FAT2_COLLECTION))
	{
		m_vStartDay[1] = ini.getIntValue("COLLECTION", "start_day");
		m_vEndDay[1] = ini.getIntValue("COLLECTION", "end_day");
		m_PlantId = ini.getIntValue("COLLECTION", "plant");
		m_PlantCount = ini.getIntValue("COLLECTION", "count");

		std::string strMap = ini.getStrValue("COLLECTION", "map");
		if (!strMap.empty() && strMap != "-1")
		{
			StringVector SplitStr = StringUtility::split(strMap, "|");
			for (StringVector::iterator it = SplitStr.begin(); it != SplitStr.end(); ++it)
			{
				StringVector vstr = StringUtility::split(*it, ":");
				if (vstr.size() == 3)
				{
					MapPos stuPos;
					stuPos.m_MapId = atoi(vstr[0].c_str());
					stuPos.m_Pos.x = atoi(vstr[1].c_str());
					stuPos.m_Pos.y = atoi(vstr[2].c_str());
					m_PlantMapPosVt.push_back(stuPos);
				}
			}
		}

		m_Times = ini.getIntValue("COLLECTION", "time");

		int32_t nLeftTime = getLeftTime();
		if (nLeftTime > 0 && m_PlantId > 0)
		{
			const CfgPlant* pCfgPlant = CFG_DATA.getPlant(m_PlantId);
			if (pCfgPlant)
			{
				std::random_shuffle(m_PlantMapPosVt.begin(), m_PlantMapPosVt.end());
				int32_t nFreshCount = std::min(m_PlantCount, (int32_t)m_PlantMapPosVt.size());

				for (int32_t i = 0; i < nFreshCount; ++i)
				{
					Map* pMap = MAP_MANAGER.GetMap(m_PlantMapPosVt[i].m_MapId);
					if (pMap)
					{
						Plant* plant = new Plant();
						if (plant)
						{
							CfgMapPlant stu;
							memset(&stu, 0, sizeof(stu));
							stu.mapid = m_PlantMapPosVt[i].m_MapId;
							stu.plantid = m_PlantId;
							stu.x = m_PlantMapPosVt[i].m_Pos.x;
							stu.y = m_PlantMapPosVt[i].m_Pos.y;
							plant->init(pMap, *pCfgPlant, stu);
							pMap->addPlant(plant);
						}
					}
				}
			}
		}
	}

	// DATI section
	if (isOpen(FAT2_DA_TI))
	{
		m_vStartDay[2] = ini.getIntValue("DATI", "start_day");
		m_vEndDay[2] = ini.getIntValue("DATI", "end_day");

		std::string strDayGift = ini.getStrValue("DATI", "gift_day");
		MemChrBagVector dayItems = CItemHelper::parseItemString(0, strDayGift);
		if (!dayItems.empty())
		{
			m_DayGift = dayItems[0];
		}

		std::string strActGift = ini.getStrValue("DATI", "gift_act");
		MemChrBagVector actItems = CItemHelper::parseItemString(0, strActGift);
		if (!actItems.empty())
		{
			m_ActGift = actItems[0];
		}

		int32_t nDay = m_vEndDay[2] - m_vStartDay[2];
		if (nDay > 0)
		{
			m_StringVtVector.resize(nDay);
			for (int32_t i = 0; i < nDay; ++i)
			{
				char szCol[64] = {0};
				snprintf(szCol, sizeof(szCol) - 1, "da_an%d", i + 1);
				std::string DaAnString = ini.getStrValue("DATI", szCol);

				if (!DaAnString.empty() && DaAnString != "-1")
				{
					StringVector SplitStr = StringUtility::split(DaAnString, "|");
					int32_t nSize = SplitStr.size();
					if (nSize > 0)
					{
						m_StringVtVector[i].resize(nSize);
						for (int32_t j = 0; j < nSize; ++j)
						{
							m_StringVtVector[i][j] = SplitStr[j];
						}
					}
				}
			}
		}
	}

	// NPC section
	if (isOpen(FAT2_NPC))
	{
		m_vStartDay[3] = ini.getIntValue("NPC", "start_day");
		m_vEndDay[3] = ini.getIntValue("NPC", "end_day");
		m_NpcId = ini.getIntValue("NPC", "npcid");
		m_NpcCount = ini.getIntValue("NPC", "count");

		std::string strMap = ini.getStrValue("NPC", "map");
		if (!strMap.empty() && strMap != "-1")
		{
			StringVector SplitStr = StringUtility::split(strMap, "|");
			for (StringVector::iterator it = SplitStr.begin(); it != SplitStr.end(); ++it)
			{
				StringVector vstr = StringUtility::split(*it, ":");
				if (vstr.size() == 3)
				{
					MapPos stuPos;
					stuPos.m_MapId = atoi(vstr[0].c_str());
					stuPos.m_Pos.x = atoi(vstr[1].c_str());
					stuPos.m_Pos.y = atoi(vstr[2].c_str());
					m_NpcMapPosVt.push_back(stuPos);
				}
			}
		}

		int32_t nLeftTime = getLeftTime();
		if (nLeftTime > 0 && m_NpcId > 0)
		{
			const CfgNpc* pCfgNpc = CFG_DATA.getNpc(m_NpcId);
			if (pCfgNpc)
			{
				std::random_shuffle(m_NpcMapPosVt.begin(), m_NpcMapPosVt.end());
				int32_t nFreshCount = std::min(m_NpcCount, (int32_t)m_NpcMapPosVt.size());

				for (int32_t i = 0; i < nFreshCount; ++i)
				{
					Map* pMap = MAP_MANAGER.GetMap(m_NpcMapPosVt[i].m_MapId);
					if (pMap)
					{
						Npc* npc = new Npc();
						if (npc)
						{
							int32_t nEndTime = DayTime::now() + nLeftTime;
							npc->init(*pCfgNpc, nEndTime);
							pMap->addNpc(npc, m_NpcMapPosVt[i].m_Pos.x, m_NpcMapPosVt[i].m_Pos.y);
						}
					}
				}
			}
		}
	}

	// COLLECTION2 section
	if (isOpen(FAT2_COLLECTION2))
	{
		m_vStartDay[4] = ini.getIntValue("COLLECTION2", "start_day");
		m_vEndDay[4] = ini.getIntValue("COLLECTION2", "end_day");
		m_PlantTime = ini.getIntValue("COLLECTION2", "plant_time");
	}

	// DUI_HUAN section
	if (isOpen(FAT2_DUI_HUAN))
	{
		m_vStartDay[5] = ini.getIntValue("DUI_HUAN", "start_day");
		m_vEndDay[5] = ini.getIntValue("DUI_HUAN", "end_day");
		m_DuiHuanSize = ini.getIntValue("DUI_HUAN", "size");

		if (m_DuiHuanSize > 0)
		{
			m_ChangeItemCfgVt.resize(m_DuiHuanSize);

			for (int32_t i = 0; i < m_DuiHuanSize; ++i)
			{
				char szCol[64] = {0};

				snprintf(szCol, sizeof(szCol) - 1, "need_item%d", i + 1);
				std::string strNeedItem = ini.getStrValue("DUI_HUAN", szCol);
				m_ChangeItemCfgVt[i].lCostItem = CItemHelper::parseItemDataListString(strNeedItem);

				snprintf(szCol, sizeof(szCol) - 1, "need_gold%d", i + 1);
				m_ChangeItemCfgVt[i].nCostGold = ini.getIntValue("DUI_HUAN", szCol);

				snprintf(szCol, sizeof(szCol) - 1, "get_item%d", i + 1);
				std::string strGetItem = ini.getStrValue("DUI_HUAN", szCol);
				m_ChangeItemCfgVt[i].GetItems = CItemHelper::parseItemVectorString(strGetItem);

				snprintf(szCol, sizeof(szCol) - 1, "time%d", i + 1);
				m_ChangeItemCfgVt[i].Times = ini.getIntValue("DUI_HUAN", szCol);
			}
		}
	}
}

int32_t CFestivalActivity::loadVersion()
{
	char szSQL[4096] = {0};
	DBPOOL;
	MySqlDBGuard db(DBPOOL);

	snprintf(szSQL, sizeof(szSQL) - 1,
		"SELECT * FROM `sys_server_config` WHERE `name`='FESTIVAL_2_VERSION'");

	MySqlQuery result = db.query(szSQL);
	if (!result.eof())
	{
		std::string strValue = result.getStringValue("value", "");
		return atoi(strValue.c_str());
	}
	return 0;
}

void CFestivalActivity::saveVersion()
{
	char szSQL[4096] = {0};
	DBPOOL;
	MySqlDBGuard db(DBPOOL);

	int32_t nNowTime = DayTime::now();
	snprintf(szSQL, sizeof(szSQL) - 1,
		"INSERT INTO `sys_server_config` ( `name`, `value`, `refresh_time` ) "
		"VALUES ( 'FESTIVAL_2_VERSION', %d, %d ) ON DUPLICATE KEY UPDATE `value`=%d, `refresh_time`=%d",
		m_nVersion, nNowTime, m_nVersion, nNowTime);

	db.excute(szSQL);
}

void CFestivalActivity::GetIconState(Player* player, IconStateList& IconList)
{
	if (!player)
	{
		return;
	}

	if (needShowIcon())
	{
		ShowIcon stu;
		getIconState(stu, player);
		IconList.push_back(stu);
	}
}

void CFestivalActivity::SendIconState(Player* player)
{
	if (!player)
	{
		return;
	}

	if (needShowIcon())
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, 0x2CC3);
		if (packet)
		{
			packet->writeInt32(m_nIcon);
			packet->writeInt8(IsInTime() ? 1 : 0);
			packet->writeInt32(getLeftTime());
			packet->writeInt8(0);
			packet->writeInt32(0);
			packet->writeInt8(0);
			packet->setSize(packet->getWOffset());
			GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
		}
	}
}

bool CFestivalActivity::needShowIcon()
{
	if (GAME_SERVICE.getLine() == 9)
	{
		return false;
	}
	return m_nDay >= 0 && m_nDay < m_nEndDay;
}

int32_t CFestivalActivity::getLeftTime()
{
	if (m_nDay < 0)
	{
		return 0;
	}
	int32_t nNowTime = TIMER.GetNow();
	return 86400 * (m_nEndDay - m_nDay) - (nNowTime - DayTime::dayzero(nNowTime));
}

bool CFestivalActivity::IsInTime(FESTIVAL_ACTIVITY_TYPE_2 nType)
{
	return IsInTime()
		&& m_nDay >= m_vStartDay[nType]
		&& m_nDay < m_vEndDay[nType];
}

bool CFestivalActivity::IsInTime()
{
	return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CFestivalActivity::IsOpen(FESTIVAL_ACTIVITY_TYPE_2 nType)
{
	return IsInTime() && isOpen(nType);
}

bool CFestivalActivity::isOpen(FESTIVAL_ACTIVITY_TYPE_2 nType) const
{
	return m_vOpen[nType] != 0;
}

void CFestivalActivity::initOpenList(const std::string& str)
{
	memset(m_vOpen, 0, 6);

	StringVector vOpen = StringUtility::split(str, "|");
	for (StringVector::iterator it = vOpen.begin(); it != vOpen.end(); ++it)
	{
		int8_t nType = atoi(it->c_str());
		if (nType > 0 && nType <= 5)
		{
			m_vOpen[nType] = 1;
		}
	}
}

int32_t CFestivalActivity::GetPlantTimes()
{
	if (!IsInTime(FAT2_COLLECTION))
	{
		return 0;
	}
	return m_Times;
}

int32_t CFestivalActivity::GetPlantTimes2()
{
	if (!IsInTime(FAT2_COLLECTION2))
	{
		return 0;
	}
	return m_PlantTime;
}

int32_t CFestivalActivity::GetActDay(FESTIVAL_ACTIVITY_TYPE_2 nType)
{
	int32_t index = m_nDay - m_vStartDay[nType];
	if (index >= 0 && index <= m_vEndDay[nType] - m_vStartDay[nType] - 1)
	{
		return m_nDay - m_vStartDay[nType];
	}
	return -1;
}

int32_t CFestivalActivity::GetDaTiReward(Player* player, int8_t RewardType)
{
	if (!player)
	{
		return ERR_INVALID_DATA;
	}
	if (!IsInTime(FAT2_DA_TI))
	{
		return 0;
	}

	// Check answer count
	int32_t DaTiTimes = player->getRecord(2120);
	int32_t index = GetActDay(FAT2_DA_TI);
	int32_t nSize = m_StringVtVector.size();

	if (index < 0 || index >= nSize)
	{
		return ERR_INVALID_DATA;
	}

	int32_t DaAnCount = m_StringVtVector[index].size();
	if (DaTiTimes < DaAnCount)
	{
		return ERR_INVALID_DATA;
	}

	// Check reward type
	int32_t record = 0;
	MemChrBag* pItem = NULL;
	if (RewardType == 1)
	{
		record = 2121;
		pItem = &m_DayGift;
	}
	else
	{
		record = 37401;
		pItem = &m_ActGift;
	}

	if (player->getRecord(record) > 0)
	{
		return ERR_INVALID_DATA;
	}

	// Give item
	if (pItem && !player->GetBag().AddItem(*pItem, (ITEM_ADD_REASON)IACR_DA_TI_ACT))
	{
		return ERR_INVALID_DATA;
	}

	player->updateRecord(record, 1);
	return 0;
}

int32_t CFestivalActivity::DaTi(Player* player, std::string& p_DaAn)
{
	if (!player || p_DaAn.empty())
	{
		return ERR_INVALID_DATA;
	}
	if (!IsInTime(FAT2_DA_TI))
	{
		return 0;
	}

	int32_t DaTiTimes = player->getRecord(2120);
	int32_t index = GetActDay(FAT2_DA_TI);
	int32_t nSize = m_StringVtVector.size();

	if (index < 0 || index >= nSize)
	{
		return ERR_INVALID_DATA;
	}

	int32_t DaAnCount = m_StringVtVector[index].size();
	if (DaTiTimes < 0 || DaTiTimes >= DaAnCount)
	{
		return ERR_INVALID_DATA;
	}

	// Check answer
	if (m_StringVtVector[index][DaTiTimes] != p_DaAn)
	{
		return ERR_INVALID_DATA;
	}

	player->updateRecord(2120, DaTiTimes + 1);
	return 0;
}

int32_t CFestivalActivity::DuiHuan(Player* player, int32_t nIndex)
{
	if (!player)
	{
		return ERR_INVALID_DATA;
	}
	if (nIndex < 0 || nIndex >= m_DuiHuanSize)
	{
		return ERR_INVALID_DATA;
	}
	if (!IsInTime(FAT2_DUI_HUAN))
	{
		return ERR_INVALID_DATA;
	}

	// Check times
	int32_t Record = player->getRecord(nIndex + 10101);
	if (Record >= m_ChangeItemCfgVt[nIndex].Times)
	{
		return ERR_INVALID_DATA;
	}

	// Check gold
	if (m_ChangeItemCfgVt[nIndex].nCostGold > 0)
	{
		int64_t Currency = player->GetCurrency(CURRENCY_GOLD);
		if (Currency < m_ChangeItemCfgVt[nIndex].nCostGold)
		{
			return ERR_INVALID_DATA;
		}
	}

	// Exchange items
	if (!player->GetBag().AddAndRemoveItem(
		m_ChangeItemCfgVt[nIndex].GetItems,
		(ITEM_ADD_REASON)IDCR_FESTIVAL_ACT_2,
		m_ChangeItemCfgVt[nIndex].lCostItem,
		(ITEM_DEL_REASON)IDCR_FESTIVAL_ACT_2))
	{
		return ERR_INVALID_DATA;
	}

	// Deduct gold
	if (m_ChangeItemCfgVt[nIndex].nCostGold > 0)
	{
		player->DecCurrency(CURRENCY_GOLD, m_ChangeItemCfgVt[nIndex].nCostGold, GCR_FESTIVAL_ACT_2, 0);
	}

	// Update record
	player->updateRecord(nIndex + 10101, Record + 1);
	return 0;
}

void CFestivalActivity::getIconState(ShowIcon& stu, Player* player)
{
	stu.nId = m_nIcon;
	stu.nState = IsInTime() ? 1 : 0;
	stu.nLeftTime = getLeftTime();
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
}
