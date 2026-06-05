#ifndef __TPOC_FESTIVAL_ACTIVITY_H__
#define __TPOC_FESTIVAL_ACTIVITY_H__

#include "DataStructs.h"
#include "Shared.h"
#include <vector>
#include <map>
#include <string>
#include <list>

class Player;

enum FESTIVAL_ACTIVITY_TYPE_2
{
	FAT2_COLLECTION		= 1,
	FAT2_DA_TI			= 2,
	FAT2_NPC			= 3,
	FAT2_COLLECTION2	= 4,
	FAT2_DUI_HUAN		= 5,
};

struct MapPos
{
	MapId_t		m_MapId;
	Position	m_Pos;
};

struct ChangeItemCfg
{
	std::list<ItemData>	lCostItem;
	MemChrBagVector		GetItems;
	int32_t				nCostGold;
	int32_t				Times;
};

class CFestivalActivity
{
public:
	CFestivalActivity();
	~CFestivalActivity();

	void Init();
	void OnDaySwitch();
	void OnNewMinute(int32_t nMinute);

	// Icon
	void GetIconState(Player* player, IconStateList& IconList);
	void SendIconState(Player* player);
	bool needShowIcon();
	void hideIcon(int32_t nIconId);

	// Time
	int32_t getLeftTime();
	bool IsInTime();
	bool IsInTime(FESTIVAL_ACTIVITY_TYPE_2 nType);
	bool IsOpen(FESTIVAL_ACTIVITY_TYPE_2 nType);

	// Collection
	int32_t GetPlantTimes();
	int32_t GetPlantTimes2();

	// DaTi
	int32_t GetActDay(FESTIVAL_ACTIVITY_TYPE_2 nType);
	int32_t GetDaTiReward(Player* player, int8_t RewardType);
	int32_t DaTi(Player* player, std::string& p_DaAn);

	// DuiHuan
	int32_t DuiHuan(Player* player, int32_t nIndex);

private:
	void initCfgData();
	void initOpenList(const std::string& str);
	bool isOpen(FESTIVAL_ACTIVITY_TYPE_2 nType) const;
	void getIconState(ShowIcon& stu, Player* player);
	int32_t loadVersion();
	void saveVersion();

	CFestivalActivity(const CFestivalActivity&);
	CFestivalActivity& operator=(const CFestivalActivity&);

	// Config
	int32_t m_nVersion;
	int32_t m_nStartDay;
	int32_t m_nEndDay;
	int32_t m_nIcon;
	int32_t m_nDay;
	int32_t m_nMinute;

	// Open days
	int8_t m_vOpen[6];
	int32_t m_vStartDay[6];
	int32_t m_vEndDay[6];

	// COLLECTION
	int32_t m_PlantId;
	int32_t m_PlantCount;
	int32_t m_Times;
	std::vector<MapPos> m_PlantMapPosVt;

	// DATI
	MemChrBag m_DayGift;
	MemChrBag m_ActGift;
	std::vector<std::vector<std::string>> m_StringVtVector;

	// NPC
	int32_t m_NpcId;
	int32_t m_NpcCount;
	std::vector<MapPos> m_NpcMapPosVt;

	// COLLECTION2
	int32_t m_PlantTime;

	// DUI_HUAN
	int32_t m_DuiHuanSize;
	std::vector<ChangeItemCfg> m_ChangeItemCfgVt;
};

#endif // __TPOC_FESTIVAL_ACTIVITY_H__
